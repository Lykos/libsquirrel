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
#include <iostream>

using namespace std;
using namespace Rice;
using namespace Crypto;

template <typename BlockCipher>
CBCDecrypter<BlockCipher>::CBCDecrypter(const string& private_key, const string& initial_state)
{
  m_decrypter = new CBC::Decrypter<BlockCipher>(BlockCipher(from_hex(private_key)), from_hex(initial_state));
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
string CBCDecrypter<BlockCipher>::state()
{
  return to_hex(m_decrypter->state());
}

template <typename BlockCipher>
const string& CBCDecrypter<BlockCipher>::set_state(const string& new_state)
{
  m_decrypter->state(from_hex(new_state));
  return new_state;
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
