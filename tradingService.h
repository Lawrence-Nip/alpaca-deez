#ifndef TRADING_SERVICE_H
#define TRADING_SERVICE_H

#include <string>

// TradingService Interface
class ITradingService
{
public:
    virtual void checkAccount() = 0;
    virtual double getLastPrice(const std::string &symbol) = 0;
    virtual void placeOrder(const std::string &symbol, int qty, const std::string &side) = 0;
    virtual ~ITradingService() = default;
};

#endif //TRADING_SERVICE_H