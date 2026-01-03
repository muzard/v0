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

    void setMidPrice() 
    {
        m_midprice = ((findMaxBid(m_bids) + findMinAsk(m_asks)) / 2);
    }

    void setMicroPrice()
    {
        const double bestBid = findMaxBid(m_bids);
        const double bestAsk = findMinAsk(m_asks);
        const int bidVolume = findVolume(bestBid, m_bids);
        const int askVolume = findVolume(bestAsk, m_asks);
        const int totalVolume = bidVolume + askVolume;

        const double buySide = (bidVolume / totalVolume) * bestBid;
        const double sellSide = (askVolume / totalVolume) * bestAsk;

        m_microprice = buySide + sellSide;

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
    int getVolume() const {return m_size;}
};

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
}

int main()
{
    return 0;
}
