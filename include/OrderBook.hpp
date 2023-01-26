#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include "Order.hpp"
#include "Level.hpp"
#include <vector>

class OrderBook {
    public:
        OrderBook();
        bool addOrder(OrderType order_type, double price, unsigned int quantity);
        double bestBid();
        double bestAsk();
        double getSpread();
        void printOrderBook();
      
    private:
        double spread;
        std::map<double, std::shared_ptr<Level>> bid_levels;
        std::map<double, std::shared_ptr<Level>> ask_levels;

        bool addBid();
        bool addAsk();
};

#endif