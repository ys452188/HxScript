#ifndef __LEVER_H__
#define __LEVER_H__
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "HXS/variable.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
wchar_t* deleteSpaceAndTab(const wchar_t* s) {
    setlocale(LC_ALL,"chinese");
    if (s == NULL) return NULL; // 先检查 NULL
    size_t len = wcslen(s);
    wchar_t* result = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    if (result == NULL) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }
    wchar_t* p = result;
    const wchar_t* q = s; // 使用 `q` 遍历，避免修改原始指针
    while (*q) {
        if (*q != L' ' && *q != L'\t') {
            *p++ = *q;
        }
        q++;
    }
    *p = L'\0';  // 终止字符串
    return result;
}
bool isChar(const wchar_t* s) {
    wchar_t* s1 = wcsdup(s);
    if(s1 == NULL) {
        return false;
    }

    if(wcslen(s1) != 3) { // 格式：'c'，字符长度为3（包括两边的引号）
        free(s1);
        return false;
    }

    const wchar_t* p = s1;
    if (*p != L'\'') {  // 检查第一个字符是不是单引号
        free(s1);
        return false;
    }

    p++;  // 移动到字符部分
    if (*p == L'\'') { // 单引号内没有字符
        free(s1);
        return false;
    }

    if (*(p + 1) != L'\'') {  // 检查字符后是否是单引号
        free(s1);
        return false;
    }

    free(s1);
    return true;
}

wchar_t getWChar(const wchar_t* s) {
    // 提取并返回字符（单引号内的字符）
    return s[1];  // 假设字符串格式是 'c'，返回 'c'
}

