#ifndef CBCMAC_H
#define CBCMAC_H

#ifdef __cplusplus

#include "Crypto/cbc_mac.h"
#include "Crypto/aes_encrypter.h"
#include <rice/Data_Type.hpp>

template <typename BlockCipher>
class CBCMAC {
public:

  CBCMAC(const std::string& public_key, const std::string& initial_state);

  ~CBCMAC();

  void sign(std::string& message);

  bool verify(const std::string& message);

private:
  Crypto::CBC::MAC<BlockCipher>* m_mac;
};


typedef CBCMAC<Crypto::AES::Encrypter> AESSigner;

typedef CBCMAC<Crypto::AES::Encrypter> AESVerifier;

extern Rice::Data_Type<AESSigner> rb_cAESSigner;

extern Rice::Data_Type<AESVerifier> rb_cAESVerifier;

extern "C" {
#endif

void Init_CBCMAC();

#ifdef __cplusplus
}
#endif

#endif // CBCMAC_H
