#ifndef RSADIRECTSTRATEGY_H
#define RSADIRECTSTRATEGY_H

#include "rsa_types.h"
#include "rsa_decryptstrategy.h"

namespace Crypto {

  namespace RSA {

  class DirectStrategy : public DecryptStrategy
  {
  public:
    inline DirectStrategy(const private_key_t& private_key): DecryptStrategy(private_key) {}

    plain_text_t decrypt(const cipher_text_t& cipher_text) const;

    DirectStrategy* copy() const { return new DirectStrategy (DecryptStrategy::m_private_key); }

  };

  }

}

#endif // RSADIRECTSTRATEGY_H
