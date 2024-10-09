#include "client/Client.hpp"

int main() {
    Client client;

    // Connect to the server
    if (!client.connectToServer("127.0.0.1")) {
        return -1;
    }

    // Send message to the server
    client.sendMessage("Hello from client");

    // Read and print the server response
    std::string response = client.readResponse();
    std::cout << "Server response: " << response << std::endl;

    // Close the connection
    client.closeConnection();

    return 0;
}
