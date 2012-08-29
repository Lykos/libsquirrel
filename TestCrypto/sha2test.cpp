#include "sha2test.h"
#include "Crypto/sha2hasher.h"
#include <iostream>
#include <QtTest/QTest>

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

void SHA2Test::test_fixed()
{
  uchar message[57] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  uchar message2[] = "Affe\n";
  uchar digest2[32];
  uchar digest[32];
  uchar real_digest[32] = {0x24, 0x8d, 0x6a, 0x61, 0xd2, 0x06, 0x38, 0xb8,
                           0xe5, 0xc0, 0x26, 0x93, 0x0c, 0x3e, 0x60, 0x39,
                           0xa3, 0x3c, 0xe4, 0x59, 0x64, 0xff, 0x21, 0x67,
                           0xf6, 0xec, 0xed, 0xd4, 0x19, 0xdb, 0x06, 0xc1};
  uchar real_digest2[32] = {0x23, 0x15, 0x92, 0xa3, 0x93, 0x0b, 0xd3, 0x6e,
                            0x2d, 0x03, 0xdc, 0x78, 0x84, 0x07, 0xa9, 0x59,
                            0x09, 0x53, 0xcb, 0x9b, 0x09, 0xd9, 0x4e, 0xb5,
                            0x81, 0xc6, 0xd4, 0x73, 0xa6, 0x09, 0x19, 0x2e};
  SHA2Hasher hasher;
  hasher.hash(message, 56, digest);
  hasher.hash(message2, 5, digest2);
  for (uint i = 0; i < 32; ++i) {
    QCOMPARE(digest[i], real_digest[i]);
    QCOMPARE(digest2[i], real_digest2[i]);
  }
}
