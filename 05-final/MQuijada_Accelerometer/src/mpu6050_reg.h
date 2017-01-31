#define SENSOR_NAME "mpu6050-i2c"     /*se queda 2*/
//#define SENSOR_I2C_SLAVE_ADDRESS 0x68
//#define SENSOR_IRQ_NR 48
//#define SENSOR_I2C_ADAPTER_NR 1

//Reg map
#define MPU6050_REG_WHO_AM_I    0x75 /*se queda 1*/
//    #define MPU6050_WHO_AM_I    0x68
//    #define WHO_AM_I_MASK       0x3f
//    #define WHO_AM_I_OFFSET     1
//    #define WHO_AM_I            0x34

//#define MPU6050_REG_AUX_VDDIO   0x01
//    #define AUX_VDDIO_OFFSET    6
//    enum {
//        AUX_VDDIO_VLOGIC,
//        AUX_VDDIO_VDD
//    };
/*
 * Divide the output rate of gyroscope to generate the
 * Sample Rate for MPU6050. Such as FIFO output, register
 * output, DMP sampling, Motion detection, and so on are
 * all based on this Sample Rate.
 *
 * Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 *
 * the Gyroscope Output Rate is 8kHz while DLPF is disabled
 * (DLPF_CFG = 0 or 7) and 1kHz while DLPF is enabled.
 */
//#define MPU6050_REG_SMPLRT_DIV   0x19
//    #define SMPLRT_MASK          0xFF

/*
 * FSYNC(external Frame Synchronization) and DLPF(Digital
 * Low Pass Filter) both for Gyro and Acce
 */
//#define MPU6050_REG_CONFIG      0x1A
 //   #define EXT_SYNC_SET_MASK   0x07
 //   #define EXT_SYNC_SET_OFFSET 3
 //   enum {
 //       FSYNC_INPUT_DISABLED,
 //       FSYNC_TEMP_OUT_L,
 //       FSYNC_GYRO_XOUT_L,
 //       FSYNC_GYRO_YOUT_L,
 //       FSYNC_GYRO_ZOUT_L,
 //       FSYNC_ACCEL_XOUT_L,
 //       FSYNC_ACCEL_YOUT_L,
 //       FSYNC_ACCEL_ZOUT_L
 //   };
 //   #define DLPF_CFG_MASK       0x07
    /*
     *  CFG Bandwidth(Hz) Delay(ms) Fs(kHz)
     *  Accel is always 1kHz, and Gyro can be 1khz or 8kHz
     */
 //   enum {
 //       DLPF_B2XX_D0_8KHZ,
 //       DLPF_B1XX_D2_1KHZ,
 //       DLPF_B9X_D3_1KHZ,
 //       DLPF_B4X_D5_1KHZ,
 //       DLPF_B2X_D8_1KHZ,
 //       DLPF_B10_D13_1KHZ,
 //       DLPF_B5_D19_1KHZ,
 //       DLPF_NULL_8KHZ
 //   };

//#define MPU6050_REG_GYRO_CONFIG     0x1B
//    #define GYRO_CONFIG_XG_ST_OFFSET    7
//    #define GYRO_CONFIG_YG_ST_OFFSET    6
//    #define GYRO_CONFIG_ZG_ST_OFFSET    5
//    #define GYRO_CONFIG_FS_SEL_MASK     0x03
//    #define GYRO_CONFIG_FS_SEL_OFFSET   3
 //   enum {
 //       FS_SEL_250_S,
 //       FS_SEL_500_S,
 //       FS_SEL_1000_S,
 //       FS_SEL_2000_S
 //   };

//#define MPU6050_REG_ACCEL_CONFIG    0x1C
//    #define ACCEL_CONFIG_XA_ST_OFFSET   7
//    #define ACCEL_CONFIG_YA_ST_OFFSET   6
//    #define ACCEL_CONFIG_ZA_ST_OFFSET   5
//    #define ACCEL_CONFIG_AFS_SEL_MASK   0x03
//    #define ACCEL_CONFIG_AFS_SEL_OFFSET 3
//    enum {
//        AFS_SEL_2G,
//        AFS_SEL_4G,
//        AFS_SEL_8G,
//        AFS_SEL_16G
//    };
    /* Digital High Pass Filter(DHPF) */
