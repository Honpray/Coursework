#obj-m += birthday_mod.o
#obj-m += listing_task_mod.o
obj-m += listing_task_dfs_mod.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
