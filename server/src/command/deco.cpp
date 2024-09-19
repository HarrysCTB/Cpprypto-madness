#include "command.hpp"

/**
 * @brief Handles the client disconnection command (DECO).
 * 
 * This function processes the DECO command sent by a client and disconnects the client from the server.
 * It ensures that the client is properly disconnected and resets their session data.
 * 
 * @param client  A pointer to the ClientData structure representing the client's data sending the command.
 * @param commands  A vector of strings containing the commands sent by the client.
 *                   - commands[0]: The command name (e.g., "DECO").
 * 
 * @return void
 * 
 * @details
 * The following errors can occur and will send an error code to the client:
 * 
 *  - **550**: Invalid number of arguments. Exactly 1 argument is required:
 *    - The command name ("DECO").
 * 
 *  - **561**: Client is not connected.
 *    - The client is not connected to the server or their connection has already been terminated.
 * 
 *  - **562**: An unexpected error occurred during the disconnection process (server-side error).
 * 
 *  If disconnection is successful:
 * 
 *  - **250**: The client has been successfully disconnected and their session reset.
 */
void Command::handleDecoCommand(ClientData* client, std::vector<std::string> commands) {
    if (commands.size() != 1) {
        sendToClient(client, "550 Invalid number of arguments\r\n");
        return;
    }

    if (!client->authenticated) {
        sendToClient(client, "561 Client not connected\r\n");
        return;
    }

    bool disconnected = true; //Todo
    if (!disconnected) {
        sendToClient(client, "562 Failed to disconnect from server\r\n");
        return;
    }

    client->reset();
    sendToClient(client, "250 Disconnected from server successfully\r\n");
}