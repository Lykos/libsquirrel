#include "aestest.h"
#include "aes_encrypter.h"

using namespace Crypto::AES;

void AESTest::test_bla()
{
  char plain[256] = "Hallo, ich bin so toll.";
  char key[128];
  Encrypter enc (key, 128);
}
