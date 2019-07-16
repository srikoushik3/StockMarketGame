 /*
  * File: Portfolio.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the Portfolio class which contains an
  *   unordered map (portfolio) that maps the name of stock to a tuple of
  *   number of shares and book value of portfolio. Consequently, it is
  *   responsible for functionalities such as adding and removing shares to
  *   portfolio and making various portfolio based calculations such as profit
  *   and book value.
  */
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class Portfolio {
  // dict of stockName: (numShares, bookValue)
  std::unordered_map<std::string, std::tuple<int, float>> stocksPurchased;
  float profit;
  std::vector<float> historicalProfits;
  public:
    Portfolio();
    Portfolio(const json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    // return all the stocks in the portfolio (map of stockName : numShares)
    std::map<std::string, std::tuple<int, float>> getPortfolioInfo();
    float getProfit();
    std::vector<float> getHistoricalProfits();
    json serialize() const;
};


#endif
