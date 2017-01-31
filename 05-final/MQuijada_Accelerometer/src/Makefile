obj-m += mpu_driver.o
obj-m += mpu_client.o



all:
#	Para compilar el módulo de kernel en PC con Ubuntu:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

#	Para compilar el módulo de kernel con el compilador cruzado para la Raspberry PI 3:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/mauricio/Diplomado/learning_kernel/09-raspKernel/linux M=$(PWD) modules

clean:
#	Para compilar el módulo de kernel en PC con Ubuntu:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

#	Para compilar el módulo de kernel con el compilador cruzado para la Raspberry PI 3:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/mauricio/Diplomado/learning_kernel/09-raspKernel/linux M=$(PWD) clean
