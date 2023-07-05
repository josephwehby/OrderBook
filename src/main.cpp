#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include <memory>

int main() {

    OrderBook orderbook;
    std::shared_ptr<Order> bid;
    std::shared_ptr<Order> bid2;
    std::shared_ptr<Order> ask;
    std::shared_ptr<Order> ask2;
    
    bid = std::make_shared<Order>(Buy, 100, 3.99);
    bid2 = std::make_shared<Order>(Buy, 100, 4.02);
    ask = std::make_shared<Order>(Sell, 100, 4.02);
    ask2 = std::make_shared<Order>(Sell, 5000, 4.30);
    
	std::cout << "Limit Order Book" << std::endl;

    orderbook.addOrder(bid);
    orderbook.addOrder(ask);
    orderbook.addOrder(ask2);
    
	orderbook.printOrderBook();
    std::cout << "==================" << std::endl;
	orderbook.addOrder(bid2);
    
	orderbook.printOrderBook();
	
    return 0;
}
