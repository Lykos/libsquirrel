#ifndef CRYPTO_KEYREADER_H
#define CRYPTO_KEYREADER_H

namespace Crypto {
  
  template <typename Key>
  class KeyReader
  {
  public:
    Key read_key(std::string key_string);

  };
  
}

#endif // CRYPTO_KEYREADER_H
