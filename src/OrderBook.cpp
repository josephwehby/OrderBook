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

    if (!bid && !ask) return false;

    
    return true;

}

double OrderBook::bestBid() {
    return bid_levels.end()->first;
}

double OrderBook::bestAsk() {
    return ask_levels.begin()->first;
}

void OrderBook::printOrderBook() {
    return;
}

