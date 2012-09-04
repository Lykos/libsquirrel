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
using namespace Elgamal;

ElgamalVerifier::ElgamalVerifier(const string& public_key)
{
  m_verifier = new Verifier(from_hex(public_key));
}

ElgamalVerifier::~ElgamalVerifier()
{
  delete m_verifier;
}

bool ElgamalVerifier::verify(const string& message)
{
  return m_verifier->verify(message);
}

string& ElgamalVerifier::remove_signature(string& message)
{
  m_verifier->remove_signature(message);
  return message;
}

number_size_t ElgamalVerifier::signature_length()
{
  return m_verifier->signature_length();
}

Data_Type<ElgamalVerifier> rb_cElgamalVerifier;

extern "C" void Init_ElgamalVerifier()
{
  rb_cElgamalVerifier = define_class_under<ElgamalVerifier>(rb_mCrypto, "ElgamalVerifier")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalVerifier, const string&>(),
                     Arg("public_key"))
      .define_method("verify", &ElgamalVerifier::verify,
                     Arg("message"))
      .define_method("remove_signature", &ElgamalVerifier::remove_signature,
                     Arg("message"))
      .define_method("signature_length", &ElgamalVerifier::signature_length);
}
