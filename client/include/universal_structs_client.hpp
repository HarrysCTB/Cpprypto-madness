#pragma once

#include <chrono>
#include <cstdint>
#include <cstring>

enum CodeResponseStatus {
    Ok,
    Ongoing,
    End,
    Error
};

struct StuctToServ {
    uint32_t id;
    uint32_t opcode;
    std::chrono::system_clock::time_point timestamp;
    void* data;

    StuctToServ()
        : id(0),
          opcode(0x00),
          data(nullptr)
    {
        memset(status, 0, sizeof(status)); 
        timestamp = std::chrono::system_clock::now();
    }
};

struct StructToClient {
    uint32_t id;
    uint32_t opcode;
    std::chrono::system_clock::time_point timestamp;
    void* data;
    int status[2][1];
};
