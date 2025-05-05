#include "thresholdStrategy.h"
#include <iostream>

// Basic Threshold Strategy
bool ThresholdStrategy::shouldBuy(double price)
{
    return price < 260.0;
}
bool ThresholdStrategy::shouldSell(double price)
{
    return price > 280.0;
}

bool ThresholdStrategy::analyse(nlohmann::json marketData)
{
    if (!marketData.contains("bars"))
    {
        std::cerr << "Market data does not contain 'bars' key." << std::endl;
        return false;
    }

    for (const auto &bar : marketData["bars"])
    {
        double open = bar["o"];
        double close = bar["c"];
        double high = bar["h"];
        double low = bar["l"];
        double volume = bar["v"];

        // Example analysis: Print data and check for a simple trend
        std::cout << "Time: " << bar["t"] << ", Open: " << open
                  << ", Close: " << close << ", High: " << high
                  << ", Low: " << low << ", Volume: " << volume << std::endl;

        // Example logic: Buy if the price is trending up, sell if trending down
        if (close > open)
        {
            std::cout << "Uptrend detected. Consider buying." << std::endl;
        }
        else if (close < open)
        {
            std::cout << "Downtrend detected. Consider selling." << std::endl;
        }
    }

    return true; // Analysis completed successfully
}
