#include <optional>
#include <string>
#include <vector>

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
    void addOrder(Order order)
    {
        std::vector<Order>& orderVector {order.isBid() ? m_bids : m_asks};
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
    bool isBid() {return orderIsBid;}
};

int main()
{
    return 0;
}
