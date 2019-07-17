 /*
  * File: GameStateManager.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the GameStateManager class which is the
  *   parent class to Decorator and GameStateBase Classes and is responsible
  *   for managing the game state via Decorator and communicating with Stock
  *   and User Manager via GameStateBase.
  */
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "ADTs/UserManager.h"
#include "ADTs/StockManager.h"
#include <memory>


class GameStateManager
{
public:
    GameStateManager();
    GameStateManager(std::shared_ptr<GameStateManager>);
    virtual ~GameStateManager() = 0;
protected:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<StockManager> stockManager;
};

#endif // GAMESTATEMANAGER_H
