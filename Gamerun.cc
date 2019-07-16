#include "Decorator.h"
#include "GameStateManager.h"
#include "Gamerun.h"
#include <memory>
#include <map>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

string GameRun::getTurn(){
  // returns the username of the current user playing
  return usernames.at(currentTurn % usernames.size());
}

GameRun::GameRun(std::shared_ptr<GameStateManager> g, int daysPerTurn, int totalDays): Decorator(g), daysPerTurn{daysPerTurn}, totalDays{totalDays}{
  currentDay = daysPerTurn;
  currentTurn = 0;
  // note that the initial order of the users playing will be random
  usernames = userManager->getUsernames();
}

void GameRun::buyStockCurrentUser(int numShares, string stockName){
  // throw exceptions if something goes wrong
  stockManager->buyShares(numShares, stockName);
  string usernameOfCurrentPlayer = getTurn();
  float currentStockValue = stockManager->getEODStockPrice(stockName);
  userManager->addShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
}

void GameRun::sellStockCurrentUser(int numShares, string stockName){
  // throw exceptions if something goes wrong
  stockManager->sellShares(numShares, stockName);
  string usernameOfCurrentPlayer = getTurn();
  float currentStockValue = stockManager->getEODStockPrice(stockName);
  userManager->removeShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
}

vector<string> GameRun::getAllAvailableStocks(){
  return stockManager->getAllAvailableStocks();
}

map<string, tuple<int, float, float, float>> GameRun::getCurrentUserStockInfo(){
  // return a map of stockname to {Shares Owned, Average Purchase Price, Current Price, Dividends}
  // call UM to get stockName -> (sharesOwned, avgPurchasePrice)
  float currentStockValue, dividend;
  int sharesOwned;
  float avgPurchasePrice;
  string usernameOfCurrentPlayer = getTurn();
  map<string, tuple<int, float, float, float>> stockInfo;
  map<string, tuple<int, float>> portfolioInfo = userManager->getUserPortfolioInfo(usernameOfCurrentPlayer);
  vector<string> allStockNames = getAllAvailableStocks();
  for(auto& it: allStockNames){
    currentStockValue = stockManager->getEODStockPrice(it);
    dividend = stockManager->getEODReturns(it);
    if(portfolioInfo.find(it) != portfolioInfo.end()){
      // stock exists in user's portfolio
      sharesOwned = get<0>(portfolioInfo[it]);
      avgPurchasePrice = get<1>(portfolioInfo[it]);
    }
    else{
      // stock does not exist in user's portfolio
      sharesOwned = 0;
      avgPurchasePrice = 0;
    }
    stockInfo.insert(pair<string, tuple<int, float, float, float>>(it, make_tuple(sharesOwned, avgPurchasePrice, currentStockValue, dividend)));
  }
  return stockInfo;
}

void GameRun::skipNextDayForCurrentUser(){
  // throw exceptions if something goes wrong
  // if the currentDay = 0, then increment turn and return new user info
  // add dividends to user's cash balance
  currentDay--;
  if(currentDay == 0){
    currentTurn++;
    currentDay = daysPerTurn;
  }
  float totalDividends = 0;
  string usernameOfCurrentPlayer = getTurn();
  // map of stockName: (numShares, avgPurchasePrice)
  map<string, tuple<int, float>> portfolioInfo = userManager->getUserPortfolioInfo(usernameOfCurrentPlayer);

  // add up dividends per stock across entire portfolio
  for(auto& it: portfolioInfo){
    totalDividends += (stockManager->getEODReturns(it.first) * get<0>(it.second));
  }
  userManager->addDividendsToUser(totalDividends, usernameOfCurrentPlayer);

  // set the EOD stock prices
  stockManager->setEODStockPrices();
}

tuple<string, float, float, int> GameRun::getCurrentUserInformation(){
  string usernameOfCurrentPlayer = getTurn();
  float cashBalance = userManager->getUserCashBalance(usernameOfCurrentPlayer);
  float profits = userManager->getUserProfits(usernameOfCurrentPlayer);

  return make_tuple(usernameOfCurrentPlayer, cashBalance, profits, daysPerTurn - currentDay);
}

vector<float> GameRun::getHistoricalUserProfits(){
  // note: this method will return the historical profits as per the transaction number
  string usernameOfCurrentPlayer = getTurn();
  return userManager->getHistoricalUserProfits(usernameOfCurrentPlayer);
}

json GameRun::saveGameForUsers(){
  // call save game for users
  return userManager->saveGameForAllUsers();
}

json GameRun::saveGameForAllStocks(){
  // call save game for stocks
  return stockManager->saveGameForAllStocks();
}
