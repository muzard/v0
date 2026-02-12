#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Order.hpp"

int main()
{
    OrderBook orderBook;
    Matcher matcher{orderBook};

    // Create some sample orders
    BookOrder buyOrder1 = {1, 1};  // id, quantity
    BookOrder buyOrder2 = {2, 2};

    // Add orders to the order book
    orderBook.addBid(buyOrder1, 101);
    orderBook.addBid(buyOrder2, 201);

    Order sellOrder {3, 100, true, 10, OrderType::limit};

    matcher.match(sellOrder);

    return 0;
}
