#include "rsa_decrypter.h"
#include "rsa_pqstrategy.h"
#include "rsa_directstrategy.h"

namespace Crypto {

  namespace RSA {

    Decrypter::Decrypter(const private_key_t& private_key):
      CryptoDecrypter(private_key)
    {
      if (private_key.p_q_available) {
        assert(private_key.p * private_key.q == private_key.modulus);
        m_strategy = new PQStrategy(private_key);
      } else {
        m_strategy = new DirectStrategy(private_key);
      }
    }

    Decrypter& Decrypter::operator=(const Decrypter& other)
    {
      delete m_strategy;
      m_strategy = other.m_strategy->copy();
      CryptoDecrypter::operator=(other);
      return *this;
    }


  }

}
