obj-m := hellowork.o
KERNELDIR=/opt/kernel
PWD=$(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY :clean
clean:
		rm -rf *.o *.ko *.mod.c modules.* Module.*
