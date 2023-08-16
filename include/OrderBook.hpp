#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include "Order.hpp"
#include "Level.hpp"
#include "Logger.hpp"
#include <vector>
#include <iostream>
#include <deque>

class OrderBook {
    public:
        OrderBook();
        bool addOrder(std::shared_ptr<Order>);
        double bestBid();
        double bestAsk();
        double getSpread();
        void printOrderBook();
      
    private:
        //       price,  price_level 
        std::map<double, std::shared_ptr<Level>> bid_levels;
        std::map<double, std::shared_ptr<Level>> ask_levels;

        double addBid(std::shared_ptr<Order>);
        double addAsk(std::shared_ptr<Order>);
        double createNewLevel(std::shared_ptr<Order>);
        
        void removeLevels(OrderType);
};

#endif
