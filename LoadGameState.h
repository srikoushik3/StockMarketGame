#ifndef LOADGAMESTATE_H_
#define LOADGAMESTATE_H_
#include <string>
#include <memory>
#include "decorator.h"
#include "json.hpp"
using json = nlohmann::json;

class LoadGameState : public Decorator {
  public:
    LoadGameState(std::shared_ptr<Decorator>);
    void loadStocksFromFile(json&);
    void loadUsersFromFile(json&);
    ~LoadGameState();
};

#endif