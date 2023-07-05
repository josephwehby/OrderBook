#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include "Order.hpp"

class Level {
    public:
        Level(std::shared_ptr<Order>);
        unsigned int getLevelQuantity();
        unsigned int getOrderQuantity();
        void printLevel();
    private:
        friend class OrderBook;
        double price;
        std::deque <std::shared_ptr<Order>> level_orders;
};

#endif
