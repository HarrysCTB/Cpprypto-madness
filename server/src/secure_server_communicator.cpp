#include "secure_server_communicator.hpp"
#include <openssl/err.h>
#include <iostream>
#include <iomanip>

extern "C" const unsigned char key_bin[];

SecureServerCommunicator::SecureServerCommunicator() {
    std::memcpy(key_, key_bin, KEY_SIZE_);
}

void SecureServerCommunicator::prepareMessage(const std::string& message, unsigned char* buffer) {
    if (message.empty()) {
        return;
    }

    unsigned char iv[16];
    RAND_bytes(iv, sizeof(iv));

    unsigned char ciphertext[1024];
    size_t ciphertext_len = encrypt(reinterpret_cast<const unsigned char*>(message.c_str()), message.size(), ciphertext, iv);

    memcpy(buffer, &ciphertext_len, sizeof(ciphertext_len));
    memcpy(buffer + sizeof(ciphertext_len), iv, sizeof(iv));
    memcpy(buffer + sizeof(ciphertext_len) + sizeof(iv), ciphertext, ciphertext_len);
    memset(buffer + sizeof(ciphertext_len) + sizeof(iv) + ciphertext_len, 0, 1040 - (sizeof(ciphertext_len) + sizeof(iv) + ciphertext_len));
}

size_t SecureServerCommunicator::encrypt(const unsigned char* plaintext, size_t size, unsigned char* ciphertext, unsigned char* iv) {
    size_t padding = 16 - (size % 16);
    size_t padded_size = size + padding;

    unsigned char* padded_plaintext = new unsigned char[padded_size];
    memcpy(padded_plaintext, plaintext, size);

    for (size_t i = size; i < padded_size; ++i) {
        padded_plaintext[i] = static_cast<unsigned char>(padding);
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Échec de la création du contexte de chiffrement");

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key_, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        delete[] padded_plaintext;
        throw std::runtime_error("Échec de l'initialisation du chiffrement");
    }

    int len;
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, padded_plaintext, padded_size) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        delete[] padded_plaintext;
        throw std::runtime_error("Échec de la mise à jour du chiffrement");
    }

    int ciphertext_len = len;
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &ciphertext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        delete[] padded_plaintext;
        throw std::runtime_error("Échec de la finalisation du chiffrement");
    }

    EVP_CIPHER_CTX_free(ctx);
    delete[] padded_plaintext;
    return padded_size;
}

void SecureServerCommunicator::decrypt(const unsigned char* buffer, size_t size, unsigned char* plaintext) {
    size_t ciphertext_len;
    memcpy(&ciphertext_len, buffer, sizeof(ciphertext_len));

    unsigned char iv[16];
    memcpy(iv, buffer + sizeof(ciphertext_len), sizeof(iv));
    const unsigned char* ciphertext = buffer + sizeof(ciphertext_len) + sizeof(iv);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key_, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Échec de l'initialisation du déchiffrement");
    }

    int len;
    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Échec de la mise à jour du déchiffrement");
    }

    int plaintext_len = len;
    if (EVP_DecryptFinal_ex(ctx, plaintext + plaintext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Échec de la finalisation du déchiffrement");
    }
    EVP_CIPHER_CTX_free(ctx);
}