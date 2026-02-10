#pragma once

#include <deque>
#include "Order.hpp"

struct PriceLevel
{
    std::deque<Order> orders {}; // queue of orders

    void addOrder(Order o)
    {
        orders.push_back(o);
    }
};
