#include "command.hpp"

/**
 * @brief Handles the client message command (MESS).
 * 
 * This function processes the MESS command sent by a client, ensuring that the client is part of a room
 * and that a valid message is provided. The message is then broadcast to the room.
 * 
 * @param client  A pointer to the ClientData structure representing the client's data sending the command.
 * @param commands  A vector of strings containing the commands sent by the client.
 *                   - commands[0]: The command name (e.g., "MESS").
 *                   - commands[1+]: The message to be sent.
 * 
 * @return void
 * 
 * @details
 * The following errors can occur and will send an error code to the client:
 * 
 *  - **550**: Insufficient arguments. At least two parameters are required:
 *    - The command name ("MESS").
 *    - A message.
 * 
 *  - **561**: Client is not connected to any room.
 *    - The client must be part of a room to send a message.
 * 
 *  - **562**: An unexpected error occurred while sending the message (server-side error).
 * 
 *  If the message is successfully sent:
 * 
 *  - **250**: The message was successfully sent to the room.
 */
void Command::handleMessCommand(ClientData* client, std::vector<std::string> commands) {
    if (commands.size() < 2) {
        sendToClient(client, "550 Insufficient arguments\r\n");
        return;
    }

    if (client->room_join == nullptr) {
        sendToClient(client, "561 Client not connected to any room\r\n");
        return;
    }

    Rooms* room = static_cast<Rooms*>(client->room_join);
    if (room == nullptr) {
        sendToClient(client, "562 Server error: room not found\r\n");
        return;
    }

    commands.erase(commands.begin());
    std::string message;
    for (const auto& part : commands) {
        message += part + " ";
    }
    message.pop_back(); 

    room->setMessage(client->username, message);
    bool messageSent = true; //Todo
    if (!messageSent) {
        sendToClient(client, "562 Failed to send message\r\n");
        return;
    }

    sendToClient(client, "250 Message sent successfully\r\n");
}
    