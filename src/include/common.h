#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include "types.h"

// 向端口写一个字节
void outb(uint16_t port, uint8_t value);

// 从端口读一个字节
uint8_t inb(uint16_t port);

// 从端口读一个字
uint16_t inw(uint16_t port);


#endif // INCLUDE_COMMON_H