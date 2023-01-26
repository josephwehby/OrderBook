#include "Level.hpp"

Level::Level(std::shared_ptr<Order> order) {
    price = order->price;
    level_orders[order->time] = order;
}

unsigned int Level::getLevelQuantity() {
    unsigned int count;

    count = 0;

    for (auto it = level_orders.begin(); it != level_orders.end(); it++) {
        auto current_order = it->second;
        count += current_order->quantity;
    }

    return count;
}

unsigned int Level::getOrderQuantity() {
    return level_orders.size();
}