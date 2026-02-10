#include <map>
#include <functional>
#include "PriceLevel.hpp"

class OrderBook
{
private:
    std::map<int, PriceLevel, std::greater<int>> bids {}; // map of price keys in ticks and order queues as values
    std::map<int, PriceLevel> asks {};
public: // TODO: add matching before adding new orders
    void addBid(Order o, int price)
    {
        if (bids.contains(price))
            bids[price].addOrder(o);
        else
            bids[price] = PriceLevel{o} 
    }

    void addAsk(Order o, int price)
    {
        if (asks.contains(price))
            asks[price].addOrder(o);
        else
            asks[price] = PriceLevel{o} 
    }
};
