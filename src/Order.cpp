#include "Order.hpp"

Order::Order(std::shared_ptr<User> user, OrderType order_type, unsigned int quantity, double price, double time) {
    trader = user;
    this->order_type = order_type;
    this->quantity = quantity;
    this->price = price;
    this->time = time;
}