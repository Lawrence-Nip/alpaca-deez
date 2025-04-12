#include "tradingBot.h"
#include <iostream>

TradingBot::TradingBot(std::shared_ptr<ITradingService> tradingService,
                       std::shared_ptr<ITradingStrategy> strategy)
    : tradingService(std::move(tradingService)),
      strategy(std::move(strategy)) {}

void TradingBot::run(const std::string &symbol)
{
    tradingService->checkAccount();
    double price = tradingService->getLastPrice(symbol);
    if (price <= 0.0)
    {
        std::cerr << "Invalid price received for " << symbol << ", skipping trading.\n";
        return;
    }
    std::cout << "Current price of " << symbol << " is $" << price << std::endl;
    if (strategy->shouldBuy(price))
    {
        tradingService->placeOrder(symbol, 1, "buy");
    }
    else if (strategy->shouldSell(price))
    {
        tradingService->placeOrder(symbol, 1, "sell");
    }
    else
    {
        std::cout << "No action needed for " << symbol << std::endl;
    }
}
