#ifndef STOCKMANAGER_H_
#define STOCKMANAGER_H_
#include <string>
#include <unordered_map>
#include <fstream>
#include "Stock.h"
using namespace std;

class StockManager {
    unordered_map<string,Stock> stocks;

  public:
    void addStock(int numShares, int marketCap, string stockName, float openingPrice, float maxPriceVariation);
    void deleteStock(Stock s);
    void buyShares(int numShares, string stockName);
    void sellShares(int numShares, string stockName);
    void setEODStockPrices();
    void loadStockFromFile();
    void saveGameForAllStocks(fstream& stream);
    ~StockManager();
};
    
#endif