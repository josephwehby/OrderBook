#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <map>
#include "Order.hpp"

class Level {
    public:
        Level();
        unsigned int getLevelQuantity();
        unsigned int getOrderQuantity();
    private:
        double price;
        std::map <double, std::shared_ptr<Order>> level_orders;
};

#endif