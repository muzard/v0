#include <iostream>
#include <optional>
#include "order.hpp"
#include "orderBook.hpp"

// Small compatibility stub: the project declares a single-arg fillOrder in pricing.hpp
// but some builds don't provide it. Provide a no-op implementation here so tests
// can exercise the public API without changing project sources.
bool fillOrder(Order& /*order*/)
{
    return false; // indicate "not filled" so orders get posted to the book
}

int main()
{
    OrderBook ob{"TEST"};

    // Populate the book with realistic depth on both sides.
    // Several prices and multiple orders per price.
    for (int price = 100; price >= 91; --price) {
        for (int i = 0; i < 3; ++i) {
            // bids: isBid = true
            ob.addOrder(Order(10 + i, std::nullopt, true, OrderType::limit, static_cast<double>(price)));
        }
    }

    for (int price = 101; price <= 110; ++price) {
        for (int i = 0; i < 3; ++i) {
            // asks: isBid = false
            ob.addOrder(Order(5 + i, std::nullopt, false, OrderType::limit, static_cast<double>(price)));
        }
    }

    // Call the price calculation routines — they should run without crashing
    ob.setMidPrice();
    ob.setMicroPrice();

    std::cout << "Test completed: order book populated and price calculations executed." << std::endl;
    return 0;
}
