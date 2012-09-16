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
  string message = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  string message2 = "Affe\n";
  string real_digest ({char(0x24), char(0x8d), char(0x6a), char(0x61), char(0xd2), char(0x06), char(0x38), char(0xb8),
                      char(0xe5), char(0xc0), char(0x26), char(0x93), char(0x0c), char(0x3e), char(0x60), char(0x39),
                      char(0xa3), char(0x3c), char(0xe4), char(0x59), char(0x64), char(0xff), char(0x21), char(0x67),
                      char(0xf6), char(0xec), char(0xed), char(0xd4), char(0x19), char(0xdb), char(0x06), char(0xc1)});
  string real_digest2 ({char(0x23), char(0x15), char(0x92), char(0xa3), char(0x93), char(0x0b), char(0xd3), char(0x6e),
                       char(0x2d), char(0x03), char(0xdc), char(0x78), char(0x84), char(0x07), char(0xa9), char(0x59),
                       char(0x09), char(0x53), char(0xcb), char(0x9b), char(0x09), char(0xd9), char(0x4e), char(0xb5),
                       char(0x81), char(0xc6), char(0xd4), char(0x73), char(0xa6), char(0x09), char(0x19), char(0x2e)});
  SHA2Hasher hasher (256);
  string digest = hasher.hash(message);
  string digest2 = hasher.hash(message2);
  QCOMPARE(digest, real_digest);
  QCOMPARE(digest2, real_digest2);
}
