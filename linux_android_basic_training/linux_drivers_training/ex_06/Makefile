obj-m := time.o
KVER=$(shell uname -r)
KERNELDIR=/usr/src/linux-headers-${KVER}
PWD=$(shell pwd)
all:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY :clean

clean:
		rm -rf .*.cmd *.o *.mod.c *.ko *.tmp_versions module* Module*
