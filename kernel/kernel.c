#include "../graphics/screen/screen.h"
#include "../Interrupts/idt.h"
#include "../Interrupts/irq.h"
#include "../Interrupts/isr.h"
#include "../Include/malloc.h"
#include "../filesystem/filesystem.h"
#include "../Include/time.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/mouse/mouse.h"
#include "../event_handler/event_handler.h"
#include "../event_handler/event_queue.h"

void main()
{
    idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");

    init_filesystem();

    init_screen(); // DO NOT TRY TO PRINT BEFORE THIS FUNCTION IS EXECUTED

    time_init();

    Memory_Init();

    InitKeyboard();

    init_mouse();

    init_event_queue(); // Initialize the event queue

    print("Command: ");

    while (1)
    {
        handle_events();
    }

    for(;;); // does same thing as in halt.asm
}