#include <stdio.h>
//#include <sys/time.h>

#include <kernel/tty.h>

#include <kernel/tasks/tasks.h>
#include <kernel/interrupts/interrupt_handler.h>

void kernel_main(void) {
	terminal_initialize();
	printf("fusionOS v0.0.1\n");
	printf("Written by Eamonn Nugent\n");
    idt_init();

    for (;;);
}
