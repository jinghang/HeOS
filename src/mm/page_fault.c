#include "../include/vmm.h"
#include "../include/debug.h"

void page_fault(pt_regs *regs){
    uint32_t cr2;
	asm volatile ("mov %%cr2, %0" : "=r" (cr2));

    printk("Page fault at 0x%x, virtual faulting address 0x%x\n", regs->eip, cr2);
    printk("Error code: %x\n", regs->err_code);

    //bit 0 为0时，指页面不存在内存里
    if(!(regs->err_code & 0x1)){
        printk_color(background_color_black,foreground_color_red, "Because the page wasn't present.\n");
    }

    //bit 1 为0表示读错误，为1表示写错误
    if(regs->err_code & 0x2){
        printk_color(background_color_black, foreground_color_red, "Write error.\n");
    }else{
        printk_color(background_color_black, foreground_color_red, "Read error.\n");
    }

    // bit 2 为1表示在用户模式下中断， 为0表示在内核模式下中断
    if(regs->err_code & 0x4){
        printk_color(background_color_black, foreground_color_red, "In user mode.\n");
    }else{
        printk_color(background_color_black, foreground_color_red, "In kernel mode.\n");
    }

    // bit 3 为 1 表示错误是由保留为覆盖造成的
    if(regs->err_code & 0x8){
        printk_color(background_color_black, foreground_color_red, "Reserved bits being overwritten.\n");
    }

    // bit 4 为1表示错误发生在取指令的时候
    if(regs->err_code & 0x10){
        printk_color(background_color_black, foreground_color_red, "The fault occured during an instruction fetch.\n");
    }

    while(1);

}