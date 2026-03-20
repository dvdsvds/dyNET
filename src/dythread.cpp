#include "dynet/dythread.hpp"
#include "dynet/dyutils.hpp"
#include "dynet/dysyscall.hpp"
#include "dynet/dysocket.hpp"

int dy_thread_create(int (*func)(void*), void* arg) {
    // void* stack = dy_malloc(DY_THREAD_STACK_SIZE);
    // void* stack_top = reinterpret_cast<char*>(stack) + DY_THREAD_STACK_SIZE;

    // long flags = CLONE_VM | CLONE_FILES | CLONE_SIGHAND | CLONE_SYSVSEM;
    // long pid = dy_syscall(DY_SYS_CLONE, flags, (long)stack_top, 0, 0, 0);
    long pid = dy_syscall(57);
    if(pid == 0) {
        func(arg);
        dy_syscall(DY_SYS_EXIT, 0);
    } 
    return static_cast<int>(pid);
}