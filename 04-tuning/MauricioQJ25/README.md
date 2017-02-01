#Compilar el kernel de forma cruzada para la raspberry pi 3

1.-Conseguir los archivos fuentes:

	git clone --depth=1 https://github.com/raspberrypi/linux

2.-Instalar lar herramientas:

	git clone https://github.com/raspberrypi/tools

3.-Agregar las siguientes lineas al archivo ~/.bashrc:

	#Raspbian tool
	export PATH=$PATH:/home/mauricio/Diplomado/learning_kernel/09-raspKernel/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin

4.-Por último, generar el archivo .config:
	cd linux
	KERNEL=kernel
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig -j4

5.-Compilar:

	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs

6.-Grabar en la memoria, insertar la tarjeta sd y ver cuales son las particiones de boot y root:
    
    $lsblk 

	sdb1 FAT(boot)
	sdb2 ext4(root)

7.-Montar las particiones:

	mkdir mnt/fat32
	mkdir mnt/ext4
	sudo mount /dev/sdb1 mnt/fat32
	sudo mount /dev/sdb2 mnt/ext4	 

8.-Instalar los modulos (carpeta de root):

	sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=mnt/ext4 modules_install

9.-Copiar el kernle y el arbol de dispositivos (Device tree blobs en boot fat32):

	sudo cp mnt/fat32/$KERNEL.img mnt/fat32/$KERNEL-backup.img
	sudo scripts/mkknlimg arch/arm/boot/zImage mnt/fat32/$KERNEL.img
	sudo cp arch/arm/boot/dts/*.dtb mnt/fat32/
	sudo cp arch/arm/boot/dts/overlays/*.dtb* mnt/fat32/overlays/
	sudo cp arch/arm/boot/dts/overlays/README mnt/fat32/overlays/
	sudo umount mnt/fat32
	sudo umount mnt/ext4

Fuentes
	https://www.raspberrypi.org/documentation/linux/kernel/building.md
	https://www.youtube.com/watch?v=I8eHz1PqKsk&t=23s


