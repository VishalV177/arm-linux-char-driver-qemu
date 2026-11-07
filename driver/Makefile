obj-m += chardriver.o
KDIR := ../kernel/linux
ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-

all:
	make -C $(KDIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) modules

clean:
	make -C $(KDIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) clean
