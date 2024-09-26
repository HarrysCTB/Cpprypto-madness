#pragma once

#include <chrono>
#include <cstdint>
#include <cstring>

#include "responseToServerStruct.hpp"

enum CodeResponseStatus {
    Ok,
    Ongoing,
    Error
};

struct StuctToServ {
    uint32_t id;
    uint32_t opcode;
    std::chrono::system_clock::time_point timestamp;
    //void* data; on peu pas l'envoyer c'est une adress :-(
    GeneriqueDataSendStruct data;

    StuctToServ()
        : id(0),
          opcode(0x00)
    {
        timestamp = std::chrono::system_clock::now();
    }
};

struct StructToClient {
    uint32_t id;
    uint32_t opcode;
    std::chrono::system_clock::time_point timestamp;
    //void* data; on peu pas l'envoyer c'est une adress :-(
    GeneriqueDataReciveStruct data;
    int status[2][1];
};
