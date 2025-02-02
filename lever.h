#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
wchar_t* deleteSpaceAndTab(const wchar_t* s) {
    if (wcsstr(s, L" ") == NULL && wcsstr(s, L"\t") == NULL) {
        return wcsdup(s);  // 直接返回字符串副本，避免修改原始数据
    }
    size_t len = wcslen(s);
    wchar_t* result = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    if (result == NULL) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }
    wchar_t* p = result;
    for(int i = 0; i < wcslen(s); i++) {
        if (*s != L' ' && *s != L'\t') {
            *p++ = *s;
        }
        s++;
    }
    *p = L'\0';  // 终止字符串
    return result;  // 返回去掉空格的字符串
}
bool isInter(const wchar_t* s) {
    wchar_t* s1 = deleteSpaceAndTab(s);
    if (s1 == NULL) {
        return false;
    }
    const wchar_t* p = s1;
    while (*p) {
        if (!(*p >= L'0' && *p <= L'9')) {
            free(s1);  // 释放内存，防止泄漏
            return false;
        }
        p++;
    }
    free(s1);
    return true;
}
bool isFloat(const wchar_t* s) {
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
            free(s1);
            fwprintf(stderr, L"\33[38;2;255;0;0m错误：%ls不属于任何类型！\33[0m\n", s1);
            exit(1);
        }
        dot--;  // 获取小数点前的字符
        if (*dot >= L'0' && *dot <= L'9') {
            free(s1);
            return true;
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
}
/*定义变量的语句：var a: int = 0; 定义变量 变量 : int = 114;*/
bool leverDefineVariable(const wchar_t* command) {
    if (command == NULL) {
        return false;
    }
    wchar_t* command1 = wcsdup(command);  // 复制字符串，避免修改原始数据
    if (command1 == NULL) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }
    wchar_t* p = command1;  // 指针 `p` 用于遍历
    // 跳过前导空格和Tab
    while (*p == L' ' || *p == L'\t') {
        p++;
    }
    // 检查是否是 "var "
    if (wcslen(p) >= 3 && *p == L'v' && *(p+1) == L'a' && *(p+2) == L'r'
            && (*(p+3) == L' ' || *(p+3) == L'\t')) {
        p += 3;  // 跳过 "var"
        // 跳过 "var" 后的空格
        while (*p == L' ' || *p == L'\t') {
            p++;
        }
        wchar_t* nameB = p;  // 变量名起始位置
        // 找到变量名的终点
        while (*p && *p != L' ' && *p != L'\t') {
            p++;
        }
        wchar_t* nameE = p;  // 变量名终点
        // 提取变量名
        wchar_t name[128] = {0};  // 避免未初始化
        size_t len = nameE - nameB;
        if (len > 127) {
            len = 127;
        }  // 避免越界
        wcsncpy(name, nameB, len);
        name[len] = L'\0';  // 确保字符串结尾
        //提取类型
        if(!(wcsstr(p,L':') == NULL)) {
            fwprintf(stderr,L"\33[38;2;255;0;0m错误：未指定变量类型\33[0m\n");
        } else {
            p = wcsstr(p,L':');
        }
        free(command1);  // 释放字符串副本
        return true;
    }
    // 检查是否是 "定义变量 "
    if (wcslen(p) >= 3 && *p == L'定' && *(p+1) == L'义' && *(p+2) == L'变' && *(p+3) == L'量'
            && (*(p+4) == L' ' || *(p+4) == L'\t')) {
        p += 3;  // 跳过 "var"
        // 跳过 "var" 后的空格
        while (*p == L' ' || *p == L'\t') {
            p++;
        }
        wchar_t* nameB = p;  // 变量名起始位置
        // 找到变量名的终点
        while (*p && *p != L' ' && *p != L'\t') {
            p++;
        }
        wchar_t* nameE = p;  // 变量名终点
        // 提取变量名
        wchar_t name[128] = {0};
        size_t len = nameE - nameB;
        if (len > 127) {
            len = 127;
        }  // 避免越界
        wcsncpy(name, nameB, len);
        name[len] = L'\0';  // 确保字符串结尾
        //提取类型
        free(command1);  // 释放字符串副本
        return true;
    }
    free(command1);
    return false;
}