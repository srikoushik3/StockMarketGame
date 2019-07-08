#include <iostream>
#include<ctime>
#include<cstdlib>
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Stock::Stock() {
  srand(unsigned(time(NULL)));
}

void Stock::buyShares(int numSharesPurchased) {
  numShares -= numSharesPurchased;
}

void Stock::sellShares(int numSharesSold) {
  numShares += numSharesSold;
}

bool Stock::hasSufficentShares(int numSharesToBePurchased) {
  return (numShares - numSharesToBePurchased < 0) ? false : true;
}

void Stock::setEODStockPrice() {
  openingPricePerShare += (float)rand()/(RAND_MAX)*(2*maxPriceVariance)-maxPriceVariance;
}

Stock::~Stock() {}

/*
  Expected JSON Input:
  {
    'numberOfShares': <int>
    'marketCap': <float>
    'name': <string>,
    'openingPricePerShare': <float>,
    'maxPriceVariance': <float>,
  }
*/
Stock::Stock(const json& j): numShares(j["numShares"]), marketCap(j["marketCap"]), name(j["name"]),
openingPricePerShare(j["openingPricePerShare"]), maxPriceVariance(j["maxPriceVariance"]){}

/*
  Expected JSON Output:
  {
    'numberOfShares': <int>
    'marketCap': <float>
    'name': <string>,
    'openingPricePerShare': <float>,
    'maxPriceVariance': <float>,
  }
*/
json Stock::serialize() const {
  json stockJson = {
  {"numShares", numShares},
  {"marketCap", marketCap},
  {"name", name},
  {"openingPricePerShare", openingPricePerShare},
  {"isBond", false},
  {"maxPriceVariance", maxPriceVariance}};
  return stockJson;
}
