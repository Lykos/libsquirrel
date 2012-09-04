#ifndef DHKEYEXCHANGE_H
#define DHKEYEXCHANGE_H

#ifdef __cplusplus

#include "Crypto/dh_keyexchange.h"
#include <rice/Data_Type.hpp>

class DHKeyExchange {
public:

  DHKeyExchange(Crypto::number_size_t key_bits);

  ~DHKeyExchange();

  std::string& set_other(std::string& other_gen_power);

private:
  Crypto::DH::KeyExchange* m_key_exchange;
};

extern Rice::Data_Type<DHKeyExchange> rb_cKeyExchange;

extern "C" {
#endif

void Init_ElgamalSigner();

#ifdef __cplusplus
}
#endif

#endif // DHKEYEXCHANGE_H
