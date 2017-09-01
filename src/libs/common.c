
#include "common.h"

// 向端口写一个字节
inline void outb(uint16_t port, uint8_t value){
    __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(value));
}

// 从端口读一个字节
inline uint8_t inb(uint16_t port){
    uint8_t value;
    __asm__ __volatile__("inb %1, %0" : "=a"(value) : "dN"(port));
    return value;
}

// 从端口读一个字
inline uint16_t inw(uint16_t port){
    uint16_t value;
    __asm__ __volatile__("inw %1, %0" : "=a"(value) : "dN"(port));
    return value;
}