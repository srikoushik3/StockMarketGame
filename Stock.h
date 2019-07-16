 /*
  * File: Stock.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the Stock class which contains the number of
  *   shares, market capital, name of Stock, opening price and share price
  *   variance. Consequently, it is responsible for functionalities such as
  *   buying shares from and selling to the company and deciding the share
  *   price and returns at the end of day.
  */
#ifndef STOCK_H_
#define STOCK_H_
#include <string>
#include "json.hpp"

using json = nlohmann::json;

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
    bool hasSufficentShares(int numShares);
    void setEODStockPrice();
    float getEODStockPrice();
    virtual float getEODReturns() const = 0;
    Stock(const json&);
    virtual json serialize() const;
    virtual ~Stock();
};

#endif
