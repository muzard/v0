#include <optional>
#include <string>
#include <vector>
#include <string_view>
#include <limits>

enum class OrderType
{
    market,
    limit,
    fillOrKill,
    fillAndKill,
    hidden,
    iceberg,
};

class OrderBook
{
private:
    std::string m_assetTicker {"????"};
    std::vector<Order> m_bids{}; // vector(?) holding asks
    std::vector<Order> m_asks{};// vector holding bids
    double m_midprice {0.0};
    double m_microprice {0.0};

public:
    OrderBook(std::string_view ticker)
        : m_assetTicker {ticker}
        {}

    void addOrder(Order order)
    {
        std::vector<Order>& orderVector {order.isBid() ? m_bids : m_asks};
    }

    void calculateMidPrice() 
    {
        m_midprice = ((findMaxBid(m_bids) + findMinAsk(m_asks)) / 2);
    }
};

class Order
{
private:
    int m_size {}; // trade only full units for simplicity
    std::optional<double> m_mainPrice {}; // main price for orders other than market
    std::optional<int> m_icebergVisibleSize{}; // size of the iceberg "peak"
    bool orderIsBid {1}; // true if bid, assumed to be true
public:
    bool isBid() const {return orderIsBid;}
    std::optional<double> getPrice() const {return m_mainPrice;}
};

double findMaxBid(std::vector<Order>& bidVector)
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

double findMinAsk(std::vector<Order>& bidVector)
{
    double lowestAsk = std::numeric_limits<double>::max(); // for finding min
    for (const Order& order : bidVector)
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
/*
TODO: find the midprice and set it to the member

1) filter the bid and ask vectors to only include orders with a price

2) take the highest bid and lowest ask

3) set the average to midprice member var

+) calculate the weighted averages and set microprice
*/

int main()
{
    return 0;
}
