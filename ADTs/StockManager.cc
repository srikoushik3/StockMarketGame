#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "StockManager.h"
#include "BasicStock.h"
#include "Bond.h"
#include "libs/json.hpp"
#include "Exceptions/Exception.h"

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : Integer for number of shares and string for stock name
 * Return Value : None
 * Description  : 
 *    When this method is invoked it searches for stock name in the map. If
 *    found, then it calls the buyShares method for that particular stock.
 *    Else it throws an exception.
 */
void StockManager::buyShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    if (search != stocks.end()) {
        search->second->buyShares(numShares);
    }
    else {
        // throw StockDoesNotExistException
        throw StockException{"Stock Does Not Exist"};
    }

}

/* 
 * Parameters   : Integer for number of shares and string for stock name
 * Return Value : None
 * Description  : 
 *    When this method is invoked it searches for stock name in the map. If
 *    found, then it calls the sellShares method for that particular stock.
 *    Else it throws an exception.
 */
// Search for stock in map and call sellShares function on that stock
void StockManager::sellShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    if (search != stocks.end()) {
        search->second->sellShares(numShares);
    }
    else {
        // throw StockDoesNotExistException
        throw StockException{"Stock Does Not Exist"};
    }
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked iterates through all stocks in the map
 *    and calls the setEODStockPrice method on each stock.
 */
void StockManager::setEODStockPrices() {
    for(auto& it: stocks){
        it.second->setEODStockPrice();
    }
}

/* 
 * Parameters   : String for stock name
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it searches for stock name in the map. If
 *    found, then it calls the getEODStockPrice method for that particular
 *    stock to retieves its end of day returns. Else it throws an exception.
 */
// get current stock price
float StockManager::getEODStockPrice(string stockName){
  if (stocks.find(stockName) != stocks.end()) {
    return stocks[stockName]->getEODStockPrice();
  }
  else{
    throw StockException{"Stock Does Not Exist"};
  }
}

/* 
 * Parameters   : Integer for number of shares and string for stock name
 * Return Value : Boolean type
 * Description  : 
 *    When this method is invoked it searches for stock name in the map
 *    and calls the hasSufficentShares method on that stock to see if there
 *    are enough stocks available to be sold.
 */
bool StockManager::hasSufficentShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    bool res = false;
    if (search != stocks.end()) {
        res = search->second->hasSufficentShares(numShares);
    }
    return res;
}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it saves the current stocks in the game
 *    session by iterating through the map and emplacing it into a JSON
 *    array and returning this JSON.
 */
json StockManager::saveGameForAllStocks() const{
  json finalJson = json::array();
  for (auto& it: stocks) {
      finalJson.emplace_back(it.second->serialize());
  }
  return finalJson;
}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it loads the previous game session by
 *    iterating through the JSON object and inserting a unique pointer
 *    to either a Basic Stock Object or a Bond Object depending on type
 *    of Stock.
 */
void StockManager::loadStocksFromFile(json & stocksJson) {
  for (json::iterator it = stocksJson.begin(); it != stocksJson.end(); ++it) {
    json currentStock = *it;
    bool isBond = currentStock["isBond"];
    string stockName = currentStock["name"];
    if(isBond){
      stocks[stockName] = std::make_unique<Bond>(currentStock);
    }else{
      stocks[stockName] = std::make_unique<BasicStock>(currentStock);
    }
  }
}

/*
 * Parameters   : None
 * Return Value : Average Share Price accross all stocks
 * Description  :
 *    Calculate the average share price accross all stocks
 *    in the map
 */
float StockManager::getAvgSharePrice(){
    int count = 0;
    float sum = 0;
    for(auto& it: stocks){
        count++;
        sum += it.second->getEODStockPrice();
    }
    return sum/count;
}

/* 
 * Parameters   : None
 * Return Value : Vector of strings
 * Description  : 
 *    When this method is invoked it iterates over the map and pushes the
 *    stock name into a vector and returns it.
 */
vector<string> StockManager::getAllAvailableStocks(){
  vector<string> stocksAvail;
  for(auto& it: stocks){
    stocksAvail.push_back(it.first);
  }
  return stocksAvail;
}

/* 
 * Parameters   : String for stock name
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it calls the getEODReturns method of the
 *    required stock and returns the value, if the stock exists in the map.
 *    Else it throws an exception.
 */
float StockManager::getEODReturns(string stockName){
  if (stocks.find(stockName) != stocks.end()) {
    return stocks[stockName]->getEODReturns();
  }
  else{
    // throw StockDoesNotExistException
    throw StockException{"Stock Does Not Exist"};
  }
}

StockManager::~StockManager(){}
