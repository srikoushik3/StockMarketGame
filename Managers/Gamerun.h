 /*
  * File: GameRun.h
  *
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the GameRun class which inherit from
  *   the Decorator Class. This is one of the main classes as it contains
  *   methods that are responsible for handling the functionalities of the
  *   actual game play. It contains game play information such as currentTurn,
  *   currentDay, daysPerTurn and totalDays. Additionally it contains critical
  *   game play methods such as buyStockCurrentUser, sellStockCurrentUser and
  *   skipNextDayForCurrentUser to name a few.
  */
#ifndef GAMERUNSTATE_H
#define GAMERUNSTATE_H

#include "Decorator.h"
#include "GameStateManager.h"
#include "Subject.h"
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

class GameRun: public Decorator, public Subject{
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
    std::map<std::string, std::tuple<int, float, float, float>> getCurrentUserStockInfo();
    std::vector<float> getHistoricalUserProfits();
    std::vector<std::string> getAllAvailableStocks();
    json saveGameForUsers();
    json saveGameForAllStocks();
    float getMaxProfit();
    float getMinProfit();
    ~GameRun() {}
};

#endif
