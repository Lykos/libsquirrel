#include "elgamalkeygenerator.h"
#include "Crypto/elgamal_keygenerator.h"
#include "Crypto/preconditionviolation.h"
#include "cryptoexception.h"
#include "crypto.h"
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <rice/Array.hpp>

using namespace std;
using namespace Rice;
using namespace Crypto;
using namespace Elgamal;

ElgamalKeyGenerator::ElgamalKeyGenerator()
{
  m_generator = new KeyGenerator();
}

ElgamalKeyGenerator::~ElgamalKeyGenerator()
{
  delete m_generator;
}

ElgamalKeyGenerator::raw_key_pair_t ElgamalKeyGenerator::generate(number_size_t number_bits)
{
  raw_key_pair_t raw_key_pair = m_generator->generate_raw(m_random_generator, number_bits);
  raw_key_pair.public_key = raw_key_pair.public_key;
  raw_key_pair.private_key = raw_key_pair.private_key;
  return raw_key_pair;
}

template<>
Object to_ruby<ElgamalKeyGenerator::raw_key_pair_t>(ElgamalKeyGenerator::raw_key_pair_t const & pair)
{
  Array a;
  a.push(pair.public_key);
  a.push(pair.private_key);
  return a;
}

Rice::Data_Type<ElgamalKeyGenerator> rb_cElgamalKeyGenerator;

extern "C" void Init_ElgamalKeyGenerator()
{
  rb_cElgamalKeyGenerator = define_class_under<ElgamalKeyGenerator>(rb_mCrypto, "ElgamalKeyGenerator")
      .add_handler<Crypto::PreconditionViolation>(handle)
      .define_constructor(Constructor<ElgamalKeyGenerator>())
      .define_method("generate", &ElgamalKeyGenerator::generate,
                     (Arg("number_bits")));
}
