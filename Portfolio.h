#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>

class Portfolio {
  // dict of stockName: (numShares, bookValue)
  std::unordered_map<std::string, std::tuple<int, float>> stocksPurchased;
  float profit;
  std::vector<float> historicalProfits;
  public:
    Portfolio();
    //Portfolio(json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    // return all the stocks in the portfolio (map of stockName : numShares)
    std::map<std::string, std::tuple<int, float>> getPortfolioInfo();
    float getProfit();
    std::vector<float> getHistoricalProfits();
};


#endif
