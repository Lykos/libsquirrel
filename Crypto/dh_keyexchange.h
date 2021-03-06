#ifndef CRYPTO_DH_KEYEXCHANGE_H
#define CRYPTO_DH_KEYEXCHANGE_H

#include "dh_converter.h"
#include "dh_types.h"
#include "dh_keygenerator.h"
#include <string>

namespace Crypto {

  namespace DH {
    
    class KeyExchange
    {
    public:
      bool valid_key_bits(number_size_t number_bits) const;

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
      void choose_group(number_size_t number_bits);

      group_t group() const;

      number_t own_part() const;

      number_t other_part() const;

      number_t key() const;

      void group(const group_t& group);

      void other_part(const number_t& other_gen_power);

      void read_group(const std::string& raw_group);

      void read_other_part(const std::string& raw_gen_power);

      std::string write_group() const;

      std::string write_own_part() const;

      std::string write_other_part() const;

      std::string write_key() const;

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
      m_own_gen_power = key_pair.gen_power;
      m_exponent = key_pair.exponent;
      m_own_part_chosen = true;
      if (m_other_part_set) {
        complete_key();
      }
    }

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_KEYEXCHANGE_H
