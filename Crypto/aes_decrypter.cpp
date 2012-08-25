#include "aes_decrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"

namespace Crypto {

  namespace AES {

    Decrypter::Decrypter(const char* key, uint key_length)
    {
      KeyExpander expander (key_length);
      m_expanded_key = new char[expander.expanded_length()];
      m_rounds = expander.rounds();
      for (uint i = 0; i < key_length; ++i) {
        m_expanded_key[i] = key[i];
      }
      expander.expand(m_expanded_key);
    }

    Decrypter::~Decrypter()
    {
      delete[] m_expanded_key;
    }

    void Decrypter::decrypt(const char* cipher, char* plain)
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
    }
    
  } // namespace AES

} // namespace Crypto
