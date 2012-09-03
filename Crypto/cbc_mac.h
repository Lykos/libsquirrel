#ifndef CRYPTO_CBC_MAC_H
#define CRYPTO_CBC_MAC_H

#include "Crypto/cbc_encrypter.h"
#include "Crypto/types.h"
#include <string>

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class MAC
    {
    public:
      inline MAC(BlockCipher&& block_cipher, std::string&& initial_state);

      inline MAC(const BlockCipher& block_cipher, std::string&& initial_state);

      inline MAC(BlockCipher&& block_cipher, const std::string& initial_state);

      inline MAC(const BlockCipher& block_cipher, const std::string& initial_state);

      inline number_size_t signature_length() const { return m_encrypter.plain_block_size(); }

      // Appends the MAC directly after the end of the message. Note that this changes the state.
      inline void sign(std::string& message);

      // Assumes that the MAC is directly before the end of the message. Note that this changes the state.
      // In case of failure, the state is undefined.
      inline bool verify(const std::string& message);

    private:
      CBC::Encrypter<BlockCipher> m_encrypter;

    };

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(BlockCipher&& block_cipher, std::string&& initial_state):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(const BlockCipher& block_cipher, std::string&& initial_state):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(BlockCipher&& block_cipher, const std::string& initial_state):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(const BlockCipher& block_cipher, const std::string& initial_state):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline void MAC<BlockCipher>::sign(std::string& message)
    {
      m_encrypter.encrypt(message);
      message.append(m_encrypter.get_state());
    }

    template <typename BlockCipher>
    inline bool MAC<BlockCipher>::verify(const std::string& message)
    {
      number_size_t sig_len = signature_length();
      number_size_t length = message.length();
      if (length < sig_len) {
        return false;
      }
      m_encrypter.encrypt(message);
      const std::string& mac = message.substr(length - sig_len, sig_len);
      const std::string& state = m_encrypter.get_state();
      return mac == state;
    }
    
  } // namespace CBC

} // namespace Crypto

#endif // CRYPTO_CBC_MAC_H
