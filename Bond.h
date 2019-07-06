#ifndef BOND_H
#define BOND_H

#include "json.hpp"
#include "Stock.h"

using json = nlohmann::json;

class Bond: public Stock{
    float dividendPerShare;
    public:
      void setEODStockPrice() override;
      void getEODReturns() override;
      float getDividend() const;
      Bond(json);
      Bond();
      ~Bond() {}
};

#endif
