#include "os.h"

user_app_t app_table[APP_NUM];

user_app_t *get_app_table()
{
	return app_table;
}

void show_info()
{
	lib_puts("Wellcome to toothpasteOS\n");
	lib_puts("Version: 1.0\n");
	lib_puts("Note: Derived from mini-riscv-os\n");
	lib_puts("Author: Ian Chen\n");
	exit();
}

void clear()
{
	int i = 30;
	while (i > 0)
	{
		lib_puts("\n");
		i--;
	}
	exit();
}

void user_app_init()
{
	for (int i = 0; i < APP_NUM; i++)
	{
		memset(app_table[i].path, '\0', 20);
	}
}

void user_app_subscribe(char *path, void (*task)(void))
{
	for (int i = 0; i < APP_NUM; i++)
	{
		if (app_table[i].path[0] == '\0')
		{
			memcpy(app_table[i].path, path, sizeof(char) * strlen(path));
			app_table[i].task = task;
			break;
		}
	}
}

void user_init()
{
	user_app_init();
	user_app_subscribe("info", &show_info);
	user_app_subscribe("clear", &clear);
	task_create(&sh);
}
