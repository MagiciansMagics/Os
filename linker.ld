ENTRY(_start)

SECTIONS
{
    . = 0x9000;
    
    .text ALIGN(4K) :
    {
        *(.text*)
    }
    
    .rodata ALIGN(4K) :
    {
        *(.rodata*)
    }
    
    .data ALIGN(4K) :
    {
        *(.data*)
    }
    
    . = 0x200000;

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss*)
    }
}