#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/sched.h>	/* Nedded for the for_each_process() macro*/

/* defined in struct task_struct
char comm[TASK_COMM_LEN];
pid_t pid;
volatile long state;
struct list_head children;
struct list_head sibling;
*/

void helper(struct task_struct *task){
	struct task_struct *next_task;
	struct list_head *list; 
	printk(KERN_INFO "%-15s%6d%6ld", task->comm, task->pid, task->state);
	list_for_each(list, &task->children) {
		next_task = list_entry(list, struct task_struct, sibling);
		/* next_task points to the next child in the list */
		helper(next_task);	
	}	
}

static int __init listing_task_init(void)
{
	printk(KERN_INFO "Hello world\n");
	printk(KERN_INFO "Process Name      PID State");
	helper(&init_task);
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
