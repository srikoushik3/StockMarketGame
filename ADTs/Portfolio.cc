#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>
#include "Portfolio.h"
#include "Exceptions/Exception.h"
#include "libs/json.hpp"
#include <algorithm>

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it initializes profits to 0.0, via MIL.
 *    
 */
Portfolio::Portfolio(): profit{0.0} {}

/* 
 * Parameters   : String for stock name, integer for number of shares, float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it iterates through all the stocks purchased
 *    to find the stock being bought. If it is found, then we simply update the
 *    number of shares bought and the book value of the shares bought for that
 *    particular stock. If not found, then we simply add the stock name and
 *    the 2-tuple {number of shares bought, book value of shares} into the map
 *    as a new entry.
 *    
 */
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

/* 
 * Parameters   : String for stock name, integer for number of shares, float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it iterates through all the stocks purchased
 *    to find the stock being sold. If not found, then we throw an exception;
 *    otherwise, we look at how many stocks are being sold, if we are selling
 *    more stocks than we own, then an exception is thown; otherwise, we simply
 *    update the number of shares. If we have no shares left we simply delete
 *    the entry for that stock from our map; otherwise, we simply update the
 *    book value of based on the number of shares remaining for that
 *    particular stock. Aditionally, we record the profit made from the sale.
 */
void Portfolio::removeShares(string stockName, int numShares, float currentStockValue){
  //selling shares -> need to calculate book value and the profit
  auto it = stocksPurchased.find(stockName);
  if(it != stocksPurchased.end()){
    // stock exists
    if(get<0>(it->second) < numShares){
      // throw SellingMoreThanOwnedShares Exception
      throw UserException{"Selling More Shares than Owned"};
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
    // save previous transaction profit
    historicalProfits.push_back(profit);
    // push_back to min and max heap -> to store the max and min profits for the graph
    profitsMaxHeap.push_back(profit);
    push_heap(profitsMaxHeap.begin(), profitsMaxHeap.end());
    profitsMinHeap.push_back(profit);
    push_heap(profitsMinHeap.begin(), profitsMinHeap.end(), greater<int>());
  }
  else{
    // throw StockDoesNotExistInPortfolio Exception
    throw UserException{"Stock Does Not Exist In Portfolio"};
  }
}

/* 
 * Parameters   : None
 * Return Value : Map bettween string and a 2-tuple of integer and float
 * Description  : 
 *    When this method is invoked it iterates through all the stocks owned and
 *    inserts the number of shares owned and average purchase price into a map
 *    for that particular stock, then returns this map (portfolio).
 */
map<string, tuple<int, float>> Portfolio::getPortfolioInfo(){
  // return all the stocks in the portfolio (map of stockName : (numShares, avgPurchasePrice))
  map<string, tuple<int, float>> portfolioInfo;
  int numShares;
  float avgPurchasePrice;
  for(auto& it: stocksPurchased){
    numShares = get<0>(it.second);
    // avgPurchasePrice is (bookvalue of stock) / (num of shares owned)
    avgPurchasePrice = get<1>(it.second)/get<0>(it.second);
    portfolioInfo.insert(make_pair(it.first, make_tuple(numShares, avgPurchasePrice)));
  }
  return portfolioInfo;
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it simply returns the profit made from
 *    selling current stocks.
 */
float Portfolio::getProfit(){
    return profit;
}

/* 
 * Parameters   : None
 * Return Value : Vector of float type
 * Description  : 
 *    When this method is invoked it simply returns the profit made from
 *    selling all previous stocks.
 */
vector<float> Portfolio::getHistoricalProfits(){
  return historicalProfits;
}

/* 
 * Parameters   : Reference to JSON
 * Expected JSON Input:
    "profit": <int>,
    "stocks":[
      {
        "stockName": <string>,
        "numShares": <int>,
        "bookValue": <int>
      }
    ]
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns profit field form JSON to
 *    profit variable, via MIL. It then iterates through every field in the
 *    JSON and builds a 2-tuple {number of shares, book vlaue of shares}
 *    and inserts this into a map between the stock name and the 2-tuple.
 *    Additionally, makes a max-heap and min-heap for profits.
 */
Portfolio::Portfolio(const json& j) : profit(j["profit"]){
  // stocksPurchased
  json iterJson = j["stocks"];
  for(json::iterator it = iterJson.begin(); it != iterJson.end(); ++it) {
    json currentStock = *it;
    string stockName = currentStock["stockName"];
    tuple<int, float> x = make_tuple(currentStock["numShares"], currentStock["bookValue"]);
    stocksPurchased[stockName] = x;
  }
  json histAvg = j["avgProfitHistory"];
  for(json::iterator it = histAvg.begin(); it != histAvg.end(); ++it){
      historicalProfits.emplace_back(*it);
  }
  profitsMaxHeap = historicalProfits;
  make_heap(profitsMaxHeap.begin(), profitsMaxHeap.end());
  profitsMinHeap = historicalProfits;
  make_heap(profitsMinHeap.begin(), profitsMinHeap.end(), greater<int>());
}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Expected JSON Output:
    "profit": <int>,
    "stocks":[
        {
            "stockName": <string>,
            "numShares": <int>,
            "bookValue": <int>
        }
    ]
 * Description  : 
 *    When this method is invoked it build the JSON object for profits,
 *    array of average historical profit and array of stocks owned.
 */
json Portfolio::serialize() const {
  json stock;
  json stocksArray = json::array();
  json avgProfits = json::array();
  int numShares = 0;
  float bookValue = 0.0;
  for(float f: historicalProfits){
      avgProfits.emplace_back(f);
  }
  for(auto& it: stocksPurchased){
    stock["stockName"] = it.first;
    tie(numShares, bookValue) = it.second;
    stock["numShares"] = numShares;
    stock["bookValue"] = bookValue;
    stocksArray.emplace_back(stock);
  }
  json portfolioJson = {
      {"profit", profit},
      {"avgProfitHistory", avgProfits},
      {"stocks", stocksArray}};
  return portfolioJson;
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it simply returns the value at the front of
 *    the vector, which is the maximum profit made.
 */
float Portfolio::getMaxProfit(){
  return profitsMaxHeap.front();
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it simply returns the value at the front of
 *    the vector, which is the minimum profit made.
 */
float Portfolio::getMinProfit(){
  return profitsMinHeap.front();
}
