#include "pricing.hpp"

Order& findMaxBid(std::vector<Order>& bidVector)
{
    Order* highestBidOrder {};
    double highestBidAmount = -1; // for finding min
    for (Order& order : bidVector)
    {
        std::optional<double> price {order.getPrice()};
        // if order isn't market order and price is higher than max, set to min
        if (price && price.value() > highestBidAmount)
        {
            highestBidAmount = price.value();
            highestBidOrder = &order;
        } 
    }

    // TODO: add exception if currentMin didn't change (only market orders)

    return *highestBidOrder;
}

Order& findMinAsk(std::vector<Order>& askVector)
{
    Order* lowestAskOrder {};
    double lowestAskAmount = std::numeric_limits<double>::max(); // for finding min
    for (Order& order : askVector)
    {
        std::optional<double> price {order.getPrice()};
        // if order isn't market order and price is lower than min, set to min
        if (price && price.value() < lowestAskAmount)
        {
            lowestAskAmount = price.value();
            lowestAskOrder = &order;
        } 
    }

    // TODO: add exception if currentMin didn't change (only market orders)

    return *lowestAskOrder;
}

Order& findNearestToMid(const std::vector<Order>& orders, const bool isBid) 
{
    if (isBid)
        return findMaxBid(orders);
    else
        return findMinAsk(orders);
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

bool fillOrder(Order& order, std::vector<Order>& opposingOrders)
{
    // TODO return the orders that were filled
    switch (order.getOrderType())
    {
    using enum OrderType;
    case market:
        while (order.getVolume() > 0)
        {
            
        } 
        break;
    
    default:
        break;
    }
}
