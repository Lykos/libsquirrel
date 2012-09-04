#include "sha2hasher.h"
#include "Crypto/sha2hasher.h"
#include "Crypto/preconditionviolation.h"
#include "Crypto/types.h"
#include "cryptoexception.h"
#include "hexconverters.h"
#include "crypto.h"
#include <rice/Exception.hpp>
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <string>

using namespace Rice;
using namespace std;

string SHA2Hasher::hash(const string& message)
{
  return to_hex(m_hasher.hash(message));
}


Data_Type<SHA2Hasher> rb_cSHA2Hasher;

void Init_SHA2Hasher()
{
  rb_cSHA2Hasher = define_class_under<SHA2Hasher>(rb_mCrypto, "SHA2Hasher")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<SHA2Hasher, Crypto::number_size_t>(),
                          Arg("digest_length") = 256)
      .define_method("hash", &SHA2Hasher::hash);
}
