#include "UserManager.h"
#include "User.h"
#include <memory>
#include <string>
using namespace std;

UserManager::UserManager(){}

UserManager::createUsersFromUsername(vector<string> usernames){
  for(int i = 0; i<usernames.size(); ++i){
    addUser(usernames[i]);
  }
}

UserManager::addUser(string username){
  // if User DNE -> add user
  if()
  users.insert(make_pair<string, unique_ptr<User>>(usernames[i], make_unique<User>(usernames[i])));
}
