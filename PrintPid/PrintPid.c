#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sem.h>
#include <linux/list.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("Print pid and name of the current process");
MODULE_VERSION("0.1");

static int __init printpid_init(void)
{
	struct task_struct *pos;
	struct list_head *current_head;
	int count = 0;

	printk(KERN_DEBUG "PrintPid Init");

	printk(KERN_DEBUG "Traversal module is working...\n");

	current_head = &(current->tasks);
	list_for_each_entry(pos, current_head, tasks)
	{
		count++;
		printk("[process %d]: %s\'s pid is %d\n",count, pos->comm, pos->pid);
	}
	printk(KERN_DEBUG "The number of process is %d\n", count);

	return 0;
}

static void __exit printpid_exit(void)
{
	printk(KERN_DEBUG "PrintPid Exit!");
}

module_init(printpid_init);
module_exit(printpid_exit);
