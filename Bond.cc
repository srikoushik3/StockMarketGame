#include <iostream>
#include "Bond.h"
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

Bond::Bond() {}

Bond::~Bond() {}

float Bond::getEODReturns() const {
  return 0.0;
}

Bond::Bond(const json & j): Stock(j), dividendPerShare(j["dividendPerShare"]) {}

float Bond::getDividendPerShare() const{
  return dividendPerShare;
}

json Bond::serialize() const {
  json bondJson = Stock::serialize();
  bondJson["dividendPerShare"] = dividendPerShare;
  bondJson["isBond"] = true;
  return bondJson;
}
