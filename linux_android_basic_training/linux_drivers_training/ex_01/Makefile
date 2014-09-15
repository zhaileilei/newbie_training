obj-m := hellowork.o
KVER=$(shell uname -r)
KERNELDIR=/usr/src/linux-headers-${KVER}
PWD=$(shell pwd)
all:
		make -C $(KERNELDIR) M=$(PWD) modules
.PHONY :clean
clean:
		rm -rf .*.cmd *.o *.ko *.mod.c modules* Module*


