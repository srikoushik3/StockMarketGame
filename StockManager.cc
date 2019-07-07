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

}

void StockManager::sellShares(int numShares, string stockName) {

}

void StockManager::setEODStockPrices() {

}

void StockManager::saveGameForAllStocks() const{
  json finalJson = json::array();
  for (auto& it: stocks) {
      finalJson.emplace_back(it.second->serialize());
  }
  ofstream o("stocks.json");
  o << setw(4) << finalJson << endl;
}

void StockManager::loadStocksFromFile() {
  ifstream i("stocks.json");
  json stocksJson;
  i >> stocksJson;
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
