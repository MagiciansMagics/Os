#include "../Interrupts/idt.h"
#include "../Interrupts/irq.h"
#include "../Interrupts/isr.h"
#include "../graphics/screen/screen.h"

void main()
{
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");

    Memory_Init();

    InitKeyboard();

    screen_init();

    handle_screen();

    for(;;); // does same thing as in halt.asm
}