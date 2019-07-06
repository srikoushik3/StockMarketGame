#ifndef BASICSTOCK_H
#define BASICSTOCK_H

#include "json.hpp"
#include "Stock.h"

using json = nlohmann::json;

class BasicStock: public Stock{
    public:
      void setEODStockPrice() override;
      void getEODReturns() override;
      BasicStock(json);
      BasicStock();
      ~BasicStock() {}
};

#endif
