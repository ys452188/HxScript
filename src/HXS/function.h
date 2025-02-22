#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "user_code/userCodeInfo.h"
#define INITIAL_CAPACITY 1
typedef struct {
    wchar_t* name;          //函数名
    wchar_t* returnType;    //返回类型
    wchar_t** args;         //参数
    wchar_t** argsType;     //参数类型
    wchar_t* body;          //函数体
}Function;
Function *functionSymbolTable = NULL;
int functionCapacity = 0;
void expandFunctionSymbolTable(void) {
    if(functionCount == 0) { 
        functionCapacity = INITIAL_CAPACITY;
        functionSymbolTable = (Function*)malloc(functionCapacity*sizeof(Function));
    } else {
        functionCapacity += 1;
        void* temp = realloc(functionSymbolTable,sizeof(Function)* functionCapacity);
        if (!temp) {
            perror("错误：符号表扩容失败！");
            exit(1);
        }
        functionSymbolTable = (Function*)temp;
    }
    return;
}
#endif