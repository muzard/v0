#include "orderBook.hpp"
#include "pricing.hpp"


OrderBook::OrderBook(std::string_view ticker)
        : m_assetTicker {ticker}
        {}

void OrderBook::addOrder(Order order)
    {
        std::vector<Order>& orderVector {order.isBid() ? m_bids : m_asks};
        // fill order, if it didn't fill (false) add it to the book
        if (!(fillOrder(order)))
            orderVector.push_back(order);
    }

void OrderBook::setMidPrice() 
    {
        m_midprice = ((findMaxBid(m_bids).getPriceOrZero() + findMinAsk(m_asks).getPriceOrZero()) / 2);
    }

void OrderBook::setMicroPrice()
    {
        const double bestBid = findMaxBid(m_bids).getPriceOrZero();
        const double bestAsk = findMinAsk(m_asks).getPriceOrZero();
        const int bidVolume = findVolume(bestBid, m_bids);
        const int askVolume = findVolume(bestAsk, m_asks);
        const double totalVolume = bidVolume + askVolume;
        // total volume is a double so that the following divisions work

        const double buySide = (bidVolume / totalVolume) * bestBid;
        const double sellSide = (askVolume / totalVolume) * bestAsk;

        m_microprice = buySide + sellSide;

    }

