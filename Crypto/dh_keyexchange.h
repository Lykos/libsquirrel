#ifndef CRYPTO_DH_KEYEXCHANGE_H
#define CRYPTO_DH_KEYEXCHANGE_H

#include "Crypto_global.h"
#include "dh_converter.h"
#include "dh_types.h"
#include "dh_keygenerator.h"

namespace Crypto {

  namespace DH {
    
    class CRYPTOSHARED_EXPORT KeyExchange
    {
    public:
      bool valid_key_bits(uint number_bits) const;

      // Sets an appropriate group and returns it.
      group_t choose_group(uint number_bits);

      void set_group(group_t group);

      // Is the group already set?
      bool group_chosen() const { return m_group_chosen; }

      // Is the exponent already set?
      bool exponent_chosen() const { return m_exponent_chosen; }

      // Is the partial key of the other party already set?
      bool other_partial_set() const { return m_other_partial_set; }

      // Is the key ready?
      bool key_ready() const { return m_key_ready; }

      // Generate the key for this side.
      template <typename Engine>
      number_t generate_partial_key(Engine& engine);

      void set_other_partial_key(number_t other_gen_power);

       number_t get_key();

    private:
      Converter m_converter;

      KeyGenerator m_key_generator;

      group_t m_group;

      exponent_t m_exponent;

      number_t m_other_gen_power;

      number_t m_key;

      bool m_group_chosen = false;

      bool m_exponent_chosen = false;

      bool m_other_partial_set = false;

      bool m_key_ready = false;

      void complete_key();

    };

    template <typename Engine>
    number_t KeyExchange::generate_partial_key(Engine& engine)
    {
      assert(m_group_chosen);
      m_key_ready = false;
      partial_key_pair_t key_pair = m_key_generator.generate(engine, m_group);
      m_exponent = key_pair.exponent;
      m_exponent_chosen = true;
      if (m_other_partial_set) {
        complete_key();
      }
      return key_pair.gen_power;
    }

  } // namespace DH

} // namespace Crypto

#endif // CRYPTO_DH_KEYEXCHANGE_H
