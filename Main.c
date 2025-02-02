#include <stdio.h>
#include "lever.h"
#include <stdbool.h>
#include "HS/variable.h"
#include "HS/HSIO/HSIO.h"
#include "HS/constant.h"
void isExisted(const wchar_t* name);
void cleanUpVariableAndConstant(void);
void defineConstantPlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value);
void defineVariablePlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value);

/****************/////*//*******************************/
int main(void) {
    wchar_t* command = L"定义变量 变量一:double = 3.1415926;";
    wprintf(L"%ls\n",command);
    cleanUpVariableAndConstant();
    return 0;
}                                                    //
/****************************************************/

void isExisted(const wchar_t* name) {
    for(int i = 0; i < variableCount; i++) {        //检查常量是否重复定义
        if(wcscmp(variableSymbolTable[i].name, name) == 0) {
            wprintf(L"\33[38;2;255;0;0m错误：变量%ls已定义！\33[0m\n",name);
            exit(1);
        }
    }
    for(int j = 0; j < constantCount; j++) {        //检查常量是否重复定义
        if(wcscmp(constantSymbolTable[j].name,name) == 0) {
            wprintf(L"\33[38;2;255;0;0m错误：常量%ls已定义！\33[0m\n",name);
            exit(1);
        }
    }
    return;
}
void cleanUpVariableAndConstant(void) {
    for(int i = 0; i < variableCount; i++) {
        free(variableSymbolTable[i].address);
        free(variableSymbolTable[i].name);
        free(variableSymbolTable[i].type);
    }
    for(int j = 0; j < constantCount; j++) {
        free(constantSymbolTable[j].address);
        free(constantSymbolTable[j].name);
        free(constantSymbolTable[j].type);
    }
    return;
}
void defineConstantPlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value) {
    isExisted(name);
    defineConstant(type,name,hasValue,value);
}
void defineVariablePlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value) {
    isExisted(name);
    defineVariable(type,name,hasValue,value);
}