#include "dynet/dysyscall.hpp"

long dy_syscall(long number) {
    long result;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1) {
    long result;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1, long a2) {
    long result;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1), "S"(a2)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1, long a2, long a3) {
    long result;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1, long a2, long a3, long a4) {
    long result;
    register long r10 asm("r10") = a4;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5) {
    long result;
    register long r10 asm("r10") = a4;
    register long r8 asm("r8") = a5;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
        : "rcx", "r11", "memory"
    );
    return result;
}

long dy_syscall(long number, long a1, long a2, long a3, long a4, long a5, long a6) {
    long result;
    register long r10 asm("r10") = a4;
    register long r8 asm("r8") = a5;
    register long r9 asm("r9") = a6;
    asm volatile (
        "syscall"
        : "=a"(result)
        : "a"(number), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );
    return result;
}