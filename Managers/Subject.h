#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "UIHandlers/Observer.h"


class Subject {
  std::vector<Observer *> observers;

 public:
  Subject();
  void attach(Observer *);
  void detach(Observer *);
  void notifyRender();
  void notifyGameOver();
  virtual ~Subject()=0;
};

#endif // SUBJECT_H
