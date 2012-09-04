#include "aes_encrypter.h"
#include "aes_keyexpander.h"
#include "aes_constants.h"
#include "preconditionviolation.h"
#include "conditiontype.h"
#include <stdexcept>
#include <string>

using namespace std;

namespace Crypto {

  namespace AES {

    Encrypter::Encrypter(const string& key)
    {
      KeyExpander expander;
      m_rounds = expander.rounds(key.length());
      m_expanded_key = expander.expand(key);
    }

    string Encrypter::encrypt(const string& plain)
    {
      PREC(PlainBlockLength, plain.length() == BLOCK_BYTE_SIZE);
      string cipher (plain);
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
      assert(cipher.length() == BLOCK_BYTE_SIZE);
      return cipher;
    }

  }

}
