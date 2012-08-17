#ifndef CRYPTO_ELGAMAL_KEYPERSONALIZER_H
#define CRYPTO_ELGAMAL_KEYPERSONALIZER_H

#include "elgamal_types.h"
#include "keypersonalizer.h"

namespace Crypto {

  namespace Elgamal {
    
    class KeyPersonalizer : public Crypto::KeyPersonalizer<public_key_t, personalized_public_key_t>
    {
    public:
      personalized_public_key_t personalize_key(public_key_t key) const;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_KEYPERSONALIZER_H
