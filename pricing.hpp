#pragma once
#include "order.hpp"
#include <vector>

Order& findMaxBid(const std::vector<Order>& bidVector);
Order& findMinAsk(const std::vector<Order>& askVector);
int findVolume(double price, const std::vector<Order>& orders);
bool fillOrder(Order& order);
Order& findNearestToMid(const std::vector<Order>& orders, const bool isBid);
