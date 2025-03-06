#include "./time.h"

int timer_ticks = 0;
int seconds = 0;

void timer_phase(int hz)
{
	int divisor = 1193180 / hz;	   /* Calculate our divisor */
	outb(0x43, 0x36);			 /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outb(0x40, divisor >> 8);	 /* Set high byte of divisor */
}

void timer_handler(regs *r)
{
	timer_ticks++;
	

	if (timer_ticks % 18 == 0)
	{
		seconds++;
	}
}


void sleep(int milliseconds) 
{
    int startTicks = timer_ticks;
    int targetTicks = startTicks + (milliseconds * 10 / 1000);
    
    while (timer_ticks < targetTicks) 
	{
        asm volatile("hlt");
    }
}

void time_init()
{
	irq_install_handler(0, timer_handler);
}