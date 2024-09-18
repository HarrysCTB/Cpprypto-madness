#include "command.hpp"

/**
 * @brief Handles the account creation command (CREA).
 * 
 * This function processes the CREA command sent by a client and validates the provided information
 * before confirming the creation of the user account.
 * 
 * @param client  A pointer to the ClientData structure representing the client's data sending the command.
 * @param commands  A vector of strings containing the commands sent by the client.
 *                   - commands[0]: The command name (e.g., "CREA").
 *                   - commands[1]: The proposed username.
 *                   - commands[2]: The proposed password.
 * 
 * @return void
 * 
 * @details
 * The following errors can occur and will send an error code to the client:
 * 
 *  - **550**: The number of arguments is insufficient. At least 3 parameters are required:
 *    - The command name ("CREA").
 *    - A username.
 *    - A password.
 * 
 *  - **551**: The username is invalid.
 *    - It must be between 3 and 16 characters long.
 *    - It can only contain letters, numbers, and allowed characters (e.g., `_`, `-`).
 * 
 *  - **552**: The username is already taken. The user must choose a different one.
 * 
 *  - **560**: The password does not meet the security requirements.
 *    - The password must be at least 6 characters long.
 *    - It must contain at least one uppercase letter, one special character (e.g., `!`, `@`, `#`, etc.), and one number.
 * 
 *  - **561**: An unexpected error occurred during account creation (server-side error).
 * 
 *  If all validations pass successfully:
 * 
 *  - **250**: The account has been successfully created, and the client is informed of the successful operation.
 */
void Command::handleCreaCommand(ClientData* client, std::vector<std::string> commands) {
    if (commands.size() != 3) {
        sendToClient(client, "550 Insufficient arguments\r\n");
        return;
    }

    const std::string& username = commands[1];
    const std::string& password = commands[2];

    if (username.length() < 3 || username.length() > 16) {
        sendToClient(client, "551 Invalid username\r\n");
        return;
    }

    if (!std::all_of(username.begin(), username.end(), [](char c) {
        return std::isalnum(c) || c == '_' || c == '-';
    })) {
        sendToClient(client, "551 Invalid username\r\n");
        return;
    }

    bool usernameExists = false; //Todo
    if (usernameExists) {
        sendToClient(client, "552 Username already taken\r\n");
        return;
    }

    if (password.length() < 6) {
        sendToClient(client, "560 Password too short\r\n");
        return;
    }

    bool hasUppercase = std::any_of(password.begin(), password.end(), ::isupper);
    bool hasSpecialChar = std::any_of(password.begin(), password.end(), [](char c) {
        return std::ispunct(c);
    });
    bool hasDigit = std::any_of(password.begin(), password.end(), ::isdigit);

    if (!hasUppercase || !hasSpecialChar || !hasDigit) {
        sendToClient(client, "560 Password does not meet security requirements\r\n");
        return;
    }

    bool accountCreated = false; //Todo
    if (!accountCreated) {
        sendToClient(client, "561 Server error during account creation\r\n");
        return;
    }

    sendToClient(client, "250 Account created successfully\r\n");
}
