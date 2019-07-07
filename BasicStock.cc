#include <iostream>
#include "BasicStock.h"
using namespace std;

BasicStock::BasicStock() {}

float BasicStock::getEODReturns() const {
  return 0.0;
}

BasicStock::~BasicStock() {}

BasicStock::BasicStock(const json & j): Stock(j){}
