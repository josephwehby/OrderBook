#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
    public:
        User(std::string, unsigned long);
    private:
        std::string name;
        unsigned long id;
};

#endif