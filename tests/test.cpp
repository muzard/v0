#include <cassert>
#include <iostream>

#include "../OrderBook.hpp"
#include "../Matcher.hpp"

void test(OrderBook& ob, Matcher& matcher)
{
    std::cout << "entered tester \n";
    // populate order book with asks on different price levels
    BookOrder ask1 {1, 1}; // id, quantity
    BookOrder ask2 {2, 2};
    BookOrder ask3 {3, 3};
    ob.addAsk(ask1, 1);
    ob.addAsk(ask2, 2);
    ob.addAsk(ask3, 3);

    // Test matching a bid order
    Order bid {4, 4, true, 8, OrderType::limit}; // id, price, isBid, quantity, type
    matcher.match(bid);

    // expect book to have PriceLevel 4, including order with id 4 and quantity 2 
    const auto& bids = ob.getBids();
    const auto& asks = ob.getAsks();
    assert(bids.contains(4));
    assert(bids.at(4).orders.front().quantity == 2);

    assert(asks.empty());
    std::cout << "asks were cleared and partially filled bid was added to book\n";

    Order counterOrder {5, 4, false, 2, OrderType::limit};
    matcher.match(counterOrder);

    const auto& newBids = ob.getBids();
    const auto& newAsks = ob.getAsks();
    assert(newBids.empty());
    assert(newAsks.empty());
    std::cout << "whole book clears when offer is countered\n";
}
