#pragma once

#include "define.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <md5.h>
#include <hex.h>

class UserManager {
private:
    void loadUser();
    std::string hashPassword(const std::string& password) const;

    std::string filename_;
    std::string currentUser_;
    std::string currentPassword_;
    std::string currentSalt_;
    bool userExists_;

public:
    UserManager(const std::string& user, const std::string& file = _DEFAULT_FILE_USERS);
    bool userExist() const;
    bool verifyPassword(const std::string& password);
    bool createUser(const std::string& password);
};
