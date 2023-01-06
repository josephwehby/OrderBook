#ifndef ORDER_HPP
#define ORDER_HPP

enum OrderType {Buy, Sell};

class Order {
    public:
        Order();
    private:
        OrderType  order_type;
        unsigned int quantity;
        double price; 
        long user_id; // pointer to user instead most likely
        double time;
};

#endif