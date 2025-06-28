section .text
    global _start

_start:
    ; 设置段寄存器
    mov ax, 0x07C0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; 显示启动信息
    mov si, boot_msg
    call print_string

    ; 加载内核到内存地址 0x10000
    mov ax, 0x1000
    mov es, ax
    mov bx, 0x0000

    ; 从第一个扇区加载内核
    mov ah, 0x02        ; 读扇区
    mov al, 0x01        ; 读取1个扇区
    mov ch, 0x00        ; 柱面0
    mov cl, 0x02        ; 扇区2
    mov dh, 0x00        ; 磁头0
    mov dl, 0x80        ; 硬盘0

    int 0x13            ; 调用中断

    ; 检查是否加载成功
    jc load_error

    ; 跳转到内核
    jmp 0x1000:0x0000

load_error:
    mov si, load_error_msg
    call print_string
    jmp $

; 打印字符串函数
print_string:
    lodsb
    or al, al
    jz print_done
    mov ah, 0x0E
    int 0x10
    jmp print_string
print_done:
    ret

; 字符串数据
boot_msg: db 'sky cloud (skc) boot loader', 0
load_error_msg: db 'Error loading kernel', 0
times 510-($-$$) db 0
db 0x55, 0xAA