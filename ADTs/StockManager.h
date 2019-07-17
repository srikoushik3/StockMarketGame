 /*
  * File: StockManager.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the StockManager class which contains an
  *   unordered map that maps the name of stock to a pointer to 'Stock' object.
  *   Consequently, it is responsible for functionalities such as buy and
  *   sell specific shares, get the stock price and returns.
  */
#ifndef STOCKMANAGER_H_
#define STOCKMANAGER_H_
#include <string>
#include <unordered_map>
#include <string>
#include <memory>
#include "Stock.h"
#include "libs/json.hpp"
using json = nlohmann::json;

class StockManager {
    std::unordered_map<std::string,std::unique_ptr<Stock>> stocks;

  public:
    void addStock(int numShares, int marketCap, std::string stockName, float openingPrice, float maxPriceVariation);
    void buyShares(int numShares, std::string stockName);
    void sellShares(int numShares, std::string stockName);
    void setEODStockPrices();
    float getEODStockPrice(std::string);
    bool hasSufficentShares(int numShares, std::string stockName);
    void loadStocksFromFile(json &);
    float getAvgSharePrice();
    json saveGameForAllStocks() const;
    std::vector<std::string> getAllAvailableStocks();
    float getEODReturns(std::string stockName);
    ~StockManager();
};

#endif
