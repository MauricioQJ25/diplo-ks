#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/init.h>

#include "mpu6050_reg.h"
#include "log.h"

static struct i2c_board_info mpu6xxx_id =
{
    I2C_BOARD_INFO(SENSOR_NAME, 0x68),
};

static int __init mpu6xxx_init(void)
{
    struct i2c_adapter *adap;
    struct i2c_client *client;

    adap = i2c_get_adapter(1);
    if (!adap)
        goto erradap;

    mpu6xxx_id.irq = gpio_to_irq(48);
    client = i2c_new_device(adap, &mpu6xxx_id);
    if (!client)
        goto errclient;

    D("Client OK\n");
    return 0;
errclient:
    i2c_unregister_device(client);
erradap:
    i2c_put_adapter(adap);
    return -ENODEV;

}

static void __exit mpu6xxx_exit(void)
{
    /*Agregar función para quitar el registro del cliente*/
}

module_init(mpu6xxx_init);
module_exit(mpu6xxx_exit);
MODULE_AUTHOR("Mauricio quijada");
MODULE_LICENSE("GPL");
