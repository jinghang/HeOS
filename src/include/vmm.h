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

// 页目录成员数
#define PGD_SIZE (PAGE_SIZE/sizeof(pte_t))

// 页表成员数
#define PTE_SIZE (PAGE_SIZE/sizeof(uint32_t))

// 映射 512MB 内存所需的页
#define PTE_COUNT 128

// 内核页目录区域
extern pgd_t pgd_kern[PGD_SIZE];

// 初始化虚拟内存管理
void init_vmm();

// 更换当前页目录
void switch_pgd(uint32_t pd);

// 把物理地质 pa 映射到虚拟地质 va
void map(pgd_t * pgd_now, uint32_t va, uint32_t pa, uint32_t flags);

// 取消虚拟地质 va 的物理地质映射
void unmap(pgd_t *pgd_now, uint32_t va);

// 如果虚拟地址 va 映射到物理地质，则返回 1
// 同时如果 pa 不是空指针， 则把物理地址写入 pa 参数
uint32_t get_mapping(pgd_t *pgd_now, uint32_t va, uint32_t *pa);

// 页错误中断的函数处理
void page_fault(pt_regs *regs);

#endif // INCLUDE_VMM_H