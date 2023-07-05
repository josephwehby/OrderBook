#ifndef ORDER_HPP
#define ORDER_HPP

#include <memory>

enum OrderType {Buy, Sell};

class Order {
    public:
        Order(OrderType, unsigned int, double);
    private:
        friend class Level;
        friend class OrderBook;
        OrderType order_type;
        unsigned int quantity;
        double price; 

};

#endif
