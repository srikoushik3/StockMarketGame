#include "User.h"
#include "Portfolio.h"
#include <memory>
#include <string>
#include <iostream>
#include "Exception.h"

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

void User::addDividends(float totalDividends){
  cashBalance += totalDividends;
}

Portfolio User::getPortfolio(){
  return portfolio;
}

map<string, tuple<int, float>> User::getPortfolioInfo(){
  return portfolio.getPortfolioInfo();
}

float User::getCashBalance(){
  return cashBalance;
}

float User::getProfits(){
  return portfolio.getProfit();
}

vector<float> User::getHistoricalProfits(){
  return portfolio.historicalProfits();
}
