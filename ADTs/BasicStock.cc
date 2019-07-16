#include <iostream>
#include "BasicStock.h"
using namespace std;

BasicStock::BasicStock() {}

/* 
 * Parameters   : None
 * Return Value : Returns float value for end of day stock return
 * Description  : 
 *    Since BasicStocks do not have any form of dividends
 *    this function simply returns 0.0
 */
float BasicStock::getEODReturns() const {
  return 0.0;
}

BasicStock::~BasicStock() {}

/* 
 * Parameters   : reference to json
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it will call the Stock constructor
 *    by passing in a reference to json via MIL
 */
BasicStock::BasicStock(const json & j): Stock(j){}
