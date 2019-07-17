 /*
  * File: User.h
  *
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the User class which contains the username
  *   and an instance of the user portfolio. Consequently, it is responsible
  *   for functionalities such as add shares to and remove shares from
  *   specific user portfolio and get various user portfolio information.
  */
#ifndef USER_H
#define USER_H
#include "Portfolio.h"
#include <string>
#include <memory>
#include <unordered_map>
#include "libs/json.hpp"

using json = nlohmann::json;

class User {
  std::string username;
  Portfolio portfolio;
  float cashBalance;
  public:
    User(std::string);
    Portfolio getPortfolio();
    // saveUserState();
    User(const json&);
    void addShares(std::string, int, float);
    void removeShares(std::string, int, float);
    void addDividends(float);
    std::map<std::string, std::tuple<int, float>> getPortfolioInfo();
    float getCashBalance();
    float getProfits();
    std::vector<float> getHistoricalProfits();
    json serialize() const;
    float getMaxProfit();
    float getMinProfit();
    ~User();
};

#endif
