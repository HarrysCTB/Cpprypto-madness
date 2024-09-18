#pragma once

#include <string>

#define _ROOT_DEFAULT_DIRECTORY_NAME "ServerCryptoMadnessVortex"
#if defined(__linux__)
#define _ROOT_DIRECTORY "/srv/ServerCryptoMadnessVortex/"
#elif defined(__APPLE__) && defined(__MACH__)
#define _ROOT_DIRECTORY "/Users/Shared/ServerCryptoMadnessVortex/"
#else
#error "Unsupported operating system"
#endif

#define _DEFAULT_DIR_SERVER std::string(std::string(_ROOT_DIRECTORY) + std::string("server/")).c_str()
#define _DEFAULT_FILE_USERS std::string(std::string(_DEFAULT_DIR_SERVER) + std::string("users")).c_str()
