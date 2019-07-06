#ifndef BOND_H_
#define BOND_H_
#include <string>
#include "Stock.h"

class Bond : public Stock{

  public:
    Bond();
    void setEODStockPrice();
    float getEODReturns() const;
    ~Bond();
};
    
#endif