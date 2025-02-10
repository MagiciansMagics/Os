#include "../Interrupts/idt.h"
#include "../Interrupts/irq.h"
#include "../Interrupts/isr.h"

#include "../Include/malloc.h"

void main()
{
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");

    Memory_Init();

    for(;;); // does same thing as in halt.asm
}