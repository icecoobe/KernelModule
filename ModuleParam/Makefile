TARGET=ModuleParam
KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
obj-m := $(TARGET).o
default:
	make -C $(KDIR) M=$(PWD) modules
install:
	insmod $(TARGET).ko
uninstall:
	rmmod $(TARGET).ko
clean:
	make -C $(KDIR) M=$(PWD) clean
