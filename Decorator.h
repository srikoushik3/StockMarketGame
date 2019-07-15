#ifndef DECORATOR_H
#define DECORATOR_H

#include "GameStateManager.h"
#include <memory>


class Decorator: public GameStateManager{
    protected:
        std::shared_ptr<GameStateManager> gsm;
    public:
        Decorator(std::shared_ptr<GameStateManager>);
        ~Decorator(){}
};

#endif // DECORATOR_H
