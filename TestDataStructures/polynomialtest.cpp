#include "DataStructures/polynomial.h"
#include "DataStructures/longint.h"
#include "polynomialtest.h"
#include "DataStructures/arraylist.h"
#include <iostream>
#include <climits>
#include <ostream>

using namespace DataStructures;

/*
struct Bool {
  bool value;
  Bool(): value (false) {}
  Bool(bool val): value (val) {}
  Bool zero() const { return {false}; }
  Bool one() const { return {true}; }
  bool operator==(const Bool& other) const { return value == other.value; }
  bool operator!=(const Bool& other) const { return value != other.value; }
  Bool operator*=(const Bool& other) { return value &= other.value; }
  Bool operator/=(const Bool& other) { return value &= other.value; }
  Bool operator+=(const Bool& other) { return value ^= other.value; }
  Bool operator-=(const Bool& other) { return value ^= other.value; }
  Bool mult_inv() const { return *this; }
  Bool add_inv() const { return *this; }
  Bool operator*(const Bool& other) const { return Bool(value & other.value); }
  Bool operator/(const Bool& other) const { return Bool(value & other.value); }
  Bool operator+(const Bool& other) const { return Bool(value ^ other.value); }
  Bool operator-(const Bool& other) const { return Bool(value ^ other.value); }
};

std::ostream& operator<<(std::ostream out, const Bool& b)
{
  return out << (b.value ? 1 : 0) << std::endl;
}
typedef Polynomial<Bool> PB;*/

typedef LongInt L;
typedef Polynomial<L> P;

Q_DECLARE_METATYPE(P)
Q_DECLARE_METATYPE(L)

void PolynomialTest::test_pow_data()
{
  QTest::addColumn<P>("left");
  QTest::addColumn<int>("right");
  QTest::addColumn<P>("result");
  // x^2 + 2
  LongInt input_coeffs[] {2, 0, 1};
  // x^8 + 8 x^6 + 24 x^4 + 32 x^2 + 16
  LongInt result_coeffs[] {16, 0, 32, 0, 24, 0, 8, 0, 1};
  QTest::newRow("(x^2 + 2) ** 4") << P(input_coeffs + 0, input_coeffs + 3) << 4 << P(result_coeffs + 0, result_coeffs + 9);
}

using namespace std;

void PolynomialTest::test_pow()
{
  QFETCH(P, left);
  QFETCH(int, right);
  QFETCH(P, result);

  P copy (left);

  QCOMPARE(left.pow(right), result);
  QCOMPARE(left, copy);
  QCOMPARE(copy.pow_eq(right), result);
  QCOMPARE(copy, result);
}

void PolynomialTest::test_evaluate_data()
{
  QTest::addColumn<P>("left");
  QTest::addColumn<L>("right");
  QTest::addColumn<L>("result");

  // 3 x^2 + 4 x + 1
  LongInt left_coeffs[] = {1, 4, 3};
  QTest::newRow("(3 x^2 + 4x + 1)(2)") << P(left_coeffs + 0, left_coeffs + 3) << L(2) << L(21);
  QTest::newRow("(3 x^2 + 4x + 1)(10000000000000000)") << P(left_coeffs + 0, left_coeffs + 3) << L("10000000000000000") << L("300000000000000040000000000000001");
}

void PolynomialTest::test_evaluate()
{
  QFETCH(P, left);
  QFETCH(L, right);
  QFETCH(L, result);

  QCOMPARE(left(right), result);
}
void PolynomialTest::test_modulo_data()
{
  QTest::addColumn<P>("left");
  QTest::addColumn<P>("right");
  QTest::addColumn<P>("result");

  // 3 x^5 + 1
  LongInt left_coeffs[] = {1, 0, 0, 0, 0, 3};
  // x^2 + 1
  LongInt right_coeffs[] = {1, 0, 1};
  // 3x + 1
  LongInt result_coeffs[] = {1, 3};
  QTest::newRow("(3 x^5 + 1) % (x^2 + 1)") << P(left_coeffs + 0, left_coeffs + 6) << P(right_coeffs + 0, right_coeffs + 3) << P(result_coeffs + 0, result_coeffs + 2);
}

void PolynomialTest::test_modulo()
{
  QFETCH(P, left);
  QFETCH(P, right);
  QFETCH(P, result);

  P copy (left);

  QCOMPARE(left % right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy %= right, result);
  QCOMPARE(copy, result);
}

void PolynomialTest::test_divide_data()
{
  QTest::addColumn<P>("left");
  QTest::addColumn<P>("right");
  QTest::addColumn<P>("result");

  // 3 x^2 + 1
  LongInt left_coeffs[] = {1, 0, 0, 0, 0, 3};
  // x^2 + 1
  LongInt right_coeffs[] = {1, 0, 1};
  // 3x^3 - 3x
  LongInt result_coeffs[] = {0, -3, 0, 3};
  QTest::newRow("(3 x^5 + 1) / (x^2 + 1)") << P(left_coeffs + 0, left_coeffs + 6) << P(right_coeffs + 0, right_coeffs + 3) << P(result_coeffs + 0, result_coeffs + 4);
}

void PolynomialTest::test_divide()
{
  QFETCH(P, left);
  QFETCH(P, right);
  QFETCH(P, result);

  P copy (left);

  QCOMPARE(left / right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy /= right, result);
  QCOMPARE(copy, result);
}
/*
void PolynomialTest::test_sbox()
{
  unsigned char box[1 << CHAR_BIT];
  Bool coeffs[] = {1, 1, 0, 1, 1, 0, 0, 0, 1};
  PB prim (coeffs + 0, coeffs + CHAR_BIT + 1);

  for (unsigned int i = 0; i < (1 << CHAR_BIT); ++i) {
    Bool coeffs[CHAR_BIT];
    for (unsigned int j = 0; j < CHAR_BIT; ++j) {
      coeffs[j] = (i >> j) & 1;
    }
    PB p (coeffs + 0, coeffs + CHAR_BIT);
    unsigned char inv_byte = 0;
    if (i != 0) {
      PB p_inv = p.mult_inv_mod(prim);
      for (unsigned int j = 0; j <= p_inv.deg(); ++j) {
        Bool coeff = p_inv.coefficients()[j];
        inv_byte |= coeff.value << j;
      }
    }
    unsigned char s = inv_byte;
    for (unsigned int j = 0; j < 4; ++j) {
      s <<= 1;
      inv_byte ^= s;
    }
    s ^= 0x63;
    box[i] = s;
    std::cout << hex << int(s) << " ";
    if (i % 16 == 15) {
      std::cout << std::endl;
    }
  }
}
*/
