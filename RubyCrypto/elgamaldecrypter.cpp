#include "elgamaldecrypter.h"
#include "Crypto/cbc_decrypter.h"
#include "Crypto/elgamal_decrypter.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include "hexconverters.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;

ElgamalDecrypter::ElgamalDecrypter(const string& private_key, const string& initial_state)
{
  string binary_private_key = from_hex(private_key);
  if (binary_private_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument 1 has to be a hexadecimal string.");
  }
  string binary_initial_state = from_hex(initial_state);
  if (binary_initial_state.empty()) {
    throw Exception(rb_eCryptoException, "Argument 2 has to be a hexadecimal string.");
  }
  m_decrypter = new CBC::Decrypter<Elgamal::Decrypter>(
        Elgamal::Decrypter(binary_private_key),
        binary_initial_state);
}

ElgamalDecrypter::~ElgamalDecrypter()
{
  delete m_decrypter;
}

string ElgamalDecrypter::decrypt(const string& cipher)
{
  return m_decrypter->decrypt(cipher);
}

Rice::Data_Type<ElgamalDecrypter> rb_cElgamalDecrypter;

extern "C" void Init_ElgamalDecrypter()
{
  rb_cElgamalDecrypter = define_class_under<ElgamalDecrypter>(rb_mCrypto, "ElgamalDecrypter")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalDecrypter, const string&, const string&>(),
                     (Arg("public_key"), Arg("initial_state")))
      .define_method("decrypt", &ElgamalDecrypter::decrypt,
                     (Arg("plain")));
}