#pragma once
#include <string>
#include <string_view>

class Participant
{
private:
    inline static int nextId {0};
    std::string m_name;
    int m_id {0};
    double m_cashBalance {0.0};
    double m_assetBalance {0.0};

public:
    Participant(std::string_view name, double startingBalance)
    : m_name {name}
    , m_cashBalance {startingBalance}
    {}

    void depositMoney(double amount)
    {
        if (amount <= 0.0)
            ;// error handling
        else
            m_cashBalance += amount;
    }

    void withdrawMoney(double amount)
    {
        if (amount >= m_cashBalance)
            m_cashBalance = 0;
        else
            m_cashBalance -= amount; 
    }
};
