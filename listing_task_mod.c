#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/sched.h>	/* Nedded for the for_each_process() macro*/

/*
char comm[TASK_COMM_LEN];
pid_t pid;
volatile long state;

struct list_head children;
struct list_head sibling;
*/

static int __init listing_task_init(void)
{
	printk(KERN_INFO "Hello world\n");
	struct task_struct *task;
	printk(KERN_INFO "   Process Name   PID State");
	for_each_process(task) {
		/* on each iteration task points to the next task */
		printk(KERN_INFO "%-15s%6d%5ld", task->comm, task->pid, task->state); 		
	}

	return 0;
}

static void __exit listing_task_exit(void)
{
	printk(KERN_INFO "Goodbye world\n");
}

module_init(listing_task_init);
module_exit(listing_task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linux Kernel Module for Listing Tasks");
MODULE_AUTHOR("Hanbing Leng");
