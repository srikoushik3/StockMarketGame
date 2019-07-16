 /*
  * File: UserManager.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the UserManager class which contains an
  *   unordered map that maps the name of stock to a pointer to 'User' object.
  *   Consequently, it is responsible for functionalities such as create user,
  *   add shares to and remove shares from specific user portfolio and get
  *   various user portfolio information.
  */
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>
#include "json.hpp"
using json = nlohmann::json;

class UserManager{
  // map of username to ptr to User objects
  std::unordered_map<std::string, std::unique_ptr<User>> users;
  void addUser(std::string);
  public:
    UserManager();
    //void removeUser(std::string);
    json saveGameForAllUsers() const;
    void loadUsersFromFile(json &);
    void addShares(std::string, std::string, int, float);
    void removeShares(std::string, std::string, int, float);
    std::vector<User> getUsers();
    void createUsersFromUsername(std::vector<std::string>);
    void addDividendsToUser(float, std::string);
    std::map<std::string, std::tuple<int, float>> getUserPortfolioInfo(std::string);
    float getUserCashBalance(std::string);
    float getUserProfits(std::string);
    std::vector<float> getHistoricalUserProfits(std::string);
    std::vector<std::string> getUsernames();
    ~UserManager();
};

#endif
