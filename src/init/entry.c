
#include "../include/gdt.h"
#include "../include/console.h"
#include "../include/debug.h"
#include "../include/idt.h"

int kernel_entry(){
    
    init_debug();
    init_gdt();
    init_idt();
    
    console_clear();
    printk_color(background_color_black, foreground_color_green, "Hello HeOS kernel!\n");
    //panic("test");

    asm volatile("int $0x03");
    asm volatile("int $0x04");
    asm volatile("int $0xff");
    
    return 0;
}