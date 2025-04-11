#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

// Strategy Interface
class ITradingStrategy
{
public:
    virtual bool shouldBuy(double price) = 0;
    virtual bool shouldSell(double price) = 0;
    virtual ~ITradingStrategy() = default;
};

#endif //TRADING_STRATEGY_H