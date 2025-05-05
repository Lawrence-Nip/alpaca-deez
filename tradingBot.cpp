#include "tradingBot.h"
#include "alpacaTradingService.h"
#include "thresholdStrategy.h"
#include <iostream>

TradingBot::TradingBot(std::shared_ptr<ITradingService> tradingService,
                       std::shared_ptr<ITradingStrategy> strategy)
    : tradingService(std::move(tradingService)),
      strategy(std::move(strategy)) {}

void TradingBot::run(const std::string &symbol)
{
    // tradingService->checkAccount();
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

void TradingBot::runWithMarketData(const std::string &symbol)
{
    auto marketData = tradingService->fetchMarketData(symbol);

    // Process market data (example: print the data)
    // for (const auto& bar : marketData["bars"]) {
    //     std::cout << "Time: " << bar["t"] << ", Open: " << bar["o"]
    //                 << ", Close: " << bar["c"] << ", High: " << bar["h"]
    //                     << ", Low: " << bar["l"]<< ", Volume: " << bar["v"] << std::endl;
    // }

    // Use the strategy to make decisions based on market data
    strategy->analyse(marketData);
}
