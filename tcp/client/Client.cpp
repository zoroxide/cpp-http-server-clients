#include "Client.hpp"

// Constructor: Initialize socket and server address
Client::Client() {
    // Creating socket file descriptor
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        // std::cout << "Socket creation error" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setting server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
}

// Connect to the server
bool Client::connectToServer(const std::string& ip_address) {
    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, ip_address.c_str(), &serv_addr.sin_addr) <= 0) {
        // std::cout << "Invalid address / Address not supported" << std::endl;
        return false;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        // std::cout << "Connection failed" << std::endl;
        return false;
    }

    return true;
}

// Send a message to the server
void Client::sendMessage(const std::string& message) {
    send(sock, message.c_str(), message.size(), 0);
    // std::cout << "Message sent: " << message << std::endl;
}

// Read the server response
std::string Client::readResponse() {
    char buffer[1024] = {0};
    read(sock, buffer, sizeof(buffer));
    return std::string(buffer);
}

// Close the connection
void Client::closeConnection() {
    close(sock);
}
