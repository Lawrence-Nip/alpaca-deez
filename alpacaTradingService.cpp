#include <iostream>
#include "alpacaTradingService.h"
#include <nlohmann/json.hpp>
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