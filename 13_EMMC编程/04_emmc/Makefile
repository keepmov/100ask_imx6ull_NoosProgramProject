PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

my_mmc.img : start.S  uart.c main.c my_printf.c mmc.c
	$(CC) -nostdlib -g -c -o start.o start.S 
	$(CC) -nostdlib -g -c -o uart.o uart.c	
	$(CC) -nostdlib -g -c -o main.o main.c	
	$(CC) -nostdlib -g -c -o my_printf.o my_printf.c
	$(CC) -nostdlib -g -c -o mmc.o mmc.c
	
	$(LD) -T imx6ull.lds -g start.o uart.o main.o my_printf.o mmc.o -o my_mmc.elf -lgcc -L/home/book/100ask_imx6ull-sdk/ToolChain/gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/6.2.1
	
	$(OBJCOPY) -O binary -S my_mmc.elf  my_mmc.bin
	$(OBJDUMP) -D -m arm  my_mmc.elf  > my_mmc.dis	
	./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d my_mmc.bin my_mmc.imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin my_mmc.imx > my_mmc.img

clean:
	rm -f my_mmc.dis  my_mmc.bin my_mmc.elf my_mmc.imx my_mmc.img *.o


	
