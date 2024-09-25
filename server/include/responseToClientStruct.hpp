#pragma once
#include <cstring> 

struct CnntStruct {
    char code[6];

    CnntStruct(const char* inputCode = 000000) {
        strncpy(code, inputCode, sizeof(code) - 1);
        code[sizeof(code) - 1] = '\0';
    }
};

struct GeneriqueDataReciveStruct {
    int uid;
    unsigned char username[48];
    unsigned char password[48];
    unsigned char msg[256];
    unsigned char nameRoom[48];
    unsigned char passPhraseClient[48];

    GeneriqueDataReciveStruct() {
        std::memset(this, 0, sizeof(GeneriqueDataReciveStruct));
    }
};

struct GeneriqueDataSendStruct {
    int uid;
    unsigned char username[48];
    unsigned char msg[256];
    unsigned char nameRoom[48];

    GeneriqueDataSendStruct() {
        std::memset(this, 0, sizeof(GeneriqueDataSendStruct));
    }
};
