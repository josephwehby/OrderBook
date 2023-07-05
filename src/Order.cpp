#include "Order.hpp"

Order::Order(OrderType order_type, unsigned int quantity, double price, double time) {
    this->order_type = order_type;
    this->quantity = quantity;
    this->price = price;
    this->time = time;
}
