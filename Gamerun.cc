#include "decorator.h"
#include "gamestatemanager.h"
#include "GameRun.h"
#include <memory>

using namespace std;

GameRun::GameRun(std::shared_ptr<GameStateManager> g): Decorator(g){}
