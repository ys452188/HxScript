#include <stdio.h>
#include <locale.h>
#include "lever.h"
#include <stdbool.h>
#include "HXS/variable.h"
#include "HXS/HXSIO/HXSIO.h"
#include "HXS/constant.h"
#include "HXS/HXS_out.h"
void isExisted(const wchar_t* name);
void cleanUpVariableAndConstant(void);
void defineConstantPlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value);
void defineVariablePlus(const wchar_t* type,const wchar_t* name,bool hasValue,double value);

/******************************************************/
int main(void) {
    //测试
    setlocale(LC_ALL,"chinese");
    wprintf(L"Test1:变量\n");
    wprintf(L"是否在定义变量？： %d\n",leverDefineVariable(L"定义变量 变量一:整型 = 114514"));
    wprintf(L"value = %d\n",(int)getVariableValue(L"变量一"));
    assignment(L"变量一",514);
    wprintf(L"value = %d\n",(int)getVariableValue(L"变量一"));
    wprintf(L"是否在定义变量？： %d\n",leverDefineVariable(L"定义变量 变量二:char = \'v\'"));
    wprintf(L"value = %c\n",(wchar_t)getVariableValue(L"变量二"));
    wprintf(L"%d\n",leverAssignment(L"exit = vvv"));
    wprintf(L"*****************************************\n");
    wprintf(L"Test2:函数\n");
    callFunction(L"call func()");
    cleanUpVariableAndConstant();
    return 0;
}                                                    //
/****************************************************/

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