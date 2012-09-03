#include "aes_decrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include <string>

using namespace std;

namespace Crypto {

  namespace AES {

    Decrypter::Decrypter(const string& key)
    {
      KeyExpander expander;
      m_expanded_key = expander.expand(key);
    }

    string Decrypter::decrypt(const string& cipher)
    {
      string plain (cipher);
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
      return plain;
    }
    
  } // namespace AES

} // namespace Crypto
