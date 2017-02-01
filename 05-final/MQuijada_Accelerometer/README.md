#Proyecto final del módulo Espacio de Kernel
<br />
##Creacion de un Driver de I2C para el acelerómetro mpu6050 en la RaspberryPi 3
<br />
Contenido de la carpeta:<br />
<br />
		src/ 			*Contienen el codigo fuente del driver*<br />
        proyectoRedes/ 	*Contiene información relativa al proyecto de Redes*<br />
		imagprueba/ 	*Contiene imagenes que prueban el funcionamiento del driver*<br />
<br />
<br />
<br />
###Resumen
<br />
El driver tiene como objetivo leer los registros de temperatura, aceleración y orientación del mpu6050, <br />
además de escribir en el registro de *POWER MANAGEMENT* para activar o poner al dispositivo en *stand by*.<br />
<br />
####¿Qué es I2C?
<br />
I2C es un bus de comunicaciones entre circuitos integrados desarrollado por Phillips Semiconductors (ahora NXP Semiconductors). <br />
Se trata de un bus muy sencillo con solo dos hilos:<br />
<br />
<br />
    línea de datos (SDA) #pin 3 de la RaspberryPi3<br />
    línea de reloj (SCL) #pin 4 de la RaspberryPi4<br />
<br />
    http://pinout.xyz/ *liga a GPIO de la RaspberryPi3*<br />
<br />
    Además el dispositivo se debe conectar 3.3[V] y GND.<br />
<br />
    PWR 3.3[V]	#pin 1 de la RaspberryPi3<br />
    GND 0.0[V]	#pin 5 de la RaspberryPi3<br />
<br />
<br />
<br />
Se pueden realizar transmisiones serie bidireccionales de hasta 100 kbit/s en modo estándar y 400 kbit/s en modo rápido.<br />
Las versiones más modernas de I2C incorporan modos con mayores tasas de transferencia (hasta 5Mbit/s)<br />
pero el procesador de la Raspberry Pi no los implementa.<br />
<br />
El bus requiere de un maestro y un esclavo, solamente el maestro puede iniciar la transacción de datos <br />
y el esclavo puede replicar la transacción  iniciada por el maestro.<br />
<br />
En sistemas Linux el controlador I2C embebido en el procesador es tipicamente el maestro que controla el bus.<br />
<br />
Cada esclavo es identificado por una unica dirección I2C. Cada transacción iniciada por el maestro contiene la dirección<br />
del esclavo, lo cual permite reconocer cual replicará la transacción.<br />
<br />
En la siguiente imágen se puede observar el bus de I2C.<br />
<br />
[imagen de I2C]<br />
<br />
Formato del mensaje de I2C<br />
<br />
start + slave address + read/write + Acknowledge + data + Acknowledge ... + Stop<br />
<br />
Para mayor información acerca de como funciona el protocolo y el Formato del mensaje vea la siguiente liga<br />
<br />
[liga a protocolo I2C]<br />
<br />
<br />
###Subsistema I2C
<br />
Como todo los subsistemas, el I2C subsystem. es responsable de proveer un API para implementar controladores de I2C.<br />
<br />
El núcleo del I2C se encuentra localizado en drivers/i2c.<br />
El controlador de I2C se encuentra localizado en drivers/i2c/busses<br />
<br />
###Registrar un I2C driver
<br />
Como todos los subsistemas define una estructura<br />
<br />
**struct i2c_driver** que proviene de<br />
**struct device_driver**, la cual debe ser instanciada y registar cada dispositivo I2C. <br />
<br />
Como es usual la estructura apunta a  las funciones **->probe() y ->remove()**<br />
<br />
Tambien contiene un campo **id_table** que debe apuntar  a los ID de los dispositivos.<br />
<br />
y para registrar el driver se usan las funciones<br />
<br />
**i2c_add_driver() y i2c_del_driver()**<br />
<br />
y si el driver no hace nada en **init() y exit()** se usa **module_i2c_driver()**<br />


###Registrar un dispositivo I2C: non-DT
<br />
La estructura **i2c_board_info** permite descriver como un dispositivo I2C es conectado a la tarjeta<br />
Tal como la estructura está normalmente definida con la macro<br />
**I2C_BOARD_INFO()**<br />
<br />
###probe() y remove()
<br />
La función *->probe()* es responsable de inicializar el dispositivo y registrarlo en el kernel framework<br />
y recibe como argumentos:<br />
		struct i2c_client pointer    #representa al driver por si mismo<br />
		struct i2c_device_id pointer #representa la id del dispositivo que es probada<br />
<br />
La función *->remover()* es responsable de quitar el registro del dispositivo del kernel framework<br />
y recibe tambien el mismo argumento<br />
		struct i2c_client.<br />
<br />
###Comunicación con I2C

Para comunicarnos con I2C hay varias formas, en este driver se usa la lista de funciones de SMBus,<br />
en particular las siguientes funciones de lectura/escritura.<br />
<br />
▶ s32 i2c_smbus_read_byte_data(const struct i2c_client *client, u8 command);<br />
▶ s32 i2c_smbus_write_byte_data(const struct i2c_client *client, u8 command, u8 value);<br />
<br />
<br />
###Registros del driver
<br />
Para leer los datos o escribir en el dispositivo, es necesario conocer el mapa de registros.<br />
El cual lo podemos encontrar en la carpeta Documents.<br />
<br />
En un archivo de cabecera se definen, los que usé para escribir el driver.<br />
<br />
###Pruebas Realizadas
<br />
<br />
###Referencias
<br />
Coloco todas las referencias que me fueron útiles, pero en general todo se puede encontrar en la documentación del Kernel.<br />
<br />
https://www.kernel.org/doc/Documentation/i2c/writing-clients<br />
<br />
http://elinux.org/Interfacing_with_I2C_Devices<br />
https://lwn.net/Kernel/LDD3/<br />
http://opensourceforu.com/2015/01/writing-i2c-clients-in-linux/<br />
https://www.kernel.org/doc/Documentation/i2c/dev-interface<br />
http://lxr.free-electrons.com/source/drivers/i2c/i2c-dev.c<br />
http://www.linuxjournal.com/article/7136<br />
http://en.wikipedia.org/wiki/I2C<br />
http://pinout.xyz/<br />
http://www.linux-drivers.org/<br />

