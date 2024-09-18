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

bool UserManager::createUser(const std::string& password) {
    if (userExists_) {
        return false;
    }

    std::ofstream file(filename_, std::ios::app); 
    if (!file.is_open()) {
        return false;
    }

    std::string hashedPassword = hashPassword(password);
    file << currentUser_ << ":" << hashedPassword << "\n";
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
        std::string username, password;

        if (std::getline(ss, username, ':') && std::getline(ss, password)) {
            if (username == currentUser_) {
                currentPassword_ = password;
                userExists_ = true;
                break;
            }
        }
    }
    file.close();
}

std::string UserManager::hashPassword(const std::string& password) const {
    CryptoPP::MD5 hash;
    std::string digest;

    CryptoPP::StringSource ss(password, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    return digest;
}