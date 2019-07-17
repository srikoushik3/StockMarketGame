#include "User.h"
#include <memory>
#include "Portfolio.h"
#include <string>
#include <iostream>
#include "Exceptions/Exception.h"
#include "libs/json.hpp"

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : String for user name
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it sets user name and cash balance, via MIL.
 */
User::User(string username): username{username}, cashBalance{1000} {}

User::~User(){}

/* 
 * Parameters   : String for stock name, integer for number of shares and float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it subtracts the stock purchase cost from
 *    cash balance, if the stock purchase cost is less than or equal to cash
 *    balance. Else it throws an exception.
 */
void User::addShares(string stockName, int numShares, float currentStockValue){
  if (numShares*currentStockValue <= cashBalance){
    cashBalance -= numShares*currentStockValue;
    portfolio.addShares(stockName, numShares, currentStockValue);
  }
  else{
    // throw NotEnoughCashForTransaction exception
    throw UserException{"Not Enough Money For Transaction"};
  }
}

/* 
 * Parameters   : String for stock name, integer for number of shares and float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it adds the stock sale cost to the
 *    cash balance and calls the removeShares method to update the number
 *    of stocks available for that particular stock.
 */
void User::removeShares(string stockName, int numShares, float currentStockValue){
  cashBalance += numShares*currentStockValue;
  portfolio.removeShares(stockName, numShares, currentStockValue);
}

/* 
 * Parameters   : Float for total dividends
 * Return Value : None
 * Description  : 
 *    When this method is invoked it updates cash balance by adding the
 *    total dividends to the cash balance.
 */
void User::addDividends(float totalDividends){
  cashBalance += totalDividends;
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it simply returns the user portfolio object.
 */
Portfolio User::getPortfolio(){
  return portfolio;
}

/* 
 * Parameters   : None
 * Return Value : Map between string and 2-tuple of integer and float
 * Description  : 
 *    When this method is invoked it simply returns information on user
 *    portfolio by calling the getPortfolioInfo method on the portfolio object.
 */
map<string, tuple<int, float>> User::getPortfolioInfo(){
  return portfolio.getPortfolioInfo();
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it simply returns the user cash balance.
 */
float User::getCashBalance(){
  return cashBalance;
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it returns the profit from user portfolio
 *    by calling the getProfits method on the portfolio object.
 */
float User::getProfits(){
  return portfolio.getProfit();
}

/* 
 * Parameters   : None
 * Return Value : Vector of float type
 * Description  : 
 *    When this method is invoked it returns the historical profit from user
 *    portfolio by calling the getHistoricalProfits method on the
 *    portfolio object.
 */
vector<float> User::getHistoricalProfits(){
  return portfolio.getHistoricalProfits();
}

/*
  Expected JSON Input:
  "userName": <string>,
  "cashBalance": <int>,
  "portfolio": <portfolio>
*/
/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns various fields from the
 *    JSON to user member variables, via MIL.
 */
User::User(const json& j) : username(j["userName"]), portfolio(Portfolio(j["portfolio"])), cashBalance(j["cashBalance"]){}

/*
  Expected JSON Output:
  "userName": <string>,
  "cashBalance": <int>,
  "portfolio": <portfolio>
*/
/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it builds the JSON object by assigning
 *    various member variables to their respective JSON fields, then
 *    returns this object.
 */
json User::serialize() const {
  json userJson;
  userJson["userName"] = username;
  userJson["cashBalance"] = cashBalance;
  userJson["portfolio"] = portfolio.serialize();
  return userJson;
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this contructor is invoked it calls the getMaxProfit method on
 *    the portfolio object and returns the maximum profit.
 */
float User::getMaxProfit(){
  return portfolio.getMaxProfit();
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this contructor is invoked it calls the getMinProfit method on
 *    the portfolio object and returns the minimum profit.
 */
float User::getMinProfit(){
  return portfolio.getMinProfit();
}
