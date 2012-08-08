#ifndef RSADIRECTSTRATEGY_H
#define RSADIRECTSTRATEGY_H

#include "rsakey.h"
#include "rsastrategy.h"

namespace Crypto {

  class RSADirectStrategy : public RSAStrategy
  {
  public:
    RSADirectStrategy(const RSAKey& secret_key);

    RSAKey::text_t encrypt(const RSAKey::text_t& plain_text) const;

    RSADirectStrategy* copy() const;

  private:
    RSAKey m_secret_key;

  };

}

#endif // RSADIRECTSTRATEGY_H
