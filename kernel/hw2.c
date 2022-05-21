#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/init_task.h>

struct recognized_task {
	struct list_head	list;
	struct task_struct* 	proc_ptr;
	pid_t			pid;
}

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

void recognized_add_process(struct recognized_task* new) {
	struct list_head* iter;
	struct recognized* entry;

	list_for_each(iter, init_task.recognized) {
		entry = list_entry(iter, struct recognized_task, list);
		if (entry->pid == new->pid) {
			return;
		}
	}
	list_add_tail(&(new->list), &(init_task.recognized));
}

asmlinkage long sys_register_process(void) {
	struct recongnized_task new = {
		.list = LIST_HEAD_INIT(new.list),
		.proc_ptr = current,
		.pid = current->pid
	};
	recognized_add_process(&new);

	return 0;
}

asmlinkage long sys_get_all_cs(void) {
	long sum = 0;
	if (list_empty(&(init_task.recognized))) {
		return -ENODATA;
	}

	struct list_head* iter;
	struct recognized* entry;

	list_for_each(iter, init_task.recognized) {
		entry = list_entry(iter, struct recognized_task, list);
		/* we assume the entry->proc_ptr is never empty */
		if (entry->proc_ptr->status == 1) {
			sum += entry->pid;
		}
	}

	return sum;
}
