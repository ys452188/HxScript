#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "user_code/userCodeInfo.h"
typedef struct {
    wchar_t* name;          //函数名
    wchar_t* returnType;    //返回类型
    wchar_t* body;          //函数体
}Function;
#endif