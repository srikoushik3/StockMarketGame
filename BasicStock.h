#ifndef BASICSTOCK_H_
#define BASICSTOCK_H_
#include <string>
#include "Stock.h"

class BasicStock : public Stock{

  public:
    BasicStock();
    void setEODStockPrice();
    float getEODReturns() const;
    ~BasicStock();
};
    
#endif