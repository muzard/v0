#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "order.hpp"

class OrderBook
{
private:
    std::string m_assetTicker {"????"};
    std::vector<Order> m_bids{}; // vector holding asks
    std::vector<Order> m_asks{};// vector holding bids
    double m_midprice {0.0};
    double m_microprice {0.0};

public:
    explicit OrderBook(std::string_view ticker);

    void addOrder(Order order);

    void setMidPrice();

    void setMicroPrice();
};
