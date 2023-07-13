#include <iostream>
#include "OrderBook.hpp"
#include "Order.hpp"
#include "Window.hpp"
#include <memory>
#include <string>



using namespace std;

int main(int argc, char *argv[]) {
    OrderBook orderbook;
    std::shared_ptr<Order> order;
    std::string buy_sell;
    double price;
    unsigned int quantity;
    
    while (true) {
        printf("Buy/Sell: ");
        std::cin >> buy_sell; 
        
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        printf("Quantity: ");
        std::cin >> quantity;

        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        printf("Share Price: ");
        std::cin >> price;
        
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        if (buy_sell == "buy") {
            order = std::make_shared<Order>(Buy, quantity, price);
        } else {
            order = std::make_shared<Order>(Sell, quantity, price);
        }

        orderbook.addOrder(order);
        orderbook.printOrderBook();
    }

    return 0;
}
