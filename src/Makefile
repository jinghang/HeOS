#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm
KERNEL_NAME = he_kernel

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@echo 编译代码文件 $<
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件……
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $(KERNEL_NAME)

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) $(KERNEL_NAME)

.PHONY:update_image
update_image:
	sudo mount disk.img /mnt
	sudo cp $(KERNEL_NAME) /mnt/boot/
	sleep 1
	sudo umount /mnt

.PHONY:mount_image
mount_image:
	sudo mount disk.img /mnt

.PHONY:umount_image
umount_image:
	sudo umount /mnt	

.PHONY:qemu
qemu:
	qemu -hda disk.img

.PHONY:debug
debug:
	qemu -S -s -hda disk.img &
	sleep 1
	cgdb -x scripts/gdbinit