
MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 	; Multiboot 魔数，由规范决定的

MBOOT_PAGE_ALIGN 	equ 	1 << 0    	; 0 号位表示所有的引导模块将按页(4KB)边界对齐
MBOOT_MEM_INFO 		equ 	1 << 1    	; 1 号位通过 Multiboot 信息结构的 mem_* 域包括可用内存的信息
MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

section .init.text

dd MBOOT_HEADER_MAGIC 	; GRUB 会通过这个魔数判断该映像是否支持
dd MBOOT_HEADER_FLAGS   ; GRUB 的一些加载时选项，其详细注释在定义处
dd MBOOT_CHECKSUM       ; 检测数值，其含义在定义处

[GLOBAL start] 	    	; 内核代码入口，此处提供该声明给 ld 链接器
[GLOBAL mboot_ptr_tmp] 	; 全局的 struct multiboot * 变量
[EXTERN kernel_entry] 	; 声明内核 C 代码的入口函数

start:
	cli  		    	 ; 此时还没有设置好保护模式的中断处理，要关闭中断; 所以必须关闭中断
	mov esp, STACK_TOP      ; 设置内核栈地址
	mov ebp, 0 	    	 ; 帧指针修改为 0
	and esp, 0FFFFFFF0H	 ; 栈地址按照16字节对齐
	mov [mboot_ptr_tmp], ebx ; 将 ebx 中存储的指针存入全局变量
	call kernel_entry		 ; 调用内核入口函数
stop:
	hlt 			 ; 停机指令，什么也不做，可以降低 CPU 功耗
	jmp stop 		 ; 到这里结束，关机什么的后面再说

;-----------------------------------------------------------------------------

section .init.data 			 ; 开启分页前临时的数据段
stack: times 1024 db 0
STACK_TOP equ $ -stack -1
mboot_ptr_tmp: dd 0				;全局的 multiboot 数据结构指针
;-----------------------------------------------------------------------------