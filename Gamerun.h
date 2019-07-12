#include "decorator.h"
#include "gamestatemanager.h"
#include <memory>

class GameRun: public Decorator{
  public:
    GameRun(std::shared_ptr<GameStateManager> g);
    ~GameRun();
};
