#ifndef INCLUDE_CONSOLE_H
#define INCLUDE_CONSOLE_H

#include "types.h"

// 控制台背景色
typedef enum _console_background_color_t {

    background_color_black  =   0b0000, // 黑
    background_color_blue   =   0b0001, // 蓝
    background_color_green  =   0b0010, // 绿
    background_color_cyan   =   0b0011, // 青
    background_color_red    =   0b0100, // 红
    background_color_magenta=   0b0101, // 品红
    background_color_brown  =   0b0110, // 棕
    background_color_white  =   0b0111  // 白

} console_background_color_t;

// 控制台前景色
typedef enum _console_foreground_color_t {

    foreground_color_black  =   0b0000, // 黑
    foreground_color_blue   =   0b0001, // 蓝
    foreground_color_green  =   0b0010, // 绿
    foreground_color_cyan   =   0b0011, // 青
    foreground_color_red    =   0b0100, // 红
    foreground_color_magenta=   0b0101, // 品红
    foreground_color_brown  =   0b0110, // 棕
    foreground_color_white  =   0b0111, // 灰白

    foreground_color_light_black  =   0b1000, // 灰
    foreground_color_light_blue   =   0b1001, // 浅蓝
    foreground_color_light_green  =   0b1010, // 浅绿
    foreground_color_light_cyan   =   0b1011, // 浅青
    foreground_color_light_red    =   0b1100, // 浅红
    foreground_color_light_magenta=   0b1101, // 浅品红
    foreground_color_light_brown  =   0b1110, // 黄
    foreground_color_light_white  =   0b1111  // 白

} console_foreground_color_t;

// 清屏
void console_clear();

uint16_t get_color_attribute(console_foreground_color_t foreground_color, console_background_color_t background_color);

// 屏幕输出一个字符，带颜色
void console_put_char_color(char c, console_foreground_color_t foreground_color, console_background_color_t background_color);

// 屏幕输出一个以\0结尾德字符窜，默认黑底白字
void console_write(char* str);

// 屏幕输出一个以\0结尾德字符窜，带颜色
void console_write_color(char* str, console_foreground_color_t foreground_color, console_background_color_t background_color);

// 屏幕输出一个十六禁止的整数
void console_write_hex(uint32_t num, console_foreground_color_t foreground_color, console_background_color_t background_color);

// 屏幕输出一个十进制的整数
void console_write_dec(uint32_t num, console_foreground_color_t foreground_color, console_background_color_t background_color);

#endif