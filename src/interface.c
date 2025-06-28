#include <stdio.h>

void command_line_interface() {
    printf("sky cloud v0.01 beta\n");
    printf("输入"help"，获取可用命令\n");
    char input[256];
    while (1) {
        printf("skc> ");
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
        process_command(input);
    }
}

void process_command(char *input) {
    char *args[10];
    int arg_count = 0;
    char *token = strtok(input, " \t\n");
    if (token) {
        args[arg_count++] = token;
    }
    while ((token = strtok(NULL, " \t\n")) != NULL) {
        if (arg_count < 10) {
            args[arg_count++] = token;
        }
    }
    args[arg_count] = NULL;

    if (strcmp(args[0], "help") == 0) {
        print_help();
    } else if (strcmp(args[0], "mem") == 0) {
        print_memory_info();
    } else {
        printf("找不到此命令: %s\n", args[0]);
    }
}

void print_help() {
    printf("可用命令\n");
    printf("  help: 查看可用命令信息\n");
    printf("  mem: 查看内存占用\n");
}

void print_memory_info() {
    printf("内存占用:\n");
    for (int i = 0; i < memory_region_count; i++) {
        printf("  区域 %d: 开始 %lu, 结束 %lu\n", i, memory_regions[i].start, memory_regions[i].end);
    }
}