#pragma once

#include "OrderBook.hpp"
#include "Order.hpp"

class Matcher
{
private:
    OrderBook& orderBook;
public:
    Matcher(OrderBook& ob) : orderBook{ob} {}

    void match(Order& o)
    {
        if (o.isBid)
        {
            // Match bid order against asks
            // (Matching logic to be implemented)

            // 1) while lower orders exist -> fill
            for ()
            // 2) if order not filled, add to book
            // 3) delete empty PriceLevels

            // 4) fillOrKill and other types of orders
        }
        else
        {
            // Match ask order against bids
            // (Matching logic to be implemented)
        }
    }
};
