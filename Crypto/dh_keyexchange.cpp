#include "dh_keyexchange.h"

namespace Crypto {

  namespace DH {

    void KeyExchange::complete_key()
    {
      assert(m_other_partial_set && m_exponent_chosen);
      m_key = m_other_gen_power.pow_mod(m_exponent, m_group.modulus);
      m_key_ready = true;
    }

    bool KeyExchange::valid_key_bits(uint number_bits) const
    {
      return m_key_generator.valid_key_bits(number_bits);
    }

    group_t KeyExchange::choose_group(uint number_bits)
    {
      assert(m_key_generator.valid_key_bits(number_bits));
      m_exponent_chosen = false;
      m_other_partial_set = false;
      m_key_ready = false;
      m_group = m_key_generator.choose_group(number_bits);
      m_group_chosen = true;
      return m_group;
    }

    void KeyExchange::set_group(group_t group)
    {
      m_exponent_chosen = false;
      m_other_partial_set = false;
      m_key_ready = false;
      m_group = group;
      m_group_chosen = true;
    }

    void KeyExchange::set_other_partial_key(number_t other_gen_power)
    {
      m_key_ready = false;
      m_other_gen_power = other_gen_power;
      m_other_partial_set = true;
      if (m_exponent_chosen) {
        complete_key();
      }
    }

    number_t KeyExchange::get_key()
    {
      assert(m_key_ready);
      return m_key;
    }


  } // namespace DH

} // namespace Crypto
