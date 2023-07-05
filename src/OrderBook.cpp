#include "OrderBook.hpp"

OrderBook::OrderBook() {

}

bool OrderBook::addOrder(std::shared_ptr<Order> order) {
    
    bool add_order = true;

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
        return 0;
    }

    return bid_levels.rbegin()->first;
}

double OrderBook::bestAsk() {
    
    if (ask_levels.size() == 0) return 0;

    return ask_levels.begin()->first;
}

void OrderBook::printOrderBook() {
    
    std::cout << "BID" << std::endl;
    for (auto bit = bid_levels.rbegin(); bit != bid_levels.rend(); bit++) {  
        bit->second->printLevel();
    }
    
    std::cout << "ASK" << std::endl;
    for (auto ait = ask_levels.begin(); ait != ask_levels.end(); ait++) {  
        ait->second->printLevel();
    }
    
}

bool OrderBook::addBid(std::shared_ptr<Order> order) {
    
    unsigned int i;
    double best_ask;
	int available_shares, share_count;
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
				
				for (i = 0; i < ask_level->level_orders.size(); i++) {
					if (share_count == (int) ask_level->level_orders[i]->quantity) {
						ask_level->level_orders.pop_front();
						break;
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

bool OrderBook::addAsk(std::shared_ptr<Order> order) {
   
    auto ask_it = ask_levels.find(order->price);

    // if price level does not exist then create a new level with the current bid submitted
    if (ask_it == ask_levels.end()) {
        auto l = std::make_shared<Level>(order);
        ask_levels[order->price] = l;
        return true;
    
    // if level already exists then add order into the level_orders map
    } else {
        auto l = ask_it->second;
        l->level_orders.push_back(order);
        return true;
    }

    return false;
}
