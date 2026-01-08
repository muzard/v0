#pragma once
#include "order.hpp"
#include <vector>

Order& findMaxBid(std::vector<Order>& bidVector);
Order& findMinAsk(std::vector<Order>& askVector);
int findVolume(double price, const std::vector<Order>& orders);
bool fillOrder(Order& order);
Order& findNearestToMid(std::vector<Order>& orders, const bool isBid);
bool fillOrder(Order& order, std::vector<Order>& opposingOrders);
