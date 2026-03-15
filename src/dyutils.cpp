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