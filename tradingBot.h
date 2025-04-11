#ifndef TRADING_BOT_H
#define TRADING_BOT_H

#include <memory>
#include <string>
#include "tradingService.h"
#include "tradingStrategy.h"
#include "marketDataService.h"

class TradingBot
{
public:
    TradingBot(std::shared_ptr<ITradingService> tradingService,
               std::shared_ptr<MarketDataService> marketData,
               std::shared_ptr<ITradingStrategy> strategy);

    void run(const std::string &symbol);

private:
    std::shared_ptr<ITradingService> tradingService;
    std::shared_ptr<MarketDataService> marketData;
    std::shared_ptr<ITradingStrategy> strategy;
};

#endif //TRADING_BOT_H