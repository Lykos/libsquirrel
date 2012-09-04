#include "dhkeyexchange.h"
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
using namespace DH;

DHKeyExchange::DHKeyExchange()
{
  m_key_exchange = new KeyExchange();
}

DHKeyExchange::~DHKeyExchange()
{
  delete m_key_exchange;
}

std::string DHKeyExchange::choose_group(number_size_t number_bits)
{
  m_key_exchange->choose_group(number_bits);
  m_key_exchange->choose_own_part(m_random_generator);
  return m_key_exchange->write_group();
}

std::string DHKeyExchange::group()
{
  return m_key_exchange->write_group();
}

std::string DHKeyExchange::own_part()
{
  return m_key_exchange->write_own_part();
}

std::string DHKeyExchange::other_part()
{
  return m_key_exchange->write_other_part();
}

const std::string& DHKeyExchange::set_group(const std::string& raw_group)
{
  m_key_exchange->read_group(raw_group);
  m_key_exchange->choose_own_part(m_random_generator);
  return raw_group;
}

const std::string& DHKeyExchange::set_other(const std::string& raw_gen_power)
{
  m_key_exchange->read_other_part(raw_gen_power);
  return raw_gen_power;
}

std::string DHKeyExchange::key()
{
  return m_key_exchange->write_key();
}

bool DHKeyExchange::group_chosen()
{
  return m_key_exchange->group_chosen();
}

bool DHKeyExchange::other_part_set()
{
  return m_key_exchange->other_part_set();
}

Rice::Data_Type<DHKeyExchange> rb_cDHKeyExchange;

extern "C" void Init_DHKeyExchange()
{
  rb_cDHKeyExchange = define_class_under<DHKeyExchange>(rb_mCrypto, "DHKeyExchange")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<DHKeyExchange>())
      .define_method("choose_group", &DHKeyExchange::choose_group,
                     Arg("number_bits"))
      .define_method("group", &DHKeyExchange::group)
      .define_method("own_part", &DHKeyExchange::own_part)
      .define_method("other_part", &DHKeyExchange::other_part)
      .define_method("group=", &DHKeyExchange::set_group,
                     Arg("raw_group"))
      .define_method("other_part=", &DHKeyExchange::set_other,
                     Arg("raw_gen_power"))
      .define_method("key", &DHKeyExchange::key)
      .define_method("group_chosen", &DHKeyExchange::group_chosen)
      .define_method("other_part_set", &DHKeyExchange::other_part_set);
}
