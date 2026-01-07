#pragma once
#include <optional>

enum class OrderType
{
    market,
    limit,
    fillOrKill,
    fillAndKill,
    hidden,
    iceberg,
};

class Order
{
private:
    int m_size {}; // trade only full units for simplicity
    std::optional<double> m_mainPrice {}; // main price for orders other than market
    std::optional<int> m_icebergVisibleSize{}; // size of the iceberg "peak"
    bool m_isBid {1}; // true if bid, assumed to be true
    OrderType m_orderType {OrderType::market};
public:
    bool isBid() const {return m_isBid;}
    std::optional<double> getPrice() const {return m_mainPrice;}

    int getVolume() const {return m_size;}
    OrderType getOrderType() const {return m_orderType;}

    void editSize(int toFill)
    {
        m_size -= toFill;
    }
};
