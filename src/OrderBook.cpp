#include "OrderBook.hpp"

OrderBook::OrderBook() {

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
        return 0;
    }

    return bid_levels.rbegin()->first;
}

double OrderBook::bestAsk() {
    
    if (ask_levels.size() == 0) return 0;

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
    
    
    printf("Spread: %.2f\n", getSpread());
    printf("BID\t\tASK\n");
    while (bid || ask) {
        
        if (bit != bid_levels.rend()) {
            bit->second->printLevel();
            bit++;
        } else {
            bid = false;
        }
        std::cout << "\t";
        if (ait != ask_levels.end()) {
            ait->second->printLevel();
            ait++;
        } else {
            ask = false;
        }

        std::cout << "\n";
    }
}

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