//    #define ACCEL_CONFIG_ACCEL_HPF_MASK 0x07
//    enum {
//        ACCEL_HPF_FM_RST_F_NONE,
//        ACCEL_HPF_FM_ON_F_5HZ,
//        ACCEL_HPF_FM_ON_F_2_5HZ,
//        ACCEL_HPF_FM_ON_F_1_25HZ,
//        ACCEL_HPF_FM_ON_F_0_63HZ,
//        ACCEL_HPF_FM_HOLD_F_NONE = 7
//    };

//#define MPU6050_REG_FF_THR      0x1D
//    #define FF_THR_MASK         0xFF
//#define MPU6050_REG_FF_DUR      0x1E
//    #define FF_DUR_MASK         0xFF
//#define MPU6050_REG_MOT_THR     0x1F
//    #define MOT_THR_MASK        0xFF
//#define MPU6050_REG_MOT_DUR     0x20
//    #define MOT_DUR_MASK        0xFF
//#define MPU6050_REG_ZRMOT_THR   0x21
//    #define ZRMOT_THR_MASK      0xFF
//#define MPU6050_REG_ZRMOT_DUR   0x22
 //   #define ZEMOT_DUR_MASK      0xFF

//#define MPU6050_REG_FIFO_EN     0x23
 //   enum {
 //       FIFO_EN_SLV0_OFFSET,
 //       FIFO_EN_SLV1_OFFSET,
 //       FIFO_EN_SLV2_OFFSET,
 //       FIFO_EN_ACCEL_OFFSET,
 //       FIFO_EN_ZG_OFFSET,
 //       FIFO_EN_YG_OFFSET,
 //       FIFO_EN_XG_OFFSET,
  //      FIFO_EN_TEMP_OFFSET
  //  };
/*
#define MPU6050_REG_I2C_MST_CTRL    0x24
    #define I2C_MULT_MST_EN_0FFSET  7
    #define I2C_WAIT_FOR_ES_OFFSET  6
    #define I2C_SLV3_FIFO_EN_OFFSET 5
    #define I2C_MST_P_NSR_OFFSET    4
    #define I2C_MST_CLOCK_MASK      0x0F
        #define I2C_MST_CLOCK_S_400KHZ_DIV20    13

#define MPU6050_REG_I2C_SLV0_ADDR   0x25
#define MPU6050_REG_I2C_SLV1_ADDR   0x28
#define MPU6050_REG_I2C_SLV2_ADDR   0x2B
#define MPU6050_REG_I2C_SLV3_ADDR   0x2E
#define MPU6050_REG_I2C_SLV4_ADDR   0x31
    #define I2C_SLVX_RW_OFFSET      7
    #define I2C_SLVX_ADDR_MASK      0x7F

#define MPU6050_REG_I2C_SLV0_REG    0x26
#define MPU6050_REG_I2C_SLV1_REG    0x29
#define MPU6050_REG_I2C_SLV2_REG    0x2C
#define MPU6050_REG_I2C_SLV3_REG    0x2F
#define MPU6050_REG_I2C_SLV4_REG    0x32
    #define I2C_SLVX_REG_MASK       0xFF

#define MPU6050_REG_I2C_SLV0_CTRL   0x27
#define MPU6050_REG_I2C_SLV1_CTRL   0x2A
#define MPU6050_REG_I2C_SLV2_CTRL   0x2D
#define MPU6050_REG_I2C_SLV3_CTRL   0x30
    #define I2C_SLVX_EN_OFFSET      7
    #define I2C_SLVX_BYTE_SW_OFFSET 6
    #define I2C_SLVX_REG_DIS_OFFSET 5
    #define I2C_SLVX_GRP_OFFSET     4
    #define I2C_SLVX_LEN_MASK       0x0F

#define MPU6050_REG_I2C_SLV4_DO     0x33
#define MPU6050_REG_I2C_SLV4_DI     0x35
    #define I2C_SLV4_DIO_MASK       0xFF
#define MPU6050_REG_I2C_SLV4_CTRL   0x34
    #define I2C_SLV4_EN_OFFSET      7
    #define I2C_SLV4_INT_EN_OFFSET  6
    #define I2C_SLV4_REG_DIS_OFFSET 5
    #define I2C_MST_DLY_MASK        0xFF

#define MPU6050_REG_I2C_MST_STATUS  0x36
    enum {
        I2C_STATUS_SLV0_NACK,
        I2C_STATUS_SLV1_NACK,
        I2C_STATUS_SLV2_NACK,
        I2C_STATUS_SLV3_NACK,
        I2C_STATUS_SLV4_NACK,
        I2C_STATUS_LOST_ARB,
        I2C_STATUS_SLV4_DONE,
        I2C_STATUS_PASS_THROUGH,
    };

#define MPU6050_REG_INT_PIN_CFG     0x37
    enum {
        INT_CFG_CLKOUT_EN,
        INT_CFG_I2C_BYPASS_EN,
        INT_CFG_FSYNC_INT_EN,
        INT_CFG_FSYNC_INT_LEVEL,
        INT_CFG_RD_CLEAR,
        INT_CFG_LATCH_INT_EN,
        INT_CFG_INT_OPEN,
        INT_CFG_INT_LEVEL,
    };

#define MPU6050_REG_INT_ENABLE      0x38
    enum {
        INT_ENABLE_DATA_RDY,
        INT_ENABLE_I2C_MST_INT = 3,
        INT_ENABLE_FIFO_OFLOW,
        INT_ENABLE_ZMOT,
        INT_ENABLE_MOT,
        INT_ENABLE_FF,
    };

#define MPU6050_REG_INT_STATUS      0x3A
    enum {
        INT_STATUS_DATA_RDY,
        INT_STATUS_I2C_MST = 3,
        INT_STATUS_FIFO_OFLOW,
        INT_STATUS_ZMOT,
        INT_STATUS_MOT,
        INT_STATUS_FF
    };
*/

