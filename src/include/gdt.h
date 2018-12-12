#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// 全局描述符类型
typedef struct gdt_entry_t{
    uint16_t limit_low;     // 段界限 0～15 位长
    uint16_t base_low;      // 段及地址 0～15位
    uint8_t base_middle;    // 段基地址 16～23位
    uint8_t access;         // 段存在位、描述符特权级、描述符类型、描述符子类别
    uint8_t granularity;    // 其他标志、段界限16～19
    uint8_t base_high;      // 段基地址 24～31
} __attribute__((packed)) gdt_entry_t;

#endif // INCLUDE_GDT_H_

// GDTR
typedef struct gdt_ptr_t{
    uint16_t limit;          // 全局描述符限长
    uint32_t base;           // 全局描述符表32位基地址
} __attribute__((packed)) gdt_ptr_t;

// 初始化全局描述符表
void init_gdt();

// GDT 加载到 GDTR 的函数（汇编实现）
extern void gdt_flush(uint32_t);