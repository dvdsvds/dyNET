#pragma once

struct dySocket {
    unsigned short family;
    unsigned short port;
    unsigned int addr;
    char zero[8];
};

int dy_socket(int domain, int type, int protocol);
int dy_bind(int fd, dySocket* addr, unsigned int addrlen);
int dy_listen(int fd, int backlog);
int dy_accept(int fd, dySocket* addr, unsigned int* addrlen);
int dy_read(int fd, const void* buf, unsigned long size);
int dy_write(int fd, const void* buf, unsigned long size);
int dy_close(int fd);
