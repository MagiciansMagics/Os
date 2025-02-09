#include "../Interrupts/idt.h"
#include "../Interrupts/irq.h"
#include "../Interrupts/isr.h"

void main()
{
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");

    for(;;); // does same thing as in halt.asm
}