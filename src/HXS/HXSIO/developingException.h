#ifndef __EXCEPTION__
#define __EXCEPTION__
#include <stdio.h>
#include <stdlib.h>
void memoryException_malloc(void* p) {
    if(p == NULL) {
        fwprintf(stderr,L"\033[38;2;255;0;0m错误：内存分配失败！\033[0m\n");
        exit(1);
    }
    return;
}
#endif