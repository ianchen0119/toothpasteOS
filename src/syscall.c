#include "os.h"

static int sys_gethid(unsigned int *ptr_hid)
{
	lib_printf("--> sys_gethid, arg0 = 0x%x\n", ptr_hid);
	if (ptr_hid == NULL)
	{
		lib_printf("ptr_hid == NULL\n");
		return -1;
	}
	else
	{
		lib_printf("ptr_hid != NULL\n");
		*ptr_hid = r_mhartid();
		return 0;
	}
}

static int sys_exec(char *file, uint32_t *pc)
{
	user_app_t *app_table = get_app_table();
	for (int i = 0; i < APP_NUM; i++)
	{
		if (strcmp(app_table[i].path, file) < 0)
		{
			continue;
		}
		else
		{
			*pc = app_table[i].task;
			return 0;
		}
	}
	return -1;
}

static int sys_exit()
{
	task_kill();
}

void do_syscall(struct context *ctx, uint32_t *pc)
{
	uint32_t syscall_num = ctx->a7;
	int ppid = get_current_task();
	lib_printf("syscall_num: %d\n", syscall_num);
	switch (syscall_num)
	{
	case 1:
		ctx->a0 = sys_gethid((unsigned int *)(ctx->a0));
		break;
	case 2:
		/* fork
		 * returned value:
		 *	child process: 0
		 *  parent process: pid of child process
		 */
		ctx->a0 = task_copy(ppid);
		break;
	case 3:
		// exec
		ctx->a0 = sys_exec((char *)ctx->a0, pc);
		break;
	case 4:
		// exit
		sys_exit();
		break;
	default:
		lib_printf("Unknown syscall no: %d\n", syscall_num);
		ctx->a0 = -1;
	}
	if (syscall_num != 3)
	{
		*pc = *pc + 4;
	}
	return;
}
