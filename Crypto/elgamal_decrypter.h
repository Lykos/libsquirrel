#ifndef CRYPTO_ELGAMAL_DECRYPTER_H
#define CRYPTO_ELGAMAL_DECRYPTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/elgamal_types.h"
#include "Crypto/longintconverter.h"
#include <string>

namespace Crypto {

  namespace Elgamal {
    
    class CRYPTOSHARED_EXPORT Decrypter
    {
    public:
      explicit Decrypter(const private_key_t& private_key);

      Decrypter(const std::string& raw_private_key);

      number_t decrypt(const number_t& cipher, const number_t& other_gen_power) const;

      std::string decrypt(const std::string& cipher_text) const;

      number_size_t plain_block_size() const { return m_plain_length; }

      number_size_t cipher_block_size() const { return m_cipher_length; }

    private:
      number_t m_modulus;

      exponent_t m_exponent;

      // cipher_part_length is the length of the encrypted text itself, cipher_length also includes
      // the key part, which also has to be sent
      number_size_t m_plain_length, m_key_part_length, m_cipher_part_length, m_cipher_length;

      LongIntConverter m_converter;

    };
    
  } // namespace Elgamal

} // namespace Crypto

#endif // CRYPTO_ELGAMAL_DECRYPTER_H
