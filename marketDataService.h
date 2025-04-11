#ifndef MARKET_DATA_SERVICE_H
#define MARKET_DATA_SERVICE_H

#include <memory>
#include "httpService.h"

// MarketDataService
class MarketDataService
{
public:
    explicit MarketDataService(std::shared_ptr<IHttpService> httpService);

    double getLastPrice(const std::string &symbol);

private:
    std::shared_ptr<IHttpService> http;
};

#endif //MARKET_DATA_SERVICE_H