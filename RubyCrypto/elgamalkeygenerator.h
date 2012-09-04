#ifndef ELGAMALKEYGENERATOR_H
#define ELGAMALKEYGENERATOR_H

#ifdef __cplusplus

#include "Crypto/elgamal_keygenerator.h"
#include <string>
#include <rice/Data_Type.hpp>
#include <boost/random/random_device.hpp>

class ElgamalKeyGenerator {
public:
  typedef Crypto::Elgamal::KeyGenerator::raw_key_pair_t raw_key_pair_t;

  ElgamalKeyGenerator();

  ~ElgamalKeyGenerator();

  raw_key_pair_t generate(Crypto::number_size_t number_bits);

private:
  Crypto::Elgamal::KeyGenerator* m_generator;

  boost::random::random_device m_random_generator;

};

template<>
Rice::Object to_ruby<ElgamalKeyGenerator::raw_key_pair_t>(ElgamalKeyGenerator::raw_key_pair_t const & pair);

extern Rice::Data_Type<ElgamalKeyGenerator> rb_cElgamalKeyGenerator;

extern "C" {
#endif

void Init_ElgamalKeyGenerator();

#ifdef __cplusplus
}
#endif

#endif // ELGAMALKEYGENERATOR_H
