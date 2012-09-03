#include "dh_keyexchange.h"
#include "preconditionviolation.h"
#include "types.h"
#include <string>

using namespace std;

namespace Crypto {

  namespace DH {

    bool KeyExchange::valid_key_bits(uint number_bits) const
    {
      return m_key_generator.valid_key_bits(number_bits);
    }

    void KeyExchange::choose_group(uint number_bits)
    {
      PREC(DHKeyLength, m_key_generator.valid_key_bits(number_bits));
      m_own_part_chosen = false;
      m_other_part_set = false;
      m_key_ready = false;
      m_group = m_key_generator.choose_group(number_bits);
      m_group_chosen = true;
    }

    group_t KeyExchange::get_group() const
    {
      PREC(NoGroupChosen, m_group_chosen);
      return m_group;
    }

    number_t KeyExchange::get_own_part() const
    {
      PREC(NoOwnPartChosen, m_own_part_chosen);
      return m_own_gen_power;
    }

    number_t KeyExchange::get_key() const
    {
      PREC(KeyNotReady, m_key_ready);
      return m_key;
    }

    void KeyExchange::set_group(const group_t& group)
    {
      m_own_part_chosen = false;
      m_other_part_set = false;
      m_key_ready = false;
      m_group = group;
      m_group_chosen = true;
    }

    void KeyExchange::set_other_part(const number_t& other_gen_power)
    {
      m_key_ready = false;
      m_other_gen_power = other_gen_power;
      m_other_part_set = true;
      if (m_own_part_chosen) {
        complete_key();
      }
    }

    void KeyExchange::read_group(const string& raw_group)
    {
      set_group(m_converter.read_group(raw_group));
    }

    void KeyExchange::read_other_part(const string& raw_gen_power)
    {
      set_other_part(m_converter.read_number(raw_gen_power));
    }

    string KeyExchange::write_group() const
    {
      return m_converter.write_group(get_group());
    }

    string KeyExchange::write_own_part() const
    {
      return m_converter.write_number(get_own_part());
    }

    string KeyExchange::write_key() const
    {
      return m_converter.write_number(get_key());
    }

    void KeyExchange::complete_key()
    {
      assert(m_own_part_chosen && m_other_part_set);
      m_key = m_other_gen_power.pow_mod(m_exponent, m_group.modulus);
      m_key_ready = true;
    }

  } // namespace DH

} // namespace Crypto
