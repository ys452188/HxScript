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
void run(const wchar_t* command);

/******************************************************/
int main(void) {
    //测试
    setlocale(LC_ALL,"chinese");
    while (true) {
        run(getLineFromStdin());
    }
    getchar();
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
void run(const wchar_t* command) {
    setlocale(LC_ALL,"chinese");
    if(command == NULL || wcslen(command) == 0) {
        return;
    }
    if(leverDefineVariable(command)) {
        return;
    } else if(leverDefineConstant(command)) {
        return; 
    } else if(leverAssignment(command)) {
        return;
    } else {
        fwprintf(stdout,L"\033[38;2;255;0;0m无法识别的命令！\033[0m\n");
        return;
    }
    return;
}