bool isInter(const wchar_t* s) {
    wchar_t* s1 = deleteSpaceAndTab(s);
    if (s1 == NULL) {
        return false;
    }
    const wchar_t* p = s1;
    while (*p) {
        if (!(*p >= L'0' && *p <= L'9')) {
            free(s1);
            return false;
        }
        p++;
    }
    free(s1);
    return true;
}
bool isFloat(const wchar_t* s) {
    setlocale(LC_ALL,"chinese");
    wchar_t* s1 = deleteSpaceAndTab(s);
    if (s1 == NULL) {
        return false;
    }
    const wchar_t *p = s1;
    int pointCount = 0;
    while (*p) {
        if (*p == L'.') {
            pointCount++;
        }
        p++;
    }
    if (pointCount == 0) {
        free(s1);
        return false;
    } else if (pointCount == 1) {
        // 找到小数点
        wchar_t *dot = wcsstr(s1, L".");
        if (dot == s1) {  // 小数点不能是第一个字符
            fwprintf(stderr, L"\33[38;2;255;0;0m错误：%ls不属于任何类型！\33[0m\n", s1);
            free(s1);
            exit(1);
        }
        else if (dot > s1) {  // 先检查是否有效
            dot--;
            if (*dot >= L'0' && *dot <= L'9') {
                free(s1);
                return true;
            }
        } else {
            fwprintf(stderr, L"\33[38;2;255;0;0m错误：%ls不属于任何类型！\33[0m\n", s1);
            free(s1);
            exit(1);
        }
    } else {
        fwprintf(stderr, L"\33[38;2;255;0;0m错误：%ls不属于任何类型！\33[0m\n", s1);
        free(s1);
        exit(1);
    }
    return false;
}
/*定义变量的语句：var a: int = 0; 定义变量 变量 : int = 114;*/
bool leverDefineVariable(const wchar_t* command) {
    setlocale(LC_ALL,"chinese");
    if (command == NULL) {
        return false;
    }
    wchar_t* command1 = wcsdup(command);  // 复制字符串，避免修改原始数据
    if (command1 == NULL) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }
    wchar_t* p = command1;  // 指针 p 用于遍历
    // 跳过前导空格和Tab
    while (*p == L' ' || *p == L'\t') {
        p++;
    }
    // 检查是否是 "var "
    if (wcslen(p) >= 3 && p[0] == L'v' && p[1] == L'a' && p[2] == L'r' &&
            (p[3] == L' ' || p[3] == L'\t')) {
        p += 3;  // 跳过 "var"
        if(p == NULL||*p == L'\0') {
            return false;
        }
        // 跳过 "var" 后的空格
        while (*p == L' ' || *p == L'\t') {
            p++;
        }
        if (*p == L'\0') {
            fwprintf(stderr, L"错误：未指定变量名！\033[0m\n");
            free(command1);
            exit(1);
        }
        wchar_t* nameB = p;  // 变量名起始位置
        // 找到变量名的终点
        while (*p && *p != L' ' && *p != L'\t' && *p != L':') {
            p++;
        }
        size_t nameLen = p - nameB;
        wchar_t* name = (wchar_t*)malloc((nameLen + 1) * sizeof(wchar_t));
        if (name == NULL) {
            fwprintf(stderr, L"内存分配失败\n");
            free(command1);
            exit(1);
        }
        wcsncpy(name, nameB, nameLen);
        name[nameLen] = L'\0';
        wprintf(L"name: %ls\n", name);

        // 提取类型，要求后面有冒号
        wchar_t* colonPos = wcsstr(p, L":");
        if (colonPos == NULL) {
            fwprintf(stderr, L"\33[38;2;255;0;0m错误：未指定变量类型\33[0m\n");
            free(name);
            free(command1);
            exit(1);
        }
        colonPos++;  // 跳过冒号
        // 跳过冒号后的空格
        while (*colonPos == L' ' || *colonPos == L'\t') {
            colonPos++;
        }
        wchar_t* typeB = colonPos;
        // 以空格、Tab 或 '=' 为结束标志
        while (*colonPos && *colonPos != L' ' && *colonPos != L'\t' && *colonPos != L'=') {
            colonPos++;
        }
        size_t typeLen = colonPos - typeB;
        wchar_t* type = (wchar_t*)malloc((typeLen + 1) * sizeof(wchar_t));
        if (type == NULL) {
            fwprintf(stderr, L"内存分配失败\n");
            free(name);
            free(command1);
            exit(1);
        }
        wcsncpy(type, typeB, typeLen);
        type[typeLen] = L'\0';
        wprintf(L"type: %ls\n", type);
        // 判断是否提供初始值
        double value = 0;
        wchar_t* equalPos = wcsstr(p, L"=");
        if (equalPos != NULL) {
            equalPos++;  // 跳过 '='
            while (*equalPos == L' ' || *equalPos == L'\t') {
                equalPos++;
            }
            if (*equalPos == L'\0') {
                fwprintf(stderr, L"\033[38;2;255;0;0m错误：\"=\"后未指定初始值！\033[0m\n");
                free(type);
                free(name);
                free(command1);
                exit(1);
            }
            // 提取初始值字符串直到遇到分隔符（例如空格或分号）或字符串末尾
            wchar_t* valueStart = equalPos;
            while (*equalPos && *equalPos != L' ' && *equalPos != L'\t' && *equalPos != L';') {
                equalPos++;
            }
            size_t valueLen = equalPos - valueStart;
            wchar_t* valueString = (wchar_t*)malloc((valueLen + 1) * sizeof(wchar_t));
            if (valueString == NULL) {
                fwprintf(stderr, L"内存分配失败\n");
                free(type);
                free(name);
                free(command1);
                exit(1);
            }
            wcsncpy(valueString, valueStart, valueLen);
            valueString[valueLen] = L'\0';
            wchar_t* cleanValue = wcsdup(valueString);
            free(valueString);
            while(*cleanValue == L' ') {
                cleanValue++;
            }


            wprintf(L"%ls\n",cleanValue);


            // 转换字符串到数值
            printf("%d\n",isChar(cleanValue));


            if (isChar(cleanValue)) {
                value = (double)getWChar(cleanValue);
            } else {
                cleanValue = deleteSpaceAndTab(cleanValue);
                if (isFloat(cleanValue)) {
                    value = wcstod(cleanValue, NULL);
                } else if (isInter(cleanValue)) {
                    value = (double)wcstol(cleanValue, NULL, 10);
                } else {
                    fwprintf(stderr, L"错误：初始值格式不正确！\n");
                    free(cleanValue);
                    free(type);
                    free(name);
                    free(command1);
                    exit(1);
                }
            }
            free(cleanValue);
            // 调用定义变量的接口
            defineVariablePlus(type, name, true, value);
        } else {
            // 没有初始值，调用定义变量接口（默认值为0）
            defineVariablePlus(type, name, false, 0);
        }
        free(type);
        free(name);
        free(command1);
        return true;
    }
    // 检查是否是 "定义变量"
    if (wcslen(p) >= 4 && p[0] == L'定' && p[1] == L'义' && p[2] == L'变' && p[3] == L'量'
            && (p[4] == L' ' || p[4] == L'\t')) {
        p += 4;  // 跳过
        if(p == NULL || *p == L'\0') {
            return false;
        }
        // 跳过空格
        while (*p == L' ' || *p == L'\t') {
            p++;
        }
        if (*p == L'\0') {
            fwprintf(stderr, L"错误：未指定变量名！\033[0m\n");
            free(command1);
            exit(1);
        }
        wchar_t* nameB = p;  // 变量名起始位置
        // 找到变量名的终点
        while (*p && *p != L' ' && *p != L'\t' && *p != L':') {
            p++;
        }
        size_t nameLen = p - nameB;
        wchar_t* name = (wchar_t*)malloc((nameLen + 1) * sizeof(wchar_t));
        if (name == NULL) {
            fwprintf(stderr, L"内存分配失败\n");
            free(command1);
            exit(1);
        }
        wcsncpy(name, nameB, nameLen);
        name[nameLen] = L'\0';
        wprintf(L"name: %ls\n", name);
        // 提取类型，要求后面有冒号
        wchar_t* colonPos = wcsstr(p, L":");
        if (colonPos == NULL) {
            fwprintf(stderr, L"\33[38;2;255;0;0m错误：未指定变量类型\33[0m\n");
            free(name);
            free(command1);
            exit(1);
        }
        colonPos++;  // 跳过冒号
        // 跳过冒号后的空格
        while (*colonPos == L' ' || *colonPos == L'\t') {
            colonPos++;
        }
        wchar_t* typeB = colonPos;
        // 以空格、Tab 或 '=' 为结束标志
        while (*colonPos && *colonPos != L' ' && *colonPos != L'\t' && *colonPos != L'=') {
            colonPos++;
        }
        size_t typeLen = colonPos - typeB;
        wchar_t* type = (wchar_t*)malloc((typeLen + 1) * sizeof(wchar_t));
        if (type == NULL) {
            fwprintf(stderr, L"内存分配失败\n");
            free(name);
            free(command1);
            exit(1);
        }
        wcsncpy(type, typeB, typeLen);
        type[typeLen] = L'\0';
        wprintf(L"type: %ls\n", type);
        // 判断是否提供初始值
        double value = 0;
        wchar_t* equalPos = wcsstr(p, L"=");
        if (equalPos != NULL) {
            equalPos++;  // 跳过 '='
            while (*equalPos == L' ' || *equalPos == L'\t') {
                equalPos++;
            }
            if (*equalPos == L'\0') {
                fwprintf(stderr, L"\033[38;2;255;0;0m错误：\"=\"后未指定初始值！\033[0m\n");
                free(type);
                free(name);
                free(command1);
                exit(1);
            }
            // 提取初始值字符串直到遇到分隔符（例如空格或分号）或字符串末尾
            wchar_t* valueStart = equalPos;
            while (*equalPos && *equalPos != L' ' && *equalPos != L'\t' && *equalPos != L';') {
                equalPos++;
            }
            size_t valueLen = equalPos - valueStart;
            wchar_t* valueString = (wchar_t*)malloc((valueLen + 1) * sizeof(wchar_t));
            if (valueString == NULL) {
                fwprintf(stderr, L"内存分配失败\n");
                free(type);
                free(name);
                free(command1);
                exit(1);
            }
            wcsncpy(valueString, valueStart, valueLen);
            valueString[valueLen] = L'\0';
            // 去除值字符串中的空格和Tab（返回一个新字符串）
            wchar_t* cleanValue = wcsdup(valueString);
            free(valueString);
            while(*cleanValue == L' ') {
                cleanValue++;
            }


            wprintf(L"%ls\n",cleanValue);


            // 转换字符串到数值
            printf("%d\n",isChar(cleanValue));
            if (isChar(cleanValue)) {
                value = (double)getWChar(cleanValue);
            } else {
                cleanValue = deleteSpaceAndTab(cleanValue);
                if (isFloat(cleanValue)) {
                    value = wcstod(cleanValue, NULL);
                } else if (isInter(cleanValue)) {
                    value = (double)wcstol(cleanValue, NULL, 10);
                } else {
                    fwprintf(stderr, L"错误：初始值格式不正确！\n");
                    free(cleanValue);
                    free(type);
                    free(name);
                    free(command1);
                    exit(1);
                }
            }
            free(cleanValue);
            // 调用定义变量的接口
            defineVariablePlus(type, name, true, value);
        } else {
            // 没有初始值，调用定义变量接口（默认值为0）
            defineVariablePlus(type, name, false, 0);
        }
        free(type);
        free(name);
        free(command1);
        return true;
    }
    free(command1);
    return false;
}
// 调用 func(args); call func(args);
bool callFunction(const wchar_t* Ucommand) {
    setlocale(LC_ALL,"chinese");
    if (Ucommand == NULL) {
        return false;
    }
    wchar_t* commandDup = wcsdup(Ucommand);
    if (commandDup == NULL) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }
    wchar_t* p = commandDup;
    while (*p == L' ' || *p == L'\t') {
        p++;  // 跳过前导空格
    }
    if (*p == L'\0') {  // 空字符串
        free(commandDup);
        return false;
    }
    // 处理 "调用" 或 "call"
    if ((wcsncmp(p, L"调用", 2) == 0 && iswspace(p[2])) ||
            (wcsncmp(p, L"call", 4) == 0 && iswspace(p[4]))) {
        p += (*p == L'调') ? 2 : 4;  // 跳过 "调用" 或 "call"
        while (*p == L' ' || *p == L'\t') {
            p++;  // 跳过空格
        }
        if (*p == L'\0') {
            fwprintf(stderr, L"\033[38;2;255;0;0m错误：未知的调用函数！\033[0m\n");
            free(commandDup);
            return false;
        }
        wchar_t* functionBegin = p;
        while (*p != L'(' && *p != L' ' && *p != L'\t' && *p != L'\0') {
            p++;  // 找到函数名结束位置
        }
        if (*p == L'\0') {
            fwprintf(stderr, L"\033[38;2;255;0;0m错误：调用函数的语法不正确！\033[0m\n");
            free(commandDup);
            return false;
        }
        wchar_t functionName[128] = {0};
        size_t len = p - functionBegin;
        if (len >= 128) {
            fwprintf(stderr, L"错误：函数名过长！\n");
            free(commandDup);
            return false;
        }
        wcsncpy(functionName, functionBegin, len);
        functionName[len] = L'\0';  // 确保字符串终止
        // 处理参数部分
        wchar_t* argsStart = wcschr(p, L'(');
        wchar_t* argsEnd = wcschr(p, L')');
        if (argsStart && argsEnd && argsEnd > argsStart) {
            wchar_t args[256] = {0};
            size_t argsLen = argsEnd - argsStart - 1;
            if (argsLen >= 256) {
                fwprintf(stderr, L"错误：参数列表过长！\n");
                free(commandDup);
                return false;
            }
            wcsncpy(args, argsStart + 1, argsLen);
            args[argsLen] = L'\0';

            /*--------------------调试输出--------------------*/
            printf("函数名：%ls\n", functionName);
            if (argsLen > 0) {
                wprintf(L"参数：%ls\n", args);
            } else {
                wprintf(L"无参数\n");
            }
        } else {
            wprintf(L"函数名：%ls\n", functionName);
            wprintf(L"无参数\n");
        }
        free(commandDup);
        return true;
    }
    free(commandDup);
    return false;
}
bool leverAssignment(const wchar_t* command1) {
    wchar_t* command = wcsdup(command1);
    if (command == NULL) {
        fwprintf(stderr, L"内存分配失败！\n");
        return false;
    }

    wchar_t* p = command;
    int equalSignCount = 0;

    // 计算等号的数量
    while (*p != L'\0') {
        if (*p == L'=') {
            equalSignCount++;
        }
        p++;
    }

    if (equalSignCount != 1) {  // 如果等号数不是1，返回错误
        free(command);
        return false;
    }

    p = wcsstr(command, L"=");  // 查找第一个等号的位置
    if (p == NULL) {
        fwprintf(stderr, L"错误：没有指定需赋值的目标变量！\n");
        free(command);
        return false;
    }

    // 反向遍历查找目标变量
    wchar_t* var1E = p - 1;
    while (var1E >= command && (*var1E == L' ' || *var1E == L'\t')) {
        var1E--;
    }

    // 反向查找变量名的开始位置
    wchar_t* var1B = var1E;
    while (var1B >= command && *var1B != L' ' && *var1B != L'\t' && *var1B != L'=') {
        var1B--;
    }
    var1B++;  // 移到变量名的开头位置
    size_t length = var1E - var1B + 1;
    wchar_t* variable1 = (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));
    if (variable1 == NULL) {
        free(command);
        fwprintf(stderr, L"\033[38;2;255;0;0m内存分配失败！\033[0m\n");
        return false;
    }
    wcsncpy(variable1, var1B, length);
    variable1[length] = L'\0';
    if(isInter(variable1) || isFloat(variable1)) {
        fwprintf(stderr,L"\033[38;2;255;0;0m错误：变量名不能是数字！\033[0m\n");
        exit(1);
    }

    free(variable1);
    free(command);
    return true;
}
#endif