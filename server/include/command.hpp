#pragma once

#include "server.hpp"
#include "client_data.hpp"
#include "thread_pool.hpp"
#include "client_queue_thread_pool.hpp"

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

    int acceptClient();
    int getServerSocket() const;
    bool handleClient(ClientData* client);
    void sendToClient(ClientData *client, const std::string& message);

    bool serverStart_;

private:
    void setupServer(int port);
    void processCommand(ClientData* client, const std::string& command);

    void handleAuthCommand(ClientData* client, std::vector<std::string> command);
    void handleMessCommand(ClientData* client, std::vector<std::string> command);
    void handleQuitCommand(ClientData* client, std::vector<std::string> command);

    int serverSocketCommand_;
    struct sockaddr_in serverAddrCommand_;

    using CommandHandler = void (Command::*)(ClientData *, std::vector<std::string>);
    std::map<std::string, CommandHandler> commandHandlers_;

    ClientQueueThreadPool* queueClient_;
    ClientData* client_;

    std::vector<int> portUse_;
};
