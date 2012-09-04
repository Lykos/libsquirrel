#ifndef CRYPTO_CBC_MAC_H
#define CRYPTO_CBC_MAC_H

#include "preconditionviolation.h"
#include "conditiontype.h"
#include "cbc_encrypter.h"
#include "types.h"
#include <string>

namespace Crypto {

  namespace CBC {

    template <typename BlockCipher>
    class MAC
    {
    public:
      inline MAC(BlockCipher&& block_cipher, std::string&& initial_state) throw(PreconditionViolation);

      inline MAC(const BlockCipher& block_cipher, std::string&& initial_state) throw(PreconditionViolation);

      inline MAC(BlockCipher&& block_cipher, const std::string& initial_state) throw(PreconditionViolation);

      inline MAC(const BlockCipher& block_cipher, const std::string& initial_state) throw(PreconditionViolation);

      inline number_size_t signature_length() const throw() { return m_encrypter.plain_block_size(); }

      // Appends the MAC directly after the end of the message. Note that this changes the state.
      inline void sign(std::string& message) throw();

      // Assumes that the MAC is directly before the end of the message. Note that this changes the state.
      // In case of failure, the state is invalid.
      inline bool verify(const std::string& message) throw(PreconditionViolation);

      inline void remove_signature(std::string& message) const throw(PreconditionViolation);

      inline void state(const std::string& state) throw(PreconditionViolation);

      inline const std::string& state() const throw();

      inline bool state_valid() const throw() { return m_valid; }

    private:
      CBC::Encrypter<BlockCipher> m_encrypter;

      bool m_valid = true;

    };

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(BlockCipher&& block_cipher, std::string&& initial_state) throw(PreconditionViolation):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(const BlockCipher& block_cipher, std::string&& initial_state) throw(PreconditionViolation):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(BlockCipher&& block_cipher, const std::string& initial_state) throw(PreconditionViolation):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline MAC<BlockCipher>::MAC(const BlockCipher& block_cipher, const std::string& initial_state) throw(PreconditionViolation):
      m_encrypter (block_cipher, initial_state)
    {}

    template <typename BlockCipher>
    inline void MAC<BlockCipher>::sign(std::string& message) throw()
    {
      m_encrypter.encrypt(message);
      message.append(m_encrypter.state());
    }

    template <typename BlockCipher>
    inline bool MAC<BlockCipher>::verify(const std::string& message) throw(PreconditionViolation)
    {
      PREC(InvalidState, m_valid);
      m_valid = false;
      number_size_t sig_len = signature_length();
      number_size_t length = message.length();
      if (length < sig_len) {
        return false;
      }
      m_encrypter.encrypt(message.substr(0, length - sig_len));
      const std::string& mac = message.substr(length - sig_len, sig_len);
      const std::string& state = m_encrypter.state();

      return m_valid = mac == state;
    }

    template <typename BlockCipher>
    inline void MAC<BlockCipher>::remove_signature(std::string& message) const throw(PreconditionViolation)
    {
      number_size_t sig_len = signature_length();
      number_size_t length = message.length();
      PREC(SignatureLength, length >= sig_len)
      message.erase(length - sig_len, sig_len);
    }

    template <typename BlockCipher>
    inline void MAC<BlockCipher>::state(const std::string& state) throw(PreconditionViolation)
    {
      m_encrypter.state(state);
      m_valid = true;
    }

    template <typename BlockCipher>
    inline const std::string& MAC<BlockCipher>::state() const throw()
    {
      return m_encrypter.state();
    }

  } // namespace CBC

} // namespace Crypto

#endif // CRYPTO_CBC_MAC_H
