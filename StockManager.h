#ifndef STOCKMANAGER_H_
#define STOCKMANAGER_H_
#include <string>
#include <unordered_map>
#include <string>
#include <memory>
#include "Stock.h"
#include "json.hpp"
using json = nlohmann::json;

class StockManager {
    std::unordered_map<std::string,std::unique_ptr<Stock>> stocks;

  public:
    void addStock(int numShares, int marketCap, std::string stockName, float openingPrice, float maxPriceVariation);
    void buyShares(int numShares, std::string stockName);
    void sellShares(int numShares, std::string stockName);
    void setEODStockPrices();
    bool hasSufficentShares(int numShares, std::string stockName);
    void loadStocksFromFile(json &);
    json saveGameForAllStocks() const;
    ~StockManager();
};

#endif
