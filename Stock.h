#ifndef STOCK_H_
#define STOCK_H_
#include <string>

class Stock{
    int numShares;
    int marketCap;
    std::string name;
    float openingPricePerShare;
    float maxPriceVariance;

  public:
    Stock();
    void buyShares(int numShares);
    void sellShares(int numShares);
    virtual void setEODStockPrice() = 0;
    void setMaxVariance(float maxVariance);
    virtual float getEODReturns() const = 0;
    virtual ~Stock();
};
    
#endif