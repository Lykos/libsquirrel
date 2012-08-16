#include "rsa_pqstrategy.h"

namespace Crypto {

  namespace RSA {

    PQStrategy::PQStrategy(const private_key_t& private_key):
      DecryptStrategy(private_key),
      m_p_inv (private_key.p.inv_mod(private_key.q)),
      m_q_inv (private_key.q.inv_mod(private_key.p))
    {
      assert(private_key.p * private_key.q == private_key.modulus);
      assert((private_key.p * m_p_inv) % private_key.q == 1);
      assert((private_key.q * m_q_inv) % private_key.p == 1);
    }

    plain_text_t PQStrategy::decrypt(const cipher_text_t& cipher_text) const
    {
      // According to precalculated inverses for chinese remainder theorem
      const private_key_t& private_key = DecryptStrategy::m_private_key;
      const number_t& p = private_key.p;
      const number_t& q = private_key.q;
      const number_t& n = private_key.modulus;
      number_t mod_p = cipher_text.pow_mod(private_key.exponent, p);
      number_t mod_q = cipher_text.pow_mod(private_key.exponent, q);
      number_t p_factor = (mod_p * m_q_inv) % p;
      number_t q_factor = (mod_q * m_p_inv) % q;
      number_t res = p_factor * q + q_factor * p;
      if (res >= n) {
        res -= n;
      }
      assert(res < n);
      return res;
    }

  }

}
