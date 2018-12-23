#ifndef INCLUDE_VMM_H
#define INCLUDE_VMM_H

#include "types.h"
#include "idt.h"
#include "pmm.h"

// 内核的偏移地址
#define PAGE_OFFSET 0xC0000000

#define PAGE_PRESENT 0x1

#define PAGE_WRITE 0x2

#define PAGE_USER 0x4

// 虚拟分页大小
#define PAGE_SIZE 4096

// 页掩码，用与4KB对齐
#define PAGE_MASK 0xFFFFF000

// 获取一个地址的页目录
#define PGD_INDEX(x) (((x) >> 22) & 0x3FF)

// 获取一个地址的页表项
#define PTE_INDEX(x) (((x) >> 12) & 0x3FF)

// 获取一个地址的页内偏移
#define OFFSET_INDEX(x) ((x) & 0xFFF)

// 页目录数据类型
typedef uint32_t pgd_t;

// 页表数据项
typedef uint32_t pte_t;

#endif // INCLUDE_VMM_H