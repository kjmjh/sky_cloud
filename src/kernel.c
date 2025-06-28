#include <stdio.h>
#include "memory.h"

void main() {
    printf("sky cloud v0.01 beta\n");
    printf("正在初始化硬件...\n");
    hardware_init();
    printf("正在初始化内存管理器...\n");
    memory_init();
    printf("正在加载主界面...\n");
    command_line_interface();
}