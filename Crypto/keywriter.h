#ifndef CRYPTO_KEYWRITER_H
#define CRYPTO_KEYWRITER_H

namespace Crypto {

  template <typename Key>
  class KeyReader
  {
  public:
    std::string write_key(Key key);
  };

}

#endif // CRYPTO_KEYWRITER_H
