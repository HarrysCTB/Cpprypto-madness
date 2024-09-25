#include "command.hpp"
#include "user_manager.hpp"

/**
 * @brief Handles the client authentication command (AUTH).
 * 
 * This function processes the AUTH command sent by a client, validates the provided credentials, 
 * and, if valid, authenticates the client and assigns them to a room.
 * 
 * @param client  A pointer to the ClientData structure representing the client's data sending the command.
 * 
 * @return void
 * 
 * @details
 * The following errors can occur and will send an error code to the client:
 * 
 *  - **550**: The number of arguments is incorect. At least 2 parameters are required:
 *    - The command name ("AUTH").
 *    - A username.
 * 
 *  - **551**: The username is invalid or not found in the system.
 *    - The username provided does not exist in the system.
 * 
 *  - **552**: Authentication failed.
 *    - The provided password is incorrect (if required).
 * 
 *  - **561**: An unexpected error occurred during the authentication process (server-side error).
 * 
 *  If authentication is successful:
 * 
 *  - **250**: The client is successfully authenticated and can proceed to the next operations.
 */

struct AuthStruct {
    int uid;
    unsigned char username[50];
    unsigned char password[50];
};

void Command::handleAuthCommand(ClientData* client, const StuctToServ& message) {

    //AuthStruct* authData = static_cast<AuthStruct*>(message.data);
    //const std::string username(reinterpret_cast<char*>(authData->username));
    //const std::string password(reinterpret_cast<char*>(authData->password));

    const std::string username(reinterpret_cast<const char*>(message.data.username));
    const std::string password(reinterpret_cast<const char*>(message.data.password));

    StructToClient response;
    response.id = message.id;
    response.opcode = NONE_CODE;

    if (username.empty() || password.empty()) {
        response.setStatus(CodeResponseStatus::Error, 550);
        sendToClient(client, response);
        return;
    }

    UserManager userManager(username);

    if (!userManager.userExist()) {
        response.setStatus(CodeResponseStatus::Error, 551);
        sendToClient(client, response);
        return;
    }

    if (!userManager.verifyPassword(password)) {
        response.setStatus(CodeResponseStatus::Error, 552);
        sendToClient(client, response);
        return;
    }

    auto it = rooms_->find(1);
    if (it == rooms_->end()) {
        response.setStatus(CodeResponseStatus::Error, 561);
        sendToClient(client, response);
        return;
    }

    client->room_join = it->second;
    Rooms* room = static_cast<Rooms*>(client->room_join);
    room->connectClient(client->socket_fd);

    client->username = username;
    client->authenticated = true;

    response.setStatus(CodeResponseStatus::Ok, 250);
    sendToClient(client, response);
}
