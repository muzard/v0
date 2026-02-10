#include "OrderBook.hpp"

int main()
{
    OrderBook orderBook;

    // Create some sample orders
    Order buyOrder1 = {1, 1};  // id, quantity
    Order buyOrder2 = {2, 2};
    Order sellOrder1 = {3, 1};
    Order sellOrder2 = {4, 2};

    // Add orders to the order book
    orderBook.addBid(buyOrder1, 100);
    orderBook.addBid(buyOrder2, 101);
    orderBook.addAsk(sellOrder1, 102);
    orderBook.addAsk(sellOrder2, 103);

    return 0;
}
