#include "hexconverters.h"
#include "cryptoexception.h"
#include <string>
#include <rice/Exception.hpp>

using namespace std;
using namespace Rice;

string from_hex(const string& hex_string) {
  string binary (hex_string.size() / 2, 0);
  for (uint i = 0; i < hex_string.size(); ++i) {
    char c = hex_string[i];
    char out;
    if (c >= '0' && c <= '9') {
      out = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      out = 10 + c - 'A';
    } else if (c >= 'a' && c <= 'f') {
      out = 10 + c - 'a';
    } else {
      throw Exception(rb_eCryptoException, "Argument has to be a hexadecimal string.");
    }
    if (i % 2 == 0) {
      binary[i / 2] = out << 4;
    } else {
      binary[i / 2] |= out;
    }
  }
  return binary;
}

string to_hex(const string& binary_string) {
  static const string hex_chars = "0123456789ABCDEF";
  string hex (binary_string.size() * 2, 0);
  for (uint i = 0; i < binary_string.size(); ++i) {
    hex[2 * i] = hex_chars[(binary_string[i] >> 4) & 0xF];
    hex[2 * i + 1] = hex_chars[binary_string[i] & 0xF];
  }
  return hex;
}
