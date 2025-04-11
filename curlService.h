#ifndef CURL_SERVICE_H
#define CURL_SERVICE_H

#include "httpService.h"
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s);

// Concrete Curl HTTP Service
class CurlHttpService : public IHttpService
{
public:
    explicit CurlHttpService(const std::string& baseUrl, const std::string& marketDataUrl);

    std::string get(const std::string &endpoint) override;

    std::string getMarketData(const std::string &endpoint) override;

    std::string post(const std::string &endpoint, const std::string &payload) override;

private:
    std::string request(const std::string &url, const std::string &method = "GET", const std::string &payload = "");

    std::string BASE_URL;          // Member variable for base URL
    std::string MARKET_DATA_URL;   // Member variable for market data URL
};

#endif //CURL_SERVICE_H
