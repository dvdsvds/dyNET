#include "dynet/dysocket.hpp"
#include "dynet/dysyscall.hpp"

int dy_socket(int domain, int type, int protocol) {
    return dy_syscall(DY_SYS_SOCKET, domain, type, protocol);
}

int dy_bind(int fd, dySocket* addr, unsigned int addrlen) {
    return dy_syscall(DY_SYS_BIND, fd, reinterpret_cast<long>(addr), addrlen);
}

int dy_listen(int fd, int backlog) {
    return dy_syscall(DY_SYS_LISTEN, fd, backlog);
}

int dy_accept(int fd, dySocket* addr, unsigned int* addrlen) {
    return dy_syscall(DY_SYS_ACCEPT, fd, reinterpret_cast<long>(addr), reinterpret_cast<long>(addrlen));
}

int dy_read(int fd, const void* buf, unsigned long size) {
    return dy_syscall(DY_SYS_READ, fd, reinterpret_cast<long>(buf), size);
}

int dy_write(int fd, const void* buf, unsigned long size) {
    return dy_syscall(DY_SYS_WRITE, fd, reinterpret_cast<long>(buf), size);
}

int dy_close(int fd) {
    return dy_syscall(DY_SYS_CLOSE, fd);
}