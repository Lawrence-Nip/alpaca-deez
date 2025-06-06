#ifndef TRADING_SERVICE_H
#define TRADING_SERVICE_H

#include <string>
#include <nlohmann/json.hpp> //dependency, interface

// TradingService Interface
class ITradingService
{
public:
    virtual void checkAccount() = 0;
    virtual double getLastPrice(const std::string &symbol) = 0;
    virtual void placeOrder(const std::string &symbol, int qty, const std::string &side) = 0;
    virtual nlohmann::json fetchMarketData(const std::string& symbol);
    virtual ~ITradingService() = default;
};

#endif //TRADING_SERVICE_H