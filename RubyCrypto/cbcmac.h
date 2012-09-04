#ifndef CBCMAC_H
#define CBCMAC_H

#ifdef __cplusplus

#include "Crypto/cbc_mac.h"
#include "Crypto/aes_encrypter.h"
#include <rice/Data_Type.hpp>

template <typename BlockCipher, int Tag>
class CBCMAC {
public:

  CBCMAC(const std::string& public_key, const std::string& initial_state);

  ~CBCMAC();

  std::string& sign(std::string& message);

  bool verify(const std::string& message);

  std::string& remove_signature(std::string& message);

  std::string state();

  const std::string& set_state(const std::string& new_state);

  bool state_valid();

  Crypto::number_size_t signature_length();

private:
  Crypto::CBC::MAC<BlockCipher>* m_mac;
};


typedef CBCMAC<Crypto::AES::Encrypter, 1> AESSigner;

typedef CBCMAC<Crypto::AES::Encrypter, 2> AESVerifier;

extern Rice::Data_Type<AESSigner> rb_cAESSigner;

extern Rice::Data_Type<AESVerifier> rb_cAESVerifier;

extern "C" {
#endif

void Init_CBCMAC();

#ifdef __cplusplus
}
#endif

#endif // CBCMAC_H
