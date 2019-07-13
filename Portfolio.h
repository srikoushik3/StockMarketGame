#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class Portfolio {
  // dict of stockName: (numShares, bookValue)
  std::unordered_map<std::string, std::tuple<int, float>> stocksPurchased;
  float profit;
  public:
    Portfolio();
    //Portfolio(json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    // return all the stocks in the portfolio (map of stockName : numShares)
    std::map<string, tuple<int, float>> getPortfolioInfo();
};


#endif
