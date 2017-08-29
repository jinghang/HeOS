#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

CC = gcc
LD = ld

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T kernel.ld -m elf_i386 -nostdlib

all: $(C_OBJECTS) link
.c.o:
	@echo 编译代码文件 $<
	$(CC) $(C_FLAGS) $< -o $@

link:
	@echo 链接内核文件……
	$(LD) $(LD_FLAGS) $(C_OBJECTS) -o Xos

.PHONY:clean
clean:
	$(RM) $(C_OBJECTS) Xos