#ifndef THRESHOLD_STRATEGY_H
#define THRESHOLD_STRATEGY_H

#include "tradingStrategy.h"
// Basic Threshold Strategy
class ThresholdStrategy : public ITradingStrategy
{
public:
    bool shouldBuy(double price) override;
    bool shouldSell(double price) override;
    bool analyse(nlohmann::json marketData) override;
};

#endif //THRESHOLD_STRATEGY_H