#pragma once

#include <string>
#include <memory>

struct ClientData {
    int socket_fd;

    std::string client_adress_ip;
    std::string username;
    std::string current_directory;

    bool authenticated;

    ClientData(int fd = -1) :
        socket_fd(fd),
        client_adress_ip(""),
        username(""),
        authenticated(false)
    {}
};
