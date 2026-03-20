#include "dynet/dyutils.hpp"

unsigned short dy_htons(unsigned short port) {
    return (port >> 8) | (port << 8);
}

void dy_strcpy(char* dst, const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

void dy_strcat(char* dst, int& dst_len, const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dst[dst_len] = src[i];
        dst_len++;
        i++;
    }
}

void dy_itoa(int num, char* buf) {
    int i = 0;
    while(num > 0) {
        buf[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    int left = 0;
    int right = i - 1;
    while(left < right) {
        char tmp = buf[left];
        buf[left] = buf[right];
        buf[right] = tmp;
        left++;
        right--;
    }
    buf[i] = '\0';
}

void* dy_malloc(unsigned long size) {
    return reinterpret_cast<void*>(dy_syscall(
        DY_SYS_MMAP, 
        0, 
        static_cast<long>(size), 
        3,
        34, 
        -1, 
        0
    )
    );
}

void dy_free(void* ptr, unsigned long int size) {
    dy_syscall(DY_SYS_MUNMAP, reinterpret_cast<long>(ptr), static_cast<long>(size));
}

void* dy_realloc(void* ptr, unsigned long old_size, unsigned long new_size) {
    void* new_ptr = dy_malloc(new_size);

    char* src = reinterpret_cast<char*>(ptr);
    char* dst = reinterpret_cast<char*>(new_ptr);
    for(unsigned long i = 0; i < old_size; i++) {
        dst[i] = src[i];
    }

    dy_free(ptr, old_size);

    return new_ptr;
}

bool dy_strcmp(const char* a, const char* b) {
    while(*a != '\0' && *b != '\0') {
        if(*a != *b) return false;
        a++;
        b++;
    }
    return *a == *b;
}