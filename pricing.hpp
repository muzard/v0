#pragma once
#include "order.hpp"
#include <vector>

double findMaxBid(const std::vector<Order>& bidVector);
double findMinAsk(const std::vector<Order>& askVector);
int findVolume(double price, const std::vector<Order>& orders);
