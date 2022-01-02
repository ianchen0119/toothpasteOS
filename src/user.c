#include "os.h"
#include "user_api.h"

user_app_t app_table[APP_NUM];

user_app_t *get_app_table()
{
	return app_table;
}

void show_info()
{
	lib_puts("Wellcome to toothpasteOS!\n");
	exit();
}

void user_app_subscribe()
{
	memset(app_table[0].path, '\0', 20);
	memcpy(app_table[0].path, "info", 4);
	app_table[0].task = &show_info;
}

int shared_var = 500;

lock_t lock;

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
	while (1)
	{
		for (int i = 0; i < 50; i++)
		{
			lock_acquire(&lock);
			shared_var++;
			lock_free(&lock);
			lib_delay(100);
		}
		lib_printf("The value of shared_var is: %d \n", shared_var);
	}
}

void user_task3(void)
{
	lib_puts("Task3: Created!\n");
	while (1)
	{
		lib_puts("Trying to get the lock... \n");
		lock_acquire(&lock);
		lib_puts("Get the lock!\n");
		lock_free(&lock);
		lib_delay(1000);
	}
}

void user_task4(void)
{
	lib_puts("Task4: Created!\n");
	unsigned int hid = -1;

	/*
	 * if syscall is supported, this will trigger exception, 
	 * code = 2 (Illegal instruction)
	 */
	// hid = r_mhartid();
	// lib_printf("hart id is %d\n", hid);

	// perform system call from the user mode
	int ret = -1;
	ret = gethid(&hid);
	// ret = gethid(NULL);
	if (!ret)
	{
		lib_printf("system call returned!, hart id is %d\n", hid);
	}
	else
	{
		lib_printf("gethid() failed, return: %d\n", ret);
	}

	while (1)
	{
		lib_puts("Task4: Running...\n");
		lib_delay(1000);
	}
}

void user_init()
{
	user_app_subscribe();
	task_create(&user_task1);
	task_create(&sh);
}
