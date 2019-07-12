#include "newgamestate.h"
#include <memory>

using namespace std;

NewGameState::NewGameState(shared_ptr<Decorator> gsm): Decorator(gsm) {}
