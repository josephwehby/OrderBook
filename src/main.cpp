#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include <memory>

int main() {

    OrderBook orderbook;
    std::shared_ptr<Order> bid;
    std::shared_ptr<Order> bid2;
    std::shared_ptr<Order> ask;
   // std::shared_ptr<Order> ask2;
    
    bid = std::make_shared<Order>(Buy, 100, 3.99, 10.0);
    bid2 = std::make_shared<Order>(Buy, 100, 4.02, 11.0);
    ask = std::make_shared<Order>(Sell, 100, 4.02, 10.6);
    //ask2 = std::make_shared<Order>(Sell, 50, 4.02, 10.7);
    
	std::cout << "Limit Order Book" << std::endl;

    orderbook.addOrder(bid);
    orderbook.addOrder(ask);
    //orderbook.addOrder(ask2);
    
	orderbook.printOrderBook();
    std::cout << "==================" << std::endl;
	orderbook.addOrder(bid2);
    
	orderbook.printOrderBook();
	
    return 0;
}
