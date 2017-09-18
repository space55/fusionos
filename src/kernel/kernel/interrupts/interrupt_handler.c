#include "interrupt_handler.h"

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

    // IDT for keyboard
    keyboard_address = (unsigned long) keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	// ICW1 to begin initialization
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	// ICW2
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	// ICW3
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

    // ICW4, which is the environment info
    write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
    // Initialization finished

	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void PIC_EOI(uint8_t irqnum)
{
    // Apparently an interrupt happened
	printf("An interrupt happened! id=" + irqnum + "\n");
}

void PIC_EOI_spourious(uint8_t irqnum)
{
    // A spurious interrupt happened!
	printf("A spurous interrupt happened! id=" + irqnum + "\n");
}

void init()
{
    fillidte(idt+32, 8, irq0handler(), 0xe, 0);//IRQ handlers
    fillidte(idt+33, 8, irq1handler(), 0xe, 0);
    fillidte(idt+34, 8, irq2handler(), 0xe, 0);
    fillidte(idt+35, 8, irq3handler(), 0xe, 0);
    fillidte(idt+36, 8, irq4handler(), 0xe, 0);
    fillidte(idt+37, 8, irq5handler(), 0xe, 0);
    fillidte(idt+38, 8, irq6handler(), 0xe, 0);
    fillidte(idt+39, 8, irq7handler(), 0xe, 0);
    fillidte(idt+40, 8, irq8handler(), 0xe, 0);
    fillidte(idt+41, 8, irq9handler(), 0xe, 0);
    fillidte(idt+42, 8, irq10handler(), 0xe, 0);
    fillidte(idt+43, 8, irq11handler(), 0xe, 0);
    fillidte(idt+44, 8, irq12handler(), 0xe, 0);
    fillidte(idt+45, 8, irq13handler(), 0xe, 0);
    fillidte(idt+46, 8, irq14handler(), 0xe, 0);
    fillidte(idt+47, 8, irq15handler(), 0xe, 0);

    fillidte(idt+0, 8, int0handler(), 0xe, 0);//exception handlers
    fillidte(idt+1, 8, int1handler(), 0xe, 0);
    fillidte(idt+2, 8, int2handler(), 0xe, 0);
    fillidte(idt+3, 8, int3handler(), 0xe, 0);
    fillidte(idt+4, 8, int4handler(), 0xe, 0);
    fillidte(idt+5, 8, int5handler(), 0xe, 0);
    fillidte(idt+6, 8, int6handler(), 0xe, 0);
    fillidte(idt+7, 8, int7handler(), 0xe, 0);
    fillidte(idt+8, 8, int8handler(), 0xe, 0);
    fillidte(idt+9, 8, int9handler(), 0xe, 0);
    fillidte(idt+10, 8, int10handler(), 0xe, 0);
    fillidte(idt+11, 8, int11handler(), 0xe, 0);
    fillidte(idt+12, 8, int12handler(), 0xe, 0);
    fillidte(idt+13, 8, int13handler(), 0xe, 0);
    fillidte(idt+14, 8, int14handler(), 0xe, 0);
    fillidte(idt+16, 8, int16handler(), 0xe, 0);

    fillidte(idt+0x80, 8, int0x80handler(), 0xe, 3);//system call handler
}
