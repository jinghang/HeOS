#include "../include/gdt.h"
#include "../include/string.h"

// 全局描述符表产度
#define GDT_LENGTH 5

// 全局描述符表定义
gdt_entry_t gdt_entries[GDT_LENGTH];
// GDTR
gdt_ptr_t gdt_ptr;

// 设置全局描述符表中的数据
static void set_gdt_entry(int32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// 声明内核栈地质
extern uint32_t stack;

// 初始化全局描述符表
void init_gdt(){
    // set gdtr
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH -1;
    gdt_ptr.base = (uint32_t)&gdt_entries;
    // 设置全局描述符
    set_gdt_entry(0, 0, 0, 0, 0);                  // intel 要求第一个全为0
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // 指令段
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // 数据段
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // 用户模式指令段
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // 用户模式数据段

    // 加载全局表述符表地址及地址上限到GDTR
    gdt_flush((uint32_t)&gdt_ptr);
}

// 全局描述符表构造函数，根据下标构造
// 参数分别是 数组下标、基地址、限长、访问标志，其它访问标志
/* 结构体定义如下：
typedef struct
{
	uint16_t limit_low;     // 段界限   15～0
	uint16_t base_low;      // 段基地址 15～0
	uint8_t  base_middle;   // 段基地址 23～16
	uint8_t  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别
	uint8_t  granularity; 	// 其他标志、段界限 19～16
	uint8_t  base_high;     // 段基地址 31～24
} __attribute__((packed)) gdt_entry_t;
*/
static void set_gdt_entry(int32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entries[index].base_low     = (base & 0xFFFF);
	gdt_entries[index].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[index].base_high    = (base >> 24) & 0xFF;

	gdt_entries[index].limit_low    = (limit & 0xFFFF);
	gdt_entries[index].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[index].granularity |= gran & 0xF0;
	gdt_entries[index].access       = access;
}