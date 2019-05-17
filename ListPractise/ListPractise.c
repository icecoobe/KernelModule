#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("mudongliangabcd@gmail.com");
MODULE_DESCRIPTION("Linux Kernel List Practise");
MODULE_VERSION("0.1");

#define N 5

struct ListNode
{
	int num;
	struct list_head list;
};

static struct ListNode head;

static int __init lp_init(void)
{
	struct list_head *pos, *tmp;
	struct ListNode *tmpNode;
	int i = 0;

	printk(KERN_ALERT "LP Init");
	INIT_LIST_HEAD(&head.list);

	for(;i < N;i++)
	{
		tmpNode = (struct ListNode *)kmalloc(sizeof(struct ListNode), GFP_KERNEL);
		tmpNode->num = i;
		//list_add(&tmpNode->list, &head.list);
		list_add_tail(&tmpNode->list, &head.list);
	}

	list_for_each_entry(tmpNode, &head.list, list)
	{
		printk("data : %d \n", tmpNode->num);	
	}

	list_for_each_safe(pos, tmp, &head.list)
	{
		tmpNode = list_entry(pos, struct ListNode, list);
		printk(KERN_DEBUG "data : %d\n", tmpNode->num);
	}

    return 0;
}

static void __exit lp_exit(void)
{
    printk(KERN_ALERT "LP Exit!");
}

module_init(lp_init);
module_exit(lp_exit);
