#include "Level.hpp"

Level::Level(std::shared_ptr<Order> order) {
    price = order->price;
    level_orders.push_back(order);
}

unsigned int Level::getLevelQuantity() {
    unsigned int count, i;

    count = 0;

    for (i = 0; i < level_orders.size(); i++) {
		std::shared_ptr<Order> current_order = level_orders[i];
        count += current_order->quantity;
    }

    return count;
}

unsigned int Level::getOrderQuantity() {
    return level_orders.size();
}

void Level::printLevel() {
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << getLevelQuantity() << " @ $" << price;

}
