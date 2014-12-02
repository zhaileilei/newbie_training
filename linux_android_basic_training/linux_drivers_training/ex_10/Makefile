obj-m := char.o
KVER=$(shell uname -r)
KERNELDIR=/usr/src/linux-headers-${KVER}
#KERNELDIR=/opt/linux-3.0
PWD=$(shell pwd)
all:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY :clean

clean:
		rm -rf .*.cmd *.o *.mod.c *.ko *.tmp_versions module* Module*
