#include <kernel/tty.h>
#include "interrupt_def.h"

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#ifndef INTERRUPT_HANDLER
#define INTERRUPT_HANDLER

void PIC_EOI(uint8_t irqnum)
void PIC_EOI_spourious(uint8_t irqnum)
void idt_init(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

#endif
