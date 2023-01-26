#include "OrderBook.hpp"

OrderBook::OrderBook() {

}

bool OrderBook::addOrder(OrderType order_type, double price, unsigned int quantity) {
    
    bool bid, ask;
    bid = false;
    ask = false;

    switch(order_type) {
        case Buy:
            bid = true;
            break;
        case Sell:
            ask = true;
            break;
        default:
            break;
    }

    if (bid) addBid();
    if (ask) addAsk();

    return true;
}

double OrderBook::bestBid() {
    
    if (bid_levels.size() == 0) return 0;

    return bid_levels.end()->first;
}

double OrderBook::bestAsk() {
    
    if (ask_levels.size() == 0) return 0;

    return ask_levels.begin()->first;
}

void OrderBook::printOrderBook() {
    return;
}

bool OrderBook::addBid() {
    return true;
}

bool OrderBook::addAsk() {
    return true;
}