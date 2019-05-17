#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("FileSystem");
MODULE_VERSION("0.1");

static int __init moduletest_init(void)
{
	// copy from /proc/filesystems
	const char *systype[] = {
		"sysfs",
		"rootfs",
		"ramfs",
		"bdev",
		"proc",
		"cpuset",
		"cgroup",
		"tmpfs",
		"devtmpfs",
		"binfmt_misc",
		"configfs",
		"debugfs",
		"tracefs",
		"securityfs",
		"sockfs",
		"pipefs",
		"devpts",
		"hugetlbfs",
		"autofs",
		"pstore",
		"mqueue",
		"ext3",
		"ext2",
		"ext4",
		"fuseblk",
		"fuse",
		"fusectl"
	};

	struct file_system_type *file_sys = NULL;
	int i;

	for (i=0; i< sizeof(systype)/sizeof(char *); i++){
		file_sys = get_fs_type(systype[i]);
		printk(KERN_ALERT "current = %p, name = %s, next = %p", file_sys, file_sys->name, file_sys->next);
	}
	return 0;
}

static void __exit moduletest_exit(void)
{
	printk(KERN_ALERT "FileSystem!");
}

module_init(moduletest_init);
module_exit(moduletest_exit);
