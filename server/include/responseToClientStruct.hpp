#pragma once
#include <cstring> 

struct CnntStruct {
    char code[6];

    CnntStruct(const char* inputCode = 000000) {
        strncpy(code, inputCode, sizeof(code) - 1);
        code[sizeof(code) - 1] = '\0';
    }
};