#include "OrderBook.hpp"

OrderBook::OrderBook() {
    printf("[!] Orderbook created\n");
}

bool OrderBook::addOrder(std::shared_ptr<Order> order) {
    
    bool add_order = true;
    std::cout << "ORDER SUMBITTED" << std::endl;
    switch(order->order_type) {
        case Buy:
            addBid(order);
            break;
        case Sell:
			addAsk(order);
            break;
        default:
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
}

// create a new level and return the price added at
double OrderBook::createNewLevel(std::shared_ptr<Order> order) {
    std::shared_ptr<Level> level;
    level = std::make_shared<Level>(order);

    if (order->order_type == Buy) {
        bid_levels[order->price] = level;
    } else {
        ask_levels[order->price] = level;
    }

    return order->price;
}

// returns price order was added at.
double OrderBook::addBid(std::shared_ptr<Order> order) {
    unsigned int available_shares;
    
    auto bid_it = bid_levels.find(order->price);
	std::shared_ptr<Level> level;

    if (bid_it == bid_levels.end() && order->price >= bestAsk()) {
        
        if (bestAsk() == -1) {
            return createNewLevel(order);
        }

        for (auto ask_it = ask_levels.begin(); ask_it != ask_levels.end(); ask_it++) {
            available_shares = ask_it->second->getLevelQuantity();
            if (available_shares == order->quantity) {
                ask_levels.erase(ask_it);
                return ask_it->first;
            } else {
                level = ask_it->second;
                for (auto order_it = level->level_orders.begin(); order_it != level->level_orders.end(); order_it++) {

                } 
            }
        }


    } else {
        auto l = bid_it->second;
        l->level_orders.push_back(order);
        return order->price;
    }

    return -1;
}

/*
bool OrderBook::addBid(std::shared_ptr<Order> order) {
    
    unsigned int i;
    double best_ask;
	int available_shares, share_count, current_order_quantity, temp;
    auto bid_it = bid_levels.find(order->price);
	
    
	// if price level does not exist then create a new level with the current bid submitted
    if (bid_it == bid_levels.end()) {
		best_ask = bestAsk();
        
		if (order->price >= best_ask && best_ask != 0) {
			auto ask_level = ask_levels.begin()->second;
			available_shares = ask_level->getLevelQuantity() - order->quantity;
			
			if (available_shares == 0) {
				ask_levels.erase(best_ask);
			
			// loop through each order on the level and subtract shares until none remain
			} else if (available_shares > 0) {
				ask_level->level_orders;
				share_count = order->quantity;
				
                // delete orders and fix quantity 
				for (i = 0; i < ask_level->level_orders.size(); i++) {
                    
                    current_order_quantity = (int) ask_level->level_orders[i]->quantity;
                    
                    if (share_count == current_order_quantity) {    
                        share_count -= current_order_quantity;
						ask_level->level_orders.pop_front();

					} else if (share_count < current_order_quantity){
                        temp = current_order_quantity - share_count;
                        share_count = 0;
                        ask_level->level_orders[i]->quantity = temp; 
                    
                    }
                    
                    if (share_count == 0) {
                        return true;
                    } else {
                        order->quantity = share_count;
                        auto new_level = std::make_shared<Level>(order);
			            bid_levels[order->price] = new_level;
			            return true; 
                    }
				}
			} else {
				return false;
			}

		} else {
			auto new_level = std::make_shared<Level>(order);
			bid_levels[order->price] = new_level;
			return true;
		} 
    // if level already exists then add order into the level_orders map
    } else {
        auto l = bid_it->second;
        l->level_orders.push_back(order);
        return true;
    }

    return false;
}
*/
double OrderBook::addAsk(std::shared_ptr<Order> order) {
   
    auto ask_it = ask_levels.find(order->price);

    // if price level does not exist then create a new level with the current bid submitted
    if (ask_it == ask_levels.end()) {
       return createNewLevel(order);
    
    // if level already exists then add order into the level_orders map
    } else {
        auto l = ask_it->second;
        l->level_orders.push_back(order);
        return order->price;
    }

    return -1;
}
