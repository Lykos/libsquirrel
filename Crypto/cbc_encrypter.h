#ifndef CRYPTO_CBC_ENCRYPTER_H
#define CRYPTO_CBC_ENCRYPTER_H

#include "Crypto_global.h"
#include "cbc_types.h"
#include <cstring>
#include <cassert>

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

      uint m_plain_block_size, m_cipher_block_size;

      cbc_byte_t* m_state;

    public:
      inline Encrypter(BlockCipher&& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline Encrypter(const BlockCipher& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline Encrypter(const Encrypter& other);

      inline Encrypter(Encrypter&& other);

      inline ~Encrypter();

      inline Encrypter<BlockCipher>& operator=(const Encrypter& other);

      inline Encrypter<BlockCipher>& operator=(Encrypter&& other);

      inline ulong get_cipher_length(ulong plain_length) const;

      inline ulong encrypt(const cbc_byte_t* plain, ulong length, cbc_byte_t* cipher);

      inline const cbc_byte_t* get_state() const { return m_state; }

    };

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(BlockCipher&& block_cipher, const cbc_byte_t* initial_state, uint state_length):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      assert(state_length >= m_plain_block_size);
      memcpy(m_state, initial_state, m_plain_block_size);
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(const BlockCipher& block_cipher, const cbc_byte_t* initial_state, uint state_length):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      assert(state_length >= m_plain_block_size);
      memcpy(m_state, initial_state, m_plain_block_size);
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(const Encrypter& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      memcpy(m_state, other.m_state, m_block_cipher.plain_block_size());
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::Encrypter(Encrypter&& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (other.m_state)
    {}

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>::~Encrypter()
    {
      delete[] m_state;
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>& Encrypter<BlockCipher>::operator=(const Encrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      m_block_cipher = other.m_block_cipher;
      m_plain_block_size = other.m_plain_block_size;
      m_cipher_block_size = other.m_cipher_block_size;
      m_state = new cbc_byte_t[m_plain_block_size];
      memcpy(m_state, other.m_state, m_block_cipher.plain_block_size());
      return *this;
    }

    template <typename BlockCipher>
    inline Encrypter<BlockCipher>& Encrypter<BlockCipher>::operator=(Encrypter&& other)
    {
      if (this == &other) {
        return *this;
      }
      m_block_cipher = std::move(other.m_block_cipher);
      m_plain_block_size = other.m_plain_block_size;
      m_cipher_block_size = other.m_cipher_block_size;
      m_state = other.m_state;
      other.m_state = NULL;
      return *this;
    }

    template <typename BlockCipher>
    inline ulong Encrypter<BlockCipher>::get_cipher_length(ulong plain_length) const
    {
      // Add at least one bit for padding and then adjust to multiple of block_size
      uint padding = m_plain_block_size - (plain_length + 1) % m_plain_block_size;
      ulong cipher_length = plain_length + 1 + padding % m_plain_block_size;
      assert(cipher_length > plain_length && cipher_length <= plain_length + m_plain_block_size);
      assert(cipher_length % m_plain_block_size == 0);
      return cipher_length;
    }

    template <typename BlockCipher>
    inline ulong Encrypter<BlockCipher>::encrypt(const cbc_byte_t* plain, ulong plain_length, cbc_byte_t* cipher)
    {
      ulong cipher_length = get_cipher_length(plain_length);
      cbc_byte_t *block = new cbc_byte_t[m_plain_block_size];
      cbc_byte_t *null_cipher = (cipher == NULL ? new cbc_byte_t[m_cipher_block_size] : NULL);
      ulong blocks = cipher_length / m_plain_block_size;
      for (ulong i = 0; i < blocks; ++i) {
        if (i == blocks - 1) {
          ulong remaining_length = plain_length % m_plain_block_size;
          memcpy(block, plain + i * m_plain_block_size, remaining_length);
          block[remaining_length] = 0x80;
          memset(block + 1 + remaining_length, 0, m_plain_block_size - remaining_length - 1);
        } else {
          memcpy(block, plain + i * m_plain_block_size, m_plain_block_size);
        }
        for (uint j = 0; j < m_plain_block_size; ++j) {
          block[j] ^= m_state[j];
        }
        if (cipher == NULL) {
          // If this encryption should only change the state, i.e. the initial vector
          m_block_cipher.encrypt(block, null_cipher);
          for (uint j = 0; j < m_plain_block_size; ++j) {
            m_state[j] = null_cipher[j];
          }
        } else {
          m_block_cipher.encrypt(block, cipher + i * m_cipher_block_size);
          // It should be clear that the cipher block size is at least the plain block size.
          for (uint j = 0; j < m_plain_block_size; ++j) {
            m_state[j] = cipher[i * m_cipher_block_size + j];
          }
        }
      }
      delete[] block;
      return cipher_length;
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
