#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include "Order.hpp"
#include <vector>

class OrderBook {
    public:
        OrderBook();
        int bestBid();
        int bestAsk();
    private:
        double best_bid;
        double best_ask;
        int bid_quantity;
        int ask_quantity;

        std::map<int, std::vector<Order *>> bid_levels;
        std::map<int, std::vector<Order *>> ask_levels;
};

#endif