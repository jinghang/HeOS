
void printk(char* str);

void kernel_entry(void){
    printk("Hello World!\n");
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