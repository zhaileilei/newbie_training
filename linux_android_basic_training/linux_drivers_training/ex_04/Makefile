obj-m := driver.o
KVER = $(shell uname -r)
KERNELDIR = /usr/src/linux-headers-${KVER}
PWD = $(shell pwd)
all:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY :clean

clean:
		rm -rf .*.cmd *.ko *.o *.mod.c *.tmp_versions module* Module*
