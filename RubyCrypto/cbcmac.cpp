#include "cbcmac.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/aes_encrypter.h"
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
CBCMAC<BlockCipher>::CBCMAC(const std::string& public_key, const std::string& initial_state)
{
  string binary_public_key = from_hex(public_key);
  if (binary_public_key.empty()) {
    throw Exception(rb_eCryptoException, "Argument 1 has to be a hexadecimal string.");
  }
  string binary_initial_state = from_hex(initial_state);
  if (binary_initial_state.empty()) {
    throw Exception(rb_eCryptoException, "Argument 2 has to be a hexadecimal string.");
  }
  m_mac = new CBC::MAC<BlockCipher>(
        BlockCipher(binary_public_key),
        binary_initial_state);
}

template <typename BlockCipher>
CBCMAC<BlockCipher>::~CBCMAC()
{
  delete m_mac;
}

template <typename BlockCipher>
void CBCMAC<BlockCipher>::sign(string& message)
{
  m_mac->sign(message);
}

template <typename BlockCipher>
bool CBCMAC<BlockCipher>::verify(const string& message)
{
  return m_mac->verify(message);
}

Rice::Data_Type<AESSigner> rb_cAESSigner;

Rice::Data_Type<AESVerifier> rb_cAESVerifier;

extern "C" void Init_CBCMAC()
{
  rb_cAESSigner = define_class_under<AESSigner>(rb_mCrypto, "AESSigner")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESSigner, const string&, const string&>(),
                          (Arg("key"), Arg("initial_state")))
      .define_method("sign", &AESSigner::sign,
                     (Arg("message")));


  rb_cAESVerifier = define_class_under<AESVerifier>(rb_mCrypto, "AESMAC")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESVerifier, const string&, const string&>(),
                          (Arg("key"), Arg("initial_state")))
      .define_method("verify", &AESVerifier::verify,
                     (Arg("message")));
}
