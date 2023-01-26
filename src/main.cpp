#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "User.hpp"
#include <memory>

int main() {

    OrderBook orderbook;
    std::shared_ptr<User> user;
    std::shared_ptr<Order> order;
    
    //OrderType bid = Buy;
    
    user = std::make_shared<User>("Joseph", 100);
    order = std::make_shared<Order>(user, Buy, 100, 3.99, 10.0);
    std::cout << "Trading Simulator" << std::endl;

    orderbook.addOrder(order);
    orderbook.printOrderBook();
    
    return 0;
}