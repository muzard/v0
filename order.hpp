#pragma once
#include <optional>
#include <iostream>

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
    inline static int nextId {0};
    int m_size {}; // trade only full units for simplicity
    std::optional<double> m_mainPrice {}; // main price for orders other than market
    std::optional<int> m_icebergVisibleSize{}; // size of the iceberg "peak"
    bool m_isBid {1}; // true if bid, assumed to be true
    OrderType m_orderType {OrderType::market};
    int m_id {0};
public:
    Order(int volume, std::optional<double> price, std::optional<int> icebergSize, bool isBid, OrderType orderType)
        : m_size {volume}, m_mainPrice {price}, m_icebergVisibleSize {icebergSize}
        , m_isBid {isBid}, m_orderType {orderType}, m_id {++nextId}
        {}

    bool isBid() const {return m_isBid;}
    std::optional<double> getPrice() const {return m_mainPrice;}
    double getPriceOrZero() const {return m_mainPrice || 0;} // DANGEROUS

    int getVolume() const {return m_size;}
    OrderType getOrderType() const {return m_orderType;}


    // returns num of units filled
    int fillOrder(int toFill)
    {
        if (toFill >= m_size)
        {
            const int temp {m_size}; // TODO make sure this copies -> works
            m_size = 0;
            // REMOVE FROM ASK/BID LIST

            return temp;
        }
        else
        {
            const int temp {toFill - m_size};
            m_size -= toFill;
            return temp;
        }
    }
};
