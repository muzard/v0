#pragma once
#include <iostream>
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
            // get the cheapest pair (price, PriceLevel)
            auto it = orderBook.asks.begin();

            // iterate through levels
            while ((o.quantity > 0) && (it != orderBook.asks.end()) && (it->first <= o.price))
            {
                while (o.quantity > 0 && !(it->second.orders.empty()))
                {
                    auto& ask = it->second.orders.front();
                    // if opposing order covers order, fill and break
                    // else get next order
                    if (o.quantity < ask.quantity)
                    {
                        ask.quantity -= o.quantity;
                        o.quantity = 0;
                        break;
                    }
                    else // o.quantity >= ask.quantity
                    {
                        o.quantity -= ask.quantity;
                        // ask.quantity is filled -> remove from queue
                        it->second.orders.pop_front();
                        continue;                        
                    }
                }
            // remove level if empty
            if (orderBook.asks.at(it->first).orders.empty())
                it = orderBook.asks.erase(it);
            else
                ++it;
            }

            // 2) if order not filled, add to book
            if ((o.quantity > 0) && (o.type == OrderType::limit))
            {
                BookOrder bookOrd {o.orderId, o.quantity};
                orderBook.addBid(bookOrd, o.price);
            }
            // 4) fillOrKill and other types of orders
        }
        else
        {   // get the cheapest pair (price, PriceLevel)
            auto it = orderBook.bids.begin();

            // iterate through levels
            while ((o.quantity > 0) && (it != orderBook.bids.end()) && (it->first >= o.price))
            {
                while (o.quantity > 0 && !(it->second.orders.empty()))
                {
                    auto& bid = it->second.orders.front();
                    // if opposing order covers order, fill and break
                    // else get next order
                    if (o.quantity < bid.quantity)
                    {
                        bid.quantity -= o.quantity;
                        o.quantity = 0;
                        break;
                    }
                    else // o.quantity >= ask.quantity
                    {
                        o.quantity -= bid.quantity;
                        // ask.quantity is filled -> remove from queue
                        it->second.orders.pop_front();
                        continue;                        
                    }
                }
            // remove level if empty
            if (orderBook.bids.at(it->first).orders.empty())
                it = orderBook.bids.erase(it);
            else
                ++it;
            }

            // 2) if order not filled, add to book
            if ((o.quantity > 0) && (o.type == OrderType::limit))
            {
                BookOrder bookOrd {o.orderId, o.quantity};
                orderBook.addAsk(bookOrd, o.price);
            }
            // 4) fillOrKill and other types of orders
            // Match ask order against bids
            // (Matching logic to be implemented)
        }
    }
};
