#include "orderBook.hpp"
#include "pricing.hpp"


OrderBook::OrderBook(std::string_view ticker)
        : m_assetTicker {ticker}
        {}

void OrderBook::addOrder(Order order)
    {
        std::vector<Order>& orderVector {order.isBid() ? m_bids : m_asks};
        // TODO implement adding order
    }

void OrderBook::setMidPrice() 
    {
        m_midprice = ((findMaxBid(m_bids) + findMinAsk(m_asks)) / 2);
    }

void OrderBook::setMicroPrice()
    {
        const double bestBid = findMaxBid(m_bids);
        const double bestAsk = findMinAsk(m_asks);
        const int bidVolume = findVolume(bestBid, m_bids);
        const int askVolume = findVolume(bestAsk, m_asks);
        const double totalVolume = bidVolume + askVolume;
        // total volume is a double so that the following divisions work

        const double buySide = (bidVolume / totalVolume) * bestBid;
        const double sellSide = (askVolume / totalVolume) * bestAsk;

        m_microprice = buySide + sellSide;

    }

