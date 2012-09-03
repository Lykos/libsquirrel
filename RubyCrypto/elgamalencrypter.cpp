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
        Elgamal::Encrypter((const uchar*)binary_public_key.c_str(), binary_public_key.size()),
        (const uchar*)binary_initial_state.c_str(), binary_initial_state.size());
}

ElgamalEncrypter::~ElgamalEncrypter()
{
  delete m_encrypter;
}

string ElgamalEncrypter::encrypt(const string& plain)
{
  uchar* cipher = new uchar[m_encrypter->cipher_length(plain.size())];
  ulong cipher_length = m_encrypter->encrypt((const uchar*)plain.c_str(), plain.size(), (uchar*)cipher);
  string result ((const char*)cipher, cipher_length);
  delete[] cipher;
  return result;
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
