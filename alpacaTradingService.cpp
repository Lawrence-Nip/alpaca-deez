#include <iostream>
#include "alpacaTradingService.h"
using json = nlohmann::json;

// Alpaca Trading Service

AlpacaTradingService::AlpacaTradingService(std::shared_ptr<IHttpService> httpService)
    : http(std::move(httpService)) {}

void AlpacaTradingService::checkAccount()
{
    std::string response = http->get("/v2/account");
    json j = json::parse(response);
    std::cout << "Account Info:\n"
              << j.dump(4) << std::endl;
}

double AlpacaTradingService::getLastPrice(const std::string &symbol)
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

void AlpacaTradingService::placeOrder(const std::string &symbol, int qty, const std::string &side)
{
    json order = {
        {"symbol", symbol},
        {"qty", qty},
        {"side", side},
        {"type", "market"},
        {"time_in_force", "gtc"}};
    std::string response = http->post("/v2/orders", order.dump());
    json j = json::parse(response);
    std::cout << "Order Response:\n"
              << j.dump(4) << std::endl;
}

nlohmann::json AlpacaTradingService::fetchMarketData(const std::string &symbol)
{
    std::string endpoint = "/v2/stocks/bars/latest?symbols=" + symbol;
    std::string response = http->getMarketData(endpoint);
    try
    {
        json j = json::parse(response);
        return j;
    }
    catch (...)
    {
        std::cerr << "Failed to get price for " << symbol << std::endl;
        return nullptr;
    }
}