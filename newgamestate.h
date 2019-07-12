#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include "decorator.h"
#include <memory>


class NewGameState: public Decorator
{
public:
    NewGameState(std::shared_ptr<Decorator>);
    ~NewGameState(){}
};

#endif // NEWGAMESTATE_H
