// THIS SHIT HANDLES EVERY GUI AND EVERYTHING YOU SEE ON SCREEN
#include "./screen.h"
#include "../draw/draw.h"
#include "../../Include/string.h"
#include "../../event_handler/event_handler.h"

uint32_t *VidMem;
uint32_t *BackBuffer;

uint8_t Bpp, PixelStride;
int Pitch;

void screen_init()
{
    /* Convert bits per pixel into bytes per pixel. Take care of 15-bit modes as well */
    PixelStride = (BPP | 7) >> 3;
    /* The pitch is the amount of bytes between the start of each row. This isn't always bytes * width. */
    /* This should work for the basic 16 and 32 bpp modes (but not 24) */
    Pitch = WSCREEN * PixelStride;

    VidMem = ((uint32_t*)0x1028);

    BackBuffer = ((uint32_t*) (AllocateMemory(HSCREEN * Pitch)));
}

void SwapBuffers()
{
	memcpy(VidMem, BackBuffer, HSCREEN * Pitch);
}

void handle_screen()
{
	while(true)
	{
		process_pending_events(process_event);		// please never COMMENT THIS CODE BECAUSE THEN KABOOM

		/*
		 * You should probably implement some sort of FillScreen or FillRect function,
		 * or something that clears the back buffer before drawing. Setting the entire
		 * back buffer to 0 (black) will suffice for a basic system.
		 */
		memset(BackBuffer, 0, HSCREEN * Pitch);

		/* Draw everything: a GUI, windows, other things. This example puts 2 white pixels on the screen. */

		/* When done drawing, swap the buffers and let the user see what you've drawn. */
		SwapBuffers();
	}
}