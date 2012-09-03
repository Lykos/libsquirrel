#include "hexconverters.h"
#include <string>

using namespace std;

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
      return string();
    }
    if (i % 2 == 0) {
      binary[i / 2] = out << 4;
    } else {
      binary[i / 2] |= out;
    }
  }
  return binary;
}
