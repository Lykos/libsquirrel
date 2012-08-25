#include "aes_encrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <stdexcept>

namespace Crypto {

  namespace AES {

    Encrypter::Encrypter(const char* key, uint key_length)
    {
      KeyExpander expander (key_length);
      m_expanded_key = new char[expander.expanded_length()];
      m_rounds = expander.rounds();
      for (uint i = 0; i < key_length; ++i) {
        m_expanded_key[i] = key[i];
      }
      expander.expand(m_expanded_key);
    }

    Encrypter::~Encrypter()
    {
      delete[] m_expanded_key;
    }

    void Encrypter::encrypt(const char* plain, char* cipher)
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
