#ifndef BOND_H_
#define BOND_H_
#include <string>
#include "Stock.h"
#include "json.hpp"

using json = nlohmann::json;

class Bond : public Stock{
  float dividendPerShare;
  public:
    Bond();
    float getEODReturns() const;
    float getDividendPerShare() const;
    json serialize() const override;
    Bond(const json &);
    ~Bond();
};

#endif
