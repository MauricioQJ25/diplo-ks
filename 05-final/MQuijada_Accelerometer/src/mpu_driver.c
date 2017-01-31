#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/i2c.h>
#include <linux/types.h>

#include "log.h"
#include "mpu6050_reg.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauricio Quijada");

struct axis_data {
    u16 value;
    int standby;
};

struct sub_sensor {
    int st;         // self-test
    int reset;      // reset
    int sel;        // full scale range
    struct axis_data x;
    struct axis_data y;
    struct axis_data z;
};

struct temp_sensor {
    int enable;
    int reset;
    u16 value;
};

struct pwr_mgmt {
    int reset;
    int sleep;
    int cycle;
    int cycle_HZ;
    int clksel;
    int all_standby;
};

struct mpu6050_data {
    struct mutex lock;
    struct i2c_client *client;
    struct delayed_work work;
    struct workqueue_struct *wq;
    int delay_ms;

    struct sub_sensor gyro;
    struct sub_sensor accel;
    struct temp_sensor temp_s;
    struct pwr_mgmt power;
    int dlph;
    int dhph;
};

enum {
    RANGE,
    LSB
};
/*
static float accel_sel[][2] = {
    {2, 16384},
    {4, 8192},
    {8, 4096},
    {16, 2048}
};

static float gyro_sel[][2] = {
    {250, 131},
    {500, 65.5},
    {1000, 32.8},
    {2000, 16.4}
};
*/
static void mpu6050_enable(struct mpu6050_data *mpu6050)
{
    struct i2c_client *client = mpu6050->client;
    i2c_smbus_write_byte_data(client, MPU6050_REG_PWR_MGMT_1, 0);
}

static void mpu6050_disable(struct mpu6050_data *mpu6050)
{
    struct i2c_client *client = mpu6050->client;
    i2c_smbus_write_byte_data(client, MPU6050_REG_PWR_MGMT_1,
            1 << PWR_1_SLEEP_OFFSET);
}

static void mpu6050_reset(struct mpu6050_data *mpu6050)
{
    struct i2c_client *client = mpu6050->client;
    i2c_smbus_write_byte_data(client, MPU6050_REG_PWR_MGMT_1,
            1 << PWR_1_DEVICE_RESET_OFFSET);
}

/*
 * Get gyro/accel/temprature data
 * @type :  0 - gyro
 *          1 - accel
 *          2 - temprature
 */
static int mpu6050_read_data(struct mpu6050_data *mpu6050, int type)
{
    s16 values[3];
    int i, addr, ret;
    struct i2c_client *client = mpu6050->client;

    switch(type) {
    case 0:
        addr = MPU6050_REG_GYRO_XOUT_H;
        break;
    case 1:
        addr = MPU6050_REG_ACCEL_XOUT_H;
        break;
    case 2:
        addr = MPU6050_REG_TEMP_OUT_H;
        break;
    default:
        addr = MPU6050_REG_GYRO_XOUT_H;
        break;
    }

    if (type == 0 || type == 1) {
        ret = i2c_smbus_read_i2c_block_data(client, addr,
               6, (u8 *)values);
        if (ret < 0) {
            E("error read gyro\n");
            return ret;
        }

        for (i = 0; i < 3; i++) {
            values[i] = be16_to_cpu(values[i]);
        }
    } else if (type == 2) {
        ret = i2c_smbus_read_i2c_block_data(client, addr,
               2, (u8 *)values);
        if (ret < 0) {
            E("error read gyro\n");
            return ret;
        }

        for (i = 0; i < 1; i++) {
            values[i] = be16_to_cpu(values[i]);
        }
    }

    switch(type) {
    case 0:
        mpu6050->gyro.x.value = values[0];
        mpu6050->gyro.y.value = values[1];
        mpu6050->gyro.z.value = values[2];
        break;
    case 1:
        mpu6050->accel.x.value = values[0];
        mpu6050->accel.y.value = values[1];
        mpu6050->accel.z.value = values[2];
        break;
    case 2:
        mpu6050->temp_s.value = values[0];
        break;
    default:
        break;
    }

    return 0;
}

static int mpu6050_read_gyro(struct mpu6050_data *mpu6050)
{
    return mpu6050_read_data(mpu6050, 0);
}

static int mpu6050_read_accel(struct mpu6050_data *mpu6050)
{
    return mpu6050_read_data(mpu6050, 1);
}

static int mpu6050_read_temprature(struct mpu6050_data *mpu6050)
{
    return mpu6050_read_data(mpu6050, 2);
}

static void mpu6050_dump_all(struct mpu6050_data *mpu6050)
{
    D("Gyro(X:%d Y:%d Z:%d)\tAccel(X:%d Y:%d Z:%d)\tTemp:%d\n",
            mpu6050->gyro.x.value, mpu6050->gyro.y.value,
            mpu6050->gyro.z.value, mpu6050->accel.x.value, mpu6050->accel.y.value,
            mpu6050->accel.z.value, mpu6050->temp_s.value);
}

static void mpu6050_work(struct work_struct *work)
{
    //int ret;
    struct mpu6050_data *mpu6050 = container_of(
            (struct delayed_work *)work, struct mpu6050_data, work);

    mpu6050_read_gyro(mpu6050);
    mpu6050_read_accel(mpu6050);
    mpu6050_read_temprature(mpu6050);

    mpu6050_dump_all(mpu6050);

    schedule_delayed_work(&mpu6050->work,
            msecs_to_jiffies(mpu6050->delay_ms));
}

static int mpu6050_probe(struct i2c_client *client,
        const struct i2c_device_id *id)
{
    struct mpu6050_data *mpu6050;
    u16 version;

    D("Probe match happend, ID %s\n", id->name);

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        E("I2C check error\n");
        return -EINVAL;
    }

    mpu6050 = kzalloc(sizeof(*mpu6050), GFP_KERNEL);
    if (!mpu6050) {
        E("Mem error\n");
        return -ENOMEM;
    } else
        D("Alloc OK\n");

    mpu6050->client = client;
    i2c_set_clientdata(client, mpu6050);
    mutex_init(&mpu6050->lock);
    mpu6050->delay_ms = 1000;
    D("Set OK\n");

    INIT_DELAYED_WORK(&mpu6050->work, mpu6050_work);
    D("Work queue OK\n");

    version = i2c_smbus_read_byte_data(client, MPU6050_REG_WHO_AM_I);
    if (version != 0x68) {
        E("Version check error 0x%X, skip\n", version);
        goto free_all;
    } else
        D("Version Check OK\n");

    mpu6050_reset(mpu6050);
    mpu6050_enable(mpu6050);
    schedule_delayed_work(&mpu6050->work,
            msecs_to_jiffies(mpu6050->delay_ms));

    return 0;
free_all:
    kfree(mpu6050);
    E("A oh!!!ooops...\n");
    return -EINVAL;
}

static int mpu6050_remove(struct i2c_client *client)
{
    struct mpu6050_data *mpu6050 = i2c_get_clientdata(client);

    mpu6050_disable(mpu6050);
    cancel_delayed_work(&mpu6050->work);
    kfree(mpu6050);
    printk(KERN_INFO "adios!\n");

    return 0;
}

static struct i2c_device_id mpu6050_ids[] = {
    {SENSOR_NAME, 0},
    { },
};

static struct i2c_driver mpu6050_driver = {
    .driver = {
        .name = SENSOR_NAME,
        .owner = THIS_MODULE,
    },
    .class = I2C_CLASS_HWMON,
    .id_table = mpu6050_ids,
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
};

module_i2c_driver(mpu6050_driver);
