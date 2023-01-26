#ifndef ORDER_HPP
#define ORDER_HPP

#include <memory>

#include "User.hpp"

enum OrderType {Buy, Sell};

class Order {
    public:
        Order(std::shared_ptr<User>, OrderType, unsigned int, double, double);
    private:
        friend class Level;
        friend class OrderBook;
        std::shared_ptr<User> trader;
        OrderType order_type;
        unsigned int quantity;
        double price; 
        double time;
};

#endif