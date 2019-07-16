 /*
  * File: Bond.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the Bond class which inherits 
  *   from the Stock Class and is the second type of stocks. It
  *   contains the dividendPerShare variable, getEODReturns and
  *   serialize methods and a Constructor.
  */
#ifndef BOND_H_
#define BOND_H_
#include <string>
#include "Stock.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class Bond : public Stock{
  float dividendPerShare;
  public:
    Bond();
    float getEODReturns() const override;
    json serialize() const override;
    Bond(const json &);
    ~Bond();
};

#endif
