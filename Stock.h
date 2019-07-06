#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock{
  int numShares;
  float marketCap;
  std::string name;
  float openingSharePrice;
  float maxPriceVariation;
  public:
    void buyShares(int);
    void sellShares(int);
    virtual void setEODStockPrice() = 0;
    virtual void getEODReturns() = 0;
    void setMaxVaraiance(float);
    bool operator==(const Stock&) const;
    virtual ~Stock() {}
};

#endif
