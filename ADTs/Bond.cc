#include <iostream>
#include "Bond.h"
#include "Stock.h"
#include "libs/json.hpp"

using json = nlohmann::json;
using namespace std;

Bond::Bond() {}

Bond::~Bond() {}

// Returns dividendPerShare since Bonds offer dividends
/* 
 * Parameters   : None
 * Return Value : Returns a float value sfor end of day stock return
 * Description  : 
 *    Since Bonds offer dividends this function simply returns dividendPerShare
 */
float Bond::getEODReturns() const {
  return dividendPerShare;
}

/* 
 * Parameters   : reference to json
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it will assign dividendPerShare its value
 *    from the json and it will call the Stock constructor by passing in a
 *    reference to json, via MIL
 */
Bond::Bond(const json & j): Stock(j), dividendPerShare(j["dividendPerShare"]) {}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it calls Stock::serialize() to get JSON
 *    after which is adds on the dividendPerShare and isBond fields to this
 *    JSON instance and returns it.
 */
json Bond::serialize() const {
  json bondJson = Stock::serialize();
  bondJson["dividendPerShare"] = dividendPerShare;
  bondJson["isBond"] = true;
  return bondJson;
}
