#ifndef CRYPTO_CBC_MAC_H
#define CRYPTO_CBC_MAC_H

#include "Crypto/cbc_encrypter.h"
#include "Crypto/cbc_types.h"
#include <cstring>

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class MAC
    {
    public:
      inline MAC(BlockCipher&& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline MAC(const BlockCipher& block_cipher, const cbc_byte_t* initial_state, uint state_length);

      inline uint signature_length() const { return m_encrypter.plain_block_size(); }

      // Appends the MAC directly after the end of the message. Note that this changes the state.
      inline ulong sign(cbc_byte_t* message, ulong length);

      // Assumes that the MAC is directly before the end of the message. Note that this changes the state.
      // In case of failure, the state is undefined.
      inline bool verify(const cbc_byte_t* message, ulong length);

    private:
      CBC::Encrypter<BlockCipher> m_encrypter;

    };

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(BlockCipher&& block_cipher, const cbc_byte_t *initial_state, uint state_length):
      m_encrypter (block_cipher, initial_state, state_length)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(const BlockCipher& block_cipher, const cbc_byte_t *initial_state, uint state_length):
      m_encrypter (block_cipher, initial_state, state_length)
    {}

    template <typename BlockCipher>
    inline ulong MAC<BlockCipher>::sign(cbc_byte_t* message, ulong length)
    {
      m_encrypter.encrypt(message, length, NULL);
      memcpy(message + length, m_encrypter.get_state(), signature_length());
      return length + signature_length();
    }

    template <typename BlockCipher>
    inline bool MAC<BlockCipher>::verify(const cbc_byte_t* message, ulong length)
    {
      uint sig_len = signature_length();
      if (length < sig_len) {
        return false;
      }
      m_encrypter.encrypt(message, length - sig_len, NULL);
      const cbc_byte_t* mac = message + length - sig_len;
      const cbc_byte_t* state = m_encrypter.get_state();
      for (uint i = 0; i < sig_len; ++i) {
        if (state[i] != mac[i]) {
          return false;
        }
      }
      return true;
    }
    
  } // namespace CBC

} // namespace Crypto

#endif // CRYPTO_CBC_MAC_H
