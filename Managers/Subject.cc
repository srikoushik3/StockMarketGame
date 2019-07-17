#include "Subject.h"
#include "UIHandlers/Observer.h"
using namespace std;

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer* o) {
  observers.emplace_back(o);
}

void Subject::detach(Observer* o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyRender() {
  for (auto ob : observers) {
    ob->render();
  }
}
