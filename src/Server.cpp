#include "Server.hpp"

Server::Server() {

}

void Server::Run() {
    int listening;
    sockaddr_in client;
    socklen_t client_size = sizeof(client);

    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)  {
        Logger::Error("UNABLE TO CREATE SOCKET");
        return;
    }

    // bind socket to ip and port
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));
    listen(listening, SOMAXCONN);

    int client_socket = accept(listening, (sockaddr*)&client, &client_size);
    if (client_socket == -1) {
        Logger::Error("PROBLEM WITH CLIENT CONNECTING");
        return;
    }

    close(listening);
    HandleClient(client_socket);
}

void Server::HandleClient(int client_socket) {
    char buf[4096];
    std::shared_ptr<Order> order;
    double price;
    unsigned int quantity;

    send(client_socket, "LIMIT ORDERBOOK\n", 17, 0);
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(client_socket, buf, 4096, 0);
        if (bytesReceived == -1) {
            Logger::Error("ERROR RECEIVING DATA");
            break;
        }
 
        if (bytesReceived == 0) {
            Logger::Info("CLIENT DISCONNECTED");
            break;
        }


        char order_type[7];
        std::string s(buf, 0, bytesReceived);
        sscanf(s.c_str(), "%s %u %lf", order_type, &quantity, &price);
        
        std::string buy_sell(order_type);
                
        if (buy_sell == "buy") {
            order = std::make_shared<Order>(Buy, quantity, price);
        } else if (buy_sell == "sell") {
            order = std::make_shared<Order>(Sell, quantity, price);
        } else {
            Logger::Debug("INVALID ORDER TYPE");
            continue;
        }

        orderbook.addOrder(order);
        orderbook.printOrderBook();
    }
 
    // Close the socket
    close(client_socket);
}