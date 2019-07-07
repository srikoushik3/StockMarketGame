#include "User.h"
#include <memory>
#include <string>
#include <unordered_map>

class UserManager{
  std::unordered_map<string, unique_ptr<User>> users;
  public:
    UserManager();
    void addUser(std::string);
    void removeUser(std::string);
    void SaveGameForAllUsers();
    void loadUsersFromFile(fstream&);
    void addShares(string, int, float);
    void removeShares(string, int, float);
    // ??? getUsers -> why return all User objects?
    std::vector<User> getUsers();
    void createUsersFromUsername(std::vector<string>);
};
