#ifndef ORDER_HPP
#define ORDER_HPP

#include <memory>

#include "User.hpp"

enum OrderType {Buy, Sell};

class Order {
    public:
        Order();
    private:
        friend class Level;
        std::shared_ptr<User> trader;
        OrderType  order_type;
        unsigned int quantity;
        double price; 
        double time;
};

#endif