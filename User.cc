#include "User.h"
#include "Portfolio.h"
#include <memory>
#include <string>
#include <iostream>
using namespace std;

User::User(string username): username{username}, cashBalance{1000} {
  Portfolio portfolio;
}

User::~User(){}

void User::addShares(string stockName, int numShares, float currentStockValue){
  // subtract the stock purchase cost from cash balance
  cashBalance -= numShares*currentStockValue;
  portfolio.addShares(stockName, numShares, currentStockValue);
}

void User::removeShares(string stockName, int numShares, float currentStockValue){
  // add the money received to the cash balance
  cashBalance += numShares*currentStockValue;
  portfolio.removeShares(stockName, numShares, currentStockValue);
}

Portfolio User::getPortfolio(){
  return portfolio;
}
