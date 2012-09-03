#include "elgamalverifier.h"
#include "Crypto/elgamal_verifier.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include "hexconverters.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;

ElgamalVerifier::ElgamalVerifier(const string& public_key)
{
  string binary_public_key = from_hex(public_key);
  if (binary_public_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument has to be a hexadecimal string.");
  }
  m_verifier = new Elgamal::Verifier(binary_public_key);
}

ElgamalVerifier::~ElgamalVerifier()
{
  delete m_verifier;
}

bool ElgamalVerifier::verify(const string& message)
{
  return m_verifier->verify(message);
}

Rice::Data_Type<ElgamalVerifier> rb_cElgamalVerifier;

extern "C" void Init_ElgamalVerifier()
{
  rb_cElgamalVerifier = define_class_under<ElgamalVerifier>(rb_mCrypto, "ElgamalVerifier")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalVerifier, const string&>(),
                     Arg("public_key"))
      .define_method("verify", &ElgamalVerifier::verify,
                     Arg("message"));
}
