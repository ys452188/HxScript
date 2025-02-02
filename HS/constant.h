#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

/* 常量结构 */
typedef struct {
    wchar_t name[128];  // 常量名
    wchar_t type[16];   // 常量类型
    void* address;      // 常量地址
} Constant;

#define CONSTANT_SYMBOL_TABLE_MAX 1024
Constant constantSymbolTable[CONSTANT_SYMBOL_TABLE_MAX];
int constantCount = 0;  // 常量计数
#ifndef __VARIABLE_H__
// 内存分配异常检查
void memoryException(void* pointer) {
    if (pointer == NULL) {
        perror("\33[38;2;255;0;0m错误：内存分配失败！\33[0m\n");
        exit(1);
    }
}
#endif
// 定义常量
void defineConstant(const wchar_t* type, const wchar_t* name, bool hasValue, double value) {
    if (constantCount >= CONSTANT_SYMBOL_TABLE_MAX) {
        perror("\33[38;2;255;0;0m错误：符号表已满！\33[0m\n");
        exit(1);
    }

    Constant newConstant;
    wcsncpy(newConstant.name, name, 127);
    newConstant.name[127] = L'\0';
    wcsncpy(newConstant.type, type, 15);
    newConstant.type[15] = L'\0';

    if (!hasValue) {
        wprintf(L"\33[38;2;255;90;0m警告：常量 %ls 在定义时没有初始化！\33[0m\n", name);
    }

    if (wcscmp(type, L"int") == 0 || wcscmp(type, L"整型") == 0) {
        newConstant.address = malloc(sizeof(int));
        memoryException(newConstant.address);
        *(int*)newConstant.address = hasValue ? (int)value : 0;
    } else if (wcscmp(type, L"double") == 0 || wcscmp(type, L"双精度浮点型") == 0) {
        newConstant.address = malloc(sizeof(double));
        memoryException(newConstant.address);
        *(double*)newConstant.address = hasValue ? value : 0.0;
    } else if (wcscmp(type, L"float") == 0 || wcscmp(type, L"单精度浮点型") == 0) {
        newConstant.address = malloc(sizeof(float));
        memoryException(newConstant.address);
        *(float*)newConstant.address = hasValue ? (float)value : 0.0f;
    } else if (wcscmp(type, L"char") == 0 || wcscmp(type, L"字符型") == 0) {
        newConstant.address = malloc(sizeof(wchar_t));
        memoryException(newConstant.address);
        *(wchar_t*)newConstant.address = hasValue ? (wchar_t)value : L'\0';
    } else {
        wprintf(L"\33[38;2;255;0;0m错误：没有 \"%ls\" 这个类型！\33[0m\n", type);
        exit(1);
    }
    constantSymbolTable[constantCount++] = newConstant;
}
double getConstantValue(const wchar_t* name) {
    for (int i = 0; i < constantCount; i++) {
        if (wcscmp(constantSymbolTable[i].name, name) == 0) {
            if (wcscmp(constantSymbolTable[i].type, L"int") == 0 || wcscmp(constantSymbolTable[i].type, L"整型") == 0) {
                return (double)(*(int*)constantSymbolTable[i].address);
            } else if (wcscmp(constantSymbolTable[i].type, L"double") == 0 || wcscmp(constantSymbolTable[i].type, L"双精度浮点型") == 0) {
                return *(double*)constantSymbolTable[i].address;
            } else if (wcscmp(constantSymbolTable[i].type, L"float") == 0 || wcscmp(constantSymbolTable[i].type, L"单精度浮点型") == 0) {
                return (double)(*(float*)constantSymbolTable[i].address);
            } else if (wcscmp(constantSymbolTable[i].type, L"char") == 0 || wcscmp(constantSymbolTable[i].type, L"字符型") == 0) {
                return (double)(*(wchar_t*)constantSymbolTable[i].address);
            }
        }
    }
    fwprintf(stderr, L"\33[38;2;255;0;0m错误：没有%ls这个变量！\33[0m\n", name);
    exit(1);
}