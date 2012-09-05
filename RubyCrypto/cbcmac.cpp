#include "cbcmac.h"
#include "Crypto/cbc_encrypter.h"
#include "Crypto/aes_encrypter.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <iostream>

using namespace std;
using namespace Rice;
using namespace Crypto;

template <typename BlockCipher, int Tag>
CBCMAC<BlockCipher, Tag>::CBCMAC(const std::string& public_key, const std::string& initial_state)
{
  m_mac = new CBC::MAC<BlockCipher>(BlockCipher(public_key), initial_state);
}

template <typename BlockCipher, int Tag>
CBCMAC<BlockCipher, Tag>::~CBCMAC()
{
  delete m_mac;
}

template <typename BlockCipher, int Tag>
string& CBCMAC<BlockCipher, Tag>::sign(string& message)
{
  m_mac->sign(message);
  return message;
}

template <typename BlockCipher, int Tag>
bool CBCMAC<BlockCipher, Tag>::verify(const string& message)
{
  return m_mac->verify(message);
}

template <typename BlockCipher, int Tag>
string& CBCMAC<BlockCipher, Tag>::remove_signature(string& message)
{
  m_mac->remove_signature(message);
  return message;
}

template <typename BlockCipher, int Tag>
string CBCMAC<BlockCipher, Tag>::state()
{
  return m_mac->state();
}

template <typename BlockCipher, int Tag>
const string& CBCMAC<BlockCipher, Tag>::set_state(const string& new_state)
{
  m_mac->state(new_state);
  return new_state;
}

template <typename BlockCipher, int Tag>
bool CBCMAC<BlockCipher, Tag>::state_valid()
{
  return m_mac->state_valid();
}

template <typename BlockCipher, int Tag>
number_size_t CBCMAC<BlockCipher, Tag>::signature_length()
{
  return m_mac->signature_length();
}

Data_Type<AESSigner> rb_cAESSigner;

Data_Type<AESVerifier> rb_cAESVerifier;

extern "C" void Init_CBCMAC()
{
  rb_cAESSigner = define_class_under<AESSigner>(rb_mCrypto, "AESSigner")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESSigner, const string&, const string&>(),
                          (Arg("key"), Arg("initial_state")))
      .define_method("sign", &AESSigner::sign,
                     (Arg("message")))
      .define_method("state", &AESSigner::state)
      .define_method("state=", &AESSigner::set_state,
                     (Arg("new_state")))
      .define_method("state_valid?", &AESSigner::state_valid)
      .define_method("signature_length", &AESSigner::signature_length);


  rb_cAESVerifier = define_class_under<AESVerifier>(rb_mCrypto, "AESVerifier")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<AESVerifier, const string&, const string&>(),
                          (Arg("key"), Arg("initial_state")))
      .define_method("verify", &AESVerifier::verify,
                     (Arg("message")))
      .define_method("remove_signature", &AESVerifier::remove_signature,
                     (Arg("message")))
      .define_method("state", &AESVerifier::state)
      .define_method("state=", &AESVerifier::set_state,
                     (Arg("new_state")))
      .define_method("state_valid?", &AESVerifier::state_valid)
      .define_method("signature_length", &AESVerifier::signature_length);;
}
