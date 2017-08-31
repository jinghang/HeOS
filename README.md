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

* http://wiki.ubuntu.org.cn/%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F
