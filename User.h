#ifndef USER_H
#define USER_H
#include "Portfolio.h"
#include <string>
#include <memory>
#include "json.hpp"

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
    json serialize() const;
    ~User();
};

#endif
