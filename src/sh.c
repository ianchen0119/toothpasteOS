#include "os.h"
void sh()
{
    char input[50];
    int ready = 1;
    while (ready)
    {
        lib_puts("$ ");
        lib_gets(input);
        ready = 0;
        user_app_t *app_table = get_app_table();
        int i = 0;
        for (; i < APP_NUM; i++)
        {
            if (strcmp(app_table[i].path, input) >= 0)
            {
                break;
            }
        }
        if (i == APP_NUM)
        {
            lib_printf("shell: %s: command not found.\n", input);
        }
        else if (task_create(app_table[i].task) > 0)
        {
            lib_printf("shell: task[%s] is created! \n", app_table[i].path);
        }
        else
        {
            lib_printf("Only allow 30 tasks to run simultaneously.\n");
        }
        lib_delay(1000);
        ready = 1;
        w_mie(r_mie() | MIE_MTIE);
    }
}