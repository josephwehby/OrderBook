#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
    public:
        User(int, unsigned long);
    private:
        friend class Server;
        int socket;
        unsigned long id;
};

#endif