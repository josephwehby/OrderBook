#include "OrderBook.hpp"

OrderBook::OrderBook() {

}

bool OrderBook::addOrder(std::shared_ptr<Order> order) {
    
    bool bid, ask;
    bid = false;
    ask = false;

    switch(order->order_type) {
        case Buy:
            bid = true;
            break;
        case Sell:
            ask = true;
            break;
        default:
            break;
    }

    if (bid) addBid(order);
    if (ask) addAsk(order);

    return true;
}

double OrderBook::bestBid() {
    
    if (bid_levels.size() == 0) {
        return 0;
    }

    return bid_levels.rbegin()->first;
}

double OrderBook::bestAsk() {
    
    if (ask_levels.size() == 0) return 0;

    return ask_levels.begin()->first;
}

void OrderBook::printOrderBook() {

    std::cout << "BEST BID" << std::endl;
    std::cout << bestBid() << std::endl;

}

bool OrderBook::addBid(std::shared_ptr<Order> order) {
    
    auto bid_it = bid_levels.find(order->price);

    // if price level does not exist then create a new level with the current bid submitted
    if (bid_it == bid_levels.end()) {
        std::cout << "new level" << std::endl;
        auto l = std::make_shared<Level>(order);
        bid_levels[order->price] = l;
        return true;
    
    // if level already exists then add order into the level_orders map
    } else {
        auto l = bid_it->second;
        l->level_orders[order->time] = order;
        return true;
    }

    return false;
}

bool OrderBook::addAsk(std::shared_ptr<Order>) {
    return true;
}