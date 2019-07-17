 /*
  * File: BasicStock.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the BasicStock class which inherits 
  *   from the Stock Class and is the first types of stock. It contains
  *   the getEODReturns method and a Constructor.
  */
#ifndef BASICSTOCK_H_
#define BASICSTOCK_H_
#include <string>
#include "Stock.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class BasicStock : public Stock{

  public:
    BasicStock();
    float getEODReturns() const;
    ~BasicStock();
    BasicStock(const json&);
};

#endif
