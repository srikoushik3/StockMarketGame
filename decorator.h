#ifndef DECORATOR_H
#define DECORATOR_H

#include "gamestatemanager.h"
#include <memory>


class Decorator: public GameStateManager{
    protected:
        std::shared_ptr<Decorator> gsm;
    public:
        Decorator(std::shared_ptr<Decorator>);
        ~Decorator(){}
};

#endif // DECORATOR_H
