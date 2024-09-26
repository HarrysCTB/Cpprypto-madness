#ifndef CANAL_HANDLER_HPP
#define CANAL_HANDLER_HPP

#include <string>
#include <random>

#include "user_controller.h"
class UserController;

#include "secure_server_communicator.hpp"
#include "responseToServerStruct.hpp"

#define NONE_CODE 0x00

#include "universal_structs_client.hpp"
//server OpCode
#define AUTH_CODE 0x01
#define CREA_CODE 0x02
#define MESS_CODE 0x03
#define DECO_CODE 0x04

#include "responseToServerStruct.hpp"
//client OpCode
#define CNNT_CODE 0x01
#define RVUM_CODE 0x02
#define RVRM_CODE 0x03

#include "client.hpp"
class Client;

class CanalHandler {
    public:
        CanalHandler(int socket_fd, SecureServerCommunicator *communicator, std::function<void(uint32_t, std::function<void(int)>)> addCommandFunc, UserController *userController);

        void handleAuth(const std::string& username, const std::string& password);
        void handleCrea(const std::string& username, const std::string& password);
        void handleMessage(const std::string& message);
        void handleQuit();

        void callbackAuth(int code);

    private:
        int socket_fd;
        SecureServerCommunicator *communicator_;

        std::function<void(uint32_t, std::function<void(int)>)> addCommandFunc_;

        UserController *userController_;
};

#endif
