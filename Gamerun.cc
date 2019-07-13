#include "decorator.h"
#include "gamestatemanager.h"
#include "GameRun.h"
#include <memory>
#include <map>

using namespace std;

/*
+buyStockCurrentUser(numShare: int, stockName: string): void
+sellStockCurrentUser(numShares: int, stockName: string): void
+skipNextDayForCurrentUser(): void
+getAverageReturnsHistoryForUser(username: string): void
+getCurrentUserInformation(): User
*/

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
  string currentStockValue = stockManager.getEODStockPrice(stockName);
  userManager->addShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
}

void GameRun::sellStockCurrentUser(int numShares, string stockName){
  // throw exceptions if something goes wrong
  stockManager->sellShares(numShares, stockName);
  string usernameOfCurrentPlayer = getTurn();
  string currentStockValue = stockManager.getEODStockPrice(stockName);
  userManager->removeShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
}

vector<string> GameRun::getAllAvailableStocks(){
  return stockManager->getAllAvailableStocks();
}

map<string, tuple<int, float float>> GameRun::getCurrentUserStockInfo(){
  // return a map of stockname to {Shares Owned, Average Purchase Price, Current Price}
  // call UM to get stockName -> (sharesOwned, avgPurchasePrice)
  string currentStockValue;
  string usernameOfCurrentPlayer = getTurn();
  map<string, tuple<int, float, float> stockInfo;
  map<string, tuple<int, float>> portfolioInfo = userManager->getUserPortfolioInfo(usernameOfCurrentPlayer);
  for(auto& it: portfolioInfo){
    // iterate through the map and insert the current stock price to another map
    currentStockValue = stockManager->getEODStockPrice(it->first);
    stockInfo.insert(make_pair(it->first, make_tuple(get<0>(it->second), get<1>(it->second), currentStockValue)));
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
    totalDividends += (stockManager.getEODReturns(it->first) * get<0>(it->second));
  }
  userManager->addDividendsToUser(totalDividends, username);

  // set the EOD stock prices
  stockManager->setEODStockPrices();
}

tuple<string, float, float, int> GameRun::getCurrentUserInformation(){
  string usernameOfCurrentPlayer = getTurn();
  float cashBalance = userManager->getCashBalance(usernameOfCurrentPlayer);
  float profits = userManager->getProfits(usernameOfCurrentPlayer);

  return make_tuple(usernameOfCurrentPlayer, cashBalance, profits, currentDay);
}

vector<float> GameRun::getHistoricalUserProfits(){
  // note: this method will return the historical profits as per the transaction number
  string usernameOfCurrentPlayer = getTurn();
  userManager->getHistoricalUserProfits(usernameOfCurrentPlayer);
}
