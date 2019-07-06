#ifndef STOCKMANAGER_H_
#define STOCKMANAGER_H_
#include <string>
#include <unordered_map>
#include <fstream>
#include "Stock.h"

class StockManager {
    std::unordered_map<std::string,Stock> stocks;

  public:
    void addStock(int numShares, int marketCap, std::string stockName, float openingPrice, float maxPriceVariation);
    void deleteStock(Stock s);
    void buyShares(int numShares, std::string stockName);
    void sellShares(int numShares, std::string stockName);
    void setEODStockPrices();
    void loadStockFromFile();
    void saveGameForAllStocks(std::fstream& stream) const;
    ~StockManager();
};
    
#endif