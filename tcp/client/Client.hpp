#pragma once

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 8080

class Client {
private:
    int sock;
    struct sockaddr_in serv_addr;
public:
    // Constructor
    Client();
    // Connect to the server
    bool connectToServer(const std::string& ip_address);
    // Send a message to the server
    void sendMessage(const std::string& message);
    // Read the server response
    std::string readResponse();
    // Close the connection
    void closeConnection();
};
