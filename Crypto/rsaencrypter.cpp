#include "rsaencrypter.h"
#include "rsadirectstrategy.h"
#include "rsapqstrategy.h"

namespace Crypto {

  RSAEncrypter::RSAEncrypter(const RSAKey& secret_key)
  {
    m_strategy = new RSADirectStrategy(secret_key);
  }

  RSAEncrypter::RSAEncrypter(const RSAKey& secret_key, const RSAKey::text_t &p, const RSAKey::text_t &q)
  {
    m_strategy = new RSAPQStrategy(secret_key, p, q);
  }

  RSAEncrypter& RSAEncrypter::operator=(const RSAEncrypter& other)
  {
    delete m_strategy;
    m_strategy = other.m_strategy->copy();
    return *this;
  }

  RSAEncrypter::~RSAEncrypter()
  {
    delete m_strategy;
  }

}
