#ifndef RSASTRATEGY_H
#define RSASTRATEGY_H

#include "rsakey.h"

namespace Crypto {

  class RSAStrategy
  {
  public:
    virtual RSAKey::text_t encrypt(const RSAKey::text_t& plain_text) const = 0;

    virtual RSAStrategy* copy() const = 0;

    virtual ~RSAStrategy();

  };

}

#endif // RSASTRATEGY_H