/*registros donde se almacena la aceleración en los ejes x,y, z*/
/*notese que son 6 registros de 8 bits*/
/*cada lectura esta formada por 2 bytes uno H y otro L*/    
#define MPU6050_REG_ACCEL_XOUT_H    0x3B
#define MPU6050_REG_ACCEL_XOUT_L    0x3C
#define MPU6050_REG_ACCEL_YOUT_H    0x3D
#define MPU6050_REG_ACCEL_YOUT_L    0x3E
#define MPU6050_REG_ACCEL_ZOUT_H    0x3F
#define MPU6050_REG_ACCEL_ZOUT_L    0x40

/*Registros donde se almacena la temperatura*/
/*Notese que son 2 registros de 8 bits*/
/*Se pueden almacenar en un arreglo de 16 bits*/
/*Al igual que la aceleracion esta formado por un parte H y otra L*/
#define MPU6050_REG_TEMP_OUT_H      0x41
#define MPU6050_REG_TEMP_OUT_L      0x42

/*Registros del giroscopio en cada uno de los 3 ejes*/
/*Notese que son 6 registros por lo que se puede  usar la misma funcion*/
/*Para acomodar los datos que la de aceleración*/
#define MPU6050_REG_GYRO_XOUT_H     0x43
#define MPU6050_REG_GYRO_XOUT_L     0x44
#define MPU6050_REG_GYRO_YOUT_H     0x45
#define MPU6050_REG_GYRO_YOUT_L     0x46
#define MPU6050_REG_GYRO_ZOUT_H     0x47
#define MPU6050_REG_GYRO_ZOUT_L     0x48

