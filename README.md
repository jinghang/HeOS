# HeOS
* 将源码编译成汇编
```
gcc -S multboot.c
```

* 反汇编 obj 文件
```
objdump -d multboot.o
```

* 生成 汇编 lst 文件
```
name -f elf boot.asm -l boot lst
```
