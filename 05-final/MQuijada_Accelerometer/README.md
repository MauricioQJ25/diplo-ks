#Proyecto final del módulo Espacio de Kernel
###Nombre: Mauricio Quijada Jiménez
##Creacion de un Driver de I2C para el acelerómetro mpu6050 en la RaspberryPi 3

Contenido de la carpeta:<br />

	src/ 		*Contienen el codigo fuente del driver*
        proyectoRedes/ 	*Contiene información relativa al proyecto de Redes*<br />
	imagprueba/ 	*Contiene imagenes que prueban el funcionamiento del driver*<br />

###Resumen

El driver tiene como objetivo leer los registros de temperatura, aceleración y orientación del mpu6050, <br />
además de escribir en el registro de *POWER MANAGEMENT* para activar o poner al dispositivo en *stand by*.<br />

####¿Qué es I2C?

I2C es un bus de comunicaciones entre circuitos integrados desarrollado por Phillips Semiconductors (ahora NXP Semiconductors). <br />
Se trata de un bus muy sencillo con solo dos hilos:<br />

    línea de datos (SDA) #pin 3 de la RaspberryPi3<br />
    línea de reloj (SCL) #pin 4 de la RaspberryPi4<br />

    http://pinout.xyz/  *liga a GPIO de la RaspberryPi3*<br />

   Además el dispositivo se debe conectar 3.3[V] y GND:<br />

    PWR 3.3[V]	#pin 1 de la RaspberryPi3<br />
    GND 0.0[V]	#pin 5 de la RaspberryPi3<br />

Se pueden realizar transmisiones serie bidireccionales de hasta 100 kbit/s en modo estándar y 400 kbit/s en modo rápido.<br />
Las versiones más modernas de I2C incorporan modos con mayores tasas de transferencia (hasta 5Mbit/s)<br />
pero el procesador de la Raspberry Pi no los implementa.<br />

El bus requiere de un maestro y un esclavo, solamente el maestro puede iniciar la transacción de datos <br />
y el esclavo puede replicar la transacción  iniciada por el maestro.<br />
En sistemas Linux el controlador I2C embebido en el procesador es tipicamente el maestro que controla el bus.<br />
Cada esclavo es identificado por una unica dirección I2C. Cada transacción iniciada por el maestro contiene la dirección<br />
del esclavo, lo cual permite reconocer cual replicará la transacción.<br />
En la siguiente imágen se puede observar el bus de I2C.<br />

[imagen de I2C]<br />

Formato del mensaje de I2C<br />
start + slave address + read/write + Acknowledge + data + Acknowledge ... + Stop<br />


Para mayor información acerca de como funciona el protocolo y el Formato del mensaje vea la siguiente liga<br />
[liga a protocolo I2C]
https://www.google.com.mx/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwi9t8mOk-7RAhVP4mMKHc3FBo4QFggZMAA&url=http%3A%2F%2Fgalia.fc.uaslp.mx%2F~cantocar%2Fmicrocontroladores%2FEL_BUS_I2C%2FEL_BUS_I2C.PPT&usg=AFQjCNH_7e9aCBvNpbmiotQhMQB0BxOUsg&sig2=nk-S3Vbq57-QY56VuKceFA&bvm=bv.145822982,d.amc<br />


###Subsistema I2C

Como todo los subsistemas, el I2C subsystem. es responsable de proveer un API para implementar controladores de I2C.<br />
El núcleo del I2C se encuentra localizado en drivers/i2c.<br />
El controlador de I2C se encuentra localizado en drivers/i2c/busses<br />

###Registrar un I2C driver

Como todos los subsistemas define una estructura<br />
**struct i2c_driver** que proviene de<br />
**struct device_driver**, la cual debe ser instanciada y registar cada dispositivo I2C. <br />
Como es usual la estructura apunta a  las funciones **->probe() y ->remove()**<br />
Tambien contiene un campo **id_table** que debe apuntar  a los ID de los dispositivos.<br />
y para registrar el driver se usan las funciones<br />
**i2c_add_driver() y i2c_del_driver()**<br />
y si el driver no hace nada en **init() y exit()** se usa **module_i2c_driver()**<br />


###Registrar un dispositivo I2C: non-DT
La estructura **i2c_board_info** permite descriver como un dispositivo I2C es conectado a la tarjeta<br />
Tal como la estructura está normalmente definida con la macro<br />
**I2C_BOARD_INFO()**<br />

###probe() y remove()

La función *->probe()* es responsable de inicializar el dispositivo y registrarlo en el kernel framework<br />
y recibe como argumentos:<br />
		struct i2c_client pointer    #representa al driver por si mismo<br />
		struct i2c_device_id pointer #representa la id del dispositivo que es probada<br />
La función *->remover()* es responsable de quitar el registro del dispositivo del kernel framework<br />
y recibe tambien el mismo argumento<br />
		struct i2c_client.<br />
		
###Comunicación con I2C

Para comunicarnos con I2C hay varias formas, en este driver se usa la lista de funciones de SMBus,<br />
en particular las siguientes funciones de lectura/escritura:<br />

	▶ s32 i2c_smbus_read_byte_data(const struct i2c_client *client, u8 command);<br />
	▶ s32 i2c_smbus_write_byte_data(const struct i2c_client *client, u8 command, u8 value);<br />
	
###Registros del driver
Para leer los datos o escribir en el dispositivo, es necesario conocer el mapa de registros.<br />
El cual lo podemos encontrar en la carpeta Documents.<br />
En un archivo de cabecera se definen, los que usé para escribir el driver.<br />

###Pruebas Realizadas
####log del sistemma
![alt tag](https://github.com/MauricioQJ25/diplo-ks/blob/Pfinal/05-final/MQuijada_Accelerometer/ImagenesProyecto/logdriverworking.png)

####Modinfo
![alt tag](https://github.com/MauricioQJ25/diplo-ks/blob/Pfinal/05-final/MQuijada_Accelerometer/ImagenesProyecto/modinfo.png)

####rmmoddriver
![alt tag](https://github.com/MauricioQJ25/diplo-ks/blob/Pfinal/05-final/MQuijada_Accelerometer/ImagenesProyecto/rmmoddriver.png)
###Referencias

Coloco todas las referencias que me fueron útiles, pero en general todo se puede encontrar en la documentación del Kernel.<br />
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

