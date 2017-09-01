#include "console.h"
#include "common.h"

// 显卡地址
static uint16_t *video_memory = (uint16_t *)0xb8000;

// 屏幕光标位置
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

inline uint16_t get_color_attribute(console_foreground_color_t foreground_color, console_background_color_t background_color){
    return ((((uint8_t)background_color) << 4) | ((uint8_t)foreground_color)) << 8;
}

// 清屏
void console_clear(){
    //
}

// 屏幕输出一个字符，带颜色
void console_put_char_color(char c, console_foreground_color_t foreground_color, console_background_color_t background_color){
    // 构造颜色信息
    uint16_t color_attribute = get_color_attribute(foreground_color,background_color);

    if(c == 0x08){
        cursor_x--;
    }else if(c == 0x09){
        cursor_x = (cursor_x+4) & ~(8-1);
    }else if(c == '\r'){
        cursor_x = 0;
    }else if(c == '\n'){
        cursor_x = 0;
        cursor_y++;
    }else if(c >= ' '){
        video_memory[cursor_y * 80 + cursor_x] = c | color_attribute;
    }

    // 换行
    if(cursor_x >= 80){
        cursor_x = 0;
        cursor_y++;
    }
}

// 屏幕输出一个以\0结尾德字符窜，默认黑底白字
void console_write(char* str){
    //
}

// 屏幕输出一个以\0结尾德字符窜，带颜色
void console_write_color(char* str, console_foreground_color_t foreground_color, console_background_color_t background_color){
    //
}

// 屏幕输出一个十六禁止的整数
void console_write_hex(uint32_t num, console_foreground_color_t foreground_color, console_background_color_t background_color){
    //
}

// 屏幕输出一个十进制的整数
void console_write_dec(uint32_t num, console_foreground_color_t foreground_color, console_background_color_t background_color){
    //
}
