#include "sha256test.h"
#include "sha256hasher.h"
#include <iostream>

using namespace Crypto;
using namespace std;

void SHA256Test::test_bla()
{
  unsigned char bla[] = "Affe";
  char hex_chars[] = "0123456789ABCDEF";
  unsigned char digest[32];
  SHA256Hasher hasher;
  hasher.hash(bla, 4, digest);/*
  for (uint i = 0; i < 32; ++i) {
    unsigned char c = digest[i];
    cout << hex_chars[c >> 4] << hex_chars[c & 0xF];
  }
  cout << endl;*/
}
