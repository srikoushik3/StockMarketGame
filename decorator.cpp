#include "decorator.h"
#include <memory>

using namespace std;

Decorator::Decorator(shared_ptr<Decorator> gsm): gsm(gsm){
    this->stockManager = gsm->stockManager;
    this->userManager= gsm->userManager;
}
