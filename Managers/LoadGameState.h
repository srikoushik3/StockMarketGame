 /*
  * File: LoadGameState.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the LoadGameState class which inherits from
  *   the Decorator Class, thus it is part of the Decorator pattern and is
  *   responsible for loading the previously saved game state by loading all
  *   the Stocks and Users.
  */
#ifndef LOADGAMESTATE_H_
#define LOADGAMESTATE_H_
#include <string>
#include <memory>
#include "Decorator.h"
#include "libs/json.hpp"
using json = nlohmann::json;

class LoadGameState : public Decorator {
  public:
    LoadGameState(std::shared_ptr<GameStateManager>);
    void loadStocksFromFile(json&);
    void loadUsersFromFile(json&);
    ~LoadGameState();
};

#endif
