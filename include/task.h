#ifndef __TASK_H__
#define __TASK_H__

#include "riscv.h"
#include "sys.h"

#define MAX_TASK 30
#define STACK_SIZE 1024

extern int taskTop;

extern int task_create(void (*task)(void));
extern void task_go(int i);
extern void task_os();
extern int task_copy(int pid);
extern void task_kill();
extern void task_replace(void (*task)(void));

#endif
