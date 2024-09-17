#pragma once

#include <string>
#include <memory>

struct ClientData {
    int socket_fd;

    std::string client_adress_ip;
    std::string username;

    bool authenticated;

    void* room_join;

    void reset() {
        authenticated = false;
        client_adress_ip = "";
        username = "";
    }

    ClientData(int fd = -1) :
        socket_fd(fd),
        client_adress_ip(""),
        username(""),
        authenticated(false)
    {}
};
