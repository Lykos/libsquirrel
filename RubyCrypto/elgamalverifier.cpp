#include "elgamalverifier.h"
#include "Crypto/elgamal_verifier.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;
using namespace Elgamal;

Data_Type<Verifier> rb_cElgamalVerifier;

extern "C" void Init_ElgamalVerifier()
{
  typedef bool (Verifier::*verify_t)(const string&) const;
  rb_cElgamalVerifier = define_class_under<Verifier>(rb_mCrypto, "ElgamalVerifier")
      .add_handler<PreconditionViolation>(handle)
      .define_constructor(Constructor<Verifier, const string&>(),
                     Arg("public_key"))
      .define_method("verify", verify_t(&Verifier::verify),
                     Arg("message"))
      .define_method("remove_signature", &Verifier::remove_signature,
                     Arg("message"))
      .define_method("signature_length", &Verifier::signature_length);
}
