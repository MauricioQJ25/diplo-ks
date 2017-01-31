#Contenido

1.-Driver mpu6050
2.-Cliente i2c-1
3.-Makefile
4.-Archivo de Registros "reg.h"
5.-Log para debuggear
6.-Carpeta donde vienes documentos importantes del dispositivo.

#Compilar
Para compilar ejecute el comando **make**
Creará 2 modulos, el driver y el cliente. 

Inserte primero el cliente mediante el comando *insmod cliente.ko*
Despues inserte el driver mediante el comando *insmod driver.ko*

##Por ultimo

puede ver las lecturas del acelerómetro, el giroscopio y el sensor de temperatura.

###Pequeño bug

El programa tiene un pequeño bug que se puede solucionar 
ejecutando este comando antes que todo lo demás

i2cset -y 1 0x68 107 0


