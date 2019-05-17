#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("HelloWorld Module Template");
MODULE_VERSION("0.1");

static char *systype = "ext4";
module_param(systype,charp,0);

static int __init moduletest_init(void)
{
	struct file_system_type *file_sys;
	struct super_block *ssb;
	struct inode *ino;
	unsigned long count = 0; 

	file_sys = get_fs_type(systype);
	hlist_for_each_entry(ssb, &(file_sys->fs_supers), s_instances){
		printk(KERN_DEBUG "dev_t = %d, %d\n", MAJOR(ssb->s_dev), MINOR(ssb->s_dev));
		printk(KERN_DEBUG "name = %s\n", ssb->s_type->name);
		count = 0;
		list_for_each_entry(ino, &(ssb->s_inodes), i_sb_list){
			count++;
			printk(KERN_DEBUG "ino = %ld, nlink = %d\n", ino->i_ino, ino->i_nlink);
		}
		printk(KERN_DEBUG "inode count = %ld",count);
	}
	return 0;
}

static void __exit moduletest_exit(void)
{
	printk(KERN_DEBUG "Goodbye,World!");
}

module_init(moduletest_init);
module_exit(moduletest_exit);
