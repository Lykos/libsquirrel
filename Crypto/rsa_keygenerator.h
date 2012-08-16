#ifndef RSAKEYGENERATOR_H
#define RSAKEYGENERATOR_H

#include "Crypto_global.h"
#include "keygenerator.h"
#include "rsa_types.h"

namespace Crypto {

  namespace RSA {

    class CRYPTOSHARED_EXPORT KeyGenerator : public Crypto::KeyGenerator<public_key_t, private_key_t>
    {
    public:
      key_pair_t generate() const;

    };

  }

}

#endif // RSAKEYGENERATOR_H
