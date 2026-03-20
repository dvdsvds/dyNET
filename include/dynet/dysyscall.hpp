#pragma once

#ifdef __x86_64__
    #define DY_SYS_READ   0
    #define DY_SYS_WRITE  1
    #define DY_SYS_CLOSE  3
    #define DY_SYS_MMAP   9
    #define DY_SYS_MUNMAP 11
    #define DY_SYS_SOCKET 41
    #define DY_SYS_ACCEPT 43
    #define DY_SYS_BIND   49
    #define DY_SYS_LISTEN 50
    #define DY_SYS_CLONE  56
    #define DY_SYS_FORK   57
    #define DY_SYS_EXIT   60
#else
    #error "Unsupported architecture"
#endif

enum CloneFlags {
    CLONE_VM              = 0x100,
    CLONE_FS              = 0x200,
    CLONE_FILES           = 0x400,
    CLONE_SIGHAND         = 0x800,
    CLONE_THREAD          = 0x10000,
    CLONE_SYSVSEM         = 0x40000,
    CLONE_SETTLS          = 0x80000,
    CLONE_PARENT_SETTID   = 0x100000,
    CLONE_CHILD_CLEARTID  = 0x200000,
};

long dy_syscall(long number);
long dy_syscall(long number, long a1);
long dy_syscall(long number, long a1, long a2);
long dy_syscall(long number, long a1, long a2, long a3);
long dy_syscall(long number, long a1, long a2, long a3, long a4);
long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5);
long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5, long a6);