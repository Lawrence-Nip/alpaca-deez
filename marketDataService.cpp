#include <iostream>
#include "marketDataService.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

// MarketDataService
MarketDataService::MarketDataService(std::shared_ptr<IHttpService> httpService)
    : http(std::move(httpService)) {}

double MarketDataService::getLastPrice(const std::string &symbol)
{
    std::string endpoint = "/v2/stocks/" + symbol + "/quotes/latest";
    std::string response = http->getMarketData(endpoint);
    try
    {
        json j = json::parse(response);
        return j["quote"]["ap"].get<double>(); // 'ap' is ask price
    }
    catch (...)
    {
        std::cerr << "Failed to get price for " << symbol << ", defaulting to $0.0\n";
        return 0.0;
    }
}