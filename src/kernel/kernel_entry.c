#include "console.h"
#include "common.h"
#include "string.h"

void printk(char* str);

void kernel_entry(void){
    //printk("Hello World!\n");
    //console_put_char_color('a', foreground_color_green, background_color_black);
    console_write_color("Hello World!",foreground_color_green,background_color_black);
    console_write("\n");
    console_write_dec(10,foreground_color_green, background_color_black);
    console_write("\n");
    console_write_hex(10,foreground_color_green, background_color_black);
    return;
}

void printk(char* str){
    char *pvideo = (char*)0xB8000;
    while(*str != '\n'){
        *pvideo++ = *str++;
        *pvideo++ = 0x04;
    }
    return;
}