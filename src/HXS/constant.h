#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "HXSIO/developingException.h"
#include "user_code/userCodeInfo.h"
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
/* 常量结构 */
typedef struct {
    wchar_t *name;      // 常量名
    wchar_t *type;      // 常量类型
    void* address;      // 常量地址
} Constant;
#define INITIAL_CAPACITY 1  // 初始符号表容量
Constant* constantSymbolTable = NULL;  // 动态数组
int constantCapacity = 0;  // 当前符号表容量
// **扩容函数**
void expandConstantTable() {
    if (constantCapacity == 0) {
        constantCapacity = INITIAL_CAPACITY;
        constantSymbolTable = (Constant*)malloc(sizeof(Constant) * constantCapacity);
    } else {
        constantCapacity += 1;
        void* temp = (Constant*)realloc(constantSymbolTable, sizeof(Constant) * constantCapacity);
        if (!temp) {
            perror("错误：符号表扩容失败！");
            exit(1);
        }
        constantSymbolTable = (Constant*)temp;
    }
    if (!constantSymbolTable) {
        perror("\33[38;2;255;0;0m错误：符号表扩容失败！\33[0m\n");
        exit(1);
    }
}
// **定义常量**
void defineConstant(const wchar_t* type, const wchar_t* name, bool hasValue, double value) {
    setlocale(LC_ALL,"chinese");
    if (constantCount >= constantCapacity) {
        expandConstantTable();  // 触发扩容
    }
    Constant* newConstant = &constantSymbolTable[constantCount];
    newConstant->name = (wchar_t*)malloc((wcslen(name)+1)*sizeof(wchar_t));
    memoryException_malloc(newConstant->name);
    wcscpy(newConstant->name,name);
    newConstant->type = (wchar_t*)malloc((wcslen(type)+1)*sizeof(wchar_t));
    if(newConstant->type == NULL) {
        free(newConstant->name);
        fwprintf(stderr,L"\033[38;2;255;0;0m错误：内存分配失败！\033[0m\n");
        exit(1);
    }
    wcscpy(newConstant->type,type);
    if (!hasValue) {
        wprintf(L"\33[38;2;255;90;0m警告：常量 %ls 在定义时没有初始化！\33[0m\n", name);
    }
    if (wcscmp(type, L"int") == 0 || wcscmp(type, L"整型") == 0) {
        newConstant->address = malloc(sizeof(int));
        memoryException_malloc(newConstant->address);
        *(int*)newConstant->address = hasValue ? (int)value : 0;
    } else if (wcscmp(type, L"double") == 0 || wcscmp(type, L"双精度浮点型") == 0) {
        newConstant->address = malloc(sizeof(double));
        memoryException_malloc(newConstant->address);
        *(double*)newConstant->address = hasValue ? value : 0.0;
    } else if (wcscmp(type, L"float") == 0 || wcscmp(type, L"单精度浮点型") == 0) {
        newConstant->address = malloc(sizeof(float));
        memoryException_malloc(newConstant->address);
        *(float*)newConstant->address = hasValue ? (float)value : 0.0f;
    } else if (wcscmp(type, L"char") == 0 || wcscmp(type, L"字符型") == 0) {
        newConstant->address = malloc(sizeof(wchar_t));
        memoryException_malloc(newConstant->address);
        *(wchar_t*)newConstant->address = hasValue ? (wchar_t)value : L'\0';
    } else {
        wprintf(L"\33[38;2;255;0;0m错误：没有 \"%ls\" 这个类型！\33[0m\n", type);
        return;
    }
    constantCount++;  // 更新常量计数
}
// **获取常量值**
double getConstantValue(const wchar_t* name) {
    setlocale(LC_ALL,"chinese");
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
    fwprintf(stderr, L"\33[38;2;255;0;0m错误：没有 %ls 这个常量！\33[0m\n", name);
    return -114514.1919810;
}
// **释放符号表内存**
void freeConstantTable() {
    for (int i = 0; i < constantCount; i++) {
        free(constantSymbolTable[i].address);
    }
    free(constantSymbolTable);
}