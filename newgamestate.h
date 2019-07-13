#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include "decorator.h"
#include "gamestatemanager.h"
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
