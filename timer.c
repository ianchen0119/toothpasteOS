#include "timer.h"
#define interval 20000000
extern void os_kernel();
extern void trap_vector();
// a scratch area per CPU for machine-mode timer interrupts.
reg_t timer_scratch[NCPU][5];

void timer_init()
{
  // each CPU has a separate source of timer interrupts.
  int id = r_mhartid();

  // ask the CLINT for a timer interrupt.
  *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + interval;

  // prepare information in scratch[] for timervec.
  // scratch[0..2] : space for timervec to save registers.
  // scratch[3] : address of CLINT MTIMECMP register.
  // scratch[4] : desired interval (in cycles) between timer interrupts.
  reg_t *scratch = &timer_scratch[id][0];
  scratch[3] = CLINT_MTIMECMP(id);
  scratch[4] = interval;
  w_mscratch((reg_t)scratch);

  // set the machine-mode trap handler.
  w_mtvec((reg_t)trap_vector);

  // enable machine-mode interrupts.
  w_mstatus(r_mstatus() | MSTATUS_MIE);

  // enable machine-mode timer interrupts.
  w_mie(r_mie() | MIE_MTIE);
  // enable machine-mode external interrupts. (UART)
  w_mie(r_mie() | MIE_MEIE);
  // enable machine-mode software interrupts.
  w_mie(r_mie() | MIE_MSIE);
}

reg_t trap_handler(reg_t epc, reg_t cause)
{
  reg_t return_pc = epc;
  reg_t cause_code = cause & 0xfff;

  if (cause & 0x80000000)
  {
    /* Asynchronous trap - interrupt */
    switch (cause_code)
    {
    case 3:
      lib_puts("software interruption!\n");
      break;
    case 7:
      lib_puts("timer interruption!\n");
      timer_handler();
      break;
    case 11:
      lib_puts("external interruption!\n");
      uart_isr();
      break;
    default:
      lib_puts("unknown async exception!\n");
      break;
    }
  }
  else
  {
    /* Synchronous trap - exception */
    lib_puts("Sync exceptions!\n");
    // printf("Sync exceptions!, code = %d\n", cause_code);
    // panic("OOPS! What can I do!");
    //return_pc += 4;
  }
  return return_pc;
}

static int timer_count = 0;

void timer_handler()
{
  lib_printf("timer_handler: %d\n", ++timer_count);
  int id = r_mhartid();
  *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + interval;
  //os_kernel();
}
