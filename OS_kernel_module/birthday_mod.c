#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
static int __init simple_init(void)
{
        printk(KERN_INFO "Loading Module\n");
        struct birthday *person, *cat;
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month= 8;
	person->year = 1995;
	cat = kmalloc(sizeof(*cat), GFP_KERNEL);
	cat->day = 30;
	cat->month = 10;
	cat->year= 2020;
	INIT_LIST_HEAD(&person->list);
	INIT_LIST_HEAD(&cat->list);
	list_add_tail(&person->list, &birthday_list);
	list_add_tail(&cat->list, &birthday_list);
	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list) { 
		/* on each iteration ptr points */
		/* to the next birthday struct */
		printk(KERN_INFO "Inserted birthday %d %d %d", ptr->month, ptr->day, ptr->year); 
	}
	printk(KERN_INFO "Loaded\n");	
	return 0;
}

/* This function is called when the module is removed. */
static void __exit simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr,next,&birthday_list,list) {
		/* on each iteration ptr points */
		/* to the next birthday struct */
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk(KERN_INFO "Bye\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Insertion Module");
MODULE_AUTHOR("Hanbing Leng");
