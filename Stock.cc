#include <iostream>
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Stock::Stock() {

}

void Stock::buyShares(int numShares) {

}

void Stock::sellShares(int numShares) {

}

void Stock::setMaxVariance(float maxVariance) {

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
  {"maxPriceVariance", maxPriceVariance}};
  return stockJson;
}