/*
#define MPU6050_REG_EXT_SENS_DATA_00    0x49
#define MPU6050_REG_EXT_SENS_DATA_23    0x60

#define MPU6050_REG_MOT_DETECT_STATUS   0x61
    enum {
        MOT_STATUS_ZRMOT,
        MOT_STATUS_ZPOS = 2,
        MOT_STATUS_ZNEG,
        MOT_STATUS_YPOS,
        MOT_STATUS_YNEG,
        MOT_STATUS_XPOS,
        MOT_STATUS_XNEG
    };

#define MPU6050_REG_I2C_SLV0_DO     0x63
#define MPU6050_REG_I2C_SLV1_DO     0x64
#define MPU6050_REG_I2C_SLV2_DO     0x65
#define MPU6050_REG_I2C_SLV3_DO     0x66
    #define MPU6050_REG_I2C_SLV13_MASK  0xFF

#define MPU6050_REG_I2C_MST_DELAY_CTRL  0x67
    enum {
        I2C_MST_DELAY_SLV0,
        I2C_MST_DELAY_SLV1,
        I2C_MST_DELAY_SLV2,
        I2C_MST_DELAY_SLV3,
        I2C_MST_DELAY_SLV4,
        I2C_MST_DELAY_ES_SHADOW = 7,
    };

#define MPU6050_REG_SIGNAL_PATH_RESET   0x68
    enum {
        SIGNAL_RESET_TEMP,
        SIGNAL_RESET_ACCEL,
        SIGNAL_RESET_GYRO
    };

#define MPU6050_REG_MOT_DETECT_CTRL     0x69
    #define MOT_CTRL_MOT_COUNT_MASK     0x3
    #define MOT_CTRL_FF_COUNT_MASK      0x3
        #define MOT_CTRL_FF_COUNT_OFFSET    2
    #define MOT_CTRL_ACCEL_ON_DELAY_MASK    0x3
        #define MOT_CTRL_ACCEL_ON_DELAY_OFFSET 4
    enum {
        MOT_CTRL_COUNT_0_RESET,
        MOT_CTRL_COUNT_1_1,
        MOT_CTRL_COUNT_2_2,
        MOT_CTRL_COUNT_3_4
    };

#define MPU6050_REG_USER_CONTROL    0x6A
    enum {
        USER_CTRL_SIG_COND_RST,
        USER_CTRL_I2C_MST_RST,
        USER_CTRL_FIFO_RST,
        USER_CTRL_I2C_IF_DIS = 4,
        USER_CTRL_I2C_MST_EN,
        USER_CTRL_FIFO_EN
    };
*/


/**/ 
#define MPU6050_REG_PWR_MGMT_1  0x6B  /*se queda*/
/**/

    #define PWR_1_DEVICE_RESET_OFFSET   7
    #define PWR_1_SLEEP_OFFSET          6
/*
    #define PWR_1_CYCLE_OFFSET          5
    #define PWR_1_TEMP_DIS_OFFSET       3
    #define PWR_1_CLKSEL_MASK   0x7
    enum {
        PWR_CLKSEL_INTERNAL_8M,
        PWR_CLKSEL_GYRO_X,
        PWR_CLKSEL_GYRO_Y,
        PWR_CLKSEL_GYRO_Z,
        PWR_CLKSEL_EX_32K,
        PWR_CLKSEL_EX_19M,
        PWR_CLKSEL_STOP_RST = 7
    };

#define MPU6050_REG_PWR_MGMT_2  0x6C
    #define PWR_2_LP_WAKE_CTRL_MASK     0x3
    #define PWR_2_LP_WAKE_CTRL_OFFSET   5
    enum {
        PWR_2_LP_WAKE_CTRL_1_25HZ,
        PWR_2_LP_WAKE_CTRL_2_5HZ,
        PWR_2_LP_WAKE_CTRL_5HZ,
        PWR_2_LP_WAKE_CTRL_10HZ
    };
    enum {
        PWR_2_STBY_ZG,
        PWR_2_STBY_YG,
        PWR_2_STBY_XG,
        PWR_2_STBY_ZA,
        PWR_2_STBY_YA,
        PWR_2_STBY_XA
    };

#define MPU6050_REG_FIFO_COUNT_H    0x72
#define MPU6050_REG_FIFO_COUNT_L    0x73
    #define FIFO_COUNT_MASK     0xFF

#define MPU6050_REG_FIFO_RW         0x74
    #define FIFO_R_W_MASK       0xFF
*/