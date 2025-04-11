#include <iostream>
#include <string>
#include <memory>

#include "tradingBot.h"
#include "curlService.h"
#include "alpacaTradingService.h"
#include "thresholdStrategy.h"

/*to do:
1. custom options to buy/sell
2. custom options for stocks/bonds/commodities/crypto/forex
3. graphical UI
4. implement some trading algorithms
5. separate modules into files DONE
6. tidy up build process (use makefiles/cmake) DONE
*/

int main()
{
    const std::string BASE_URL = "https://paper-api.alpaca.markets";
    const std::string MARKET_DATA_URL = "https://data.alpaca.markets";
    auto httpService = std::make_shared<CurlHttpService>(BASE_URL, MARKET_DATA_URL);
    auto tradingService = std::make_shared<AlpacaTradingService>(httpService);
    auto marketData = std::make_shared<MarketDataService>(httpService);
    auto strategy = std::make_shared<ThresholdStrategy>();

    TradingBot bot(tradingService, marketData, strategy);

    // httpService->getMarketData("stocks/AAPL/quotes/latest");

    // marketData->getLastPrice("APPL");
    bot.run("TSLA");

    return 0;
}
