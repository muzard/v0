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

Order& findNearestToMid(std::vector<Order>& orders, const bool checkBids) 
{
    if (checkBids)
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

// returns bool if order needs to be added to the books
bool fillOrder(Order& order, std::vector<Order>& opposingOrders)
{
    // TODO return the orders that were filled
    // add some kind of notification for filling (bidder and asker)?
    const bool isBid = order.isBid();
    switch (order.getOrderType())
    {
    using enum OrderType;
    case market:
        while (order.getVolume() > 0)
        {   // find the lowest order matching this
            // and fill until filled. will walk the book
            Order& optimalOpposingOrder {findNearestToMid(opposingOrders, !isBid)};
            optimalOpposingOrder.fillOrder(order.getVolume());
        }
        return true; 
    case limit:
        while (order.getVolume() > 0)
        {   // find the lowest order matching this
            Order& optimalOpposingOrder {findNearestToMid(opposingOrders, !isBid)}; // order.getPrice() is safe as this cannot be a market order
            if (optimalOpposingOrder.getPriceOrZero() <= order.getPrice()) 
                optimalOpposingOrder.fillOrder(order.getVolume());
            else break; // break if price is over limit
            if (order.getVolume() == 0)
                return true;
        }
        return false; // if we haven't cleared the order before hitting the limit
    case fillAndKill: // works like limit, except do not post the order after
        while (order.getVolume() > 0)
        {   // find the lowest order matching this
            Order& optimalOpposingOrder {findNearestToMid(opposingOrders, !isBid)}; // order.getPrice() is safe as this cannot be a market order
            if (optimalOpposingOrder.getPriceOrZero() <= order.getPrice()) 
                optimalOpposingOrder.fillOrder(order.getVolume());
            else break;
        }
        return true; // kill order after filling
    case fillOrKill:
        int volumeUnderLimitPrice {0};
        // calculate the volume under orders price
        for (Order& opposingOrder: opposingOrders)
        {
            if (opposingOrder.getPrice() <= order.getPrice())
                volumeUnderLimitPrice += opposingOrder.getVolume();
        }

        if (volumeUnderLimitPrice <= order.getVolume()) // fill
        {
            while (order.getVolume() > 0)
            {   
                Order& optimalOpposingOrder {findNearestToMid(opposingOrders, !isBid)}; // order.getPrice() is safe as this cannot be a market order
                if (optimalOpposingOrder.getPriceOrZero() <= order.getPrice()) 
                    optimalOpposingOrder.fillOrder(order.getVolume());
                else break;
            }    
        } else // kill
        {
            return true;
        }
    default:
        return true; // don't add orders we haven't implemented yet
    }
}
