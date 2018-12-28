
#include "../include/gdt.h"
#include "../include/console.h"
#include "../include/debug.h"
#include "../include/idt.h"
#include "../include/timer.h"
#include "../include/pmm.h"
#include "../include/vmm.h"

// 内核初始化
void kernel_init();

// 开启分页机制之后， multiboot 数据指针
multiboot_t *glb_mboot_ptr;

// 开启分页机制之后的内核栈
char kern_stack[STACK_SIZE];

// 内核使用的临时页表
__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_high =(pgd_t *)0x3000;

// 内核入口函数
__attribute__((section(".init.text"))) void kernel_entry(){
    //
    pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
    pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high | PAGE_PRESENT | PAGE_WRITE;

    // 映射 0x00000000-0x00400000 的物理地址到虚拟地址 0xC0000000-0xC0400000
    for(int i = 0; i < 1024; i++){
        uint32_t addr = i << 12;
        pte_low[i] = addr | PAGE_PRESENT | PAGE_WRITE;
        pte_high[i] = addr | PAGE_PRESENT | PAGE_WRITE;
    }

    //设置临时页表
    asm volatile("mov %0, %%cr3" : : "r"(pgd_tmp));

    uint32_t cr0;
    // 启用分页，将 cr0 寄存器的分页位置为 1 就好
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" : : "r" (cr0));

    // 切换内核栈
    uint32_t kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE) & 0xFFFFFFF0;
    asm volatile ("mov %0, %%esp\n\t"
			"xor %%ebp, %%ebp" : : "r" (kern_stack_top));
    
    // 更新全局 multiboot_t 指针
    glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

    // 调用内核初始化函数
    kernel_init();
}

void kernel_init(){
    
    init_debug();
    init_gdt();
    init_idt();
    
    console_clear();
    printk_color(background_color_black, foreground_color_green, "Hello HeOS kernel!\n");
    //panic("test");

    // asm volatile("int $0x03");
    // asm volatile("int $0x04");
    // asm volatile("int $0xff");

    init_timer(100);
    // 开启中断
    //asm volatile("sti");

    printk("\n\n");
    printk("kernel in memory start: 0x%08X\n", kern_start);
    printk("kernel im memory end:   0x%08X\n", kern_end);
    printk("kenrel in memory used:  %dKB\n\n", (kern_end - kern_start + 1023)/1024);

    show_memory_map();
    init_pmm();
    printk_color(background_color_black, foreground_color_red, "\nThe count of physical memeory page is: %u\n\n", phy_page_count);
    uint32_t allc_addr = NULL;
    printk_color(background_color_black, foreground_color_brown, "The physical memory alloc: \n");
    allc_addr = pmm_alloc_page();
    printk_color(background_color_black, foreground_color_brown, "Alloc physical addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(background_color_black, foreground_color_brown, "Alloc physical addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(background_color_black, foreground_color_brown, "Alloc physical addr: 0x%08X\n", allc_addr);
    allc_addr = pmm_alloc_page();
    printk_color(background_color_black, foreground_color_brown, "Alloc physical addr: 0x%08X\n", allc_addr);

    
    while(1){
        asm volatile("hlt");
    }
}