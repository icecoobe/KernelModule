#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("HelloWorld Module Template");
MODULE_VERSION("0.1");

static char *systype = "ext4";
module_param(systype, charp, 0);

static int __init moduletest_init(void)
{
	struct file_system_type *file_sys;
	struct super_block *ssb;
	file_sys = get_fs_type(systype);
	hlist_for_each_entry(ssb, &(file_sys->fs_supers), s_instances){
		printk(KERN_DEBUG "dev_t = %d, %d\n", MAJOR(ssb->s_dev), MINOR(ssb->s_dev));
		printk(KERN_DEBUG "name = %s\n", ssb->s_type->name);
	}
	return 0;
}

static void __exit moduletest_exit(void)
{
	printk(KERN_DEBUG "Goodbye,World!");
}

module_init(moduletest_init);
module_exit(moduletest_exit);
