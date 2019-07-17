#include "Decorator.h"
#include "GameStateManager.h"
#include "Gamerun.h"
#include <memory>
#include <map>
#include "libs/json.hpp"

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : None
 * Return Value : String type
 * Description  : 
 *    When this method is invoked it returns the username of the current
 *    user playing the game. This way the program knows which user's
 *    information to manipulate.
 */
string GameRun::getTurn(){
  return usernames.at(currentTurn % usernames.size());
}

/* 
 * Parameters   : Shared pointer to GameStateManager, integer for
 *                day per turn and integer for total days
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns value to daysPerTurn
 *    and totalDays, via MIL. It then sets currentDay to daysPerTurn and
 *    currentTurn to 0. Note that the initial order of the users playing
 *    will be random.
 */
GameRun::GameRun(std::shared_ptr<GameStateManager> g, int daysPerTurn, int totalDays): Decorator(g), daysPerTurn{daysPerTurn}, totalDays{totalDays}{
  currentDay = daysPerTurn;
  currentTurn = 0;
  usernames = userManager->getUsernames();
}

/* 
 * Parameters   : Integer for number of shares and string for stock name
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the buyShares method of the
 *    StockManager to buy shares from the company, it then retrieves the
 *    current player and value of the stock bought by player. Finally, it
 *    calls the addShares method of UserManager to add the stock purchased
 *    to the portfolio of the user.
 */
void GameRun::buyStockCurrentUser(int numShares, string stockName){
  // throw exceptions if something goes wrong
  stockManager->buyShares(numShares, stockName);
  string usernameOfCurrentPlayer = getTurn();
  float currentStockValue = stockManager->getEODStockPrice(stockName);
  userManager->addShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
  this->notifyRender();
}

/* 
 * Parameters   : integer for number of shares and string for stock name
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the sellShares method of the
 *    StockManager to sell shares to the company, it then retrieves the
 *    current player and value of the stock sold by player. Finally, it
 *    calls the removeShares method of UserManager to remove the stock sold
 *    from the portfolio of the user.
 */
void GameRun::sellStockCurrentUser(int numShares, string stockName){
  // throw exceptions if something goes wrong
  stockManager->sellShares(numShares, stockName);
  string usernameOfCurrentPlayer = getTurn();
  float currentStockValue = stockManager->getEODStockPrice(stockName);
  userManager->removeShares(stockName, usernameOfCurrentPlayer, numShares, currentStockValue);
  this->notifyRender();
}

/* 
 * Parameters   : None
 * Return Value : Vector of strings
 * Description  : 
 *    When this method is invoked it simply returns the list of stocks
 *    whose shares can be purchased.
 */
vector<string> GameRun::getAllAvailableStocks(){
  return stockManager->getAllAvailableStocks();
}

/* 
 * Parameters   : None
 * Return Value : Map between string and 4-tuple of integer, float, float and float
 * Description  : 
 *    When this contructor is invoked it retrieves the current player and uses
 *    this to get the player's portfolio.
 *    It then iterates through all available stocks and see if a stock belongs
 *    to the user portfolio. If yes, then it gets the number of shares owned
 *    for that stock and the average price at which those shares were bought
 *    for. Else, number of shares owned and average price are set to 0.
 *    Finally, this is inserted into the a map between stock name and 4-tuple
 *    of {Shares Owned, Average Purchase Price, Current Price, Dividends},
 *    which is then returned.
 */
map<string, tuple<int, float, float, float>> GameRun::getCurrentUserStockInfo(){
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

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked, if the current day is 0, then it increments
 *    current turn and sets current day to the days per turn. It then retrieves
 *    the portfolio of the current player, calculates the dividents earned and
 *    adds these returns to the player's cash balance. Finally, it sets the end
 *    of day share price for the stocks.
 */
void GameRun::skipNextDayForCurrentUser(){
  // throw exceptions if something goes wrong
  currentDay--;
  if(currentDay == 0){
    currentTurn++;
    currentDay = daysPerTurn;
  }
  float totalDividends = 0;
  string usernameOfCurrentPlayer = getTurn();
  // map of stockName: (numShares, avgPurchasePrice)
  map<string, tuple<int, float>> portfolioInfo = userManager->getUserPortfolioInfo(usernameOfCurrentPlayer);

  for(auto& it: portfolioInfo){
    totalDividends += (stockManager->getEODReturns(it.first) * get<0>(it.second));
  }
  userManager->addDividendsToUser(totalDividends, usernameOfCurrentPlayer);

  stockManager->setEODStockPrices();
  this->notifyRender();
}

/* 
 * Parameters   : None
 * Return Value : 4-tuple of a string, float, float and integer
 * Description  : 
 *    When this method is invoked it retrieves the cash balance and profits of
 *    current player and returns a 4-tuple of the user name, cash balance,
 *    profits and number of turns left.
 */
tuple<string, float, float, int> GameRun::getCurrentUserInformation(){
  string usernameOfCurrentPlayer = getTurn();
  float cashBalance = userManager->getUserCashBalance(usernameOfCurrentPlayer);
  float profits = userManager->getUserProfits(usernameOfCurrentPlayer);

  return make_tuple(usernameOfCurrentPlayer, cashBalance, profits, daysPerTurn - currentDay);
}

/* 
 * Parameters   : None
 * Return Value : Vector of float type
 * Description  : 
 *    When this method is invoked it retrieves the user name of current
 *    player and returns the profits made by this user in the past as per
 *    the transaction number.
 */
vector<float> GameRun::getHistoricalUserProfits(){
  string usernameOfCurrentPlayer = getTurn();
  return userManager->getHistoricalUserProfits(usernameOfCurrentPlayer);
}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it saves the all user info for each player
 *    and returns the JSON containing the saved info.
 */
json GameRun::saveGameForUsers(){
  return userManager->saveGameForAllUsers();
}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it saves the all stock info for each stock
 *    and returns the JSON containing the saved info.
 */
json GameRun::saveGameForAllStocks(){
  return stockManager->saveGameForAllStocks();
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this contructor is invoked it retrieves and returns the maximum
 *    profits made by the current user.
 */
float GameRun::getMaxProfit(){
  return userManager->getMaxProfit(getTurn());
}

/* 
 * Parameters   : None
 * Return Value : Float type
 * Description  : 
 *    When this contructor is invoked it retrieves and returns the minimum
 *    profits made by the current user.
 */
float GameRun::getMinProfit(){
  return userManager->getMinProfit(getTurn());
}
