ifneq ($(KERNELRELEASE),)
	obj-m += hellowork.o
else
	KERNELDIR=/opt/kernel
all:
		PWD=$(shell pwd)
		$(MAKE) -C $(KERBEKDIR) M=$(PWD) modules
clean:
		rm -rf .*.cmd *.o *.ko *.mod.c modules* Module*
endif

