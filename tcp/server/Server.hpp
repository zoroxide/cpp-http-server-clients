#pragma once

#include <bits/stdc++.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

typedef enum {
  SOCKET_SUCCESS,
  SOCKET_FIELD,
  LISTEN_SUCCESS,
  LISTEN_FAIL,
  ACCEPT_SUCCESS,
  ACCEPT_FAIL,
  BIND_SUCCESS,
  BIND_FAIL
} State_t;

class Server {
private:

    #define HOST "127.0.0.1"
    #define PORT 8080
    #define CONNECTIONS_BACKLOG 10
    #define BUFFER_SIZE 1024

    int server_fd;
    struct sockaddr_in address;

    void handle_client(int client_socket);

public:

    Server();

    std::string renderHTML(std::filesystem::path path);

    void server_send(char * msg, int client_socket);

    void run(std::string host = HOST);
    };
