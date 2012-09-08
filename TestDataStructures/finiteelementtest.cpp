#include "finiteelementtest.h"
#include "DataStructures/longint.h"
#include "DataStructures/finitefield.h"
#include "DataStructures/finiteelement.h"

using namespace DataStructures;

typedef LongInt L;
typedef FiniteElement<L> FE;
typedef FiniteField<L> FF;
struct FEP {
  FEP(): fe (NULL) {}
  FEP(FE* e): fe (e) {}
  FE* fe;
};

Q_DECLARE_METATYPE(FEP)
Q_DECLARE_METATYPE(L)

static const FF Z37 (37, 0, 1);

static FE LEFT (&Z37, 17);

static FE RIGHT (&Z37, 5);

static FE RESULT1 (&Z37, 23);

static FE RESULT2 (&Z37, 33);

void FiniteElementTest::test_pow_data()
{
  QTest::addColumn<FEP>("leftp");
  QTest::addColumn<int>("right");
  QTest::addColumn<FEP>("resultp");

  QTest::newRow("17 ** 33 mod 37") << FEP(&LEFT) << 33 << FEP(&RESULT1);
}

void FiniteElementTest::test_pow()
{
  QFETCH(FEP, leftp);
  QFETCH(int, right);
  QFETCH(FEP, resultp);

  FE left = *leftp.fe;
  FE result = *resultp.fe;

  FE copy (left);

  QCOMPARE(left.pow(right), result);
  QCOMPARE(left, copy);
  QCOMPARE(copy.pow_eq(right), result);
  QCOMPARE(copy, result);
}

void FiniteElementTest::test_divide_data()
{
  QTest::addColumn<FEP>("leftp");
  QTest::addColumn<FEP>("rightp");
  QTest::addColumn<FEP>("resultp");

  QTest::newRow("17 / 5 mod 37") << FEP(&LEFT) << FEP(&RIGHT) << FEP(&RESULT2);
}

void FiniteElementTest::test_divide()
{
  QFETCH(FEP, leftp);
  QFETCH(FEP, rightp);
  QFETCH(FEP, resultp);

  FE left = *leftp.fe;
  FE right = *rightp.fe;
  FE result = *resultp.fe;

  FE copy (left);

  QCOMPARE(left / right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy /= right, result);
  QCOMPARE(copy, result);
}
