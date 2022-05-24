MEMORY
{
  rom      (rx)  : ORIGIN = 0x00000000, LENGTH = 0x000A0000
  ram      (rwx) : ORIGIN = 0x02000000, LENGTH = 0x00009000
  app      (rwx) : ORIGIN = 0x02005500, LENGTH = 0x00003A00
}

SECTIONS
{
    .text :
    {
        *(.text.startup.main)
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(.bss*)
    } > app 
}
