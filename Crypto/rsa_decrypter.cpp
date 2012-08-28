#include "rsa_decrypter.h"
#include "rsa_pqstrategy.h"
#include "rsa_directstrategy.h"

namespace Crypto {

  namespace RSA {

    Decrypter::Decrypter(const private_key_t& private_key):
      m_private_key (private_key)
    {
      if (private_key.p_q_available) {
        assert(private_key.p * private_key.q == private_key.modulus);
        m_strategy = new PQStrategy(private_key);
      } else {
        m_strategy = new DirectStrategy(private_key);
      }
    }

    Decrypter::Decrypter(const Decrypter& other):
      m_private_key (other.m_private_key),
      m_strategy (other.m_strategy->copy())
    {}

    Decrypter::Decrypter(Decrypter&& other):
      m_private_key (other.m_private_key),
      m_strategy (other.m_strategy)
    {
      other.m_strategy = NULL;
    }

    Decrypter& Decrypter::operator=(Decrypter&& other)
    {
      if (this == &other) {
        return *this;
      }
      m_strategy = other.m_strategy;
      m_private_key = other.m_private_key;
      other.m_strategy = NULL;
      return *this;
    }

    Decrypter& Decrypter::operator=(const Decrypter& other)
    {
      if (this == &other) {
        return *this;
      }
      delete m_strategy;
      m_strategy = other.m_strategy->copy();
      m_private_key = other.m_private_key;
      return *this;
    }


  }

}
