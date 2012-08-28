#ifndef CRYPTO_CBC_MAC_H
#define CRYPTO_CBC_MAC_H

#include "cbc_encrypter.h"
#include "cbc_types.h"
#include <cstring>

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class Mac : private Encrypter<BlockCipher>
    {
    public:
      inline uint signature_length() const { return Encrypter<BlockCipher>::plain_block_size(); }

      // Appends the MAC directly after the end of the message. Note that this changes the state.
      inline ulong mac(cbc_byte_t* message, ulong length);

      // Assumes that the MAC is directly before the end of the message. Note that this changes the state.
      // In case of failure, the state is undefined.
      inline bool verify(const cbc_byte_t* message, ulong length);

    };

    template <typename BlockCipher>
    inline ulong Mac<BlockCipher>::mac(const cbc_byte_t* message, ulong length)
    {
      Encrypter::encrypt(message, length, NULL);
      memcpy(message + length, Encrypter<BlockCipher>::get_state(), mac_length());
      return length + mac_length();
    }

    template <typename BlockCipher>
    inline bool Mac<BlockCipher>::verify(const cbc_byte_t* message, ulong length)
    {
      if (length < mac_length()) {
        return false;
      }
      Encrypter::encrypt(message, length - mac_length(), NULL);
      const cbc_byte_t* mac = message + length - mac_length();
      for (uint i = 0; i < mac_length(); ++i) {
        if (Encrypter<BlockCipher>::m_state[i] != mac[i]) {
          return false;
        }
      }
      return true;
    }
    
  } // namespace CBC

} // namespace Crypto

#endif // CRYPTO_CBC_MAC_H
