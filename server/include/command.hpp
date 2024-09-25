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

class Command {
public:
    Command(ClientQueueThreadPool* threadPool = nullptr, int port = 9999);
    ~Command() {};

    int acceptClient(std::unordered_map<int, Rooms*> *rooms);
    int getServerSocket() const;
    bool handleClient(ClientData* client);
    void sendToClient(ClientData *client, const std::string& message);

    void handleAuthCommand(ClientData* client, std::vector<std::string> commands);
    void handleCreaCommand(ClientData* client, std::vector<std::string> commands);
    void handleMessCommand(ClientData* client, std::vector<std::string> commands);
    void handleDecoCommand(ClientData* client, std::vector<std::string> commands);

    using CommandHandler = void (Command::*)(ClientData*, std::vector<std::string>);
    #ifndef INCLUDE_OPCODE
        std::map<std::string, CommandHandler> commandHandlers_;
    #else
        static CommandHandler function_table_op_code[4];
    #endif

    bool serverStart_;

private:

    void setupServer(int port);
    void processCommand(ClientData* client, const std::string& command);

    int serverSocketCommand_;
    struct sockaddr_in serverAddrCommand_;

    ClientQueueThreadPool* queueClient_;
    ClientData* client_;

    std::vector<int> portUse_;

    std::unordered_map<int, Rooms*> *rooms_;

    SecureServerCommunicator communicator_;
};
