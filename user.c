#include "os.h"

void meow()
{
	lib_puts("         +----------+ \n");
	lib_puts("         | Meow~~~:3| \n");
	lib_puts("         +----------+ \n");
	lib_puts("          o           \n");
	lib_puts("    ^^   o            \n");
	lib_puts(" ('-w-')(   )00000    \n");
	lib_puts("  () ()  ()()         \n");
}

void user_task0(void)
{
	lib_puts("Task0: Created!\n");
	while (1)
	{
		lib_puts("Task0: Running...\n");
		lib_delay(1000);
	}
}

void user_task1(void)
{
	lib_puts("Task1: Created!\n");
	while (1)
	{
		lib_puts("Task1: Running...\n");
		lib_delay(1000);
	}
}

void user_task2(void)
{
	lib_puts("Task2: Created!\n");
	int res = fork();
	if (res)
	{
		lib_puts("I'm parent!\n");
		lib_delay(3000);
		wait();
	}
	if (res == 0)
	{
		lib_puts("I'm child!\n");
		lib_delay(3000);
	}
	os_kernel();
}

void user_init()
{
	disk_init();
	lib_delay(3000);
	meow();
	task_create(&user_task0);
	task_create(&user_task1);
	task_create(&user_task2);
}
