#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "StockManager.h"
#include "BasicStock.h"
#include "Bond.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

void StockManager::addStock(int numShares, int marketCap, string name, float openingPrice, float maxPriceVariation) {

}

void StockManager::buyShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    if (search != stocks.end()) {
        search->second->buyShares(numShares);
    }
}

void StockManager::sellShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    if (search != stocks.end()) {
        search->second->sellShares(numShares);
    }
}

void StockManager::setEODStockPrices() {

}

bool StockManager::hasSufficentShares(int numShares, string stockName) {
    std::unordered_map<std::string,std::unique_ptr<Stock>>::const_iterator search = stocks.find(stockName);
    bool res = false;
    if (search != stocks.end()) {
        res = search->second->hasSufficentShares(numShares);
    }
    return res;
}

json StockManager::saveGameForAllStocks() const{
  json finalJson = json::array();
  for (auto& it: stocks) {
      finalJson.emplace_back(it.second->serialize());
  }
  return finalJson;
}

void StockManager::loadStocksFromFile(json & stocksJson) {
  for (json::iterator it = stocksJson.begin(); it != stocksJson.end(); ++it) {
    json currentStock = *it;
    bool isBond = currentStock["isBond"];
    string stockName = currentStock["name"];
    unique_ptr<Stock> stock;
    if(isBond){
      stocks[stockName] = std::make_unique<Bond>(currentStock);
    }else{
      stocks[stockName] = std::make_unique<BasicStock>(currentStock);
    }
  }
}

StockManager::~StockManager(){}
