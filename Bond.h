#ifndef BOND_H_
#define BOND_H_
#include <string>
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;

class Bond : public Stock{
  float dividendPerShare;
  public:
    Bond();
    void setEODStockPrice();
    float getEODReturns() const;
    float getDividendPerShare() const;
    json serialize() const;
    Bond(const json &);
    ~Bond();
};

#endif
