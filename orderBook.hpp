#pragma once

#include <map>
#include <functional>
#include "PriceLevel.hpp"

class OrderBook
{
private:
    std::map<int, PriceLevel, std::greater<int>> bids {}; // map of price keys in ticks and order queues as values
    std::map<int, PriceLevel> asks {};
public: // TODO: add matching before adding new orders
    void addBid(BookOrder o, int price)
    {
        auto [it, inserted] = bids.emplace(price, PriceLevel{});
        it->second.addOrder(o);
    }

    void addAsk(BookOrder o, int price)
    {
        auto [it, inserted] = asks.emplace(price, PriceLevel{});
        it->second.addOrder(o);
    }

    // unsafe, used for testing for now
    std::map<int, PriceLevel, std::greater<int>>& getBids()
    {
        return bids;
    }

    std::map<int, PriceLevel>& getAsks() {return asks;}

    friend class Matcher;
};
