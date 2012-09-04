#ifndef DHKEYEXCHANGE_H
#define DHKEYEXCHANGE_H

#ifdef __cplusplus

#include "Crypto/dh_keyexchange.h"
#include <rice/Data_Type.hpp>
#include <boost/random/random_device.hpp>

class DHKeyExchange {
public:

  DHKeyExchange();

  ~DHKeyExchange();

  std::string choose_group(Crypto::number_size_t number_bits);

  std::string group();

  std::string own_part();

  std::string other_part();

  const std::string& set_group(const std::string& raw_group);

  const std::string& set_other(const std::string& raw_other_gen_power);

  std::string key();

  bool group_chosen();

  bool other_part_set();

private:
  Crypto::DH::KeyExchange* m_key_exchange;

  boost::random::random_device m_random_generator;

};

extern Rice::Data_Type<DHKeyExchange> rb_cKeyExchange;

extern "C" {
#endif

void Init_DHKeyExchange();

#ifdef __cplusplus
}
#endif

#endif // DHKEYEXCHANGE_H
