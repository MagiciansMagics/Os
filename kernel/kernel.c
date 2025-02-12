#include "../Interrupts/idt.h"
#include "../Interrupts/irq.h"
#include "../Interrupts/isr.h"
#include "../Include/malloc.h"
#include "../drivers/keyboard/keyboard.h"
#include "../event_handler/event_handler.h"
#include "../event_handler/event_queue.h"

void main()
{
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");

    Memory_Init();

    InitKeyboard();

    init_event_queue(); // Initialize the event queue

    while (1)
    {
        handle_events();
    }

    for(;;); // does same thing as in halt.asm
}