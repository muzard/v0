#pragma once
#include "pricing.hpp"

double findMaxBid(const std::vector<Order>& bidVector)
{
    double highestBid = -1; // for finding min
    for (const Order& order : bidVector)
    {
        std::optional<double> price {order.getPrice()};
        // if order isn't market order and price is higher than max, set to min
        if (price && price.value() > highestBid)
        {
            highestBid = price.value();
        } 
    }

    // TODO: add exception if currentMin didn't change (only market orders)

    return highestBid;
}

double findMinAsk(const std::vector<Order>& askVector)
{
    double lowestAsk = std::numeric_limits<double>::max(); // for finding min
    for (const Order& order : askVector)
    {
        std::optional<double> price {order.getPrice()};
        // if order isn't market order and price is lower than min, set to min
        if (price && price.value() < lowestAsk)
        {
            lowestAsk = price.value();
        } 
    }

    // TODO: add exception if currentMin didn't change (only market orders)

    return lowestAsk;
}

int findVolume(double price, const std::vector<Order>& orders)
{
    int volume = 0;
    for (const Order& order : orders)
    {
        const auto orderPrice = order.getPrice();
        if (orderPrice && orderPrice.value() == price)
        {
            volume += order.getVolume();
        }
    }

    return volume;
}
