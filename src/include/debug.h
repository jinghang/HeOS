#include "console.h"
#include "vargs.h"

// 内和打印函数
void printk(const char *format, ...);

// 内核打印函数，带颜色
void printk_color(console_background_color_t back, console_foreground_color_t fore, const char *format, ...);