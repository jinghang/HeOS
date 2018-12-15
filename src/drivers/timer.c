
#include "../include/timer.h"
#include "../include/debug.h"
#include "../include/common.h"
#include "../include/idt.h"

void timer_callback(pt_regs *regs){
    static uint32_t tick = 0;
    printk_color(background_color_black, foreground_color_white, "Tick:%d\n", tick++);
}

void init_timer(uint32_t frequency){
    // 注册定时器相关的处理函数
    register_interrupt_handler(IRQ0, timer_callback);

    // Intel 8253/8254 PIT芯片 I/O端口地址范围是40h~43h
	// 输入频率为 1193180，frequency 即每秒中断次数
	uint32_t divisor = 1193180 / frequency;

	// D7 D6 D5 D4 D3 D2 D1 D0
	// 0  0  1  1  0  1  1  0
	// 即就是 36 H
	// 设置 8253/8254 芯片工作在模式 3 下
	outb(0x43, 0x36);

	// 拆分低字节和高字节
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t hign = (uint8_t)((divisor >> 8) & 0xFF);
	
	// 分别写入低字节和高字节
	outb(0x40, low);
	outb(0x40, hign);
}