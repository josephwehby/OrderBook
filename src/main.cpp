#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include <memory>
#include <string>

int main() {

    OrderBook orderbook;
    std::shared_ptr<Order> order;
    std::string buy_sell;
    double price;
    unsigned int quantity;
    
    std::cout << "Limit Order Book" << std::endl;
    while (true) {
        std::cout << "Buy/Sell: ";
        std::cin >> buy_sell; 
        
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        std::cout << "Price: ";
        std::cin >> price;
        
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        std::cout << "Quantity: ";
        std::cin >> quantity;

        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (buy_sell == "buy") {
            order = std::make_shared<Order>(Buy, quantity, price);
        } else {
            order = std::make_shared<Order>(Sell, quantity, price);
        }

        orderbook.addOrder(order);
        orderbook.printOrderBook();
        std::cout << "==================" << std::endl;


    }

    return 0;
}
