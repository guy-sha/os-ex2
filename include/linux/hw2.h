#ifndef HW2_
#define HW2_


struct recognized_task {
	struct list_head	list;
	struct task_struct* 	proc_ptr;
	pid_t			pid;
};


#endif