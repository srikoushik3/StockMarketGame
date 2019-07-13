#include "User.h"
#include <memory>
#include "Portfolio.h"
#include <string>
#include <iostream>
#include "Exception.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// change the initial cash balance
User::User(string username): username{username}, cashBalance{1000} {}

User::~User(){}

void User::addShares(string stockName, int numShares, float currentStockValue){
  // subtract the stock purchase cost from cash balance
  if (numShares*currentStockValue <= cashBalance){
    cashBalance -= numShares*currentStockValue;
    portfolio.addShares(stockName, numShares, currentStockValue);
  }
  else{
    // throw NotEnoughCashForTransaction exception
    throw UserException{"Not Enough Money For Transaction"};
  }
}

void User::removeShares(string stockName, int numShares, float currentStockValue){
  // add the money received to the cash balance
  cashBalance += numShares*currentStockValue;
  portfolio.removeShares(stockName, numShares, currentStockValue);
}

Portfolio User::getPortfolio(){
  return portfolio;
}

/*
  Expected JSON Input:
  "userName": <string>,
  "cashBalance": <int>,
  "portfolio": <portfolio>
*/
User::User(const json& j) : username(j["userName"]), cashBalance(j["cashBalance"]), portfolio(Portfolio(j["portfolio"])){}

/*
  Expected JSON Output:
  "userName": <string>,
  "cashBalance": <int>,
  "portfolio": <portfolio>
*/
json User::serialize() const {
  json userJson;
  userJson["userName"] = username;
  userJson["cashBalance"] = cashBalance;
  userJson["portfolio"] = portfolio.serialize();
  return userJson;
}
