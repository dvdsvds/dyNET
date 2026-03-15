#pragma once

#ifdef __x86_64__
    #define DY_SYS_READ   0
    #define DY_SYS_WRITE  1
    #define DY_SYS_CLOSE  3
    #define DY_SYS_SOCKET 41
    #define DY_SYS_ACCEPT 43
    #define DY_SYS_BIND   49
    #define DY_SYS_LISTEN 50
#else
    #error "Unsupported architecture"
#endif

long dy_syscall(long number);
long dy_syscall(long number, long a1);
long dy_syscall(long number, long a1, long a2);
long dy_syscall(long number, long a1, long a2, long a3);
long dy_syscall(long number, long a1, long a2, long a3, long a4);
long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5);
long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5, long a6);