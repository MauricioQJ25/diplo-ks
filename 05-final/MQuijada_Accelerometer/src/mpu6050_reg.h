#define SENSOR_NAME "mpu6050-i2c"     /*se queda 2*/

//Reg map
#define MPU6050_REG_WHO_AM_I    0x75 /*se queda 1*/


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

/**/ 
#define MPU6050_REG_PWR_MGMT_1  0x6B  /*se queda*/
/**/

    #define PWR_1_DEVICE_RESET_OFFSET   7
    #define PWR_1_SLEEP_OFFSET          6
