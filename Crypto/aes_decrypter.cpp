#include "aes_decrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <cstring>

namespace Crypto {

  namespace AES {

    Decrypter::Decrypter(const byte_t* key, uint key_length)
    {
      KeyExpander expander (key_length);
      m_expanded_key_length = expander.expanded_length();
      m_expanded_key = new byte_t[m_expanded_key_length];
      m_rounds = expander.rounds();
      for (uint i = 0; i < key_length; ++i) {
        m_expanded_key[i] = key[i];
      }
      expander.expand(m_expanded_key);
    }

    Decrypter::Decrypter(const Decrypter& other):
      m_expanded_key_length (other.m_expanded_key_length),
      m_expanded_key (new byte_t[m_expanded_key_length]),
      m_rounds (other.m_rounds),
      m_helper (other.m_helper)
    {
      memcpy(m_expanded_key, other.m_expanded_key, m_expanded_key_length);
    }

    Decrypter::Decrypter(Decrypter&& other):
      m_expanded_key_length (other.m_expanded_key_length),
      m_expanded_key (other.m_expanded_key),
      m_rounds (other.m_rounds),
      m_helper (other.m_helper)
    {
      other.m_expanded_key = NULL;
    }

    Decrypter& Decrypter::operator=(const Decrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      m_expanded_key_length = other.m_expanded_key_length;
      m_expanded_key = new byte_t[m_expanded_key_length];
      memcpy(m_expanded_key, other.m_expanded_key, m_expanded_key_length);
      m_rounds = other.m_rounds;
      m_helper = other.m_helper;
      return *this;
    }

    Decrypter& Decrypter::operator=(Decrypter&& other)
    {
      if (this == &other) {
        return *this;
      }
      m_expanded_key_length = other.m_expanded_key_length;
      m_expanded_key = other.m_expanded_key;
      m_rounds = other.m_rounds;
      m_helper = std::move(other.m_helper);
      other.m_expanded_key = NULL;
      return *this;
    }

    Decrypter::~Decrypter()
    {
      delete[] m_expanded_key;
    }

    bool Decrypter::decrypt(const byte_t* cipher, byte_t* plain)
    {
      for (uint i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        plain[i] = cipher[i];
      }
      m_helper.apply_round_key(plain, m_expanded_key, m_rounds - 1);
      m_helper.inv_shift_rows(plain);
      m_helper.inv_sub_bytes(plain);
      for (uint i = m_rounds - 2; i > 0; --i) {
        m_helper.apply_round_key(plain, m_expanded_key, i);
        m_helper.inv_mix_columns(plain);
        m_helper.inv_shift_rows(plain);
        m_helper.inv_sub_bytes(plain);
      }
      m_helper.apply_round_key(plain, m_expanded_key, 0);
      return true;
    }
    
  } // namespace AES

} // namespace Crypto
