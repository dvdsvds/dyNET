#pragma once

unsigned short dy_htons(unsigned short port);
void dy_strcat(char* dst, int& dst_len, const char* src);
void dy_strcpy(char* dst, const char* src);
void dy_itoa(int num, char* buf);