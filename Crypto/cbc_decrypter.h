#ifndef CRYPTO_CBC_DECRYPTER_H
#define CRYPTO_CBC_DECRYPTER_H

#include "Crypto_global.h"
#include "cbc_types.h"
#include <cstring>

namespace std {

  template <typename BlockCipher>
  inline void swap(Crypto::CBC::Decrypter<BlockCipher>& first, Crypto::CBC::Decrypter<BlockCipher>& second);

}

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class CRYPTOSHARED_EXPORT Decrypter
    {
      friend void std::swap <>(Decrypter<BlockCipher>& first, Decrypter<BlockCipher>& second);

    private:
      BlockCipher m_block_cipher;

      uint m_plain_block_size, m_cipher_block_size;

      cbc_byte_t* m_state;

    public:
      inline Decrypter(BlockCipher&& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline Decrypter(const BlockCipher& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline Decrypter(const Decrypter& other);

      inline Decrypter(Decrypter&& other);

      inline ~Decrypter();

      inline Decrypter<BlockCipher>& operator=(const Decrypter& other);

      inline Decrypter<BlockCipher>& operator=(Decrypter&& other);

      inline ulong max_plain_length(ulong cipher_length) const;

      inline ulong plain_block_size() const { return m_plain_block_size; }

      inline ulong cipher_block_size() const { return m_cipher_block_size; }

      inline ulong state_length() const { return m_plain_block_size; }

      inline ulong decrypt(const cbc_byte_t* plain, ulong length, cbc_byte_t* cipher);

      inline const cbc_byte_t* get_state() const { return m_state; }

      inline void set_state(const cbc_byte_t* new_state, uint length);

    };

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(BlockCipher&& block_cipher, const cbc_byte_t* initial_state, uint state_length):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      assert(state_length >= m_plain_block_size);
      memcpy(m_state, initial_state, m_plain_block_size);
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(const BlockCipher& block_cipher, const cbc_byte_t* initial_state, uint state_length):
      m_block_cipher (block_cipher),
      m_plain_block_size (block_cipher.plain_block_size()),
      m_cipher_block_size (block_cipher.cipher_block_size()),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      assert(state_length >= m_plain_block_size);
      memcpy(m_state, initial_state, m_plain_block_size);
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(const Decrypter& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (new cbc_byte_t[m_plain_block_size])
    {
      memcpy(m_state, other.m_state, m_block_cipher.plain_block_size());
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::Decrypter(Decrypter&& other):
      m_block_cipher (other.m_block_cipher),
      m_plain_block_size (other.m_plain_block_size),
      m_cipher_block_size (other.m_cipher_block_size),
      m_state (other.m_state)
    {}

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>::~Decrypter()
    {
      delete[] m_state;
    }

    template <typename BlockCipher>
    inline Decrypter<BlockCipher>& Decrypter<BlockCipher>::operator=(const Decrypter& other)
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
    inline Decrypter<BlockCipher>& Decrypter<BlockCipher>::operator=(Decrypter&& other)
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
    inline ulong Decrypter<BlockCipher>::max_plain_length(ulong cipher_length) const
    {
      assert(cipher_length % m_cipher_block_size == 0);
      return cipher_length / m_cipher_block_size * m_plain_block_size - 1;
    }

    template <typename BlockCipher>
    inline ulong Decrypter<BlockCipher>::decrypt(const cbc_byte_t* cipher, ulong cipher_length, cbc_byte_t* plain)
    {
      if (cipher_length % m_cipher_block_size != 0) {
        // Invalid ciphertext, treat message as empty message
        return 0;
      }
      cbc_byte_t *block = new cbc_byte_t[m_plain_block_size];
      ulong blocks = cipher_length / m_cipher_block_size;
      ulong plain_length = max_plain_length(cipher_length);
      for (ulong i = 0; i < blocks; ++i) {
        m_block_cipher.decrypt(cipher + i * m_cipher_block_size, block);
        // It should be clear that the cipher block size is at least the plain block size.
        for (uint j = 0; j < m_plain_block_size; ++j) {
          block[j] ^= m_state[j];
          m_state[j] = cipher[i * m_cipher_block_size + j];
        }
        if (i == blocks - 1) {
          ulong remaining_length = m_plain_block_size - 1;
          while (remaining_length > 0 && block[remaining_length] == 0) {
            --remaining_length;
            --plain_length;
          }
          if (block[remaining_length] != 0x80) {
            delete[] block;
            // Invalid ciphertext, treat message as empty message
            return 0;
          }
          memcpy(plain + i * m_plain_block_size, block, remaining_length);
        } else {
          memcpy(plain + i * m_plain_block_size, block, m_plain_block_size);
        }
      }
      delete[] block;
      return plain_length;
    }

    template <typename BlockCipher>
    inline void Decrypter<BlockCipher>::set_state(const cbc_byte_t* new_state, uint length)
    {
      assert(length >= m_plain_block_size);
      memcpy(m_state, new_state, m_plain_block_size);
    }

  } // namespace CBC

} // namespace Crypto

namespace std {

  template <typename BlockCipher>
  inline void swap(Crypto::CBC::Decrypter<BlockCipher>& first, Crypto::CBC::Decrypter<BlockCipher>& second)
  {
    swap(first.m_block_cipher, second.m_block_cipher);
    swap(first.m_plain_block_size, second.m_plain_block_size);
    swap(first.m_state, second.m_state);
  }

}

#endif // CRYPTO_CBC_DECRYPTER_H
