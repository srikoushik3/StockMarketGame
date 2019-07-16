#include "UserManager.h"
#include "User.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include "json.hpp"
#include "Exception.h"
using json = nlohmann::json;

using namespace std;

UserManager::UserManager(){}

void UserManager::createUsersFromUsername(vector<string> usernames){
  for(int i = 0; i<usernames.size(); ++i){
    addUser(usernames[i]);
  }
}

void UserManager::addUser(string username){
  // if User DNE -> add user
  if(users.find(username) == users.end()){
    // new user
    users.insert(make_pair(username, make_unique<User>(username)));
  }
  else{
    // throw DuplicateUsername exception
    throw UserException{"Duplicate Username"};
  }
}

void UserManager::addShares(string stockName, string username, int numShares, float currentStockValue){
  // add shares to the user with the username provided

  if(users.find(username) != users.end()){
    // valid user
    users[username]->addShares(stockName, numShares, currentStockValue);
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

void UserManager::removeShares(string stockName, string username, int numShares, float currentStockValue){
  // remove shares to the user with the username provided
  if(users.find(username) != users.end()){
    // valid user
    users[username]->removeShares(stockName, numShares, currentStockValue);
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"Username Already Exists"};
  }
}

/*
vector<User> UserManager::getUsers(){
  vector<User> usersToReturn;
  for(auto& it: users){
    usersToReturn.push_back(*(it.second));
  }
  return usersToReturn;
}
*/

vector<string> UserManager::getUsernames(){
  vector<string> usernamesToReturn;
  for(auto& it: users){
    usernamesToReturn.push_back(it.first);
  }
  return usernamesToReturn;
};

void UserManager::addDividendsToUser(float totalDividends, string username){
  if(users.find(username) != users.end()){
    // valid user
    users[username]->addDividends(totalDividends);
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

map<string, tuple<int, float>> UserManager::getUserPortfolioInfo(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getPortfolioInfo();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

float UserManager::getUserCashBalance(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getCashBalance();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

float UserManager::getUserProfits(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getProfits();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

vector<float> UserManager::getHistoricalUserProfits(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getHistoricalProfits();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

// Called when game is saved.
// Iterates through all users in map and stores information into JSON file
json UserManager::saveGameForAllUsers() const{
  json finalJson = json::array();
  for(auto& it : users) {
    finalJson.emplace_back(it.second->serialize());
  }
  return finalJson;
}

// Called when game needs to be loaded.
// Iterates through all fields in the JSON file and inserts information to users map
void UserManager::loadUsersFromFile(json & usersJson) {
  for(json::iterator it = usersJson.begin(); it != usersJson.end(); ++it) {
    json currentUser = *it;
    string userName = currentUser["userName"];
    users[userName] = std::make_unique<User>(currentUser);
  }
}

float UserManager::getMaxProfit(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getMaxProfit();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

float UserManager::getMinProfit(string username){
  if(users.find(username) != users.end()){
    // valid user
    return users[username]->getMinProfit();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

UserManager::~UserManager(){}
