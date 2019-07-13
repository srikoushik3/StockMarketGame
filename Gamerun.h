#include "decorator.h"
#include "gamestatemanager.h"
#include <memory>
#include <string>

/*
+buyStockCurrentUser(numShare: int, stockName: string): void
+sellStockCurrentUser(numShares: int, stockName: string): void
+skipNextDayForCurrentUser(): void
+getAverageReturnsHistoryForUser(username: string): void
+getCurrentUserInformation(): User
*/

class GameRun: public Decorator{
  vector<string> usernames;
  int currentTurn;
  int currentDay;
  int daysPerTurn;
  int totalDays;
  string getTurn();
  public:
    GameRun(std::shared_ptr<GameStateManager>, int, int);
    void buyStockCurrentUser(int, string);
    void sellStockCurrentUser(int, string);
    void skipNextDayForCurrentUser();
    tuple<string, float, float, int> getCurrentUserInformation();
    map<string, tuple<int, float float>> getCurrentUserStockInfo();
    std::vector<float> getHistoricalUserProfits();
    std::vector<std::string> getAllAvailableStocks();
    ~GameRun();
};
