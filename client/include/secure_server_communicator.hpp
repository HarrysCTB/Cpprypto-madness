#pragma once

#include <iostream>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string>
#include <fstream>

#include "universal_structs_client.hpp"

class SecureServerCommunicator {
public:
    SecureServerCommunicator();
    size_t encrypt(const unsigned char* plaintext, size_t size, unsigned char* ciphertext, unsigned char* iv);
    void decrypt(const unsigned char* buffer, size_t size, unsigned char* plaintext);
    void prepareMessage(const StuctToServ& msg, unsigned char* buffer);

private:
    static const int KEY_SIZE_ = 16; 
    unsigned char key_[KEY_SIZE_];
};