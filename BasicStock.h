#ifndef BASICSTOCK_H_
#define BASICSTOCK_H_
#include <string>
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;

class BasicStock : public Stock{

  public:
    BasicStock();
    void setEODStockPrice();
    float getEODReturns() const;
    ~BasicStock();
    BasicStock(const json&);
};

#endif
