#include <iostream>
#include<ctime>
#include<cstdlib>
#include <typeinfo>
#include "Stock.h"
#include "json.hpp"
#include "Exception.h"

using json = nlohmann::json;
using namespace std;

// Produces seed only once when new instance of Stock class is made
Stock::Stock() {
  srand(unsigned(time(NULL)));
}

// buyShares is called by buyShares in StockManager Class
// Removes the stocks bought from the number of stocks available
void Stock::buyShares(int numSharesPurchased) {
  if (numShares - numSharesPurchased >= 0) {
    numShares -= numSharesPurchased;
  }else{
    throw StockException{"Cannot buy more shares than total shares for stock"};
  }
}

// sellShares is called by sellShares in StockManager Class
// Adds the stocks sold to the number of stocks available
void Stock::sellShares(int numSharesSold) {
  numShares += numSharesSold;
}

// hasSufficentShares is called by hasSufficentShares in StockManager Class
// Checks to see if user is trying to buy more than what is available
bool Stock::hasSufficentShares(int numSharesToBePurchased) {
  return (numShares - numSharesToBePurchased < 0) ? false : true;
}

// setEODStockPrice is called by setEODStockPrices in StockManager Class
// Uses Variance to calculate the Stock price when user proceeds to next trading day
void Stock::setEODStockPrice() {
  openingPricePerShare += (float)rand()/(RAND_MAX)*(2*maxPriceVariance)-maxPriceVariance;
}

float Stock::getEODStockPrice(){
  return openingPricePerShare;
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
openingPricePerShare(j["openingPricePerShare"]), maxPriceVariance(j["maxPriceVariance"]){
  srand(unsigned(time(NULL)));
  // numShares: positive and int
  if(numShares < 0) throw StockException{"Number of Shares Cannot Be Negative"};
  if (typeid(numShares).name() != typeid(int).name()) throw StockException{"Number of Shares Must Be an Integer"};
  // marketCap: positive
  if(marketCap < 0) throw StockException{"Market Capital Cannot Be Negative"};
  // name: 20 chars
  if(name.length() > 5) throw StockException{"Stock Ticker Cannot Be More Than 5 Characters Long"};
  // openingPricePerShare: positive
  if(openingPricePerShare < 0) throw StockException{"Share Price Cannot Be Negative"};
  // maxPriceVariance: positve
  if(maxPriceVariance < 0) throw StockException{"Variance Cannot Be Negative"};
}

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
