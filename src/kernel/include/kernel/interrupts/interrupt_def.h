#include "interrupt_macro.h"
#include "../tasks/tasks.h"

#ifndef INTERRUPT_DEF
#define INTERRUPT_DEF

//IRQs (the 16 IRQs the PIC has)
DEFIRQWRAPPER(0)
DEFIRQWRAPPER(1)
DEFIRQWRAPPER(2)
DEFIRQWRAPPER(3)
DEFIRQWRAPPER(4)
DEFIRQWRAPPER(5)
DEFIRQWRAPPER(6)
DEFIRQWRAPPER(7)
DEFIRQWRAPPER(8)
DEFIRQWRAPPER(9)
DEFIRQWRAPPER(10)
DEFIRQWRAPPER(11)
DEFIRQWRAPPER(12)
DEFIRQWRAPPER(13)
DEFIRQWRAPPER(14)
DEFIRQWRAPPER(15)

//exceptions without error code
DEFINTWRAPPER(0)//division by 0
DEFINTWRAPPER(1)//debug
DEFINTWRAPPER(2)//NMI
DEFINTWRAPPER(3)//breakpoint
DEFINTWRAPPER(4)//INTO
DEFINTWRAPPER(5)//BOUND
DEFINTWRAPPER(6)//invalid opcode
DEFINTWRAPPER(7)//coprocessor not available
DEFINTWRAPPER(9)//coprocessor segment overrun
DEFINTWRAPPER(16)//coprocessor error

//exceptions with error code
DEFINTWRAPPER_ERR(8)//double fault
DEFINTWRAPPER_ERR(10)//TSS error
DEFINTWRAPPER_ERR(11)//segment not present
DEFINTWRAPPER_ERR(12)//stack fault
DEFINTWRAPPER_ERR(13)//general protection fault
DEFINTWRAPPER_ERR(14)//page fault

//software interrupts
DEFINTWRAPPER(0x80)//system call


void *(**irqfuncs)(void *ctx);//array of pointers to functions for the IRQs
void *(**intfuncs)(void *ctx);//array of pointers to functions for the interrupts
void *(**intfuncs_err)(void *ctx, uint32_t errcode);//array of pointers to functions for the exceptions with error code
int PIC_isnormalIRQ(uint8_t irqnum);//handles if IRQ was normal (0) or spurious (1)

#endif
