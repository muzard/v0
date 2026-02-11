#pragma once
#include <cstdint>

enum class OrderType : uint8_t
{
    market,
    limit,
}

// incoming order with price info and side info
struct Order
{
    int orderId {};
    int price {};
    bool isBid {};
    int quantity {};
    OrderType type {OrderType::limit};
}
