
#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

#include "console.h"
#include "vargs.h"
#include "elf.h"

#define assert(x, info)       \
    do{                       \
        if(!(x)){             \
            panic(info);      \
        }                     \
    }while(0)

// 编译期间静态检测
#define static _assert(x) switch(x){case 0: case (x): ;}

// 初始化 debug 信息
void init_debug();

// 打印当前的函数调用栈
void panic(const char *msg);

// 打印当前的段寄存器的值
void print_cur_status();


// 内和打印函数
void printk(const char *format, ...);

// 内核打印函数，带颜色
void printk_color(console_background_color_t back, console_foreground_color_t fore, const char *format, ...);

#endif // INCLUDE_DEBUG_H