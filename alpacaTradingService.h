#ifndef ALPACA_TRADING_SERVICE_H
#define ALPACA_TRADING_SERVICE_H

#include "tradingService.h"
#include "httpService.h"
#include <string>
#include <memory>

// Alpaca Trading Service
class AlpacaTradingService : public ITradingService
{
public:
    explicit AlpacaTradingService(std::shared_ptr<IHttpService> httpService);

    void checkAccount() override;
    double getLastPrice(const std::string &symbol) override;
    void placeOrder(const std::string &symbol, int qty, const std::string &side) override;

private:
    std::shared_ptr<IHttpService> http;
};


#endif //ALPACA_TRADING_SERVICE_H