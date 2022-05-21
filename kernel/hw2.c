#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage long sys_set_status(int status) {
	if (status != 0 && status != 1) {
		return -EINVAL;
	}
	
	current->status = status;
	return 0;
}

asmlinkage long sys_get_status(void) {
	return current->status;
}

asmlinkage long sys_register_process(void) {
	return 0;
}

asmlinkage long sys_get_all_cs(void) {
	return 0;
}
