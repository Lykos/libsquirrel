#include "elgamalsigner.h"
#include "Crypto/elgamal_signer.h"
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

ElgamalSigner::ElgamalSigner(const string& private_key)
{
  m_signer = new Signer(from_hex(private_key));
}

ElgamalSigner::~ElgamalSigner()
{
  delete m_signer;
}

string& ElgamalSigner::sign(string& message)
{
  m_signer->sign(message);
  return message;
}

number_size_t ElgamalSigner::signature_length()
{
  return m_signer->signature_length();
}

Data_Type<ElgamalSigner> rb_cElgamalSigner;

extern "C" void Init_ElgamalSigner()
{
  rb_cElgamalSigner = define_class_under<ElgamalSigner>(rb_mCrypto, "ElgamalSigner")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalSigner, const string&>(),
                     Arg("private_key"))
      .define_method("sign", &ElgamalSigner::sign,
                     Arg("message"))
      .define_method("signature_length", &ElgamalSigner::signature_length);
}
