#include "cbcencrypter.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/elgamal_encrypter.h"
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
CBCEncrypter<BlockCipher>::CBCEncrypter(const std::string& public_key, const std::string& initial_state)
{
  string binary_public_key = from_hex(public_key);
  if (binary_public_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument 1 has to be a hexadecimal string.");
  }
  string binary_initial_state = from_hex(initial_state);
  if (binary_initial_state.empty()) {
    throw Exception(rb_eCryptoException, "Argument 2 has to be a hexadecimal string.");
  }
  m_encrypter = new CBC::Encrypter<BlockCipher>(
        BlockCipher(binary_public_key),
        binary_initial_state);
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

Rice::Data_Type<ElgamalEncrypter> rb_cElgamalEncrypter;

Rice::Data_Type<AESEncrypter> rb_cAESEncrypter;

extern "C" void Init_CBCEncrypter()
{
  rb_cElgamalEncrypter = define_class_under<ElgamalEncrypter>(rb_mCrypto, "ElgamalEncrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalEncrypter, const string&, const string&>(),
                          (Arg("public_key"), Arg("initial_state")))
      .define_method("encrypt", &ElgamalEncrypter::encrypt,
                     (Arg("plain")));

  rb_cAESEncrypter = define_class_under<AESEncrypter>(rb_mCrypto, "AESEncrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESEncrypter, const string&, const string&>(),
                          (Arg("public_key"), Arg("initial_state")))
      .define_method("encrypt", &AESEncrypter::encrypt,
                     (Arg("plain")));
}
