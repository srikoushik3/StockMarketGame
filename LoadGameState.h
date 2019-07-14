#ifndef LOADGAMESTATE_H_
#define LOADGAMESTATE_H_
#include <string>
#include <memory>
#include "Decorator.h"
#include "json.hpp"
using json = nlohmann::json;

class LoadGameState : public Decorator {
  public:
    LoadGameState(std::shared_ptr<GameStateManager>);
    void loadStocksFromFile(json&);
    void loadUsersFromFile(json&);
    ~LoadGameState();
};

#endif
