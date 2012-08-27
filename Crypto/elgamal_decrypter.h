#ifndef CRYPTO_ELGAMAL_DECRYPTER_H
#define CRYPTO_ELGAMAL_DECRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"
#include "longintconverter.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    private:
      number_t m_modulus;

      exponent_t m_exponent;

      uint m_plain_length, m_exponent_length, m_cipher_length;

      LongIntConverter m_converter;

    public:
      explicit Decrypter(const private_key_t& private_key);

      void decrypt(const elgamal_byte_t* cipher_text, elgamal_byte_t* plain_text);

      uint plain_block_size() const { return m_plain_length; }

      uint cipher_block_size() const { return m_cipher_length; }

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_DECRYPTER_H
