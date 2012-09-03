#include "elgamalencrypter.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/elgamal_encrypter.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include "hexconverters.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;

ElgamalEncrypter::ElgamalEncrypter(const std::string& public_key, const std::string& initial_state)
{
  string binary_public_key = from_hex(public_key);
  if (binary_public_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument 1 has to be a hexadecimal string.");
  }
  string binary_initial_state = from_hex(initial_state);
  if (binary_initial_state.empty()) {
    throw Exception(rb_eCryptoException, "Argument 2 has to be a hexadecimal string.");
  }
  m_encrypter = new CBC::Encrypter<Elgamal::Encrypter>(
        Elgamal::Encrypter((const uchar*)binary_public_key.data(), binary_public_key.size()),
        binary_initial_state);
}

ElgamalEncrypter::~ElgamalEncrypter()
{
  delete m_encrypter;
}

string ElgamalEncrypter::encrypt(const string& plain)
{
  return m_encrypter->encrypt(plain);
}

Rice::Data_Type<ElgamalEncrypter> rb_cElgamalEncrypter;

extern "C" void Init_ElgamalEncrypter()
{
  rb_cElgamalEncrypter = define_class_under<ElgamalEncrypter>(rb_mCrypto, "ElgamalEncrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalEncrypter, const string&, const string&>(),
                                          (Arg("public_key"), Arg("initial_state")))
      .define_method("encrypt", &ElgamalEncrypter::encrypt,
                     (Arg("plain")));
}
