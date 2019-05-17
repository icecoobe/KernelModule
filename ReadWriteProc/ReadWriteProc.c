#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("Test Read and Write Handlers of Proc");
MODULE_VERSION("0.1");

#define BUFSIZE  10
 
static int aslr_switch=1;
module_param(aslr_switch, int, 0660);

static struct proc_dir_entry *ent;
 
static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) 
{
	int m;
	char buf[BUFSIZE];

	// printk(KERN_DEBUG "%ld\n", count);
	// printk(KERN_DEBUG "%lld\n", *ppos);

	if (*ppos > 0 || count > BUFSIZE)
		return -EFAULT;
	if (copy_from_user(buf, ubuf, count))
		return -EFAULT;
	// printk(KERN_DEBUG "%s\n", buf);
	if (sscanf(buf, "%d", &m) != 1)
		return -EFAULT;
	if (m != 0 && m != 1)
		return -EFAULT;

	aslr_switch = m;

	return strlen(buf);
}

static ssize_t myread(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) 
{
	char buf[BUFSIZE];
	int len = 0;

	if (*ppos > 0 || count < BUFSIZE)
		return 0;
	len += sprintf(buf, "%d\n", aslr_switch);
	//printk(KERN_DEBUG "%d\n", len);
	if (copy_to_user(ubuf, buf, len))
		return -EFAULT;

	*ppos = len;
	return len;
}

static struct file_operations myops = 
{
	.owner = THIS_MODULE,
	.read = myread,
	.write = mywrite,
};
 
static int simple_init(void)
{
	ent = proc_create("myproc", 0660, NULL, &myops);
	return 0;
}
 
static void simple_cleanup(void)
{
	proc_remove(ent);
}
 
module_init(simple_init);
module_exit(simple_cleanup);
