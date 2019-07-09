#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>
#include "Portfolio.h"
using namespace std;

Portfolio::Portfolio(): profit{0.0} {}
//Portfolio(json&);
void Portfolio::addShares(string stockName, int numShares, float currentStockValue){
  auto it = stocksPurchased.find(stockName);
  if(it != stocksPurchased.end()){
    // stock exists -> add shares
    get<0>(it->second) += numShares;
    get<1>(it->second) += numShares*currentStockValue;
  }
  else{
    // new stock purchased
    // move insertion into map with bookValue = numShares*currentStockValue
    float bookValue = numShares * currentStockValue;
    tuple<int, float> x = make_tuple(numShares, bookValue);
    stocksPurchased.insert(make_pair(stockName, x));
  }
}
void Portfolio::removeShares(string stockName, int numShares, float currentStockValue){
  //selling shares -> need to calculate book value and the profit
  auto it = stocksPurchased.find(stockName);
  if(it != stocksPurchased.end()){
    // stock exists
    if(get<0>(it->second) < numShares){
      // throw SellingMoreThanOwnedShares Exception
    }
    int oldNumShares = get<0>(it->second);
    float oldBookValue = get<1>(it->second);
    get<0>(it->second) -= numShares;
    if(get<0>(it->second) == 0){
      // all shares sold -> delete stock from portfolio
      stocksPurchased.erase(stockName);
    }
    else{
      // set new book value
      get<1>(it->second) = (float(get<0>(it->second))/float(oldNumShares))*oldBookValue;
    }
    // add the transaction profit
    profit += (numShares*currentStockValue) - (float(numShares)/float(oldNumShares))*oldBookValue;
  }
  else{
    // throw StockDoesNotExistInPortfolio Exception
  }
}
// return all the stocks in the portfolio (map of stockName : numShares)
unordered_map<string, int> Portfolio::getPortfolioStocks(){}
