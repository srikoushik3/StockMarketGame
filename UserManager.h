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
    ~UserManager();
};

#endif
