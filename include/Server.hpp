#include <vector>
#include <thread>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "Logger.hpp"
#include "OrderBook.hpp"
#include "User.hpp"

class Server {
    public:
        Server();
        void Run();
    private:
        void HandleClient(std::shared_ptr<User>); 
        OrderBook orderbook;
        int port = 31415;
        sockaddr_in hint;
        std::vector <int> clients;
};