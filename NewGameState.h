 /*
  * File: NewGameState.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the LoadGameState class which inherits from
  *   the Decorator Class, thus it is part of the Decorator pattern and is
  *   responsible for creating a new game state by loading default files.
  */
#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include "Decorator.h"
#include "GameStateManager.h"
#include <memory>
#include "json.hpp"
#include <vector>
using json = nlohmann::json;


class NewGameState: public Decorator
{
public:
    NewGameState(std::shared_ptr<GameStateManager>);
    void createStocksFromFile(json &);
    void createUsers(std::vector<std::string>);
    ~NewGameState(){}
};

#endif // NEWGAMESTATE_H
