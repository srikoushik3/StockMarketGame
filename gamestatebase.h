#ifndef GAMESTATEBASE_H
#define GAMESTATEBASE_H

#include "gamestatemanager.h"

class GameStateBase: public GameStateManager
{
public:
    GameStateBase();
    ~GameStateBase(){}
};

#endif // GAMESTATEBASE_H