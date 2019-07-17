#include "UserManager.h"
#include "User.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include "libs/json.hpp"
#include "Exceptions/Exception.h"
using json = nlohmann::json;

using namespace std;

UserManager::UserManager(){}

/* 
 * Parameters   : Vector of strings, Average Stock Value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it iterates through the vector of user names
 *    and calls the addUser method on each user name to add them to the map.
 */
void UserManager::createUsersFromUsername(vector<string> usernames, float avgSharePrice){
  for(size_t i = 0; i<usernames.size(); ++i){
    addUser(usernames[i], avgSharePrice);
  }
}

/* 
 * Parameters   : Strings for user name, Average Stock Value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks if the user name can be found
 *    in the map. If yes, then it throws an excepton. Else, it maps the user
 *    name to a unique pointer to a User object.
 */
void UserManager::addUser(string username, float avgSharePrice){
  if(users.find(username) == users.end()){
    users.insert(make_pair(username, make_unique<User>(username, avgSharePrice)));
  }
  else{
    // throw DuplicateUsername exception
    throw UserException{"Duplicate Username"};
  }
}

/* 
 * Parameters   : String for stock name, string for user name, integer for number of shares and float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks if the user name can be found in
 *    the map. If yes, then calls the addShares on the User object to update
 *    number of stocks. Else, it throws an exception.
 */
void UserManager::addShares(string stockName, string username, int numShares, float currentStockValue){
  if(users.find(username) != users.end()){
    users[username]->addShares(stockName, numShares, currentStockValue);
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : String for stock name, string for user name, integer for number of shares and float for current stock value
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks if the user name can be found in
 *    the map. If yes, then calls the removeShares on the User object to update
 *    number of stocks. Else, it throws an exception.
 */
void UserManager::removeShares(string stockName, string username, int numShares, float currentStockValue){
  if(users.find(username) != users.end()){
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

/* 
 * Parameters   : None
 * Return Value : Vector of stings
 * Description  : 
 *    When this method is invoked it iterates through the user map and
 *    pushes each user names in to a vector and return this.
 */
vector<string> UserManager::getUsernames(){
  vector<string> usernamesToReturn;
  for(auto& it: users){
    usernamesToReturn.push_back(it.first);
  }
  return usernamesToReturn;
};

/* 
 * Parameters   : Float for total dividend and string for user name
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the addDividends method on the
 *    User object to update the number of dividends. Else, it throws exception.
 */
void UserManager::addDividendsToUser(float totalDividends, string username){
  if(users.find(username) != users.end()){
    users[username]->addDividends(totalDividends);
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : String for user name
 * Return Value : Map between string and 2-tuple of integer and float
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getPortfolioInfo method on the
 *    User object to retrieve user portfolio. Else, it throws an exception.
 */
map<string, tuple<int, float>> UserManager::getUserPortfolioInfo(string username){
  if(users.find(username) != users.end()){
    return users[username]->getPortfolioInfo();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : String for user name
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getCashBalance method on the
 *    User object to retrieve user cash balance. Else, it throws an exception.
 */
float UserManager::getUserCashBalance(string username){
  if(users.find(username) != users.end()){
    return users[username]->getCashBalance();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : String for user name
 * Return Value : Float type
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getProfits method on the
 *    User object to retrieve user profit. Else, it throws an exception.
 */
float UserManager::getUserProfits(string username){
  if(users.find(username) != users.end()){
    return users[username]->getProfits();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : String for user name
 * Return Value : Vector of float type
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getHistoricalProfits method
 *    on the User object to retrieve user's historical profit. Else, it throws
 *    an exception.
 */
vector<float> UserManager::getHistoricalUserProfits(string username){
  if(users.find(username) != users.end()){
    return users[username]->getHistoricalProfits();
  }
  else{
    // throw UserDoesNotExistException
    throw UserException{"User Does Not Exist"};
  }
}

/* 
 * Parameters   : None
 * Return Value : JSON type
 * Description  : 
 *    When this method is invoked it iterates over user map and emplaces
 *    the JSON returned upon calling the serialize method on the User object
 *    into a JSON array and return this JSON.
 */
json UserManager::saveGameForAllUsers() const{
  json finalJson = json::array();
  for(auto& it : users) {
    finalJson.emplace_back(it.second->serialize());
  }
  return finalJson;
}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it iterates over the JOSN objects and
 *    assigns the user name fields to user name variable and inserts a unique
 *    pointer to the JSON User object into the user map.
 */
void UserManager::loadUsersFromFile(json & usersJson) {
  for(json::iterator it = usersJson.begin(); it != usersJson.end(); ++it) {
    json currentUser = *it;
    string userName = currentUser["userName"];
    users[userName] = std::make_unique<User>(currentUser);
  }
}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getMaxProfit method
 *    on the User object to retrieve maximum user profit. Else, it throws
 *    an exception.
 */
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

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it checks to see if the user name can be
 *    found in the map. If yes, then it calls the getMinProfit method
 *    on the User object to retrieve minimum user profit. Else, it throws
 *    an exception.
 */
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
