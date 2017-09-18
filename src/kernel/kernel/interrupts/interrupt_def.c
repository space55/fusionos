#include "interrupt_def.h"

//this function is called in all the IRQs
//it will call the corresponding function in the irqfuncs array, as long as it's not NULL (and the interrupt is not spourious)
//if the called function returns a non-NULL pointer, that pointer will be used as a stack to switch the task
//this function correctly acknowledges normal and spourious hardware interrupts
void irqfunc(uint32_t irqnum, void *ctx)
{
	void *stack = NULL;
	if(PIC_isnormalIRQ(irqnum))
	{
		if(irqfuncs[irqnum] != NULL)
			stack = irqfuncs[irqnum](ctx);
		PIC_EOI(irqnum);
		if(stack)
			taskswitch(stack);
	}
	else
	{
		PIC_EOI_spurious(irqnum);
	}
}

//this function is called in all the software interrupts, and in exceptions without error code
//it will call the corresponding function in the intfuncs array, as long as it's not NULL
//if the called function returns a non-NULL pointer, that pointer will be used as a stack to switch the task
void intfunc(uint32_t intnum, void *ctx)
{
	void *stack = NULL;
	if(intfuncs[intnum] != NULL)
		stack = intfuncs[intnum](ctx);
	if(stack)
		taskswitch(stack);
}

//this function is called in exceptions with error code
//it will call the corresponding function in the intfuncs_err array, as long as it's not NULL
//if the called function returns a non-NULL pointer, that pointer will be used as a stack to switch the task
void intfunc_err(uint32_t intnum, void *ctx, uint32_t errcode)
{
	void *stack = NULL;
	if(intfuncs_err[intnum] != NULL)
		stack = intfuncs_err[intnum](ctx, errcode);
	if(stack)
		taskswitch(stack);
}

int PIC_isnormalIRQ(uint8_t irqnum)
{
    if (irqnum == 8 || irqnum == 15)
    {
        return false;
    }
    return true;
}
