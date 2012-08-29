#ifndef CRYPTO_DH_KEYEXCHANGE_H
#define CRYPTO_DH_KEYEXCHANGE_H

#include "Crypto/Crypto_global.h"
#include "Crypto/dh_converter.h"
#include "Crypto/dh_types.h"
#include "Crypto/dh_keygenerator.h"

namespace Crypto {

  namespace DH {
    
    class CRYPTOSHARED_EXPORT KeyExchange
    {
    public:
      typedef Converter::number_size_t number_size_t;

      bool valid_key_bits(uint number_bits) const;

      // Is the group already set?
      bool group_chosen() const { return m_group_chosen; }

      // Is the exponent already set?
      bool own_part_chosen() const { return m_own_part_chosen; }

      // Is the partial key of the other party already set?
      bool other_part_set() const { return m_other_part_set; }

      // Is the key ready?
      bool key_ready() const { return m_key_ready; }

      // Generate the key part for this side.
      template <typename Engine>
      void choose_own_part(Engine& engine);

      // Chooses an appropriate group.
      void choose_group(uint number_bits);

      group_t get_group() const;

      number_t get_own_part() const;

      number_t get_key() const;

      void set_group(const group_t& group);

      void set_other_part(const number_t& other_gen_power);

      void read_group(const dh_byte_t* raw_group, number_size_t length);

      void read_other_part(const dh_byte_t* raw_gen_power, number_size_t length);

      number_size_t group_length() const;

      number_size_t own_part_length() const;

      number_size_t key_length() const;

      number_size_t write_group(dh_byte_t* raw_group) const;

      number_size_t write_own_part(dh_byte_t* raw_gen_power) const;

      number_size_t write_key(dh_byte_t* raw_key) const;

    private:
      Converter m_converter;

      KeyGenerator m_key_generator;

      group_t m_group;

      exponent_t m_exponent;

      number_t m_own_gen_power;

      number_t m_other_gen_power;

      number_t m_key;

      bool m_group_chosen = false;

      bool m_own_part_chosen = false;

      bool m_other_part_set = false;

      bool m_key_ready = false;

      void complete_key();

    };

    template <typename Engine>
    void KeyExchange::choose_own_part(Engine& engine)
    {
      assert(m_group_chosen);
      m_key_ready = false;
      partial_key_pair_t key_pair = m_key_generator.generate(engine, m_group);
      m_exponent = key_pair.exponent;
      m_own_part_chosen = true;
      if (m_other_part_set) {
        complete_key();
      }
    }

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_KEYEXCHANGE_H
