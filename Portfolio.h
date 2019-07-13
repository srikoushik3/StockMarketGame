#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class Portfolio {
  // dict of stockName: (numShares, bookValue)
  std::unordered_map<std::string, std::tuple<int, float>> stocksPurchased;
  float profit;
  public:
    Portfolio();
    Portfolio(const json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    // return all the stocks in the portfolio (map of stockName : numShares)
    std::unordered_map<std::string, int> getPortfolioStocks();
    json serialize() const;
};


#endif
