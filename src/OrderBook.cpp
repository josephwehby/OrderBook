#include "OrderBook.hpp"

OrderBook::OrderBook() {
    printf("[!] Orderbook created\n");
}

bool OrderBook::addOrder(std::shared_ptr<Order> order) {
    bool add_order = true;

    Logger::Info("ORDER SUMBITTED");
    switch(order->order_type) {
        case Buy:
            addBid(order);
            removeLevels(Buy);
            break;
        case Sell:
			addAsk(order);
            removeLevels(Sell);
            break;
        default:
            Logger::Debug("INVALID ORDER TYPE");
			add_order = false;
			break;
    }
    
    return add_order;
}

double OrderBook::bestBid() {
    
    if (bid_levels.size() == 0) {
        return -1;
    }

    return bid_levels.rbegin()->first;
}

double OrderBook::bestAsk() {
    
    if (ask_levels.size() == 0) return -1;

    return ask_levels.begin()->first;
}

double OrderBook::getSpread() {
    double spread = bestAsk() - bestBid();
    return spread;
}

void OrderBook::printOrderBook() {
    bool bid, ask;
    bid = true;
    ask = true;
    auto bit = bid_levels.rbegin();
    auto ait = ask_levels.begin();
    
    printf("============================================\n");
    printf("  Spread: %.2f\n", getSpread());
    printf("%5s %23s\n", "BID", "ASK");
    while (bid || ask) {
        
        if (bit != bid_levels.rend()) {
            bit->second->printLevel();
            bit++;
        } else {
            printf("%19s", "");
            bid = false;
        }
        printf("\t");
        if (ait != ask_levels.end()) {
            ait->second->printLevel();
            ait++;
        } else {
            ask = false;
        }
        printf("\n");
    }
    printf("============================================\n");

}

// create a new level and return the price added at
double OrderBook::createNewLevel(std::shared_ptr<Order> order) {
    std::shared_ptr<Level> level;
    level = std::make_shared<Level>(order);

    if (order->order_type == Buy) {
        bid_levels[order->price] = level;
        Logger::Info("NEW BID LEVEL CREATED @ $%.2f FOR %d SHARES", order->price, order->quantity);
    } else {
        ask_levels[order->price] = level;
        Logger::Info("NEW ASK LEVEL CREATED @ $%.2f FOR %d SHARES", order->price, order->quantity);

    }

    return order->price;
}

// returns price order was added at.
double OrderBook::addBid(std::shared_ptr<Order> order) {
    std::shared_ptr<Level> level;
    std::shared_ptr<Order> current_order;
    std::deque <std::shared_ptr<Order>> level_copy;
    unsigned int level_shares, order_shares, i;

    auto bid_it = bid_levels.find(order->price);

    if (bid_it == bid_levels.end() && order->price >= bestAsk()) {
        
        if (bestAsk() == -1) {
            return createNewLevel(order);
        }

        for (auto ask_it = ask_levels.begin(); ask_it != ask_levels.end(); ask_it++) {
            level_shares = ask_it->second->getLevelQuantity();
            if (ask_it->first > order->price){
                break;
            }
            else if (level_shares == order->quantity) {
                ask_levels.erase(ask_it);
                Logger::Info("%d SHARES BOUGHT @ $%.2f", order->quantity, ask_it->first);
                return ask_it->first;
            } else {
                
                level = ask_it->second;
                level_copy = ask_it->second->level_orders;

                for (i = 0; i < level_copy.size(); i++) {
                    current_order = level_copy[i];
                    order_shares = current_order->quantity;
                    
                    if (order_shares >= order->quantity) {
                        current_order->quantity = order_shares - order->quantity;
                        Logger::Info("%d SHARES BOUGHT @ $%.2f", order->quantity, current_order->price);
                        return current_order->price;
                    } else {
                        order->quantity -= order_shares;
                        Logger::Info("%d SHARES BOUGHT @ $%.2f", order_shares, current_order->price);
                        level->level_orders.pop_front();
                    }
                } 
            }
        }

        if (order->quantity > 0) {
            return createNewLevel(order);
        }

    } else {
        
        if (bid_it == bid_levels.end()) return createNewLevel(order);
        
        auto l = bid_it->second;
        l->level_orders.push_back(order);
        Logger::Info("BUY ORDER FOR %d SHARES ADDED @ $%.2f", order->quantity, order->price);
        return order->price;
    }

    return -1;
}

double OrderBook::addAsk(std::shared_ptr<Order> order) {
    std::shared_ptr<Level> level;
    std::shared_ptr<Order> current_order;
    std::deque <std::shared_ptr<Order>> level_copy;
    unsigned int level_shares, order_shares, i;

    auto ask_it = ask_levels.find(order->price);

    if (ask_it == ask_levels.end() && bid_levels.size() != 0) {
        
        if (bestBid() == -1) {
            return createNewLevel(order);
        }

        for (auto bid_it = bid_levels.rbegin(); bid_it != bid_levels.rend(); bid_it++) {
            level_shares = bid_it->second->getLevelQuantity();
            if (bid_it->first < order->price){
                break;
            }
            else if (level_shares == order->quantity) {
                Logger::Info("%d SHARES SOLD @ $%.2f", order->quantity, bid_it->first);
                bid_levels.erase(bid_it->first);
                return ask_it->first;
            } else {
                
                level = bid_it->second;
                level_copy = bid_it->second->level_orders;

                for (i = 0; i < level_copy.size(); i++) {
                    current_order = level_copy[i];
                    order_shares = current_order->quantity;

                    if (order_shares >= order->quantity) {
                        current_order->quantity = order_shares - order->quantity;
                        Logger::Info("%d SHARES SOLD @ $%.2f", order->quantity, current_order->price);
                        return current_order->price;
                    } else {
                        order->quantity -= order_shares;
                        Logger::Info("%d SHARES SOLD @ $%.2f", order_shares, current_order->price);
                        level->level_orders.pop_front();
                    }
                } 
            }
        }

        if (order->quantity > 0) {
            return createNewLevel(order);
        }

    } else {
        
        if (ask_it == ask_levels.end()) return createNewLevel(order);
        
        auto l = ask_it->second;
        l->level_orders.push_back(order);
        Logger::Info("SELL ORDER FOR %d SHARES ADDED @ $%.2f", order->quantity, order->price);
        return order->price;
    }

    return -1;
}

void OrderBook::removeLevels(OrderType order_type) {
    
    std::map<double, std::shared_ptr<Level>> copy;
    
    switch (order_type) {
        case Buy:
            copy = ask_levels;
            for (auto it = copy.begin(); it != copy.end(); it++) {
                if (it->second->getLevelQuantity() == 0) {
                    Logger::Debug("REMOVED $%.2f ASK LEVEL", it->first);
                    ask_levels.erase(it->first);
                }
            }
            break;
        case Sell:
            copy = bid_levels;
            for (auto it = copy.begin(); it != copy.end(); it++) {
                if (it->second->getLevelQuantity() == 0) {
                    Logger::Debug("REMOVED $%.2f BID LEVEL", it->first);
                    bid_levels.erase(it->first);
                }
            }
            break;
        default:
            break;
    }
}