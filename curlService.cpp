#include <curl/curl.h>
#include <cstdlib>
#include "curlService.h"
#include <iostream>

// Constants
const std::string CA_PATH = "curl/curl-ca-bundle.crt";

// Utility: Curl response handler
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    s->append((char *)contents, newLength);
    return newLength;
}

// Constructor
CurlHttpService::CurlHttpService(const std::string &baseUrl, const std::string &marketDataUrl)
    : BASE_URL(baseUrl), MARKET_DATA_URL(marketDataUrl) {}

// GET request
std::string CurlHttpService::get(const std::string &endpoint)
{
    return request(BASE_URL + endpoint);
}

// GET market data
std::string CurlHttpService::getMarketData(const std::string &endpoint)
{
    return request(MARKET_DATA_URL + endpoint);
}

// POST request
std::string CurlHttpService::post(const std::string &endpoint, const std::string &payload)
{
    return request(BASE_URL + endpoint, "POST", payload);
}

// Private request method
std::string CurlHttpService::request(const std::string &url, const std::string &method, const std::string &payload)
{
    // check for API keys in environment variable
    const char *API_KEY = std::getenv("API_KEY");
    const char *API_SECRET = std::getenv("API_SECRET");

    // Check if both environment variables are set
    if (API_KEY == nullptr)
    {
        std::cerr << "Error: API_KEY environment variable not set! set with $env:API_KEY = your_api_key_value" << std::endl;
    }

    if (API_SECRET == nullptr)
    {
        std::cerr << "Error: API_SECRET environment variable not set! set with $env:API_SECRET = your_api_secret_value" << std::endl;
    }

    CURL *curl = curl_easy_init();
    std::string response;

    if (curl)
    {
        long httpCode = 0;
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("APCA-API-KEY-ID: " + std::string(API_KEY)).c_str());
        headers = curl_slist_append(headers, ("APCA-API-SECRET-KEY: " + std::string(API_SECRET)).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        if (method == "POST")
        {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_CAINFO, CA_PATH.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "[ERROR] CURL request failed: " << curl_easy_strerror(res) << "\n";
        }
    }
    return response;
}
