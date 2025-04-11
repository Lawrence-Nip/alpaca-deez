#ifndef HTTP_SERVICE_H
#define HTTP_SERVICE_H

#include <string>

// Interface for HTTP Service
class IHttpService
{
public:
    virtual std::string get(const std::string &endpoint) = 0;
    virtual std::string getMarketData(const std::string &endpoint) = 0;
    virtual std::string post(const std::string &endpoint, const std::string &payload) = 0;
    virtual ~IHttpService() = default;
};

#endif //HTTP_SERVICE_H