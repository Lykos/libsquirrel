#include "dh_keyexchange.h"

namespace Crypto {

  namespace DH {

    bool KeyExchange::valid_key_bits(uint number_bits) const
    {
      return m_key_generator.valid_key_bits(number_bits);
    }

    void KeyExchange::choose_group(uint number_bits)
    {
      assert(m_key_generator.valid_key_bits(number_bits));
      m_own_part_chosen = false;
      m_other_part_set = false;
      m_key_ready = false;
      m_group = m_key_generator.choose_group(number_bits);
      m_group_chosen = true;
    }

    group_t KeyExchange::get_group() const
    {
      assert(m_group_chosen);
      return m_group;
    }

    number_t KeyExchange::get_own_part() const
    {
      assert(m_own_part_chosen);
      return m_own_gen_power;
    }

    number_t KeyExchange::get_key() const
    {
      assert(m_key_ready);
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

    void KeyExchange::read_group(const dh_byte_t* raw_group, number_size_t length)
    {
      set_group(m_converter.read_group(raw_group, length));
    }

    void KeyExchange::read_other_part(const dh_byte_t* raw_gen_power, number_size_t length)
    {
      set_other_part(m_converter.read_number(raw_gen_power, length));
    }

    KeyExchange::number_size_t KeyExchange::group_length() const
    {
      return m_converter.group_length(get_group());
    }

    KeyExchange::number_size_t KeyExchange::own_part_length() const
    {
      return m_converter.number_length(get_own_part());
    }

    KeyExchange::number_size_t KeyExchange::key_length() const
    {
      return m_converter.number_length(get_key());
    }

    KeyExchange::number_size_t KeyExchange::write_group(dh_byte_t* raw_group) const
    {
      return m_converter.write_group(get_group(), raw_group);
    }

    KeyExchange::number_size_t KeyExchange::write_own_part(dh_byte_t* raw_gen_power) const
    {
      return m_converter.write_number(get_own_part(), raw_gen_power);
    }

    KeyExchange::number_size_t KeyExchange::write_key(dh_byte_t* raw_key) const
    {
      return m_converter.write_number(get_key(), raw_key);
    }

    void KeyExchange::complete_key()
    {
      assert(m_own_part_chosen && m_other_part_set);
      m_key = m_other_gen_power.pow_mod(m_exponent, m_group.modulus);
      m_key_ready = true;
    }

  } // namespace DH

} // namespace Crypto
