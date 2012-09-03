#include "cbcdecrypter.h"
#include "Crypto/cbc_decrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include "Crypto/aes_decrypter.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include "hexconverters.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;

template <typename BlockCipher>
CBCDecrypter<BlockCipher>::CBCDecrypter(const string& private_key, const string& initial_state)
{
  string binary_private_key = from_hex(private_key);
  if (binary_private_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument 1 has to be a hexadecimal string.");
  }
  string binary_initial_state = from_hex(initial_state);
  if (binary_initial_state.empty()) {
    throw Exception(rb_eCryptoException, "Argument 2 has to be a hexadecimal string.");
  }
  m_decrypter = new CBC::Decrypter<BlockCipher>(
        BlockCipher(binary_private_key),
        binary_initial_state);
}

template <typename BlockCipher>
CBCDecrypter<BlockCipher>::~CBCDecrypter()
{
  delete m_decrypter;
}

template <typename BlockCipher>
string CBCDecrypter<BlockCipher>::decrypt(const string& cipher)
{
  return m_decrypter->decrypt(cipher);
}

template <typename BlockCipher>
const string& CBCDecrypter<BlockCipher>::state()
{
  return m_decrypter->state();
}

template <typename BlockCipher>
void CBCDecrypter<BlockCipher>::set_state(const string& new_state)
{
  m_decrypter->set_state(new_state);
}

template <typename BlockCipher>
bool CBCDecrypter<BlockCipher>::state_valid()
{
  return m_decrypter->state_valid();
}

Rice::Data_Type<ElgamalDecrypter> rb_cElgamalDecrypter;

Rice::Data_Type<AESDecrypter> rb_cAESDecrypter;

extern "C" void Init_CBCDecrypter()
{
  rb_cElgamalDecrypter = define_class_under<ElgamalDecrypter>(rb_mCrypto, "ElgamalDecrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalDecrypter, const string&, const string&>(),
                     (Arg("private_key"), Arg("initial_state")))
      .define_method("decrypt", &ElgamalDecrypter::decrypt,
                     (Arg("plain")))
      .define_method("state", &ElgamalDecrypter::state)
      .define_method("state=", &ElgamalDecrypter::set_state,
                     (Arg("new_state")))
      .define_method("state_valid?", &ElgamalDecrypter::state_valid);

  rb_cAESDecrypter = define_class_under<AESDecrypter>(rb_mCrypto, "AESDecrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESDecrypter, const string&, const string&>(),
                     (Arg("private_key"), Arg("initial_state")))
      .define_method("decrypt", &AESDecrypter::decrypt,
                     (Arg("plain")))
      .define_method("state", &AESDecrypter::state)
      .define_method("state=", &AESDecrypter::set_state,
                     (Arg("new_state")))
      .define_method("state_valid?", &AESDecrypter::state_valid);
}
