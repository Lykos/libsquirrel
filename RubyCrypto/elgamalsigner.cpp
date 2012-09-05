#include "elgamalsigner.h"
#include "Crypto/elgamal_signer.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;
using namespace Elgamal;

Data_Type<Signer> rb_cElgamalSigner;

extern "C" void Init_ElgamalSigner()
{
  typedef string& (Signer::*sign_t)(string&);
  rb_cElgamalSigner = define_class_under<Signer>(rb_mCrypto, "ElgamalSigner")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<Signer, const string&>(),
                     Arg("private_key"))
      .define_method("sign", sign_t(&Signer::sign),
                     Arg("message"))
      .define_method("signature_length", &Signer::signature_length);
}
