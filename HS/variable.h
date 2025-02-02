#pragma once
#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
/*by 硫酸铜非常好吃*/
/*变量结构*/
typedef struct {
    wchar_t name[128];         //变量名
    wchar_t type[16];          //变量类型
    void* address;             //变量在内存中的地址
} Variable;
#define VARIABLE_SYMBOL_TABLE_MAX 1024
Variable variableSymbolTable[VARIABLE_SYMBOL_TABLE_MAX];    //符号表
int variableCount = 0;                                      //变量计数
void memoryException(void* pointer         //可能发生异常的指针
                    ) {
    if(pointer == NULL) {
        fwprintf(stderr, L"\33[38;2;255;0;0m错误：内存分配失败！\33[0m\n");
        exit(1);
    }
}
//定义变量的函数
void defineVariable(
    const wchar_t* type,        //变量类型
    const wchar_t* name,        //变量名
    bool hasValue,              //在定义变量时是否提供初始值
    double value                //变量值
) {
    if(variableCount >= VARIABLE_SYMBOL_TABLE_MAX) {
        perror("\33[38;2;255;0;0m错误：符号表已满！\33[0m\n");
        exit(1);
    }
    Variable* newVariable = &variableSymbolTable[variableCount++];  // 直接在表中创建变量
    wcscpy(newVariable->name, name);
    wcscpy(newVariable->type, type);

    if (wcscmp(type, L"int") == 0 || wcscmp(type, L"整型") == 0) {
        newVariable->address = malloc(sizeof(int));
        memoryException(newVariable->address);
        *(int*)newVariable->address = hasValue ? (int)value : 0;
    } else if (wcscmp(type, L"double") == 0 || wcscmp(type, L"双精度浮点型") == 0) {
        newVariable->address = malloc(sizeof(double));
        memoryException(newVariable->address);
        *(double*)newVariable->address = hasValue ? value : 0.0;
    } else if (wcscmp(type, L"float") == 0 || wcscmp(type, L"单精度浮点型") == 0) {
        newVariable->address = malloc(sizeof(float));
        memoryException(newVariable->address);
        *(float*)newVariable->address = hasValue ? (float)value : 0.0f;
    } else if (wcscmp(type, L"char") == 0 || wcscmp(type, L"字符型") == 0) {
        newVariable->address = malloc(sizeof(wchar_t));
        memoryException(newVariable->address);
        *(wchar_t*)newVariable->address = hasValue ? (wchar_t)value : L'\0';
    } else {
        fwprintf(stderr, L"\33[38;2;255;0;0m错误：没有\"%ls\"这个类型！\33[0m\n", type);
        exit(1);
    }
}
//赋值的函数
void assignment(const wchar_t* variable_name,     //目标变量的变量名
                const double value                //所赋的值
               ) {
    for(int i = 0; i < variableCount; i++) {
        //在符号表中查找目标变量
        if(wcscmp(variableSymbolTable[i].name, variable_name) == 0) {
            //确定目标变量的类型
            if(wcscmp(variableSymbolTable[i].type,L"int") == 0 || wcscmp(variableSymbolTable[i].type,L"整型") == 0 ) {
                *(int*)variableSymbolTable[i].address = (int)value;
                return;
            } else if(wcscmp(variableSymbolTable[i].type,L"double") == 0 || wcscmp(variableSymbolTable[i].type,L"双精度浮点型") == 0 ) {
                *(double*)variableSymbolTable[i].address = (double)value;
            } else if(wcscmp(variableSymbolTable[i].type,L"float") == 0 || wcscmp(variableSymbolTable[i].type,L"单精度浮点型") == 0 ) {
                *(float*)variableSymbolTable[i].address = (float)value;
            } else if(wcscmp(variableSymbolTable[i].type,L"char") == 0 || wcscmp(variableSymbolTable[i].type,L"字符型") == 0 ) {
                *(wchar_t*)variableSymbolTable[i].address = (wchar_t)value;
            }  else {
                wprintf(L"\33[38;2;255;0;0m错误：无法确定变量%ls的类型！\33[0m\n",variable_name);
                exit(1);
            }
            return;
        }
    }
    wprintf(L"\33[38;2;255;0;0m错误：变量%ls未定义！您可能真的没有定义%ls这个变量 或将%ls定义为一个常量,但常量无法赋值！\33[0m\n",
            variable_name,
            variable_name,
            variable_name);
    exit(1);
}
double getVariableValue(const wchar_t* name) {
    for (int i = 0; i < variableCount; i++) {
        if (wcscmp(variableSymbolTable[i].name, name) == 0) {
            if (wcscmp(variableSymbolTable[i].type, L"int") == 0 || wcscmp(variableSymbolTable[i].type, L"整型") == 0) {
                return (double)(*(int*)variableSymbolTable[i].address);
            } else if (wcscmp(variableSymbolTable[i].type, L"double") == 0 || wcscmp(variableSymbolTable[i].type, L"双精度浮点型") == 0) {
                return *(double*)variableSymbolTable[i].address;
            } else if (wcscmp(variableSymbolTable[i].type, L"float") == 0 || wcscmp(variableSymbolTable[i].type, L"单精度浮点型") == 0) {
                return (double)(*(float*)variableSymbolTable[i].address);
            } else if (wcscmp(variableSymbolTable[i].type, L"char") == 0 || wcscmp(variableSymbolTable[i].type, L"字符型") == 0) {
                return (double)(*(wchar_t*)variableSymbolTable[i].address);
            }
        }
    }
    fwprintf(stderr, L"\33[38;2;255;0;0m错误：没有%ls这个变量！\33[0m\n", name);
    exit(1);
}
#endif