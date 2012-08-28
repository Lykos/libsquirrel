#include "aes_encrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <stdexcept>
#include <cstring>

namespace Crypto {

  namespace AES {

    Encrypter::Encrypter(const aes_byte_t* key, uint key_length)
    {
      KeyExpander expander (key_length);
      m_expanded_key_length = expander.expanded_length();
      m_expanded_key = new aes_byte_t[expander.expanded_length()];
      m_rounds = expander.rounds();
      for (uint i = 0; i < key_length; ++i) {
        m_expanded_key[i] = key[i];
      }
      expander.expand(m_expanded_key);
    }

    Encrypter::Encrypter(const Encrypter& other):
      m_expanded_key_length (other.m_expanded_key_length),
      m_expanded_key (new aes_byte_t[m_expanded_key_length]),
      m_rounds (other.m_rounds),
      m_helper (other.m_helper)
    {
      memcpy(m_expanded_key, other.m_expanded_key, m_expanded_key_length);
    }

    Encrypter::Encrypter(Encrypter&& other):
      m_expanded_key_length (other.m_expanded_key_length),
      m_expanded_key (other.m_expanded_key),
      m_rounds (other.m_rounds),
      m_helper (other.m_helper)
    {
      other.m_expanded_key = NULL;
    }

    Encrypter& Encrypter::operator=(const Encrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      m_expanded_key_length = other.m_expanded_key_length;
      m_expanded_key = new aes_byte_t[m_expanded_key_length];
      memcpy(m_expanded_key, other.m_expanded_key, m_expanded_key_length);
      m_rounds = other.m_rounds;
      m_helper = other.m_helper;
      return *this;
    }

    Encrypter& Encrypter::operator=(Encrypter&& other)
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

    Encrypter::~Encrypter()
    {
      delete[] m_expanded_key;
    }

    void Encrypter::encrypt(const aes_byte_t* plain, aes_byte_t* cipher)
    {
      for (uint i = 0; i < BLOCK_BYTE_SIZE; ++i) {
        cipher[i] = plain[i];
      }
      m_helper.apply_round_key(cipher, m_expanded_key, 0);
      for (uint i = 1; i < m_rounds - 1; ++i) {
        m_helper.sub_bytes(cipher);
        m_helper.shift_rows(cipher);
        m_helper.mix_columns(cipher);
        m_helper.apply_round_key(cipher, m_expanded_key, i);
      }
      m_helper.sub_bytes(cipher);
      m_helper.shift_rows(cipher);
      m_helper.apply_round_key(cipher, m_expanded_key, m_rounds - 1);
    }

  }

}
