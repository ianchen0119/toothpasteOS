#include "os.h"
void sh()
{
    char input[50];
    int ready = 1;
    while (ready)
    {
        int ppid = get_current_task();
        lib_printf("pid: %d\n", ppid);
        lib_puts("$ ");
        lib_gets(input);
        w_mie(r_mie() | MIE_MTIE);
        ready = 0;
        int pid = fork();
        if (pid == 0)
        {
            // child process
            lib_printf("child pid: %d\n", pid);
            exec(input);
        }
        else
        {
            // parent process
            lib_printf("parent pid: %d\n", pid);
            lib_delay(1000);
            ready = 1;
        }
    }
}