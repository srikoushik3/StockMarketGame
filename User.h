#ifndef USER_H
#define USER_H
#include "Portfolio.h"
#include <string>
#include <memory>

class User {
  std::string username;
  Portfolio portfolio;
  float cashBalance;
  public:
    User(std::string);
    Portfolio getPortfolio();
    //saveUserState();
    //User(json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    void addDividends(float totalDividends);
    ~User();
};

#endif
