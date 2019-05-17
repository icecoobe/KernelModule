obj-m := Superblock.o Inode.o Dentry.o

KDIR=/lib/modules/$(shell uname -r)/build

PWD=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
ins_sb:
	insmod Superblock.ko
unins_sb:
	rmmod Superblock.ko
ins_inode:
	insmod Inode.ko
unins_inode:
	rmmod Inode.ko
ins_dentry:
	insmod Dentry.ko
unins_dentry:
	rmmod Dentry.ko
clean:
	make -C $(KDIR) M=$(PWD) clean
