#include "keypair.h"

namespace Crypto {

  template <typename T>
  KeyPair<T>::KeyPair(const T& public_key, const T& secret_key):
    m_public_key (public_key),
    m_secret_key (secret_key)
  {
  }

  template <typename T>
  inline const T& KeyPair<T>::get_public_key() const
  {
    return m_public_key;
  }

  template <typename T>
  inline const T& KeyPair<T>::get_secret_key() const
  {
    return m_secret_key;
  }

}
