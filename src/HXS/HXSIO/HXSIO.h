#ifndef __HS_HSIO_HSIO_H__
#define __HS_HSIO_HSIO_H__
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK_SIZE 32
static FILE* filePtr = NULL;
static wchar_t* storedFilePath = NULL;
// 兼容 `_wcsdup` 的替代方案
#ifndef _WIN32
wchar_t* wcsdup(const wchar_t* src) {
    if (!src) return NULL;
    size_t len = wcslen(src) + 1;
    wchar_t* dup = (wchar_t*)malloc(len * sizeof(wchar_t));
    if (dup) wcscpy(dup, src);
    return dup;
}
#endif
// 读取标准输入的一行
wchar_t* getLineFromStdin(void) {
    size_t capacity = CHUNK_SIZE, length = 0;
    wchar_t* buffer = (wchar_t*)malloc(capacity * sizeof(wchar_t));
    if (!buffer) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }

    wchar_t ch;
    while ((ch = getwchar()) != WEOF && ch != L'\n') {
        if (length + 1 >= capacity) {
            capacity += CHUNK_SIZE;
            wchar_t* temp = (wchar_t*)realloc(buffer, capacity * sizeof(wchar_t));
            if (!temp) {
                free(buffer);
                fwprintf(stderr, L"内存扩展失败\n");
                exit(1);
            }
            buffer = temp;
        }
        buffer[length++] = ch;
    }

    buffer[length] = L'\0';
    return buffer;
}

// 兼容 Windows 和 Linux/macOS 的 `fopen` 处理
FILE* openFile(const wchar_t* filePath, const wchar_t* mode) {
#ifdef _WIN32
    return _wfopen(filePath, mode);
#else
    // Linux/macOS 不支持 _wfopen，需要转换 wchar_t* 到 char*
    char path[256];
    char m[16];
    wcstombs(path, filePath, sizeof(path));
    wcstombs(m, mode, sizeof(m));
    return fopen(path, m);
#endif
}

// 从文件读取下一行
wchar_t* getNextLineFromFile(const wchar_t* filePath) {
    if (!filePtr) {
        filePtr = openFile(filePath, L"r");
        if (!filePtr) {
            fwprintf(stderr, L"无法打开文件: %ls\n", filePath);
            return NULL;
        }
        free(storedFilePath);
        storedFilePath = wcsdup(filePath);
    }

    size_t capacity = CHUNK_SIZE, length = 0;
    wchar_t* buffer = (wchar_t*)malloc(capacity * sizeof(wchar_t));
    if (!buffer) {
        fwprintf(stderr, L"内存分配失败\n");
        exit(1);
    }

    wchar_t ch;
    while ((ch = fgetwc(filePtr)) != WEOF && ch != L'\n') {
        if (length + 1 >= capacity) {
            capacity += CHUNK_SIZE;
            wchar_t* temp = (wchar_t*)realloc(buffer, capacity * sizeof(wchar_t));
            if (!temp) {
                free(buffer);
                fwprintf(stderr, L"内存扩展失败\n");
                exit(1);
            }
            buffer = temp;
        }
        buffer[length++] = ch;
    }

    if (length == 0 && ch == WEOF) {
        free(buffer);
        return NULL;
    }

    buffer[length] = L'\0';
    return buffer;
}

// 关闭文件并释放路径
void reset(void) {
    if (filePtr) {
        fclose(filePtr);
        filePtr = NULL;
    }
    if (storedFilePath) {
        free(storedFilePath);
        storedFilePath = NULL;
    }
}

// 重新打开文件并从头开始读取
void restart(void) {
    if (storedFilePath) {
        reset();
        storedFilePath = wcsdup(storedFilePath);
        filePtr = openFile(storedFilePath, L"r");
        if (!filePtr) {
            fwprintf(stderr, L"无法重新打开文件: %ls\n", storedFilePath);
        }
    }
}

#endif