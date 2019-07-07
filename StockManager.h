#ifndef STOCKMANAGER_H_
#define STOCKMANAGER_H_
#include <string>
#include <unordered_map>
#include <string>
#include <memory>
#include "Stock.h"

class StockManager {
    std::unordered_map<std::string,std::unique_ptr<Stock>> stocks;

  public:
    void addStock(int numShares, int marketCap, std::string stockName, float openingPrice, float maxPriceVariation);
    void buyShares(int numShares, std::string stockName);
    void sellShares(int numShares, std::string stockName);
    void setEODStockPrices();
    void loadStocksFromFile();
    void saveGameForAllStocks() const;
    ~StockManager();
};

#endif
