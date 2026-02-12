#include <iostream>

#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Order.hpp"

#include "tests/test.cpp"

int main()
{
    OrderBook orderBook;
    Matcher matcher{orderBook};

    test(orderBook, matcher);
    std::cout << "exited test()\n";

    return 0;
}
