 /*
  * File: Decorator.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the Decorator class which inherits 
  *   from the GameStateManager Class and implements the Decorator 
  *   pattern to navigate between the various game states. It contains
  *   a shared pointer to GameStateManager and a Constructor.
  */
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
