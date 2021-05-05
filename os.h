#ifndef __OS_H__
#define __OS_H__

#include "riscv.h"
#include "lib.h"
#include "task.h"
#include "timer.h"
#include "unistd.h"
#include "virtio.h"
#include "types.h"
#include "defs.h"

extern void user_init();
extern void os_kernel();
extern void minus_current_task();
extern int os_main(void);
extern int current_task;
extern int get_current_task();

#endif
