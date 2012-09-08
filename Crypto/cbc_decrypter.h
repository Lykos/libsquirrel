#ifndef CRYPTO_CBC_DECRYPTER_H
#define CRYPTO_CBC_DECRYPTER_H

#include "types.h"
#include "Crypto_global.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include <string>
#define DEC_PREC_STATE_LENGTH() PREC(StateLength, initial_state.length() >= state_length());

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class CRYPTOSHARED_EXPORT Decrypter
    {
      friend void std::swap <>(Decrypter<BlockCipher>& first, Decrypter<BlockCipher>& second);

    private:
      BlockCipher m_block_cipher;

      number_size_t m_plain_block_size, m_cipher_block_size;

      std::string m_state, m_block;

      bool m_valid = true;

    public:
      inline Decrypter(BlockCipher&& block_cipher, std::string&& initial_state);

      inline Decrypter(const BlockCipher& block_cipher, std::string&& initial_state);

      inline Decrypter(BlockCipher&& block_cipher, const std::string& initial_state);

      inline Decrypter(const BlockCipher& block_cipher, const std::string& initial_state);

      inline message_size_t max_plain_length(message_size_t cipher_length) const;

      inline message_size_t plain_block_size() const { return m_plain_block_size; }

      inline message_size_t cipher_block_size() const { return m_cipher_block_size; }

      inline message_size_t state_length() const { return m_plain_block_size; }

      inline std::string decrypt(const std::string& plain);

      inline const std::string& state() const { return m_state; }

      inline bool state_valid() const { return m_valid; }

      inline const std::string& state(const std::string& initial_state);

    };

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(BlockCipher&& block_cipher, std::string&& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0)
    {
      DEC_PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(const BlockCipher& block_cipher, std::string&& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0)
    {
      DEC_PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(BlockCipher&& block_cipher, const std::string& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0)
    {
      DEC_PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(const BlockCipher& block_cipher, const std::string& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0)
    {
      DEC_PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline std::string Decrypter<BlockCipher>::decrypt(const std::string& cipher)
    {
      PREC(InvalidState, m_valid);
      m_valid = false;
      message_size_t cipher_length = cipher.length();
      PREC(MessageLength, cipher_length % m_cipher_block_size == 0);
      message_size_t blocks = cipher_length / m_cipher_block_size;
      std::string plain (blocks * m_plain_block_size, 0);
      for (message_size_t i = 0; i < blocks; ++i) {
        m_block.replace(0, m_plain_block_size, m_block_cipher.decrypt(cipher.substr(i * m_cipher_block_size, m_cipher_block_size)));
        // It should be clear that the cipher block size is at least the plain block size.
        for (number_size_t j = 0; j < m_plain_block_size; ++j) {
          m_block[j] ^= m_state[j];
          m_state[j] = cipher[i * m_cipher_block_size + j];
        }
        if (i < blocks - 1) {
          plain.replace(i * m_plain_block_size, m_plain_block_size, m_block);
        }
      }
      message_size_t remaining_length = m_plain_block_size - 1;
      while (remaining_length > 0 && m_block[remaining_length] == 0) {
        --remaining_length;
      }
      PREC(MessagePadding, (byte_t)m_block[remaining_length] == 0x80);
      plain.replace((blocks - 1) * m_plain_block_size, m_plain_block_size, m_block.substr(0, remaining_length));
      m_valid = true;
      return plain;
    }

    template <typename BlockCipher>
    inline const std::string& Decrypter<BlockCipher>::state(const std::string& initial_state)
    {
      DEC_PREC_STATE_LENGTH();
      m_state.replace(0, m_plain_block_size, initial_state);
      m_valid = true;
      return initial_state;
    }

  } // namespace CBC

} // namespace Crypto

#endif // CRYPTO_CBC_DECRYPTER_H

