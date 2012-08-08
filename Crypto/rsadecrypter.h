#ifndef RSADECRYPTER_H
#define RSADECRYPTER_H

#include "Crypto_global.h"
#include "decrypter.h"
#include "rsakey.h"

namespace Crypto {

  class CRYPTOSHARED_EXPORT RSADecrypter : public Decrypter
  {
  public:
    RSADecrypter(const RSAKey& public_key);

    RSAKey::text_t decrypt(const RSAKey::text_t& cipher_text) const;

  private:
    RSAKey m_public_key;
  };

}

#endif // RSADECRYPTER_H
