#include "thresholdStrategy.h"
// Basic Threshold Strategy
bool ThresholdStrategy::shouldBuy(double price)
{
    return price < 260.0;
}
bool ThresholdStrategy::shouldSell(double price)
{
    return price > 280.0;
}
