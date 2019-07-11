#include "UserManager.h"
#include "User.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include "Exception.h"

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
    throw UserException{"User Does Not Exist"};
  }
}

vector<User> UserManager::getUsers(){
  vector<User> usersToReturn;
  for(auto& it: users){
    usersToReturn.push_back(*(it.second));
  }
  return usersToReturn;
}
