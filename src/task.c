#include "task.h"
#include "os.h"

uint8_t task_stack[MAX_TASK][STACK_SIZE];
ctx_t ctx_os;
ctx_t ctx_tasks[MAX_TASK];
ctx_t *ctx_now;
int taskTop = 0; // total number of task

void task_kill(){
	taskTop--;
	int pid = get_current_task();
	for(int j = 0; j < STACK_SIZE; j++){
		task_stack[pid][j] = 0;
	}
	ctx_tasks[pid].ra = NULL;
	ctx_tasks[pid].sp = NULL;
}

int task_copy(int pid){
	int i = taskTop++;
	ctx_tasks[i].ra = ctx_tasks[pid].ra;
	for(int j = 0; j < STACK_SIZE; j++){
		task_stack[i][j] = task_stack[pid][j];
	}
	ctx_tasks[i].sp = (reg_t)&task_stack[i][STACK_SIZE - 1];
	ctx_tasks[i].a0 = 0; // return value of child process must be zero
	return i;
}

// create a new task
int task_create(void (*task)(void)){
	int i = taskTop++;
	ctx_tasks[i].ra = (reg_t)task;
	// ctx_tasks[i].pc = (reg_t)task;
	ctx_tasks[i].sp = (reg_t)&task_stack[i][STACK_SIZE - 1];
	return i;
}

// switch to task[i]
void task_go(int i){
	ctx_now = &ctx_tasks[i];
	// switch_to(ctx_now);
	sys_switch(&ctx_os, &ctx_tasks[i]);
}

// switch back to os
void task_os(){
	ctx_t *ctx = ctx_now;
	ctx_now = &ctx_os;
	// switch_to(&ctx_os);
	sys_switch(ctx, &ctx_os);
}
