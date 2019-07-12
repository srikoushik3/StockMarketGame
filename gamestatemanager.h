#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "UserManager.h"
#include "StockManager.h"
#include "decorator.h"
#include <memory>


class GameStateManager
{
public:
    friend class Decorator;
    GameStateManager();
    virtual ~GameStateManager() = 0;
protected:
    std::shared_ptr<UserManager> userManager;
    std::shared_ptr<StockManager> stockManager;
};

#endif // GAMESTATEMANAGER_H
