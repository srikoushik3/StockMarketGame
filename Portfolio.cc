#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "Portfolio.h"
using namespace std;


/*
// dict of stockName: (numShares, bookValue)
std::unordered_map<std::string,tuple<int, float>> stocksPurchased;
*/

// default constructor
Portfolio::Portfolio(): profit{0.0} {}
//Portfolio(json&);
void Portfolio::addShares(string stockName, int numShares, float currentStockValue){
  // ??? check if reference works
  auto& it = stocksPurchased.find(stockName);
  if(it != stocksPurchased.end()){
    // stock exists -> add shares
    get<0>(it->second) += numShares;
    get<1>(it->second) += numShares*currentStockValue;
  }
  else{
    // new stock purchased
    // move insertion into map with bookValue = numShares*currentStockValue
    stocksPurchased.insert(make_pair<string, tuple<int, float>(stockName, make_tuple<int, float>(numShares, numShares*currentStockValue)))
  }
}
void Portfolio::removeShares(string stockName, int numShares, float currentStockValue){
  //selling shares -> need to calculate book value and the profit
  auto& it = stocksPurchased.find(stockName);
  if(it != stocksPurchased.end()){
    // stock exists
    if(get<0>(it->second) < numShares){
      // throw SellingMoreThanOwnedShares Exception
    }
    int oldNumShares = get<0>(it->second);
    float oldBookValue =get<1>(it->second);
    get<0>(it->second) -= numShares;
    if(get<0>(it->second) == 0){
      // all shares sold -> delete stock from portfolio
    }
    else{
      // set new book value
      get<1>(it->second) = (get<0>(it->second)/oldNumShares)*oldBookValue;
    }
    // add the transaction profit
    // transactionProfit = (numShares*currentStockValue) - (numShares/oldNumShares)*oldBookValue
    profit += (numShares*currentStockValue) - (numShares/oldNumShares)*oldBookValue;
  }
  else{
    // throw StockDoesNotExistInPortfolio Exception
  }
}
// return all the stocks in the portfolio (map of stockName : numShares)
unordered_map<string, int> Portfolio::getPortfolioStocks(){}
