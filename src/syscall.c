#include "os.h"

static int sys_gethid(unsigned int *ptr_hid){
	lib_printf("--> sys_gethid, arg0 = 0x%x\n", ptr_hid);
	if (ptr_hid == NULL) {
		lib_printf("ptr_hid == NULL\n");
       		return -1;
	} else {
		lib_printf("ptr_hid != NULL\n");
		 *ptr_hid = r_mhartid();
 		 return 0;
	}
}

static int sys_exec(){
	// TODO: compare input value and app_table,
	// If required file exists, then execute this file.
}

static int sys_exit(){
	task_kill();
}

void do_syscall(struct context *ctx)
{
	uint32_t syscall_num = ctx->a7;
	lib_printf("syscall_num: %d\n", syscall_num);
	switch (syscall_num) {
	case 1:
		ctx->a0 = sys_gethid((unsigned int *)(ctx->a0));
		break;
	case 2:
		/* fork
		 * returned value:
		 *	child process: 0
		 *  parent process: pid of child process
		 */
		int ppid = get_current_task();
		ctx->a0 = task_copy(ppid);
		break;
	case 3:
		// exec
		break;
	case 4:
		// exit
		sys_exit();
		break;
	default:
		lib_printf("Unknown syscall no: %d\n", syscall_num);
		ctx->a0 = -1;
	}

	return;
}
