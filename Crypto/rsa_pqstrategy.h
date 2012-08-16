#ifndef RSAPQSTRATEGY_H
#define RSAPQSTRATEGY_H

#include "rsa_decryptstrategy.h"
#include "rsa_types.h"

namespace Crypto {

  namespace RSA {

    class PQStrategy : public DecryptStrategy
    {
    public:
      PQStrategy(const private_key_t& private_key);

      plain_text_t decrypt(const cipher_text_t& plain_text) const;

      PQStrategy* copy() const { return new PQStrategy(DecryptStrategy::m_private_key); }

    private:

      number_t m_p_inv;

      number_t m_q_inv;

    };

  }

}

#endif // RSAPQSTRATEGY_H
