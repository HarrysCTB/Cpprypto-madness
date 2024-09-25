#pragma once

struct AuthStruct {
    int uid;
    unsigned char username[50];
    unsigned char password[50];
};

struct CreaStruct {
    int uid;
    unsigned char username[50];
    unsigned char password[50];
};

struct DecoStruct {
    int uid;
    unsigned char username[50];
};

struct GeneriqueDataSendStruct {
    int uid;
    unsigned char username[48];
    unsigned char password[48];
    unsigned char msg[256];
    unsigned char nameRoom[48];
    unsigned char passPhraseClient[48];

    GeneriqueDataSendStruct() {
        std::memset(this, 0, sizeof(GeneriqueDataSendStruct));
    }
};

struct GeneriqueDataReciveStruct {
    int uid;
    unsigned char username[48];
    unsigned char msg[256];
    unsigned char nameRoom[48];

    GeneriqueDataReciveStruct() {
        std::memset(this, 0, sizeof(GeneriqueDataReciveStruct));
    }
};
