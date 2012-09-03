#ifndef CRYPTO_CBC_ENCRYPTER_H
#define CRYPTO_CBC_ENCRYPTER_H

#include "Crypto/Crypto_global.h"
#include "Crypto/conditiontype.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/types.h"
#include <cstring>
#include <cassert>
#include <string>
#define PREC_STATE_LENGTH() PREC(StateLength, initial_state.length() >= state_length());

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class CRYPTOSHARED_EXPORT Encrypter;

  }

}

namespace std {

  template <typename BlockCipher>
  inline void swap(Crypto::CBC::Encrypter<BlockCipher>& first, Crypto::CBC::Encrypter<BlockCipher>& second);

}

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class CRYPTOSHARED_EXPORT Encrypter
    {
      friend void std::swap <>(Encrypter<BlockCipher>& first, Encrypter<BlockCipher>& second);

    private:
      BlockCipher m_block_cipher;

      number_size_t m_plain_block_size, m_cipher_block_size;

      std::string m_state, m_block;

      const byte_t* m_tmp_cipher;

    public:
      inline Encrypter(BlockCipher&& block_cipher, const std::string& initial_state);

      inline Encrypter(const BlockCipher& block_cipher, const std::string& initial_state);

      inline Encrypter(const Encrypter& other);

      inline Encrypter(Encrypter&& other);

      inline ~Encrypter() {}

      inline Encrypter<BlockCipher>& operator=(const Encrypter& other);

      inline Encrypter<BlockCipher>& operator=(Encrypter&& other);

      inline message_size_t cipher_length(message_size_t plain_length) const;

      inline message_size_t plain_block_size() const { return m_plain_block_size; }

      inline message_size_t cipher_block_size() const { return m_cipher_block_size; }

      inline message_size_t state_length() const { return m_plain_block_size; }

      inline std::string encrypt(const std::string& plain);

      inline const std::string& get_state() const { return m_state; }

      inline void set_state(const std::string& new_state);

    };

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(BlockCipher&& block_cipher, const std::string& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0),
      m_tmp_cipher (new byte_t[m_cipher_block_size])
    {
      PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(const BlockCipher& block_cipher, const std::string& initial_state):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (initial_state),
      m_block (m_plain_block_size, 0)
    {
      PREC_STATE_LENGTH();
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(const Encrypter& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (other.m_state),
      m_block (m_plain_block_size, '0')
    {}

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(Encrypter&& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (std::move(other.m_state)),
      m_block (std::move(other.m_block))
    {
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>& Encrypter<BlockCipher>::operator=(const Encrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      if (m_plain_block_size != other.m_plain_block_size) {
        delete[] m_state;
        delete[] m_block;
        m_state = new byte_t[other.m_plain_block_size];
        m_block = new byte_t[other.m_plain_block_size];
      }
      m_block_cipher = other.m_block_cipher;
      m_plain_block_size = other.m_plain_block_size;
      m_cipher_block_size = other.m_cipher_block_size;
      memcpy(m_state, other.m_state, m_block_cipher.plain_block_size());
      return *this;
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>& Encrypter<BlockCipher>::operator=(Encrypter&& other)
    {
      if (this == &other) {
        return *this;
      }
      if (m_plain_block_size != other.m_plain_block_size) {
        m_state = other.m_state;
        m_block = other.m_block;
        other.m_state = NULL;
        other.m_block = NULL;
      }
      m_block_cipher = std::move(other.m_block_cipher);
      m_plain_block_size = other.m_plain_block_size;
      m_cipher_block_size = other.m_cipher_block_size;
      return *this;
    }

    template <typename BlockCipher>
    inline message_size_t Encrypter<BlockCipher>::cipher_length(message_size_t plain_length) const
    {
      // Add at least one bit for padding and then adjust to multiple of block_size
      number_size_t padding = (m_plain_block_size - (plain_length + 1) % m_plain_block_size) % m_plain_block_size;
      message_size_t padded_length = plain_length + 1 + padding;
      assert(plain_length <= padded_length && padded_length <= plain_length + m_plain_block_size);
      assert(padded_length % m_plain_block_size == 0);
      message_size_t cipher_length = padded_length / m_plain_block_size * m_cipher_block_size;
      assert(cipher_length % m_cipher_block_size == 0);
      return cipher_length;
    }

    template <typename BlockCipher>
    inline std::string Encrypter<BlockCipher>::encrypt(const std::string& plain)
    {
      message_size_t plain_length = plain.length();
      message_size_t cipher_len = cipher_length(plain_length);
      message_size_t blocks = cipher_len / m_cipher_block_size;
      std::string cipher (cipher_len, 0);
      for (message_size_t i = 0; i < blocks; ++i) {
        if (i == blocks - 1) {
          message_size_t remaining_length = plain_length % m_plain_block_size;
          m_block.replace(0, m_plain_block_size, plain.substr(i * m_plain_block_size, remaining_length));
          m_block[remaining_length] = 0x80;
          m_block.replace(remaining_length + 1, m_plain_block_size - remaining_length - 1, m_plain_block_size - remaining_length - 1, 0);
        } else {
          m_block.replace(0, m_plain_block_size, plain.substr(i * m_plain_block_size, m_plain_block_size));
        }
        for (number_size_t j = 0; j < m_plain_block_size; ++j) {
          m_block[j] ^= m_state[j];
        }
        m_block_cipher.encrypt(m_block.data(), m_tmp_cipher);
        cipher.replace(i * m_cipher_block_size, m_cipher_block_size, (const char*)m_tmp_cipher, m_cipher_block_size);
        // It should be clear that the cipher block size is at least the plain block size.
        for (number_size_t j = 0; j < m_plain_block_size; ++j) {
          m_state[j] = cipher[i * m_cipher_block_size + j];
        }
      }
      return cipher;
    }

    template <typename BlockCipher>
    inline void Encrypter<BlockCipher>::set_state(const std::string& initial_state)
    {
      PREC_STATE_LENGTH();
      m_state.replace(0, m_plain_block_size, initial_state);
    }

  } // namespace CBC

} // namespace Crypto

namespace std {

  template <typename BlockCipher>
  inline void swap(Crypto::CBC::Encrypter<BlockCipher>& first, Crypto::CBC::Encrypter<BlockCipher>& second)
  {
    swap(first.m_block_cipher, second.m_block_cipher);
    swap(first.m_plain_block_size, second.m_plain_block_size);
    swap(first.m_state, second.m_state);
  }

}

#endif // CRYPTO_CBC_ENCRYPTER_H
