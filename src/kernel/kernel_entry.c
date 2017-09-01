#include "console.h"
#include "common.h"
void printk(char* str);

void kernel_entry(void){
    //printk("Hello World!\n");
    void console_put_char_color("a", background_color_black, foreground_color_green);
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