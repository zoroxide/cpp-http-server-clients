// g++ -o server Server.cpp -pthread

#include "Server.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>

Server::Server(){
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == 0){
        perror("SOCKET_FIELD");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
}

std::string Server::renderHTML(std::filesystem::path path){
    std::ifstream file(path);
    if(!file.is_open()){
        return "<h1>404 not found</h1>";
    }

    std::string html_content((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    file.close();
    return html_content;
}

void Server::server_send(char * msg, int client_socket){
    send(client_socket, msg, strlen(msg), 0);
}

void Server::handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    
    // Read client request (although we're serving static files, we can log requests)
    read(client_socket, buffer, BUFFER_SIZE);
    // std::cout << "Request received: \n";
    // std::cout << "Request received: " << buffer << std::endl;

    // Render the HTML content (for now, serve a static HTML file from the current directory)
    std::string htmlContent = renderHTML("index.html");

    // Construct HTTP response
    std::string httpResponse = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(htmlContent.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + htmlContent;

    // Send response to client
    send(client_socket, httpResponse.c_str(), httpResponse.size(), 0);
    // std::cout << "HTML response sent to client" << std::endl;

    // Close client socket
    close(client_socket);
}

// Run the server to listen and accept connections
void Server::run(std::string host) {
    // Bind the server socket to the specified port and address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Server bound to " << host << " on port " << PORT << std::endl;

    // Listen for incoming connections
    if (listen(server_fd, CONNECTIONS_BACKLOG) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        // Accept a new connection
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        std::cout << "New client connected" << std::endl;

        // Handle the client in a separate thread (for scalability)
        std::thread client_thread(&Server::handle_client, this, client_socket);
        client_thread.detach(); // Detach the thread to allow independent execution
    }

    // Close the server socket (not reachable in this example)
    close(server_fd);
}