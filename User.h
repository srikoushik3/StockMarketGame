#ifndef USER_H
#define USER_H
#include <string>
#include <memory>

class User {
  std::string username;
  std::unique_ptr<Portfolio> portfolio;
  float cashBalance;
  public:
    User(std::string);
    getPortfolio(){
      return *portfolio;
    }
    //saveUserState();
    //User(json&);
    void addShares(string, int, float);
    void removeShares(string, int, float);
    ~User();
};

#endif
