#include <iostream>
#include<ctime>
#include<cstdlib>
#include <typeinfo>
#include "Stock.h"
#include "libs/json.hpp"
#include "Exceptions/Exception.h"

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it produces a seed only once when
 *    new instance of Stock class is made.
 */
Stock::Stock() {
  srand(unsigned(time(NULL)));
}

/* 
 * Parameters   : Integer for number of shares purchased
 * Return Value : None
 * Description  : 
 *    When this method is invoked it simply removes the number of stocks
 *    bought from the total number of stocks available for purchase.
 */
void Stock::buyShares(int numSharesPurchased) {
  if (numShares - numSharesPurchased >= 0) {
    numShares -= numSharesPurchased;
  }else{
    throw StockException{"Cannot buy more shares than total shares for stock."};
  }
}

/* 
 * Parameters   : Integer for number of shares sold
 * Return Value : None
 * Description  : 
 *    When this method is invoked it simply adds the number of stocks
 *    sold to the total number of stocks available.
 */
void Stock::sellShares(int numSharesSold) {
  numShares += numSharesSold;
}

/* 
 * Parameters   : Integer for number of shares to be bought
 * Return Value : Boolean type
 * Description  : 
 *    When this method is invoked it checks to see if user is trying
 *    to buy more than what is available.
 */
bool Stock::hasSufficentShares(int numSharesToBePurchased) {
  return (numShares - numSharesToBePurchased < 0) ? false : true;
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it uses Variance to calculate the
 *    Stock price when user proceeds to next trading day.
 */
void Stock::setEODStockPrice() {
    if(fluctuations.size() <= 0){
        openingPricePerShare += (float)rand()/(RAND_MAX)*(2*maxPriceVariance)-maxPriceVariance;
    }else {
        int range = (fluctuations.size() - 1) + 1;
        int index = rand() % range;
        openingPricePerShare += fluctuations.at(index);
    }
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it simply returns the opening price
 *    per share after setting the end of day share price.
 */
float Stock::getEODStockPrice(){
  return openingPricePerShare;
}

Stock::~Stock() {}

/* 
 * Parameters   : Reference to JSON
 * Expected JSON Input:
    {
      'numberOfShares': <int>
      'marketCap': <float>
      'name': <string>,
      'openingPricePerShare': <float>,
      'maxPriceVariance': <float>,
    }
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns various fields from JSON
 *    to their respective member variable, via MIL. If the values do not
 *    conform to certain validation checks, then appropriate exceptions
 *    are thrown.
 */
Stock::Stock(const json& j): numShares(j["numShares"]), marketCap(j["marketCap"]), name(j["name"]),
openingPricePerShare(j["openingPricePerShare"]), maxPriceVariance(j["maxPriceVariance"]){
  srand(unsigned(time(NULL)));
  json stockFluctuations = j["stockFluctuations"];
  for(json::iterator it = stockFluctuations.begin(); it != stockFluctuations.end(); ++it){
    this->fluctuations.emplace_back(*it);
  }
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
 * Parameters   : None
 * Return Value : JSON type
 * Expected JSON Output:
    {
      'numberOfShares': <int>
      'marketCap': <float>
      'name': <string>,
      'openingPricePerShare': <float>,
      'maxPriceVariance': <float>,
    }
 * Description  : 
 *    When this method is invoked it builds the JSON object by assigning
 *    various member variables to their respective JSON fields, then
 *    returns this object.
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
