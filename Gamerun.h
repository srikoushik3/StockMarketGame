#ifndef GAMERUNSTATE_H
#define GAMERUNSTATE_H

#include "decorator.h"
#include "gamestatemanager.h"
#include <memory>
#include <string>
#include <tuple>
#include <map>
#include <vector>


/*
+buyStockCurrentUser(numShare: int, stockName: string): void
+sellStockCurrentUser(numShares: int, stockName: string): void
+skipNextDayForCurrentUser(): void
+getAverageReturnsHistoryForUser(username: string): void
+getCurrentUserInformation(): User
*/

class GameRun: public Decorator{
  std::vector<std::string> usernames;
  int currentTurn;
  int currentDay;
  int daysPerTurn;
  int totalDays;
  std::string getTurn();
  public:
    GameRun(std::shared_ptr<GameStateManager> g, int daysPerTurn, int totalDays);
    void buyStockCurrentUser(int, std::string);
    void sellStockCurrentUser(int, std::string);
    void skipNextDayForCurrentUser();
    std::tuple<std::string, float, float, int> getCurrentUserInformation();
    std::map<std::string, std::tuple<int, float, float>> getCurrentUserStockInfo();
    std::vector<float> getHistoricalUserProfits();
    std::vector<std::string> getAllAvailableStocks();
    ~GameRun() {}
};

#endif
