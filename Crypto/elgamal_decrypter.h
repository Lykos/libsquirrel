#ifndef CRYPTO_ELGAMAL_DECRYPTER_H
#define CRYPTO_ELGAMAL_DECRYPTER_H

#include "Crypto_global.h"
#include "elgamal_types.h"
#include "longintconverter.h"

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    public:
      typedef LongIntConverter::number_size_t number_size_t;

      explicit Decrypter(const private_key_t& private_key);

      Decrypter(const elgamal_byte_t* raw_private_key, number_size_t length);

      number_t decrypt(const number_t& cipher, const number_t& other_gen_power) const;

      void decrypt(const elgamal_byte_t* cipher_text, elgamal_byte_t* plain_text) const;

      number_size_t plain_block_size() const { return m_plain_length; }

      number_size_t cipher_block_size() const { return m_cipher_length; }

    private:
      number_t m_modulus;

      exponent_t m_exponent;

      number_size_t m_plain_length, m_exponent_length, m_cipher_length;

      LongIntConverter m_converter;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_DECRYPTER_H
