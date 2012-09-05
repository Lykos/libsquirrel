#include "cbcencrypter.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/elgamal_encrypter.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <iostream>

using namespace std;
using namespace Rice;
using namespace Crypto;

template <typename BlockCipher>
CBCEncrypter<BlockCipher>::CBCEncrypter(const std::string& public_key, const std::string& initial_state)
{
  m_encrypter = new CBC::Encrypter<BlockCipher>(BlockCipher(public_key), initial_state);
}

template <typename BlockCipher>
CBCEncrypter<BlockCipher>::~CBCEncrypter()
{
  delete m_encrypter;
}

template <typename BlockCipher>
string CBCEncrypter<BlockCipher>::encrypt(const string& plain)
{
  return m_encrypter->encrypt(plain);
}

template <typename BlockCipher>
string CBCEncrypter<BlockCipher>::state()
{
  return m_encrypter->state();
}

template <typename BlockCipher>
const string& CBCEncrypter<BlockCipher>::set_state(const string& new_state)
{
  m_encrypter->state(new_state);
  return new_state;
}

Data_Type<ElgamalEncrypter> rb_cElgamalEncrypter;

Data_Type<AESEncrypter> rb_cAESEncrypter;

extern "C" void Init_CBCEncrypter()
{
  rb_cElgamalEncrypter = define_class_under<ElgamalEncrypter>(rb_mCrypto, "ElgamalEncrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalEncrypter, const string&, const string&>(),
                          (Arg("public_key"), Arg("initial_state")))
      .define_method("encrypt", &ElgamalEncrypter::encrypt,
                     (Arg("plain")))
      .define_method("state", &ElgamalEncrypter::state)
      .define_method("state=", &ElgamalEncrypter::set_state,
                     (Arg("new_state")));

  rb_cAESEncrypter = define_class_under<AESEncrypter>(rb_mCrypto, "AESEncrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESEncrypter, const string&, const string&>(),
                          (Arg("public_key"), Arg("initial_state")))
      .define_method("encrypt", &AESEncrypter::encrypt,
                     (Arg("plain")))
      .define_method("state", &AESEncrypter::state)
      .define_method("state=", &AESEncrypter::set_state,
                     (Arg("new_state")));
}
