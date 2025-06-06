#ifndef TRADING_BOT_H
#define TRADING_BOT_H

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "tradingService.h"
#include "tradingStrategy.h"

class TradingBot
{
public:
    TradingBot(std::shared_ptr<ITradingService> tradingService,
               std::shared_ptr<ITradingStrategy> strategy);

    void run(const std::string &symbol);
    void runWithMarketData(const std::string& symbol);

private:
    std::shared_ptr<ITradingService> tradingService;
    std::shared_ptr<ITradingStrategy> strategy;
};

#endif //TRADING_BOT_H