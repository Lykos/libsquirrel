#include "rsa.h"
#include "directstrategy.h"
#include "pqstrategy.h"

namespace Crypto {

  RSA::RSA()
  {
  }

  RSA::RSA(const RSAKey& secret_key, const RSAKey& public_key):
    m_secret_key (secret_key),
    m_public_key (public_key)
  {
    m_strategy = new DirectStrategy();
  }

  RSA::RSA(const RSAKey& secret_key, const RSAKey& public_key):
    m_secret_key (secret_key),
    m_public_key (public_key)
  {
    m_strategy = new DirectStrategy();
  }



  RSA::~RSA()
  {
    delete m_strategy;
  }

}
