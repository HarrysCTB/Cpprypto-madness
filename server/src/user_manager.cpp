#include "user_manager.hpp"

UserManager::UserManager(const std::string& user, const std::string& file)
    : filename_(file), currentUser_(user), userExists_(false) {
    loadUser();
}

bool UserManager::userExist() const {
    return userExists_;
}

bool UserManager::verifyPassword(const std::string& password) {
    if (!userExists_) {
        return false;
    }

    std::string hashedPassword = hashPassword(password);
    bool isValid = (hashedPassword == currentPassword_);
    std::fill(currentPassword_.begin(), currentPassword_.end(), '\0');
    currentPassword_.clear();
    return isValid;
}

static std::string generateSalt(size_t length = 12) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::SecByteBlock salt(length);

    rng.GenerateBlock(salt, salt.size());

    std::string encodedSalt;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(encodedSalt));
    encoder.Put(salt, salt.size());
    encoder.MessageEnd();

    return encodedSalt;
}

bool UserManager::createUser(const std::string& password) {
    if (userExists_) {
        return false;
    }

    std::ofstream file(filename_, std::ios::app); 
    if (!file.is_open()) {
        return false;
    }

    currentSalt_ = generateSalt();
    std::string hashedPassword = hashPassword(password);
    file << currentUser_ << ":" << hashedPassword << ":" << currentSalt_<< std::endl;
    file.close();
    return true;
}

void UserManager::loadUser() {
    std::ifstream file(filename_);

    if (!file.is_open()) {
        std::ofstream createFile(filename_);
        createFile.close();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, password, salt;

        if (std::getline(ss, username, ':') && std::getline(ss, password, ':') && std::getline(ss, salt)) {
            if (username == currentUser_) {
                currentPassword_ = password;
                currentSalt_ = salt;
                userExists_ = true;
                break;
            }
        }
    }
    file.close();
}

std::string UserManager::hashPassword(const std::string& password) const {
    const size_t N = 16384;  // Cost factor (iterations)
    const size_t r = 8;      // Block size
    const size_t p = 1;      // Parallelism factor (threads)
    const size_t dkLen = 32; // Desired derived key length (32 bytes for SHA3-256)

    CryptoPP::SecByteBlock derivedKey(dkLen);
    CryptoPP::Scrypt scrypt;
    scrypt.DeriveKey(derivedKey, derivedKey.size(),
                      (const CryptoPP::byte*)password.data(), password.size(),
                      (const CryptoPP::byte*)currentSalt_.data(), currentSalt_.size(),
                      N, r, p);

    CryptoPP::SHA3_256 sha3;
    std::string sha3Digest;

    std::string derivedKeyStr(reinterpret_cast<const char*>(derivedKey.data()), derivedKey.size());

    CryptoPP::StringSource ss1(derivedKeyStr, true, new CryptoPP::HashFilter(sha3, new CryptoPP::StringSink(sha3Digest)));

    std::string encodedDigest;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(encodedDigest));
    encoder.Put(reinterpret_cast<const CryptoPP::byte*>(sha3Digest.data()), sha3Digest.size());
    encoder.MessageEnd();

    return encodedDigest;
}