ejecutar final en raspberrypi
#Proyecto final 
##Creacion de un Driver para raspberrypi 3
###Dispositivo mpu3050 mediante conexión i2c

Contenido de la carpeta:
	src/ 		*Contienen el codigo fuente*
        proyectoRedes/ 	*Contiene información relativa al proyecto de Redes*
	imagprueba/ 	*Contiene imagenes que prueban el funcionamiento del driver*



####Resumen
El siguiente proyecto consiste en la creación de un Driver para el dispositivo mpu3050
mediante la conexión i2c.

Primero se procede a conectar al dispositivo en los GPIOS correspondientes de la 
tarjeta para i2c, con los buses SDA y SCL.

####Protocolo i2c
Antes de comenzar a escribir el driver es necesario saber el funcionamiento del protocolo de comunicacion
i2c. El cual funciona de la siguiente manera:

//Aqui va el funcionamiento del protocolo

Ahora que se conoce el funcionamiento básico del protocolo, se procede a la documentación acerca del 
dispositivo a usar. mpu3050, para hacer uso de los registros. Se puede encontrar la información correspondiente en el siguiente link.

[liga a mpu3050 register map]

####Kernel i2c
Ahora se procede a la documentación del Kernel para escribir un driver para i2c.

Se tienen las siguientes estructuras. 

####Estructura general del driver

resume()
init()
exit()
probe()

y todas las demas funciones

####Referencias

En esta parte se colocan todas las referencias usadas para construir el driver, tanto las vistas en clase como a las que se recurrió.
