#include "decorator.h"
#include <memory>

using namespace std;

Decorator::Decorator(shared_ptr<GameStateManager> gsm): gsm(gsm), GameStateManager(gsm){}
