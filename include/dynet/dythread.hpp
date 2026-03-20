#pragma once

#define DY_THREAD_STACK_SIZE (1024 * 1024)

int dy_thread_create(int (*func)(void*), void* arg);