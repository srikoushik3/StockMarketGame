#include "GameStateBase.h"
#include "UserManager.h"
#include "StockManager.h"
#include <memory>

using namespace std;

GameStateBase::GameStateBase()
{
    userManager = make_shared<UserManager>();
    stockManager = make_shared<StockManager>();
}
