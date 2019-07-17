 /*
  * File: GameStateBase.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the GameStateBase class which inherit from
  *   the GameStateManager Class and is responsible for linking the Game State
  *   Manager to the Stock Manager and User Manager modules via shared pointers
  *   to the two Manager modules.
  */
#ifndef GAMESTATEBASE_H
#define GAMESTATEBASE_H

#include "GameStateManager.h"

class GameStateBase: public GameStateManager
{
public:
    GameStateBase();
    ~GameStateBase(){}
};

#endif // GAMESTATEBASE_H
