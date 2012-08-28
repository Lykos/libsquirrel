#include "sha256test.h"
#include "sha256hasher.h"
#include <iostream>

using namespace Crypto;
using namespace std;

static void printit(const uchar* bla, ulong length)
{
  static const char hex_chars[17] = "0123456789ABCDEF";
  for (ulong i = 0; i < length; ++i) {
    std::cout << hex_chars[bla[i] >> 4] << hex_chars[bla[i] & 0xF];
  }
  std::cout << std::endl;
}

void SHA256Test::test_bla()
{
  uchar bla[] = "Affe";
  uchar blubb[] = "affe";
  uchar digest_bla[32];
  uchar digest_blubb[32];
  SHA256Hasher hasher;
  hasher.hash(bla, 5, digest_bla);
  hasher.hash(blubb, 5, digest_blubb);
}
