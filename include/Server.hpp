#include <vector>
#include <thread>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <mutex>
#include "Logger.hpp"
#include "OrderBook.hpp"
#include "User.hpp"

class Server {
    public:
        Server();
        void Run();
    private:
        std::mutex thread_lock; 
        void HandleClient(std::shared_ptr<User>); 
        OrderBook orderbook;
        const int port = 31415;
        sockaddr_in hint;
};