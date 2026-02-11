#pragma once

#include <deque>
#include "BookOrder.hpp"

struct PriceLevel
{
    std::deque<BookOrder> orders {}; // queue of orders

    void addOrder(BookOrder o)
    {
        orders.push_back(o);
    }
};
