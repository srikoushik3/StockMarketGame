#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class Portfolio {
  // dict of stockName: (numShares, bookValue)
  std::unordered_map<std::string,tuple<int, float>> stocksPurchased;
  float profit;
  std::vector<float> transactionHist;
  public:
    /*
    +addShares(stockName: string, numShares: int, currentStockValue: float): void
    +removeShares(stockName: string, numShares: int, currentStockValue: float): void
    +getPortfolioStocks(): map<ShareMap>
    +Portfolio(portfolio: json): void
    */
    Portfolio();
    //Portfolio(json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    // return all the stocks in the portfolio (map of stockName : numShares)
    std::unordered_map<std::string, int> getPortfolioStocks();
};


#endif
