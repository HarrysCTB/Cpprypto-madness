#include "command.hpp"
#include "user_manager.hpp"

/**
 * @brief Handles the client authentication command (AUTH).
 * 
 * This function processes the AUTH command sent by a client, validates the provided credentials, 
 * and, if valid, authenticates the client and assigns them to a room.
 * 
 * @param client  A pointer to the ClientData structure representing the client's data sending the command.
 * @param commands  A vector of strings containing the commands sent by the client.
 *                   - commands[0]: The command name (e.g., "AUTH").
 *                   - commands[1]: The provided username.
 *                   - commands[2] (optional): The provided password (if required).
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
void Command::handleAuthCommand(ClientData* client, std::vector<std::string> commands) {
    if (commands.size() != 3) { // Expecting both username and password
        sendToClient(client, "550 Insufficient arguments\r\n");
        return;
    }

    const std::string& username = commands[1];
    const std::string& password = commands[2];

    UserManager userManager(username);

    if (!userManager.userExist()) {
        sendToClient(client, "551 Username not found\r\n");
        return;
    }

    if (!userManager.verifyPassword(password)) {
        sendToClient(client, "552 Incorrect password\r\n");
        return;
    }

    auto it = rooms_->find(1);
    if (it == rooms_->end()) {
        sendToClient(client, "561 Room not found\r\n");
        return;
    }

    client->room_join = it->second;
    Rooms* room = static_cast<Rooms*>(client->room_join);
    room->connectClient(client->socket_fd);

    client->username = username;
    client->authenticated = true;

    sendToClient(client, "250 Authentication successful\r\n");
}
