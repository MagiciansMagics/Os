#include "./ata.h"

void wait_BSY()
{
	while(inb(0x1F7) & STATUS_BSY){;};
}

void wait_DRQ()
{
	while(!(inb(0x1F7) & STATUS_RDY)){;};
}

bool check_ERR()
{
	return ((inb(0x1F7) & STATUS_ERR) != 0);
}