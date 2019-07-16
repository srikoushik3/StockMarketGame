#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "StockManager.h"
#include "BasicStock.h"
#include "Bond.h"
#include "json.hpp"
#include "Exception.h"

using json = nlohmann::json;
using namespace std;

/*
void StockManager::addStock(int numShares, int marketCap, string name, float openingPrice, float maxPriceVariation) {
    // if Stock DNE -> add stock
    if(stocks.find(name) == stocks.end()){
        // new stock
        stocks.insert(make_pair(name, make_unique<Stock>(numShares, marketCap, name, openingPrice, maxPriceVariation)));
    }
    else{
        // throw DuplicateStock exception
        throw StockException{"Stock Already Exists"};
    }
}
*/

// Search for stock in map and call buyShares function on that stock
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

// Iterate through all stocks in map and call setEODStockPrice function on each stock
void StockManager::setEODStockPrices() {
    for(auto& it: stocks){
        it.second->setEODStockPrice();
    }
}

// get current stock price
float StockManager::getEODStockPrice(string stockName){
  if (stocks.find(stockName) != stocks.end()) {
    // stock found, return the price
    return stocks[stockName]->getEODStockPrice();
  }
  else{
    // throw StockDoesNotExistException
    throw StockException{"Stock Does Not Exist"};
  }
}
// Search for stock in map and call hasSufficentShares function on that stock
// Return true if enough stocks available, else return false
bool StockManager::hasSufficentShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    bool res = false;
    if (search != stocks.end()) {
        res = search->second->hasSufficentShares(numShares);
    }
    return res;
}

// Called when game is saved.
// Iterates through all stocks in map and stores information into JSON file
json StockManager::saveGameForAllStocks() const{
  json finalJson = json::array();
  for (auto& it: stocks) {
      finalJson.emplace_back(it.second->serialize());
  }
  return finalJson;
}

// Called when game needs to be loaded.
// Iterates through all fields in the JSON file and inserts information to stocks map
void StockManager::loadStocksFromFile(json & stocksJson) {
  for (json::iterator it = stocksJson.begin(); it != stocksJson.end(); ++it) {
    json currentStock = *it;
    bool isBond = currentStock["isBond"];
    string stockName = currentStock["name"];
    // unique_ptr<Stock> stock;
    if(isBond){
      stocks[stockName] = std::make_unique<Bond>(currentStock);
    }else{
      stocks[stockName] = std::make_unique<BasicStock>(currentStock);
    }
  }
}

vector<string> StockManager::getAllAvailableStocks(){
  vector<string> stocksAvail;
  for(auto& it: stocks){
    stocksAvail.push_back(it.first);
  }
  return stocksAvail;
}

float StockManager::getEODReturns(string stockName){
  if (stocks.find(stockName) != stocks.end()) {
    // stock found, return the dividend returns
    return stocks[stockName]->getEODReturns();
  }
  else{
    // throw StockDoesNotExistException
    throw StockException{"Stock Does Not Exist"};
  }
}

StockManager::~StockManager(){}
