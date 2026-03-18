#pragma once
#include "dysyscall.hpp"

unsigned short dy_htons(unsigned short port);
void dy_strcat(char* dst, int& dst_len, const char* src);
void dy_strcpy(char* dst, const char* src);
void dy_itoa(int num, char* buf);
void* dy_malloc(unsigned long size);
void dy_free(void* ptr, unsigned long int size);
void* dy_realloc(void* ptr, unsigned long old_size, unsigned long new_size);
bool dy_strcmp(const char* a, const char* b);