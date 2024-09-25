#pragma once

#include "server.hpp"
#include "client_data.hpp"
#include "thread_pool.hpp"
#include "client_queue_thread_pool.hpp"
#include "define.hpp"
#include "secure_server_communicator.hpp"

#include <map>
#include <vector>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <sys/utsname.h>
#include <sstream>
#include <iomanip>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h> 
#include <regex>

struct ClientData;

#define NONE_CODE 0x00

#include "universal_structs_server.hpp"
//server OpCode
#define AUTH_CODE 0x01
#define CREA_CODE 0x02
#define MESS_CODE 0x03
#define DECO_CODE 0x04

#include "responseToClientStruct.hpp"
//client OpCode
#define CNNT_CODE 0x01
#define RVUM_CODE 0x02
#define RVRM_CODE 0x03

class Command {
public:
    Command(ClientQueueThreadPool* threadPool = nullptr, int port = 9999);
    ~Command() {};

    int acceptClient(std::unordered_map<int, Rooms*> *rooms);
    int getServerSocket() const;
    bool handleClient(ClientData* client);
    void sendToClient(ClientData *client, const StructToClient& message);

    void handleAuthCommand(ClientData* client, const StuctToServ& message);
    void handleCreaCommand(ClientData* client, const StuctToServ& message);
    void handleMessCommand(ClientData* client, const StuctToServ& message);
    void handleDecoCommand(ClientData* client, const StuctToServ& message);

    using CommandHandler = void (Command::*)(ClientData*, const StuctToServ& message);
    #ifndef INCLUDE_OPCODE
        std::map<int, CommandHandler> commandHandlers_;
    #else
        static CommandHandler function_table_op_code[4];
    #endif

    bool serverStart_;

private:

    void setupServer(int port);
    void processCommand(ClientData* client, const StuctToServ& message);

    int serverSocketCommand_;
    struct sockaddr_in serverAddrCommand_;

    ClientQueueThreadPool* queueClient_;
    ClientData* client_;

    std::vector<int> portUse_;

    std::unordered_map<int, Rooms*> *rooms_;

    SecureServerCommunicator communicator_;
};
