#include "longinttest.h"
#include "LongArithmetic/longint.h"
#include "comparemacros.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace LongArithmetic;
using namespace std;

typedef LongInt::part_type part_type;
Q_DECLARE_METATYPE(LongInt)
Q_DECLARE_METATYPE(string)

void LongIntTest::test_empty_constructor()
{
  QCOMPARE(LongInt(), LongInt(0));
}

void LongIntTest::test_char_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(-2)") << qlonglong(-0x2) << -0x2_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-7)") << qlonglong(-0x7) << -0x7_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-106)") << qlonglong(-0x6a) << -0x6a_long;
  QTest::newRow("LongInt(83)") << qlonglong(0x53) << 0x53_long;
}

void LongIntTest::test_char_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((char)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_short_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(-2)") << qlonglong(-0x2) << -0x2_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-66)") << qlonglong(-0x42) << -0x42_long;
  QTest::newRow("LongInt(5)") << qlonglong(0x5) << 0x5_long;
  QTest::newRow("LongInt(-15420)") << qlonglong(-0x3c3c) << -0x3c3c_long;
  QTest::newRow("LongInt(9260)") << qlonglong(0x242c) << 0x242c_long;
}

void LongIntTest::test_short_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((short)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(-2)") << qlonglong(-0x2) << -0x2_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-8741)") << qlonglong(-0x2225) << -0x2225_long;
  QTest::newRow("LongInt(25537)") << qlonglong(0x63c1) << 0x63c1_long;
  QTest::newRow("LongInt(-521282240)") << qlonglong(-0x1f1222c0) << -0x1f1222c0_long;
  QTest::newRow("LongInt(1841553575)") << qlonglong(0x6dc3e0a7) << 0x6dc3e0a7_long;
}

void LongIntTest::test_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_long_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(-2)") << qlonglong(-0x2) << -0x2_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-351921594)") << qlonglong(-0x14f9e5ba) << -0x14f9e5ba_long;
  QTest::newRow("LongInt(1207293341)") << qlonglong(0x47f5d59d) << 0x47f5d59d_long;
  QTest::newRow("LongInt(-1332256655422994309)") << qlonglong(-0x127d205e98233785) << -0x127d205e98233785_long;
  QTest::newRow("LongInt(3522381860054361168)") << qlonglong(0x30e203a3abd1e450) << 0x30e203a3abd1e450_long;
}

void LongIntTest::test_long_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((long int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_long_long_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(-2)") << qlonglong(-0x2) << -0x2_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(-956046064)") << qlonglong(-0x38fc1af0) << -0x38fc1af0_long;
  QTest::newRow("LongInt(748143909)") << qlonglong(0x2c97c525) << 0x2c97c525_long;
  QTest::newRow("LongInt(-7165356004609914418)") << qlonglong(-0x637075528ffc7632) << -0x637075528ffc7632_long;
  QTest::newRow("LongInt(5007893232165696909)") << qlonglong(0x457f9c5c9851b58d) << 0x457f9c5c9851b58d_long;
}

void LongIntTest::test_long_long_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((long long int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_char_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(char)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(char)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(char)-2") << -0x2_long << qlonglong(-0x2);
  QTest::newRow("(char)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(char)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(char)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(char)6") << 0x6_long << qlonglong(0x6);
  QTest::newRow("(char)-61") << -0x3d_long << qlonglong(-0x3d);
  QTest::newRow("(char)8") << 0x8_long << qlonglong(0x8);
}

void LongIntTest::test_char_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((char)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_short_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(short)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(short)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(short)-2") << -0x2_long << qlonglong(-0x2);
  QTest::newRow("(short)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(short)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(short)-119") << -0x77_long << qlonglong(-0x77);
  QTest::newRow("(short)36") << 0x24_long << qlonglong(0x24);
  QTest::newRow("(short)-22130") << -0x5672_long << qlonglong(-0x5672);
  QTest::newRow("(short)2654") << 0xa5e_long << qlonglong(0xa5e);
}

void LongIntTest::test_short_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((short)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(int)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(int)-2") << -0x2_long << qlonglong(-0x2);
  QTest::newRow("(int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(int)-12326") << -0x3026_long << qlonglong(-0x3026);
  QTest::newRow("(int)17376") << 0x43e0_long << qlonglong(0x43e0);
  QTest::newRow("(int)-300916692") << -0x11ef9fd4_long << qlonglong(-0x11ef9fd4);
  QTest::newRow("(int)241680030") << 0xe67be9e_long << qlonglong(0xe67be9e);
}

void LongIntTest::test_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_long_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(long int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(long int)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(long int)-2") << -0x2_long << qlonglong(-0x2);
  QTest::newRow("(long int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(long int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(long int)-1567687152") << -0x5d7101f0_long << qlonglong(-0x5d7101f0);
  QTest::newRow("(long int)1510534857") << 0x5a08eec9_long << qlonglong(0x5a08eec9);
  QTest::newRow("(long int)-8962695659406258604") << -0x7c61e43740d871ac_long << qlonglong(-0x7c61e43740d871ac);
  QTest::newRow("(long int)1991924431979267640") << 0x1ba4bcb79b8bc638_long << qlonglong(0x1ba4bcb79b8bc638);
}

void LongIntTest::test_long_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((long int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_long_long_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(long long int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(long long int)-1") << -0x1_long << qlonglong(-0x1);
  QTest::newRow("(long long int)-2") << -0x2_long << qlonglong(-0x2);
  QTest::newRow("(long long int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(long long int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(long long int)-1599309552") << -0x5f5386f0_long << qlonglong(-0x5f5386f0);
  QTest::newRow("(long long int)1011091203") << 0x3c440703_long << qlonglong(0x3c440703);
  QTest::newRow("(long long int)-5234155457458268871") << -0x48a374a824f8eac7_long << qlonglong(-0x48a374a824f8eac7);
  QTest::newRow("(long long int)2246307248484438374") << 0x1f2c7c8a824cd166_long << qlonglong(0x1f2c7c8a824cd166);
}

void LongIntTest::test_long_long_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((long long int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_unsigned_char_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(222)") << qlonglong(0xde) << 0xde_long;
}

void LongIntTest::test_unsigned_char_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((unsigned char)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_unsigned_short_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(53)") << qlonglong(0x35) << 0x35_long;
  QTest::newRow("LongInt(31416)") << qlonglong(0x7ab8) << 0x7ab8_long;
}

void LongIntTest::test_unsigned_short_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((unsigned short)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_unsigned_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(31196)") << qlonglong(0x79dc) << 0x79dc_long;
  QTest::newRow("LongInt(2288025975)") << qlonglong(0x88608177) << 0x88608177_long;
}

void LongIntTest::test_unsigned_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((unsigned int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_unsigned_long_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(2457919911)") << qlonglong(0x9280e1a7) << 0x9280e1a7_long;
  QTest::newRow("LongInt(1476079906759290773)") << qlonglong(0x147c16dac67aaf95) << 0x147c16dac67aaf95_long;
}

void LongIntTest::test_unsigned_long_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((unsigned long int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_unsigned_long_long_int_constructor_data()
{
  QTest::addColumn<qlonglong>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0)") << qlonglong(0x0) << 0x0_long;
  QTest::newRow("LongInt(1)") << qlonglong(0x1) << 0x1_long;
  QTest::newRow("LongInt(2)") << qlonglong(0x2) << 0x2_long;
  QTest::newRow("LongInt(2392203614)") << qlonglong(0x8e96215e) << 0x8e96215e_long;
  QTest::newRow("LongInt(17143288491551153562)") << qlonglong(0xede9320dd4f2dd9a) << 0xede9320dd4f2dd9a_long;
}

void LongIntTest::test_unsigned_long_long_int_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((unsigned long long int)input);

  QCOMPARE(constructed, result);
}

void LongIntTest::test_unsigned_char_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(unsigned char)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(unsigned char)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(unsigned char)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(unsigned char)10") << 0xa_long << qlonglong(0xa);
  QTest::newRow("(unsigned char)115") << 0x73_long << qlonglong(0x73);
}

void LongIntTest::test_unsigned_char_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((unsigned char)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_unsigned_short_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(unsigned short)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(unsigned short)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(unsigned short)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(unsigned short)25") << 0x19_long << qlonglong(0x19);
  QTest::newRow("(unsigned short)40194") << 0x9d02_long << qlonglong(0x9d02);
}

void LongIntTest::test_unsigned_short_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((unsigned short)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_unsigned_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(unsigned int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(unsigned int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(unsigned int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(unsigned int)7843") << 0x1ea3_long << qlonglong(0x1ea3);
  QTest::newRow("(unsigned int)1726479027") << 0x66e7fab3_long << qlonglong(0x66e7fab3);
}

void LongIntTest::test_unsigned_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((unsigned int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_unsigned_long_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(unsigned long int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(unsigned long int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(unsigned long int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(unsigned long int)613867920") << 0x2496e190_long << qlonglong(0x2496e190);
  QTest::newRow("(unsigned long int)15506376993451935181") << 0xd731b7b81ffe05cd_long << qlonglong(0xd731b7b81ffe05cd);
}

void LongIntTest::test_unsigned_long_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((unsigned long int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_unsigned_long_long_int_conversion_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<qlonglong>("result");

  QTest::newRow("(unsigned long long int)0") << 0x0_long << qlonglong(0x0);
  QTest::newRow("(unsigned long long int)1") << 0x1_long << qlonglong(0x1);
  QTest::newRow("(unsigned long long int)2") << 0x2_long << qlonglong(0x2);
  QTest::newRow("(unsigned long long int)592032719") << 0x2349b3cf_long << qlonglong(0x2349b3cf);
  QTest::newRow("(unsigned long long int)7921674416298759320") << 0x6def70e929c99498_long << qlonglong(0x6def70e929c99498);
}

void LongIntTest::test_unsigned_long_long_int_conversion()
{
  QFETCH(LongInt, element);
  QFETCH(qlonglong, result);

  LongInt copy (element);

  COMPARE_INTS((unsigned long long int)element, result);
  QCOMPARE(element, copy);
}

void LongIntTest::test_copy_constructor_data()
{
  QTest::addColumn<LongInt>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(0x0_long)") << 0x0_long << 0x0_long;
  QTest::newRow("LongInt(-0x1_long)") << -0x1_long << -0x1_long;
  QTest::newRow("LongInt(0x1_long)") << 0x1_long << 0x1_long;
  QTest::newRow("LongInt(-0x90_long)") << -0x90_long << -0x90_long;
  QTest::newRow("LongInt(0x5c_long)") << 0x5c_long << 0x5c_long;
  QTest::newRow("LongInt(-0x2921369a_long)") << -0x2921369a_long << -0x2921369a_long;
  QTest::newRow("LongInt(0x1f387eef8_long)") << 0x1f387eef8_long << 0x1f387eef8_long;
  QTest::newRow("LongInt(-0x3930cca48d69ba798e1298aec2d2a14b291ed5287986160802_long)")
      << -0x3930cca48d69ba798e1298aec2d2a14b291ed5287986160802_long
      << -0x3930cca48d69ba798e1298aec2d2a14b291ed5287986160802_long;
  QTest::newRow("LongInt(0xfa326a082a73b5c2fd28ad263b782ae7663b9085ae2b1b3960_long)")
      << 0xfa326a082a73b5c2fd28ad263b782ae7663b9085ae2b1b3960_long
      << 0xfa326a082a73b5c2fd28ad263b782ae7663b9085ae2b1b3960_long;
}

void LongIntTest::test_copy_constructor()
{
  QFETCH(LongInt, input);
  QFETCH(LongInt, result);

  LongInt constructed (input);

  QCOMPARE(constructed, result);
}


void LongIntTest::test_string_constructor_data()
{
  QTest::addColumn<string>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(\"0\")") << string("0") << 0x0_long;
  QTest::newRow("LongInt(\"-1\")") << string("-1") << -0x1_long;
  QTest::newRow("LongInt(\"1\")") << string("1") << 0x1_long;
  QTest::newRow("LongInt(\"-187\")") << string("-187") << -0xbb_long;
  QTest::newRow("LongInt(\"29\")") << string("29") << 0x1d_long;
  QTest::newRow("LongInt(\"-2020497785\")") << string("-2020497785") << -0x786e5979_long;
  QTest::newRow("LongInt(\"3448487030\")") << string("3448487030") << 0xcd8bbc76_long;
  QTest::newRow("LongInt(\"-1023270288772783139308901851886526563880859787616274140228985\")")
      << string("-1023270288772783139308901851886526563880859787616274140228985")
      << -0xa304304cb7be23b6efbee6fdc874ca4e07baaad9d944fded79_long;
  QTest::newRow("LongInt(\"1278817723874217418764490819240486576067745107237667263977991\")")
      << string("1278817723874217418764490819240486576067745107237667263977991")
      << 0xcbba380302ed5a69ee100277ac0a134a56673d81372db39a07_long;
}

void LongIntTest::test_string_constructor()
{
  QFETCH(string, input);
  QFETCH(LongInt, result);

  LongInt constructed (input);

  QCOMPARE(constructed, result);
}


void LongIntTest::test_hex_string_constructor_data()
{
  QTest::addColumn<string>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("LongInt(\"0x0\")") << string("0x0") << 0x0_long;
  QTest::newRow("LongInt(\"-0x1\")") << string("-0x1") << -0x1_long;
  QTest::newRow("LongInt(\"0x1\")") << string("0x1") << 0x1_long;
  QTest::newRow("LongInt(\"-0x8f\")") << string("-0x8f") << -0x8f_long;
  QTest::newRow("LongInt(\"0x7d\")") << string("0x7d") << 0x7d_long;
  QTest::newRow("LongInt(\"-0xc027425\")") << string("-0xc027425") << -0xc027425_long;
  QTest::newRow("LongInt(\"0xa2ddc12c\")") << string("0xa2ddc12c") << 0xa2ddc12c_long;
  QTest::newRow("LongInt(\"-0x20624d186a49ebe64606c2e08b0f2fd5d69cb65b84fdc66d6a\")")
      << string("-0x20624d186a49ebe64606c2e08b0f2fd5d69cb65b84fdc66d6a")
      << -0x20624d186a49ebe64606c2e08b0f2fd5d69cb65b84fdc66d6a_long;
  QTest::newRow("LongInt(\"0xe8728c94e5a291618f846d251f32ced80373ba50bd137ba3cd\")")
      << string("0xe8728c94e5a291618f846d251f32ced80373ba50bd137ba3cd")
      << 0xe8728c94e5a291618f846d251f32ced80373ba50bd137ba3cd_long;
}

void LongIntTest::test_hex_string_constructor()
{
  QFETCH(string, input);
  QFETCH(LongInt, result);

  LongInt constructed (input);

  QCOMPARE(constructed, result);
}


void LongIntTest::test_decimal_istream_data()
{
  QTest::addColumn<string>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("istream(\"0\") >> constructed") << string("0") << 0x0_long;
  QTest::newRow("istream(\"-1\") >> constructed") << string("-1") << -0x1_long;
  QTest::newRow("istream(\"1\") >> constructed") << string("1") << 0x1_long;
  QTest::newRow("istream(\"-93\") >> constructed") << string("-93") << -0x5d_long;
  QTest::newRow("istream(\"123\") >> constructed") << string("123") << 0x7b_long;
  QTest::newRow("istream(\"-5600948181\") >> constructed") << string("-5600948181") << -0x14dd7afd5_long;
  QTest::newRow("istream(\"1198868310\") >> constructed") << string("1198868310") << 0x47754756_long;
  QTest::newRow("istream(\"-416005259508137555232037781064959239825831206560485295452851\") >> constructed")
      << string("-416005259508137555232037781064959239825831206560485295452851")
      << -0x42460190d37b052b4044af9629817d82d5242128e5f4e6f2b3_long;
  QTest::newRow("istream(\"36513148724063300399901092949917640858499859584264102864807\") >> constructed")
      << string("36513148724063300399901092949917640858499859584264102864807")
      << 0x5d11f0f5d30b1d08d18896ccb751c62176fd9f2b5b089e7a7_long;
}

void LongIntTest::test_decimal_istream()
{
  QFETCH(string, input);
  QFETCH(LongInt, result);

  LongInt constructed;
  istringstream iss (input);
  iss >> constructed;

  QCOMPARE(constructed, result);
}


void LongIntTest::test_hex_istream_data()
{
  QTest::addColumn<string>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("istream(\"0\") >> hex >> constructed") << string("0") << 0x0_long;
  QTest::newRow("istream(\"-1\") >> hex >> constructed") << string("-1") << -0x1_long;
  QTest::newRow("istream(\"1\") >> hex >> constructed") << string("1") << 0x1_long;
  QTest::newRow("istream(\"-176\") >> hex >> constructed") << string("-b0") << -0xb0_long;
  QTest::newRow("istream(\"51\") >> hex >> constructed") << string("33") << 0x33_long;
  QTest::newRow("istream(\"-7579775258\") >> hex >> constructed") << string("-1c3ca311a") << -0x1c3ca311a_long;
  QTest::newRow("istream(\"4408464862\") >> hex >> constructed") << string("106c3d5de") << 0x106c3d5de_long;
  QTest::newRow("istream(\"-1365038051999723739263583762562996798607521890301493711564069\") >> hex >> constructed")
      << string("-d9768e3d515f154fe86b13abd0019ae09fe46c00ef59916d25")
      << -0xd9768e3d515f154fe86b13abd0019ae09fe46c00ef59916d25_long;
  QTest::newRow("istream(\"1324064734456435742759655164559877875801041475582427891988423\") >> hex >> constructed")
      << string("d2ef88d821fc438525be643dbbce555b90763753cc008f77c7")
      << 0xd2ef88d821fc438525be643dbbce555b90763753cc008f77c7_long;
}

void LongIntTest::test_hex_istream()
{
  QFETCH(string, input);
  QFETCH(LongInt, result);

  LongInt constructed;
  istringstream iss (input);
  iss.flags(ios_base::hex);
  iss >> constructed;

  QCOMPARE(constructed, result);
}


void LongIntTest::test_decimal_ostream_data()
{
  QTest::addColumn<LongInt>("number");
  QTest::addColumn<string>("result");

  QTest::newRow("out << 0x0_long") << 0x0_long << string("0");
  QTest::newRow("out << -0x1_long") << -0x1_long << string("-1");
  QTest::newRow("out << 0x1_long") << 0x1_long << string("1");
  QTest::newRow("out << -0x43_long") << -0x43_long << string("-67");
  QTest::newRow("out << 0xc1_long") << 0xc1_long << string("193");
  QTest::newRow("out << -0x19bb79c8c_long") << -0x19bb79c8c_long << string("-6907468940");
  QTest::newRow("out << 0x1f18b9b55_long") << 0x1f18b9b55_long << string("8347425621");
  QTest::newRow("out << -0xe307095588e8df6c81f4bafce35bc34607257be252be7487d3_long")
      << -0xe307095588e8df6c81f4bafce35bc34607257be252be7487d3_long
      << string("-1425074627464464569380152469082124950924441607633528362928083");
  QTest::newRow("out << 0xc54d29c06a5e504817672002250c2c974f627953b247ea8e4f_long")
      << 0xc54d29c06a5e504817672002250c2c974f627953b247ea8e4f_long
      << string("1238481075388532441507084969622337957488007489698661508222543");
}

void LongIntTest::test_decimal_ostream()
{
  QFETCH(LongInt, number);
  QFETCH(string, result);

  ostringstream oss;
  oss << number;
  string string_result = oss.str();

  QCOMPARE(string_result, result);
}


void LongIntTest::test_hex_ostream_data()
{
  QTest::addColumn<LongInt>("number");
  QTest::addColumn<string>("result");

  QTest::newRow("out << hex << 0x0_long") << 0x0_long << string("0");
  QTest::newRow("out << hex << -0x1_long") << -0x1_long << string("-1");
  QTest::newRow("out << hex << 0x1_long") << 0x1_long << string("1");
  QTest::newRow("out << hex << -0x79_long") << -0x79_long << string("-79");
  QTest::newRow("out << hex << 0x72_long") << 0x72_long << string("72");
  QTest::newRow("out << hex << -0xcafade52_long") << -0xcafade52_long << string("-cafade52");
  QTest::newRow("out << hex << 0xe6545e97_long") << 0xe6545e97_long << string("e6545e97");
  QTest::newRow("out << hex << -0xbe3e955c78ed85ae7d9f3cab4b488cf0ebdf6b98475d15181e_long")
      << -0xbe3e955c78ed85ae7d9f3cab4b488cf0ebdf6b98475d15181e_long
      << string("-be3e955c78ed85ae7d9f3cab4b488cf0ebdf6b98475d15181e");
  QTest::newRow("out << hex << 0xe0607762c06f767a75f70c3da6cf1a72cd173a4df5fe901f8e_long")
      << 0xe0607762c06f767a75f70c3da6cf1a72cd173a4df5fe901f8e_long
      << string("e0607762c06f767a75f70c3da6cf1a72cd173a4df5fe901f8e");
}

void LongIntTest::test_hex_ostream()
{
  QFETCH(LongInt, number);
  QFETCH(string, result);

  ostringstream oss;
  oss.flags(ios_base::hex);
  oss << number;
  string string_result = oss.str();

  QCOMPARE(string_result, result);
}


void LongIntTest::test_assign_data()
{
  QTest::addColumn<LongInt>("input");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("i = 0x0_long") << 0x0_long << 0x0_long;
  QTest::newRow("i = -0x1_long") << -0x1_long << -0x1_long;
  QTest::newRow("i = 0x1_long") << 0x1_long << 0x1_long;
  QTest::newRow("i = -0x87_long") << -0x87_long << -0x87_long;
  QTest::newRow("i = 0x38_long") << 0x38_long << 0x38_long;
  QTest::newRow("i = -0x16fdcfe7_long") << -0x16fdcfe7_long << -0x16fdcfe7_long;
  QTest::newRow("i = 0x829116_long") << 0x829116_long << 0x829116_long;
  QTest::newRow("i = -0x85206fa5b10b413d7af9aedb6f2983d75d901724e2a58096c1_long")
      << -0x85206fa5b10b413d7af9aedb6f2983d75d901724e2a58096c1_long
      << -0x85206fa5b10b413d7af9aedb6f2983d75d901724e2a58096c1_long;
  QTest::newRow("i = 0x824c46eb3c1848921359b2a67eee511f4136ec49574a878fb8_long")
      << 0x824c46eb3c1848921359b2a67eee511f4136ec49574a878fb8_long
      << 0x824c46eb3c1848921359b2a67eee511f4136ec49574a878fb8_long;
}

void LongIntTest::test_assign()
{
  QFETCH(LongInt, input);
  QFETCH(LongInt, result);

  LongInt constructed;

  QCOMPARE(constructed = input, input);
  QCOMPARE(constructed, input);
  QCOMPARE(constructed = constructed, input);
  QCOMPARE(constructed, input);
  QCOMPARE(constructed, result);
}


void LongIntTest::test_inc_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0++") << 0x0_long << 0x1_long;
  QTest::newRow("-1++") << -0x1_long << 0x0_long;
  QTest::newRow("1++") << 0x1_long << 0x2_long;
  QTest::newRow("-182++") << -0xb6_long << -0xb5_long;
  QTest::newRow("130++") << 0x82_long << 0x83_long;
  QTest::newRow("-5071866760++") << -0x12e4e8b88_long << -0x12e4e8b87_long;
  QTest::newRow("7180933992++") << 0x1ac045b68_long << 0x1ac045b69_long;
  QTest::newRow("-175898631864245822579217274856338807530502834463789524396594++")
      << -0x1c05b367ccdd8031cf5543a7b6b2d530cc35ae9de134df2a32_long
      << -0x1c05b367ccdd8031cf5543a7b6b2d530cc35ae9de134df2a31_long;
  QTest::newRow("349162352070665532321587378875372301232894232548738763183283++")
      << 0x379ff10cb50f171db525746feb3bfd965b488539110429d4b3_long
      << 0x379ff10cb50f171db525746feb3bfd965b488539110429d4b4_long;
}

void LongIntTest::test_inc()
{
  QFETCH(LongInt, element);
  QFETCH(LongInt, result);

  LongInt copy (element);

  QCOMPARE(element++, copy);
  QCOMPARE(element, result);
  QCOMPARE(++copy, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_dec_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0--") << 0x0_long << -0x1_long;
  QTest::newRow("-1--") << -0x1_long << -0x2_long;
  QTest::newRow("1--") << 0x1_long << 0x0_long;
  QTest::newRow("-86--") << -0x56_long << -0x57_long;
  QTest::newRow("29--") << 0x1d_long << 0x1c_long;
  QTest::newRow("-435581550--") << -0x19f6726e_long << -0x19f6726f_long;
  QTest::newRow("6166247308--") << 0x16f89778c_long << 0x16f89778b_long;
  QTest::newRow("-1220900122346981763192422616492323577213804852764148177209157--")
      << -0xc28028098e66da4924e3cb4cd57d98d0aa0db7c1690b7a8745_long
      << -0xc28028098e66da4924e3cb4cd57d98d0aa0db7c1690b7a8746_long;
  QTest::newRow("351142393150490194615355566957318487897966670461785201359539--")
      << 0x37f0b1a4a144625fb29d528574b75a0e9a39607ade675ebab3_long
      << 0x37f0b1a4a144625fb29d528574b75a0e9a39607ade675ebab2_long;
}

void LongIntTest::test_dec()
{
  QFETCH(LongInt, element);
  QFETCH(LongInt, result);

  LongInt copy (element);

  QCOMPARE(element--, copy);
  QCOMPARE(element, result);
  QCOMPARE(--copy, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_unary_plus_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("+0") << 0x0_long << 0x0_long;
  QTest::newRow("+-1") << -0x1_long << -0x1_long;
  QTest::newRow("+1") << 0x1_long << 0x1_long;
  QTest::newRow("+-80") << -0x50_long << -0x50_long;
  QTest::newRow("+120") << 0x78_long << 0x78_long;
  QTest::newRow("+-639620903") << -0x261fd727_long << -0x261fd727_long;
  QTest::newRow("+2695731222") << 0xa0ad9816_long << 0xa0ad9816_long;
  QTest::newRow("+-506137252533378673022885021249553304153419829149040008947614")
      << -0x50a1df7b08c3b53809c8d4514e613935c8996dd1b049e2e79e_long
      << -0x50a1df7b08c3b53809c8d4514e613935c8996dd1b049e2e79e_long;
  QTest::newRow("+1331715107931837139794063050552514800732760185624749663416261")
      << 0xd4278a7860782cd7e62bef80806e2b192152aec3ba63956fc5_long
      << 0xd4278a7860782cd7e62bef80806e2b192152aec3ba63956fc5_long;
}

void LongIntTest::test_unary_plus()
{
  QFETCH(LongInt, element);
  QFETCH(LongInt, result);

  LongInt copy (element);

  QCOMPARE(+element, result);
  QCOMPARE(element, copy);
}


void LongIntTest::test_unary_minus_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("-0") << 0x0_long << 0x0_long;
  QTest::newRow("--1") << -0x1_long << 0x1_long;
  QTest::newRow("-1") << 0x1_long << -0x1_long;
  QTest::newRow("--161") << -0xa1_long << 0xa1_long;
  QTest::newRow("-157") << 0x9d_long << -0x9d_long;
  QTest::newRow("--1009303026") << -0x3c28bdf2_long << 0x3c28bdf2_long;
  QTest::newRow("-1463547095") << 0x573bf4d7_long << -0x573bf4d7_long;
  QTest::newRow("--444286413652188323127927819146782624979497620072076888900572")
      << -0x46c76697953efe0c0e3257f44e242ab7e60c296d0abd1e03dc_long
      << 0x46c76697953efe0c0e3257f44e242ab7e60c296d0abd1e03dc_long;
  QTest::newRow("-60209245711703287083248987364993791075377873363392256820544")
      << 0x99785db28d5ac9a675a3cf916c46c741f18e2cd07dd704540_long
      << -0x99785db28d5ac9a675a3cf916c46c741f18e2cd07dd704540_long;
}

void LongIntTest::test_unary_minus()
{
  QFETCH(LongInt, element);
  QFETCH(LongInt, result);

  LongInt copy (element);

  QCOMPARE(-element, result);
  QCOMPARE(element, copy);
}


void LongIntTest::test_bit_negate_data()
{
  QTest::addColumn<LongInt>("element");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("~0") << 0x0_long << -0x1_long;
  QTest::newRow("~-1") << -0x1_long << 0x0_long;
  QTest::newRow("~1") << 0x1_long << -0x2_long;
  QTest::newRow("~-26") << -0x1a_long << 0x19_long;
  QTest::newRow("~48") << 0x30_long << -0x31_long;
  QTest::newRow("~-4770108592") << -0x11c5214b0_long << 0x11c5214af_long;
  QTest::newRow("~6577023830") << 0x188056b56_long << -0x188056b57_long;
  QTest::newRow("~-1529586836160041552944162953397553686745919114344565524304726")
      << -0xf3ad5fb4b5cb39ab4f490521f783b80d0ac888b47f67ae9356_long
      << 0xf3ad5fb4b5cb39ab4f490521f783b80d0ac888b47f67ae9355_long;
  QTest::newRow("~550939588183687104886354922644890601813481991020338859042954")
      << 0x57c50db0b0a97bf172a2546435e9d96d88bb2c98bb6ce5688a_long
      << -0x57c50db0b0a97bf172a2546435e9d96d88bb2c98bb6ce5688b_long;
}

void LongIntTest::test_bit_negate()
{
  QFETCH(LongInt, element);
  QFETCH(LongInt, result);

  LongInt copy (element);

  QCOMPARE(~element, result);
  QCOMPARE(element, copy);
}


void LongIntTest::test_right_shift_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<int>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 >> 0") << 0x0_long << 0 << 0x0_long;
  QTest::newRow("0 >> 1") << 0x0_long << 1 << 0x0_long;
  QTest::newRow("0 >> 2") << 0x0_long << 2 << 0x0_long;
  QTest::newRow("0 >> 32") << 0x0_long << 32 << 0x0_long;
  QTest::newRow("-1 >> 0") << -0x1_long << 0 << -0x1_long;
  QTest::newRow("1 >> 0") << 0x1_long << 0 << 0x1_long;
  QTest::newRow("-1 >> 1") << -0x1_long << 1 << -0x1_long;
  QTest::newRow("-1 >> 2") << -0x1_long << 2 << -0x1_long;
  QTest::newRow("-1 >> 32") << -0x1_long << 32 << -0x1_long;
  QTest::newRow("1 >> 1") << 0x1_long << 1 << 0x0_long;
  QTest::newRow("1 >> 2") << 0x1_long << 2 << 0x0_long;
  QTest::newRow("1 >> 32") << 0x1_long << 32 << 0x0_long;
  QTest::newRow("-2247384382028194131 >> 0") << -0x1f305030348d2153_long << 0 << -0x1f305030348d2153_long;
  QTest::newRow("-11909803468383203574 >> 0") << -0xa5481f2755b230f6_long << 0 << -0xa5481f2755b230f6_long;
  QTest::newRow("13665436868736681574 >> 0") << 0xbda5626df5938666_long << 0 << 0xbda5626df5938666_long;
  QTest::newRow("16399683593533322739 >> 0") << 0xe3976156cd5af5f3_long << 0 << 0xe3976156cd5af5f3_long;
  QTest::newRow("0 >> 26") << 0x0_long << 26 << 0x0_long;
  QTest::newRow("-2700789804796963971 >> 1") << -0x257b22049feb6c83_long << 1 << -0x12bd91024ff5b642_long;
  QTest::newRow("-18416434030555812364 >> 2") << -0xff94512d24b1d20c_long << 2 << -0x3fe5144b492c7483_long;
  QTest::newRow("-11032690526702627082 >> 32") << -0x991bfd9490ed690a_long << 32 << -0x991bfd95_long;
  QTest::newRow("-8021757025548976369 >> 1") << -0x6f5301837e5740f1_long << 1 << -0x37a980c1bf2ba079_long;
  QTest::newRow("-2633401671363261645 >> 2") << -0x248bb8de2486f4cd_long << 2 << -0x922ee378921bd34_long;
  QTest::newRow("-6802112285124553110 >> 32") << -0x5e65f5158d2b6996_long << 32 << -0x5e65f516_long;
  QTest::newRow("9533980166050486608 >> 1") << 0x844f8072a50f1950_long << 1 << 0x4227c03952878ca8_long;
  QTest::newRow("16795320802998757463 >> 2") << 0xe914f748ef782857_long << 2 << 0x3a453dd23bde0a15_long;
  QTest::newRow("10266810711286374984 >> 32") << 0x8e7b09f22e666248_long << 32 << 0x8e7b09f2_long;
  QTest::newRow("13464856271114861533 >> 1") << 0xbadcc7704f7dfbdd_long << 1 << 0x5d6e63b827befdee_long;
  QTest::newRow("5935984146470639441 >> 2") << 0x5260da218abb9751_long << 2 << 0x1498368862aee5d4_long;
  QTest::newRow("14332060565244122683 >> 32") << 0xc6e5b5264ac2963b_long << 32 << 0xc6e5b526_long;
  QTest::newRow("-1 >> 19") << -0x1_long << 19 << -0x1_long;
  QTest::newRow("1 >> 22") << 0x1_long << 22 << 0x0_long;
  QTest::newRow("-2471645810085740956 >> 5") << -0x224d0cc4d8be419c_long << 5 << -0x112686626c5f20d_long;
  QTest::newRow("-3882608485031379980 >> 14") << -0x35e1cbd8a036840c_long << 14 << -0xd7872f6280db_long;
  QTest::newRow("10939137155842666484 >> 14") << 0x97cf9f4903476ff4_long << 14 << 0x25f3e7d240d1d_long;
  QTest::newRow("14331991328825283838 >> 32") << 0xc6e5762dee9c14fe_long << 32 << 0xc6e5762d_long;
}

void LongIntTest::test_right_shift()
{
  QFETCH(LongInt, left);
  QFETCH(int, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left >> right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy >>= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_left_shift_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<int>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 << 0") << 0x0_long << 0 << 0x0_long;
  QTest::newRow("0 << 1") << 0x0_long << 1 << 0x0_long;
  QTest::newRow("0 << 2") << 0x0_long << 2 << 0x0_long;
  QTest::newRow("0 << 32") << 0x0_long << 32 << 0x0_long;
  QTest::newRow("-1 << 0") << -0x1_long << 0 << -0x1_long;
  QTest::newRow("1 << 0") << 0x1_long << 0 << 0x1_long;
  QTest::newRow("-1 << 1") << -0x1_long << 1 << -0x2_long;
  QTest::newRow("-1 << 2") << -0x1_long << 2 << -0x4_long;
  QTest::newRow("-1 << 32") << -0x1_long << 32 << -0x100000000_long;
  QTest::newRow("1 << 1") << 0x1_long << 1 << 0x2_long;
  QTest::newRow("1 << 2") << 0x1_long << 2 << 0x4_long;
  QTest::newRow("1 << 32") << 0x1_long << 32 << 0x100000000_long;
  QTest::newRow("-90653548530716435 << 0") << -0x14210ec0dcd4f13_long << 0 << -0x14210ec0dcd4f13_long;
  QTest::newRow("-1164392888603459889 << 0") << -0x1028c129b8334131_long << 0 << -0x1028c129b8334131_long;
  QTest::newRow("2640293155181271810 << 0") << 0x24a434a2c1799b02_long << 0 << 0x24a434a2c1799b02_long;
  QTest::newRow("10139136394590348777 << 0") << 0x8cb572d4d8cae5e9_long << 0 << 0x8cb572d4d8cae5e9_long;
  QTest::newRow("0 << 27") << 0x0_long << 27 << 0x0_long;
  QTest::newRow("-16354738317807095732 << 1") << -0xe2f7b3d9535c8fb4_long << 1 << -0x1c5ef67b2a6b91f68_long;
  QTest::newRow("-127472702680520051 << 2") << -0x1c4dfbf69d4d573_long << 2 << -0x7137efda75355cc_long;
  QTest::newRow("-5991363171354453648 << 32") << -0x5325990f8cf0a690_long << 32 << -0x5325990f8cf0a69000000000_long;
  QTest::newRow("-14444557287863794056 << 1") << -0xc8756052a0e6b988_long << 1 << -0x190eac0a541cd7310_long;
  QTest::newRow("-5843943956510183501 << 2") << -0x5119dc10df14904d_long << 2 << -0x1446770437c524134_long;
  QTest::newRow("-13934368304938588578 << 32") << -0xc160d225595399a2_long << 32 << -0xc160d225595399a200000000_long;
  QTest::newRow("14299625149690246822 << 1") << 0xc672794f9c8776a6_long << 1 << 0x18ce4f29f390eed4c_long;
  QTest::newRow("17182149016456019849 << 2") << 0xee73417edbb03f89_long << 2 << 0x3b9cd05fb6ec0fe24_long;
  QTest::newRow("10581068424130867106 << 32") << 0x92d781abbc6c2fa2_long << 32 << 0x92d781abbc6c2fa200000000_long;
  QTest::newRow("3000049538869822273 << 1") << 0x29a2512920e90341_long << 1 << 0x5344a25241d20682_long;
  QTest::newRow("1869242113219055917 << 2") << 0x19f0e1cc5d9f512d_long << 2 << 0x67c38731767d44b4_long;
  QTest::newRow("6287781802841646083 << 32") << 0x5742b03c4f8aa403_long << 32 << 0x5742b03c4f8aa40300000000_long;
  QTest::newRow("-1 << 19") << -0x1_long << 19 << -0x80000_long;
  QTest::newRow("1 << 1") << 0x1_long << 1 << 0x2_long;
  QTest::newRow("-684828947447908173 << 10") << -0x981004ca089874d_long << 10 << -0x2604013282261d3400_long;
  QTest::newRow("-4282434532636351861 << 11") << -0x3b6e4384a3a7dd75_long << 11 << -0x1db721c251d3eeba800_long;
  QTest::newRow("6205144565796396918 << 3") << 0x561d1a1b383d5f76_long << 3 << 0x2b0e8d0d9c1eafbb0_long;
  QTest::newRow("14613843961790284246 << 4") << 0xcacecda7e17f41d6_long << 4 << 0xcacecda7e17f41d60_long;
}

void LongIntTest::test_left_shift()
{
  QFETCH(LongInt, left);
  QFETCH(int, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left << right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy <<= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_plus_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 + 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 + -1") << 0x0_long << -0x1_long << -0x1_long;
  QTest::newRow("0 + 1") << 0x0_long << 0x1_long << 0x1_long;
  QTest::newRow("-1 + 0") << -0x1_long << 0x0_long << -0x1_long;
  QTest::newRow("1 + 0") << 0x1_long << 0x0_long << 0x1_long;
  QTest::newRow("-1 + -1") << -0x1_long << -0x1_long << -0x2_long;
  QTest::newRow("-1 + 1") << -0x1_long << 0x1_long << 0x0_long;
  QTest::newRow("1 + -1") << 0x1_long << -0x1_long << 0x0_long;
  QTest::newRow("1 + 1") << 0x1_long << 0x1_long << 0x2_long;
  QTest::newRow("-13377734462799784505 + 0") << -0xb9a7429d9aaeaa39_long << 0x0_long << -0xb9a7429d9aaeaa39_long;
  QTest::newRow("-4825737689723795771843434670453664417023115965233503027259 + 0")
      << -0xc4cf0d65b28b0eff5fc41ded998ae988703c268f41da403b_long << 0x0_long
      << -0xc4cf0d65b28b0eff5fc41ded998ae988703c268f41da403b_long;
  QTest::newRow("7108230580335641046 + 0") << 0x62a5820d427981d6_long << 0x0_long << 0x62a5820d427981d6_long;
  QTest::newRow("1308458817526292251388617906572869246399209130399624753846 + 0")
      << 0x355cf28d55fb7ff9bfb07a1963f3f4b08dca01bdc4fa72b6_long << 0x0_long
      << 0x355cf28d55fb7ff9bfb07a1963f3f4b08dca01bdc4fa72b6_long;
  QTest::newRow("0 + -17307197953774908448") << 0x0_long << -0xf02f84d76c1ef420_long << -0xf02f84d76c1ef420_long;
  QTest::newRow("0 + -15572468901135912858") << 0x0_long << -0xd81c85f588060f9a_long << -0xd81c85f588060f9a_long;
  QTest::newRow("0 + 10944087882927555040") << 0x0_long << 0x97e135f1fc8dc1e0_long << 0x97e135f1fc8dc1e0_long;
  QTest::newRow("0 + 10535839731386871857") << 0x0_long << 0x9236d26a17c2f031_long << 0x9236d26a17c2f031_long;
  QTest::newRow("-8078503508769396313 + 1") << -0x701c9c23b4f25659_long << 0x1_long << -0x701c9c23b4f25658_long;
  QTest::newRow("-9790876515206382673 + 1") << -0x87e02e50f8974451_long << 0x1_long << -0x87e02e50f8974450_long;
  QTest::newRow("-4924431031561899925920630906953364489630363326624154606950 + 1")
      << -0xc8d5757a7b2548ea3aeca8abf0d7177a909aa0f705e55d66_long << 0x1_long
      << -0xc8d5757a7b2548ea3aeca8abf0d7177a909aa0f705e55d65_long;
  QTest::newRow("-4877025984015663289873415651102995481962876015836303262140 + 1")
      << -0xc6e686f0b62c1f409bebe112edddcca9c2886b7947e101bc_long << 0x1_long
      << -0xc6e686f0b62c1f409bebe112edddcca9c2886b7947e101bb_long;
  QTest::newRow("6674091410503177650 + 1") << 0x5c9f22c6e98715b2_long << 0x1_long << 0x5c9f22c6e98715b3_long;
  QTest::newRow("8668665893317471284 + 1") << 0x784d49b38fbb6c34_long << 0x1_long << 0x784d49b38fbb6c35_long;
  QTest::newRow("3057043420847428315895059911626126544609263120388034618228 + 1")
      << 0x7cad05c5bff92d321d2097e4a97a00bd7fdedaafe4db6374_long << 0x1_long
      << 0x7cad05c5bff92d321d2097e4a97a00bd7fdedaafe4db6375_long;
  QTest::newRow("2985540043892342745300075066569141269341121087723305730622 + 1")
      << 0x79c27e11e3d2c769fdf94d043e3bd7cda2da48b149a0823e_long << 0x1_long
      << 0x79c27e11e3d2c769fdf94d043e3bd7cda2da48b149a0823f_long;
  QTest::newRow("-1 + -6763032778994848973") << -0x1_long << -0x5ddb1e7afc4f94cd_long << -0x5ddb1e7afc4f94ce_long;
  QTest::newRow("-1 + -2930816503774404373") << -0x1_long << -0x28ac5a1501535f15_long << -0x28ac5a1501535f16_long;
  QTest::newRow("-1 + 13377588204255156086") << -0x1_long << 0xb9a6bd9822159776_long << 0xb9a6bd9822159775_long;
  QTest::newRow("-1 + 16552162100873261562") << -0x1_long << 0xe5b517bbcf3bf1fa_long << 0xe5b517bbcf3bf1f9_long;
  QTest::newRow("1 + -8232931167878741053") << 0x1_long << -0x72413f46f9a77c3d_long << -0x72413f46f9a77c3c_long;
  QTest::newRow("1 + -16204046919199981955") << 0x1_long << -0xe0e056d1fead8183_long << -0xe0e056d1fead8182_long;
  QTest::newRow("1 + 17482197728750755753") << 0x1_long << 0xf29d3e35ab545fa9_long << 0xf29d3e35ab545faa_long;
  QTest::newRow("1 + 7849513994081201907") << 0x1_long << 0x6cef13639caaeef3_long << 0x6cef13639caaeef4_long;
  QTest::newRow("-6893490864856376169 + -4287028376182679198") << -0x5faa996b162a2369_long << -0x3b7e95983063669e_long << -0x9b292f03468d8a07_long;
  QTest::newRow("-4565166986906424197 + -15719573679600118082") << -0x3f5abb2ff2e5d385_long << -0xda2724f9c9252942_long << -0x11981e029bc0afcc7_long;
  QTest::newRow("-12379513791776158812 + 12139612933482123287") << -0xabccde3442ddf45c_long << 0xa87891a502f09017_long << -0x3544c8f3fed6445_long;
  QTest::newRow("-13458690039398906442 + 7025285384644372384") << -0xbac6df489c75ba4a_long << 0x617ed3d5f578a7a0_long << -0x59480b72a6fd12aa_long;
  QTest::newRow("-605340341552609873504069572023148954742047352283077296481 + -5539838676601949736")
      << -0x18b00c4d707109f9775a2c4b55649cbb28a100b044384161_long << -0x4ce175eccfd44e28_long
      << -0x18b00c4d707109f9775a2c4b55649cbb7582769d140c8f89_long;
  QTest::newRow("-530609494443350370691736376779997399516001119450197588783 + -5547924765565185015")
      << -0x15a3d254e2f44d42c5b4b47c1325bf2aa503886dad4efb2f_long << -0x4cfe302e1c1aebf7_long
      << -0x15a3d254e2f44d42c5b4b47c1325bf2af201b89bc969e726_long;
  QTest::newRow("-1613005578160791341711192242220025819381962098347011146696 + 3441162548368707294")
      << -0x41c89062f10294454a32a0bf9d4e7178835ec92d574b03c8_long << 0x2fc1771b0de50ede_long
      << -0x41c89062f10294454a32a0bf9d4e7178539d52124965f4ea_long;
  QTest::newRow("-1949121058534661594465387468473662441478587948212485545143 + 12461459661501152641")
      << -0x4f7dc5fb1f790fc7850f7ac9b0fa46fe5730d189cbdedcb7_long << 0xacefff89daa2bd81_long
      << -0x4f7dc5fb1f790fc7850f7ac9b0fa46fdaa40d1fff13c1f36_long;
  QTest::newRow("6117943085429031959 + -2967492750559460769") << 0x54e74cd26b0e0417_long << -0x292ea6ef26a4bda1_long << 0x2bb8a5e344694676_long;
  QTest::newRow("3699346688349934678 + -1492027992638711776") << 0x3356b8368c1d9456_long << -0x14b4bf8de02b67e0_long << 0x1ea1f8a8abf22c76_long;
  QTest::newRow("14171934857131204558 + 2689210049144700676") << 0xc4acd3aa9b481fce_long << 0x2551fe4aa9ae3f04_long << 0xe9fed1f544f65ed2_long;
  QTest::newRow("237111116128671241 + 5137030754925082080") << 0x34a634dc9255609_long << 0x474a66412390f5e0_long << 0x4a94c98eecb64be9_long;
  QTest::newRow("3803005473950764208995021334743681840469433111008431457257 + -8574695765318159054")
      << 0x9b193ad2b44287238e465c921c5ec2d82f868817261243e9_long << -0x76ff705e2cd5cace_long
      << 0x9b193ad2b44287238e465c921c5ec2d7b88717b8f93c791b_long;
  QTest::newRow("4881149282124521636778950257341632696510007480942025386286 + -2226025561734125077")
      << 0xc711938bc3a8d06545198c985d6873fae4f33b6a083a292e_long << -0x1ee46e74541a1615_long
      << 0xc711938bc3a8d06545198c985d6873fac60eccf5b4201319_long;
  QTest::newRow("5722436246548142778310610625222440088704722478213878578355 + 12726056213112190106")
      << 0xe96105a7d092a5f2f423bb57611fdadc966096849230fcb3_long << 0xb09c08b34634749a_long
      << 0xe96105a7d092a5f2f423bb57611fdadd46fc9f37d865714d_long;
  QTest::newRow("3847164115626869601888280311512036412529695326700798211893 + 7228537604814507022")
      << 0x9ce6447b702f36107adf94a616845f84c04a6b60df0ff735_long << 0x6450eca734858c0e_long
      << 0x9ce6447b702f36107adf94a616845f85249b580813958343_long;
}

void LongIntTest::test_plus()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left + right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy += right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_minus_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 - 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 - -1") << 0x0_long << -0x1_long << 0x1_long;
  QTest::newRow("0 - 1") << 0x0_long << 0x1_long << -0x1_long;
  QTest::newRow("-1 - 0") << -0x1_long << 0x0_long << -0x1_long;
  QTest::newRow("1 - 0") << 0x1_long << 0x0_long << 0x1_long;
  QTest::newRow("-1 - -1") << -0x1_long << -0x1_long << 0x0_long;
  QTest::newRow("-1 - 1") << -0x1_long << 0x1_long << -0x2_long;
  QTest::newRow("1 - -1") << 0x1_long << -0x1_long << 0x2_long;
  QTest::newRow("1 - 1") << 0x1_long << 0x1_long << 0x0_long;
  QTest::newRow("-10234884412009372718 - 0") << -0x8e099d255f005c2e_long << 0x0_long << -0x8e099d255f005c2e_long;
  QTest::newRow("-4073613179637435824088914983820883755766251839614391205208 - 0")
      << -0xa622818c91e8c4980abd819a0b2b225d46f7bb532640bd58_long << 0x0_long
      << -0xa622818c91e8c4980abd819a0b2b225d46f7bb532640bd58_long;
  QTest::newRow("16697859669680415554 - 0") << 0xe7bab6e6889f6342_long << 0x0_long << 0xe7bab6e6889f6342_long;
  QTest::newRow("3355617899813088883374359403053902988655563732944030026007 - 0")
      << 0x88da491a699e60cd77a7504c171cd3bfb735eefabd744917_long << 0x0_long
      << 0x88da491a699e60cd77a7504c171cd3bfb735eefabd744917_long;
  QTest::newRow("0 - -2295935153676218447") << 0x0_long << -0x1fdcccdb9e33f04f_long << 0x1fdcccdb9e33f04f_long;
  QTest::newRow("0 - -18439741661607827988") << 0x0_long << -0xffe71f57e21b1a14_long << 0xffe71f57e21b1a14_long;
  QTest::newRow("0 - 13900734245424258907") << 0x0_long << 0xc0e954259f9edf5b_long << -0xc0e954259f9edf5b_long;
  QTest::newRow("0 - 3403284910961517513") << 0x0_long << 0x2f3ae5985b4ee3c9_long << -0x2f3ae5985b4ee3c9_long;
  QTest::newRow("-1711535198496831904 - 1") << -0x17c09831e6fb39a0_long << 0x1_long << -0x17c09831e6fb39a1_long;
  QTest::newRow("-16453988352139122622 - 1") << -0xe4584f3ab3aad7be_long << 0x1_long << -0xe4584f3ab3aad7bf_long;
  QTest::newRow("-1015267998739215118263195297224239748091781869264607659820 - 1")
      << -0x2967e47a72ec8f06e44075c6ddaa7e23a0eafaedacc8472c_long << 0x1_long
      << -0x2967e47a72ec8f06e44075c6ddaa7e23a0eafaedacc8472d_long;
  QTest::newRow("-5893759307919589566606343256062950109110056891782487628180 - 1")
      << -0xf05db7e352fa29355a87234aa440df03b9dac551b2e85994_long << 0x1_long
      << -0xf05db7e352fa29355a87234aa440df03b9dac551b2e85995_long;
  QTest::newRow("2738405976812842770 - 1") << 0x2600c5ba2abc6f12_long << 0x1_long << 0x2600c5ba2abc6f11_long;
  QTest::newRow("16575538761326717827 - 1") << 0xe60824aeb598eb83_long << 0x1_long << 0xe60824aeb598eb82_long;
  QTest::newRow("949962974143011522062982263679854437453372561058417945357 - 1")
      << 0x26be1383600136e919f5b7c916b7bd81f8d1022171392b0d_long << 0x1_long
      << 0x26be1383600136e919f5b7c916b7bd81f8d1022171392b0c_long;
  QTest::newRow("4628637438265898898090445424751900713991237653139013459876 - 1")
      << 0xbcc53acd01cb803df29081ab572da55b981140e5f6635fa4_long << 0x1_long
      << 0xbcc53acd01cb803df29081ab572da55b981140e5f6635fa3_long;
  QTest::newRow("-1 - -12924851825730127512") << -0x1_long << -0xb35e4c41b7340698_long << 0xb35e4c41b7340697_long;
  QTest::newRow("-1 - -12354417865592609459") << -0x1_long << -0xab73b5979d631ab3_long << 0xab73b5979d631ab2_long;
  QTest::newRow("-1 - 17969382357951953930") << -0x1_long << 0xf960120c76e5bc0a_long << -0xf960120c76e5bc0b_long;
  QTest::newRow("-1 - 4599240110710041768") << -0x1_long << 0x3fd3c8834b99aca8_long << -0x3fd3c8834b99aca9_long;
  QTest::newRow("1 - -7451543892191761438") << 0x1_long << -0x676933b0a252541e_long << 0x676933b0a252541f_long;
  QTest::newRow("1 - -2642017154378101001") << 0x1_long << -0x24aa549a9931f109_long << 0x24aa549a9931f10a_long;
  QTest::newRow("1 - 8508014054581055274") << 0x1_long << 0x761289b48b55af2a_long << -0x761289b48b55af29_long;
  QTest::newRow("1 - 9851023526144324038") << 0x1_long << 0x88b5ddb43dd931c6_long << -0x88b5ddb43dd931c5_long;
  QTest::newRow("-1487480795784684879 - -14498403006906013851") << -0x14a497e71af6254f_long << -0xc934acb80d16989b_long << 0xb49014d0f220734c_long;
  QTest::newRow("-3573164946764851078 - -3273781538941895949") << -0x31966e966fcbe786_long << -0x2d6ecef6e4dd050d_long << -0x4279f9f8aeee279_long;
  QTest::newRow("-14800993004540177979 - 10145992187611778639") << -0xcd67b0b7f6a8ae3b_long << 0x8ccdce238c7d0e4f_long << -0x15a357edb8325bc8a_long;
  QTest::newRow("-9650733307885481832 - 16360684587318517456") << -0x85ee4acfce8b6f68_long << 0xe30cd3f315541ed0_long << -0x168fb1ec2e3df8e38_long;
  QTest::newRow("-2270450977105156889626879951613337101629745909107100911124 - -4328001916473299210")
      << -0x5c989d3f62c79378df548414a014a8d45e029daeda4e8614_long << -0x3c1026cff299d10a_long
      << -0x5c989d3f62c79378df548414a014a8d421f276dee7b4b50a_long;
  QTest::newRow("-4547793210609046759365312099834659974926592836461043904335 - -11626600108595196161")
      << -0xb9792d33bda92bd0124b9941b4a9f440d2614d8351e3ef4f_long << -0xa159fb32ca55b101_long
      << -0xb9792d33bda92bd0124b9941b4a9f44031075250878e3e4e_long;
  QTest::newRow("-172804501975875419591628410877924349560264056043738854799 - 9303760198009655800")
      << -0x70c29c64de6b07a52ca4b93daa81f283b5a7acbaeb9758f_long << 0x811d989b4dc891f8_long
      << -0x70c29c64de6b07a52ca4b93daa81f28bc781366fc820787_long;
  QTest::newRow("-2869408370986288577070702878870293458816298424839378768924 - 3531211121209655070")
      << -0x7506056eccfb8eb55905cbe7a4443c2ed443a71e7d53141c_long << 0x310161ce3a9c3f1e_long
      << -0x7506056eccfb8eb55905cbe7a4443c2f054508ecb7ef533a_long;
  QTest::newRow("15625903681080966866 - -4456725464125173514") << 0xd8da5c9bbd4cbed2_long << -0x3dd97832669e6f0a_long << 0x116b3d4ce23eb2ddc_long;
  QTest::newRow("12053655012611359019 - -2749356359413807407") << 0xa7472f5ef7ce812b_long << -0x2627ad0acbd2392f_long << 0xcd6edc69c3a0ba5a_long;
  QTest::newRow("897062571035999998 - 4872152215580379964") << 0xc7301a7cfe63efe_long << 0x439d5ca0554d0b3c_long << -0x372a5af88566cc3e_long;
  QTest::newRow("17916138139308472930 - 3814211718864950394") << 0xf8a2e8b6c44f3a62_long << 0x34eecd598913d47a_long << 0xc3b41b5d3b3b65e8_long;
  QTest::newRow("6017696634120717161493071149597581765633498697212919400630 - -5847825935608564149")
      << 0xf56baf3320bf68cdaa5141b87d3aaf0e3151efc0e9edc8b6_long << -0x5127a6b49043c9b5_long
      << 0xf56baf3320bf68cdaa5141b87d3aaf0e827996757a31926b_long;
  QTest::newRow("2937852189528796359230150207965160896455008554635222370527 - -18360296186986001873")
      << 0x77d09ba7d8001ed7b5984fe2e07884fafdc3aa7fd458c8df_long << -0xfecce01ae44275d1_long
      << 0x77d09ba7d8001ed7b5984fe2e07884fbfc908a9ab89b3eb0_long;
  QTest::newRow("3927347032146290701001690756242628668585704456083062745333 - 12985062821348314960")
      << 0xa02b6a8d4327345d3149e9b4bc6473045f1c98b8efd568f5_long << 0xb43435d694990f50_long
      << 0xa02b6a8d4327345d3149e9b4bc647303aae862e25b3c59a5_long;
  QTest::newRow("5483825991676585002401819117206577648180568483068096761928 - 10585523559025232851")
      << 0xdfa5d0963b1d4cf61eb831de0477020cffec663baf0b5048_long << 0x92e75597a93a4bd3_long
      << 0xdfa5d0963b1d4cf61eb831de0477020c6d0510a405d10475_long;
}

void LongIntTest::test_minus()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left - right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy -= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_compare_to_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<int>("result");

  QTest::newRow("0 <=> 0") << 0x0_long << 0x0_long << 0;
  QTest::newRow("0 <=> -1") << 0x0_long << -0x1_long << 1;
  QTest::newRow("0 <=> 1") << 0x0_long << 0x1_long << -1;
  QTest::newRow("-1 <=> 0") << -0x1_long << 0x0_long << -1;
  QTest::newRow("1 <=> 0") << 0x1_long << 0x0_long << 1;
  QTest::newRow("-1 <=> -1") << -0x1_long << -0x1_long << 0;
  QTest::newRow("-1 <=> 1") << -0x1_long << 0x1_long << -1;
  QTest::newRow("1 <=> -1") << 0x1_long << -0x1_long << 1;
  QTest::newRow("1 <=> 1") << 0x1_long << 0x1_long << 0;
  QTest::newRow("-3070629170961472694 <=> 0") << -0x2a9d10f64c1c5cb6_long << 0x0_long << -1;
  QTest::newRow("-6252992652709242010002300241107923683769157237689412503463 <=> 0")
      << -0xff044a18397a669b3568546b7e48c0daa3aa7601ea0047a7_long << 0x0_long << -1;
  QTest::newRow("7188560899257228882 <=> 0") << 0x63c2e60d1e7d5e52_long << 0x0_long << 1;
  QTest::newRow("1248280569467621377651557509709047234676530352795831370744 <=> 0")
      << 0x32e8a8411e2f8d1634725496ff0a6ad61c2d3654aa7a03f8_long << 0x0_long << 1;
  QTest::newRow("0 <=> -814265040502395162") << 0x0_long << -0xb4cd9bd7c2a111a_long << 1;
  QTest::newRow("0 <=> -5000814613328676776") << 0x0_long << -0x456676653709c7a8_long << 1;
  QTest::newRow("0 <=> 782529615168597148") << 0x0_long << 0xadc1a89fa58ec9c_long << -1;
  QTest::newRow("0 <=> 11043925663033853482") << 0x0_long << 0x9943e7e096f4062a_long << -1;
  QTest::newRow("-7691279063574162447 <=> 1") << -0x6abce98ee4bcac0f_long << 0x1_long << -1;
  QTest::newRow("-2568393081554676458 <=> 1") << -0x23a4c3e655a32aea_long << 0x1_long << -1;
  QTest::newRow("-5421762630132937418156037472211371729709213195081971428430 <=> 1")
      << -0xdd1dd7d3065eec8eb0ab3f54a2c6ffeb8e64f17d41586c4e_long << 0x1_long << -1;
  QTest::newRow("-2154227311104837044331604173792821165127153025084184010432 <=> 1")
      << -0x57db2ebc1139381a529de9021fcd2088b8eacc41b53f1ec0_long << 0x1_long << -1;
  QTest::newRow("4733665552309601778 <=> 1") << 0x41b15bbd62eac5f2_long << 0x1_long << 1;
  QTest::newRow("16196223599196378958 <=> 1") << 0xe0c48b8d5ce6174e_long << 0x1_long << 1;
  QTest::newRow("3242575470636183626042424179746605551620401763091468111904 <=> 1")
      << 0x843e1149a879c340d03b776ad957de6b871f156f0c61d020_long << 0x1_long << 1;
  QTest::newRow("3965201371386818058020209582489361103278290161491430096570 <=> 1")
      << 0xa1b6a24b39e0379ee1abe8b70b79e77878af2171da283eba_long << 0x1_long << 1;
  QTest::newRow("-1 <=> -5558155584746757591") << -0x1_long << -0x4d22890e532f1dd7_long << 1;
  QTest::newRow("-1 <=> -2768032858467261447") << -0x1_long << -0x266a0738178cdc07_long << 1;
  QTest::newRow("-1 <=> 14400803201958810575") << -0x1_long << 0xc7d9ee36a51013cf_long << -1;
  QTest::newRow("-1 <=> 12608897776570288368") << -0x1_long << 0xaefbcdb915af48f0_long << -1;
  QTest::newRow("1 <=> -3361799752938480068") << 0x1_long << -0x2ea783104fe4e1c4_long << 1;
  QTest::newRow("1 <=> -16881851429082368349") << 0x1_long << -0xea48626e4d60095d_long << 1;
  QTest::newRow("1 <=> 15117596350379046581") << 0x1_long << 0xd1cc7dc8c215b6b5_long << -1;
  QTest::newRow("1 <=> 11374437385017309790") << 0x1_long << 0x9dda1e898de13a5e_long << -1;
  QTest::newRow("-15802550861889725933 <=> -17519996310470462033") << -0xdb4df0488bfae5ed_long << -0xf32387d1c7bf0a51_long << 1;
  QTest::newRow("-29514290357945752 <=> -8168998513964701567") << -0x68db1738954598_long << -0x715e1cde038f577f_long << 1;
  QTest::newRow("-9077115126708988370 <=> 17338012957909211895") << -0x7df8641d78d069d2_long << 0xf09cfeecab4c5af7_long << -1;
  QTest::newRow("-8641455256469504640 <=> 1702257550520333824") << -0x77ec9dc5784c0280_long << 0x179fa23926fdb600_long << -1;
  QTest::newRow("-4456080103137960380292236065450056855914596649255018445222 <=> -7096399167745696304")
      << -0xb5bba5a51f731548307c51261b10113ba9c96f99884839a6_long << -0x627b7971d9dc2230_long << -1;
  QTest::newRow("-679724834772322472947863205329593006235880829052952019975 <=> -12297618661345978562")
      << -0x1bb8a88d0b3ca7f18b495d6c4c703fd5d65f371c92988407_long << -0xaaa9eb0454bde8c2_long << -1;
  QTest::newRow("-919122845681612597587801505697639378250689366589151276604 <=> 617351449082854099")
      << -0x257c171b2e6ffc5e1d68a1ad1dab0b6483ea1b69a14a6e3c_long << 0x89145df4027fad3_long << -1;
  QTest::newRow("-2441380640958190168897099119665704696696605854897811029917 <=> 13322244851866832405")
      << -0x6391340563e195588d418fec9498cbc498fe23b95454ff9d_long << 0xb8e21f1bc64c8e15_long << -1;
  QTest::newRow("2461991098608332124 <=> -12391851130897436855") << 0x222abfdc28b92d5c_long << -0xabf8b2f2deaa10b7_long << 1;
  QTest::newRow("12868552578163977622 <=> -17845345247251990774") << 0xb2964863aae6ad96_long << -0xf7a766f424a908f6_long << 1;
  QTest::newRow("14520911822428820676 <=> 17974359622326919853") << 0xc984a45e0ea3d4c4_long << 0xf971c0d821eba2ad_long << -1;
  QTest::newRow("16541306025957299490 <=> 17246702073495264264") << 0xe58e8630e6369522_long << 0xef589828adad9c08_long << -1;
  QTest::newRow("4912640252866512994099886737770263691326484331724940290116 <=> -16612338701308658202")
      << 0xc85a5b80514405839b34a784cd41fdc3b9474a82ccbca844_long << -0xe68ae2086bfa021a_long << 1;
  QTest::newRow("274491429500012738331497845608356254163376530788333498139 <=> -2815441823188044774")
      << 0xb31d301889621eae5ca0e5c3a650d1542ab41e26909af1b_long << -0x2712756bdce6cbe6_long << 1;
  QTest::newRow("2129908971080213899335576438077950624848340381917113643587 <=> 9019673550510224836")
      << 0x56dd49889acb5bc2b9c186629b2cd0abaf889bd4b8c67243_long << 0x7d2c514e5025f5c4_long << 1;
  QTest::newRow("615113579394598179356115081459768350709359705802167635312 <=> 2720986979335775146")
      << 0x191615de21dfbd65adc4caad803c3b447d9feb0da08d4d70_long << 0x25c2e33dc5c5a3aa_long << 1;
}

void LongIntTest::test_compare_to()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(int, result);

  LongInt copy (left);
  bool larger = false, larger_equal = false, equal = false, smaller_equal = false, smaller = false, unequal = true;
  LongInt copy_left (left), copy_right (right);
  if (result == 1) {
    larger = true;
    larger_equal = true;
  } else if (result == 0) {
    larger_equal = true;
    equal = true;
    smaller_equal = true;
    unequal = false;
  } else if (result == -1) {
    smaller_equal = true;
    smaller = true;
  } else {
    QFAIL("Invalid result.");
  }

  COMPARE_INTS(left.compare_to(right), result);
  QCOMPARE(left > right, larger);
  QCOMPARE(left >= right, larger_equal);
  QCOMPARE(left == right, equal);
  QCOMPARE(left <= right, smaller_equal);
  QCOMPARE(left < right, smaller);
  QCOMPARE(left != right, unequal);
  QCOMPARE(left, copy_left);
  QCOMPARE(right, copy_right);
}


void LongIntTest::test_bit_or_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 | 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 | -1") << 0x0_long << -0x1_long << -0x1_long;
  QTest::newRow("0 | 1") << 0x0_long << 0x1_long << 0x1_long;
  QTest::newRow("-1 | 0") << -0x1_long << 0x0_long << -0x1_long;
  QTest::newRow("1 | 0") << 0x1_long << 0x0_long << 0x1_long;
  QTest::newRow("-1 | -1") << -0x1_long << -0x1_long << -0x1_long;
  QTest::newRow("-1 | 1") << -0x1_long << 0x1_long << -0x1_long;
  QTest::newRow("1 | -1") << 0x1_long << -0x1_long << -0x1_long;
  QTest::newRow("1 | 1") << 0x1_long << 0x1_long << 0x1_long;
  QTest::newRow("-1513752269862236432 | 0") << -0x1501edab53147110_long << 0x0_long << -0x1501edab53147110_long;
  QTest::newRow("-961692855688273979292237440289324231996006081527521195771 | 0")
      << -0x27388aba04840a361cfc6d7d5acd4711fe1aedc2c707b6fb_long << 0x0_long
      << -0x27388aba04840a361cfc6d7d5acd4711fe1aedc2c707b6fb_long;
  QTest::newRow("7926758222579437890 | 0") << 0x6e01809b0d411142_long << 0x0_long << 0x6e01809b0d411142_long;
  QTest::newRow("2994309165024195076653334719372564832763281233007188929688 | 0")
      << 0x7a1e0bde0cc427743faefc5157d03b7907fe564317a86c98_long << 0x0_long
      << 0x7a1e0bde0cc427743faefc5157d03b7907fe564317a86c98_long;
  QTest::newRow("0 | -7217026051228040664") << 0x0_long << -0x642806f4c62ffdd8_long << -0x642806f4c62ffdd8_long;
  QTest::newRow("0 | -197780156196166383") << 0x0_long << -0x2bea80111b19aef_long << -0x2bea80111b19aef_long;
  QTest::newRow("0 | 18005558344693758173") << 0x0_long << 0xf9e097eabe0ab8dd_long << 0xf9e097eabe0ab8dd_long;
  QTest::newRow("0 | 6684713103912384929") << 0x0_long << 0x5cc4df26a018b9a1_long << 0x5cc4df26a018b9a1_long;
  QTest::newRow("-14490873776256604263 | 1") << -0xc919ecec6ecc5867_long << 0x1_long << -0xc919ecec6ecc5867_long;
  QTest::newRow("-1534418056453462502 | 1") << -0x154b5917b7da99e6_long << 0x1_long << -0x154b5917b7da99e5_long;
  QTest::newRow("-1220846001871930829927027899442763278472057445968337063989 | 1")
      << -0x31ca3a1c3a075766a8412790dcf3e1f85fc9af6e55a25035_long << 0x1_long
      << -0x31ca3a1c3a075766a8412790dcf3e1f85fc9af6e55a25035_long;
  QTest::newRow("-1329452238804445027788332296911499362484351151353463794413 | 1")
      << -0x3638210712bb7b41a6e0060b12a3e27f4733344157eb6aed_long << 0x1_long
      << -0x3638210712bb7b41a6e0060b12a3e27f4733344157eb6aed_long;
  QTest::newRow("13887307140294236653 | 1") << 0xc0b9a04417fbd9ed_long << 0x1_long << 0xc0b9a04417fbd9ed_long;
  QTest::newRow("8720413871705987876 | 1") << 0x79052236ad6c9b24_long << 0x1_long << 0x79052236ad6c9b25_long;
  QTest::newRow("1178965297978588666860452020764134391917262056223168555442 | 1")
      << 0x3014f8d7c5b4b16d4ff3e7114512073daa7c7e5862b869b2_long << 0x1_long
      << 0x3014f8d7c5b4b16d4ff3e7114512073daa7c7e5862b869b3_long;
  QTest::newRow("176203905755484833996403931790502090897700804500919625355 | 1")
      << 0x72fa794c1e64320142862180dfb34863d59675b35f3268b_long << 0x1_long
      << 0x72fa794c1e64320142862180dfb34863d59675b35f3268b_long;
  QTest::newRow("-1 | -13016322576368406143") << -0x1_long << -0xb4a3446b76560e7f_long << -0x1_long;
  QTest::newRow("-1 | -3288923298958778602") << -0x1_long << -0x2da49a509ff1a0ea_long << -0x1_long;
  QTest::newRow("-1 | 13864270157240718931") << -0x1_long << 0xc067c8408061d653_long << -0x1_long;
  QTest::newRow("-1 | 16656188996993461510") << -0x1_long << 0xe726aba4fd90ad06_long << -0x1_long;
  QTest::newRow("1 | -6354380651290747071") << 0x1_long << -0x582f4b890fcce0bf_long << -0x582f4b890fcce0bf_long;
  QTest::newRow("1 | -6243761615610786753") << 0x1_long << -0x56a64c1bc8b333c1_long << -0x56a64c1bc8b333c1_long;
  QTest::newRow("1 | 17726042933535656861") << 0x1_long << 0xf5ff8e21a6b74b9d_long << 0xf5ff8e21a6b74b9d_long;
  QTest::newRow("1 | 17777996189732135794") << 0x1_long << 0xf6b82157bb3b6372_long << 0xf6b82157bb3b6373_long;
  QTest::newRow("-18164793349584085364 | -16760652162561077485") << -0xfc164f4f6c566174_long << -0xe899cc571155f0ed_long << -0xe8104c4700546061_long;
  QTest::newRow("-8038255442083318229 | -1976860345254617871") << -0x6f8d9ebc6f3a09d5_long << -0x1b6f38029975230f_long << -0xb0d180009300105_long;
  QTest::newRow("-16745866695789463975 | 13941182337498350574") << -0xe8654509529349a7_long << 0xc1790778ef8a03ee_long << -0x2804400110114801_long;
  QTest::newRow("-5666185305307566326 | 5262727277806773673") << -0x4ea25583b26550f6_long << 0x4908f693776e65a9_long << -0x6a2010080011055_long;
  QTest::newRow("-1298097609327412718665317919066176127895080491459234496805 | -9388879653048524460")
      << -0x34f0c57affc7086df544f98f6ff18566847ec7be2b1c0125_long << -0x824c004cced99eac_long << -0x804c000c0a180021_long;
  QTest::newRow("-5677281777649574796582382906590801756677540076388954978409 | -15455917722311735476")
      << -0xe789966271f3bc41a9753570aee23d8948d016425030b869_long << -0xd67e73478c0e38b4_long << -0x4050124200003821_long;
  QTest::newRow("-3327358376282596791630370245135778610409013295843156933098 | 12900441293769234795")
      << -0x87b33e0bc3e3d4b61ad85d6844dead8986d9a9cf825fb9ea_long << 0xb3079301d8e5596b_long
      << -0x87b33e0bc3e3d4b61ad85d6844dead8904d828ce021aa081_long;
  QTest::newRow("-3120801029522163258852907947883637516964111209804782371781 | 11469793851870106194")
      << -0x7f46aedbe296e531fa62c296940ccadf18ff35a811a803c5_long << 0x9f2ce4bd1bad5252_long
      << -0x7f46aedbe296e531fa62c296940ccadf00d3110000000185_long;
  QTest::newRow("9376087387422292537 | -4028524126384856104") << 0x821e8dcd5e537a39_long << -0x37e8315952429c28_long << -0x35e0301000008407_long;
  QTest::newRow("3164877931195684390 | -15747892495654949067") << 0x2bebe7b5ce645626_long << -0xda8bc0c9f48d90cb_long << -0xd0000048308980c9_long;
  QTest::newRow("6510279552422757491 | 17937718144074300298") << 0x5a5928c28ea5c473_long << 0xf8ef939d2aa0bb8a_long << 0xfaffbbdfaea5fffb_long;
  QTest::newRow("13740499608829717980 | 16764005136667785626") << 0xbeb00f980cb06ddc_long << 0xe8a5b5da2fe8399a_long << 0xfeb5bfda2ff87dde_long;
  QTest::newRow("4945709982571149621765108569541389279182556202410245529456 | -1307590135173085855")
      << 0xc9b39f1b969bd51f3c322a5da110fb634791a47ffc5e9f70_long << -0x12257e4ccecbfa9f_long << -0x10245a000281608f_long;
  QTest::newRow("89504406057063752803418039326930473000288485072595713493 | -17021106151645260930")
      << 0x3a67837c8c22f730c393f34bd9875ca8d3e67438ab1fdd5_long << -0xec371ddcfd082c82_long << -0x6001189c75080001_long;
  QTest::newRow("5091478222477887136588090805619339066401840535380754234724 | 13101175123220161494")
      << 0xcfa58350b3b066e716aa1857efc50e660f9f28b6bae4fd64_long << 0xb5d0b95c8fb8e3d6_long
      << 0xcfa58350b3b066e716aa1857efc50e66bfdfb9febffcfff6_long;
  QTest::newRow("5122889941674279890303819032825610863083250782157665607158 | 10159032796520571648")
      << 0xd0ed777325a70b17c540eb59c0519aa73aa2490b3c761df6_long << 0x8cfc2280ea26e300_long
      << 0xd0ed777325a70b17c540eb59c0519aa7befe6b8bfe76fff6_long;
}

void LongIntTest::test_bit_or()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left | right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy |= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_bit_xor_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 ^ 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 ^ -1") << 0x0_long << -0x1_long << -0x1_long;
  QTest::newRow("0 ^ 1") << 0x0_long << 0x1_long << 0x1_long;
  QTest::newRow("-1 ^ 0") << -0x1_long << 0x0_long << -0x1_long;
  QTest::newRow("1 ^ 0") << 0x1_long << 0x0_long << 0x1_long;
  QTest::newRow("-1 ^ -1") << -0x1_long << -0x1_long << 0x0_long;
  QTest::newRow("-1 ^ 1") << -0x1_long << 0x1_long << -0x2_long;
  QTest::newRow("1 ^ -1") << 0x1_long << -0x1_long << -0x2_long;
  QTest::newRow("1 ^ 1") << 0x1_long << 0x1_long << 0x0_long;
  QTest::newRow("-2322458059981484600 ^ 0") << -0x203b074cf6f07238_long << 0x0_long << -0x203b074cf6f07238_long;
  QTest::newRow("-1896631976267829055204650445947993945063292857085871583525 ^ 0")
      << -0x4d59c303a2ae74be251e580612edb9c482e26679c490f125_long << 0x0_long
      << -0x4d59c303a2ae74be251e580612edb9c482e26679c490f125_long;
  QTest::newRow("1131645179248315013 ^ 0") << 0xfb4694b78e10a85_long << 0x0_long << 0xfb4694b78e10a85_long;
  QTest::newRow("5725353381442249042749904941258020165520684307766738926558 ^ 0")
      << 0xe97f7a78817d82b147a58564cf550932954d1bddedc3bbde_long << 0x0_long
      << 0xe97f7a78817d82b147a58564cf550932954d1bddedc3bbde_long;
  QTest::newRow("0 ^ -8588324650653409363") << 0x0_long << -0x772fdbc451ed6053_long << -0x772fdbc451ed6053_long;
  QTest::newRow("0 ^ -5822559175832093046") << 0x0_long << -0x50cde2b89f29c176_long << -0x50cde2b89f29c176_long;
  QTest::newRow("0 ^ 18231890517955213835") << 0x0_long << 0xfd04afd452887a0b_long << 0xfd04afd452887a0b_long;
  QTest::newRow("0 ^ 9743709268829668812") << 0x0_long << 0x87389bf4a34605cc_long << 0x87389bf4a34605cc_long;
  QTest::newRow("-14070479737088862197 ^ 1") << -0xc34462c5b48367f5_long << 0x1_long << -0xc34462c5b48367f6_long;
  QTest::newRow("-17016631734976696793 ^ 1") << -0xec273867acecd1d9_long << 0x1_long << -0xec273867acecd1da_long;
  QTest::newRow("-3029576311626529254090576422282728023606499623867772370186 ^ 1")
      << -0x7b8e40a6f9a32a197446cb4fc767ebe07dd34f6edef8fd0a_long << 0x1_long
      << -0x7b8e40a6f9a32a197446cb4fc767ebe07dd34f6edef8fd09_long;
  QTest::newRow("-5880402310567814257364163617443825576112705468273950551105 ^ 1")
      << -0xefd243c6de5917aefa83a6c5d820d12a49db4cda01e16c41_long << 0x1_long
      << -0xefd243c6de5917aefa83a6c5d820d12a49db4cda01e16c42_long;
  QTest::newRow("9768186921666602764 ^ 1") << 0x878f92404d8de70c_long << 0x1_long << 0x878f92404d8de70d_long;
  QTest::newRow("7390701933930211424 ^ 1") << 0x66910c4054b3e860_long << 0x1_long << 0x66910c4054b3e861_long;
  QTest::newRow("871823896053091882586778380316835585636878476628735671570 ^ 1")
      << 0x238e44248d9c0d1f363764cd56e40311855ecf520255bd12_long << 0x1_long
      << 0x238e44248d9c0d1f363764cd56e40311855ecf520255bd13_long;
  QTest::newRow("2142681843925728160912214805898120670564144054392758753754 ^ 1")
      << 0x5762a46adab949aa7fd5ff993227989d8db7725ef3c859da_long << 0x1_long
      << 0x5762a46adab949aa7fd5ff993227989d8db7725ef3c859db_long;
  QTest::newRow("-1 ^ -15402070353210537714") << -0x1_long << -0xd5bf2561f0b076f2_long << 0xd5bf2561f0b076f1_long;
  QTest::newRow("-1 ^ -14817584282335118241") << -0x1_long << -0xcda2a265d9ff03a1_long << 0xcda2a265d9ff03a0_long;
  QTest::newRow("-1 ^ 7648467904314879468") << -0x1_long << 0x6a24d10920aa2dec_long << -0x6a24d10920aa2ded_long;
  QTest::newRow("-1 ^ 11446485842469342371") << -0x1_long << 0x9eda163a46ec4ca3_long << -0x9eda163a46ec4ca4_long;
  QTest::newRow("1 ^ -8930702224019364189") << 0x1_long << -0x7bf03a5b1977195d_long << -0x7bf03a5b1977195e_long;
  QTest::newRow("1 ^ -17458040692640515322") << 0x1_long << -0xf2476b83672704fa_long << -0xf2476b83672704f9_long;
  QTest::newRow("1 ^ 6094378669288316138") << 0x1_long << 0x5493951c3da5dcea_long << 0x5493951c3da5dceb_long;
  QTest::newRow("1 ^ 13375922824412605575") << 0x1_long << 0xb9a0d2f0ac272c87_long << 0xb9a0d2f0ac272c86_long;
  QTest::newRow("-9684921143365601809 ^ -12996802927390394802") << -0x8667c0778bfa0a11_long << -0xb45deb6706dc89b2_long << 0x323a2b108d2683a1_long;
  QTest::newRow("-2829750010533300418 ^ -8396024998697303484") << -0x27454aa454fec8c2_long << -0x7484ac4094a6fdbc_long << 0x53c1e6e4c058357a_long;
  QTest::newRow("-8317629008037446707 ^ 11405335836051262748") << -0x736e27839d8e8433_long << 0x9e47e483cbde4d1c_long << -0xed29c3005650c92f_long;
  QTest::newRow("-7046176896870382245 ^ 15599501888043514203") << -0x61c90c8e3285faa5_long << 0xd87c905145de795b_long << -0xb9b59cdf775b8400_long;
  QTest::newRow("-1747800931992082619483293498120060665204786497508194250053 ^ -8997624864160744637")
      << -0x4747e4a6bb3fa947d292040e0b48537c22a7a48abdf5ed45_long << -0x7cddfc247a8604bd_long
      << 0x4747e4a6bb3fa947d292040e0b48537c5e7a58aec773e9f8_long;
  QTest::newRow("-2946848754472109343939334698868675444022114423078971001089 ^ -7182658228130623326")
      << -0x782e895b5fe88918a5774c1b1692d42cfa349fce43444901_long << -0x63aded9a66c32f5e_long
      << 0x782e895b5fe88918a5774c1b1692d42c999972542587665d_long;
  QTest::newRow("-2641969483555981052919792132729859350868675147955996162671 ^ 6766961531756532288")
      << -0x6bbf72cd0080d76bf141cfa462fe85bfc748f41bf8cb7a6f_long << 0x5de913a90514d240_long
      << -0x6bbf72cd0080d76bf141cfa462fe85bf9aa1e7b2fddfa82f_long;
  QTest::newRow("-4614598950561492140596554346780924823301397159766651794619 ^ 7174821791863390765")
      << -0xbc32a939ee1767896eba340a3d58172cd604dbd11b4f74bb_long << 0x63921667e6bfc22d_long
      << -0xbc32a939ee1767896eba340a3d58172cb596cdb6fdf0b698_long;
  QTest::newRow("8884829549486613221 ^ -11899904231988728872") << 0x7b4d4166c30b22e5_long << -0xa524f3d9c0db1428_long << -0xde69b2bf03d036c3_long;
  QTest::newRow("10861648113032065833 ^ -11765011739347736085") << 0x96bc53694c917329_long << -0xa345b7d7de1f5615_long << -0x35f9e4be928e253e_long;
  QTest::newRow("16080573923226179581 ^ 294521159383862380") << 0xdf29acc8de4e57fd_long << 0x416596f1be94c6c_long << 0xdb3ff5a7c5a71b91_long;
  QTest::newRow("8929533745476251742 ^ 14963144568719059102") << 0x7bec13a17cf9b05e_long << 0xcfa7c4b50550a89e_long << 0xb44bd71479a918c0_long;
  QTest::newRow("1188863414509006511213337419762496164100346980301651349160 ^ -7548380912556720666")
      << 0x307c502dee6dbc9530d59d6cc15cd8886a5ce3c2398c8ea8_long << -0x68c13c726a48421a_long
      << -0x307c502dee6dbc9530d59d6cc15cd888029ddfb053c4ccb2_long;
  QTest::newRow("3666585888864821313465129442388184788865293146298766330586 ^ -18423933146794902100")
      << 0x9588f15ecaaa31249d54574dd436f7d31c23e14322940ada_long << -0xffaef59534414254_long
      << -0x9588f15ecaaa31249d54574dd436f7d3e38d14d616d5488a_long;
  QTest::newRow("1959474806459829345318626773905111798304176924032785763981 ^ 15609039540176127725")
      << 0x4fe9df1ceeea76d64b46e1c97a2a733febbfc51b62ecce8d_long << 0xd89e72c2f53986ed_long
      << 0x4fe9df1ceeea76d64b46e1c97a2a733f3321b7d997d54860_long;
  QTest::newRow("431793371667438198585071775767146419526035141950761849162 ^ 4375726216170828085")
      << 0x119c2215f9e6ea7e64548d9ee9f0f4c49f5699e6fd37d14a_long << 0x3cb9b3cf5d39f135_long
      << 0x119c2215f9e6ea7e64548d9ee9f0f4c4a3ef2a29a00e207f_long;
}

void LongIntTest::test_bit_xor()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left ^ right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy ^= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_bit_and_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 & 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 & -1") << 0x0_long << -0x1_long << 0x0_long;
  QTest::newRow("0 & 1") << 0x0_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 & 0") << -0x1_long << 0x0_long << 0x0_long;
  QTest::newRow("1 & 0") << 0x1_long << 0x0_long << 0x0_long;
  QTest::newRow("-1 & -1") << -0x1_long << -0x1_long << -0x1_long;
  QTest::newRow("-1 & 1") << -0x1_long << 0x1_long << 0x1_long;
  QTest::newRow("1 & -1") << 0x1_long << -0x1_long << 0x1_long;
  QTest::newRow("1 & 1") << 0x1_long << 0x1_long << 0x1_long;
  QTest::newRow("-1912715914555451627 & 0") << -0x1a8b54fd835068eb_long << 0x0_long << 0x0_long;
  QTest::newRow("-4903380848746135911272151144358416820639533825022622498932 & 0")
      << -0xc7f9af4aec75b550ec8bcfb7345a5a28a6f95bbf98bd0074_long << 0x0_long << 0x0_long;
  QTest::newRow("6044823777151326951 & 0") << 0x53e38732cef09ae7_long << 0x0_long << 0x0_long;
  QTest::newRow("4989166946116577470704717217270428633951378288883071796224 & 0")
      << 0xcb795558a9a9840ac83de37b04e4a3e176b47a7a8c154400_long << 0x0_long << 0x0_long;
  QTest::newRow("0 & -143934627272232688") << 0x0_long << -0x1ff5bc7e9708ef0_long << 0x0_long;
  QTest::newRow("0 & -13989350059514548658") << 0x0_long << -0xc22427c2a7f451b2_long << 0x0_long;
  QTest::newRow("0 & 15890879052135069871") << 0x0_long << 0xdc87be4def34f8af_long << 0x0_long;
  QTest::newRow("0 & 13340239273642469522") << 0x0_long << 0xb9220cf0942ca892_long << 0x0_long;
  QTest::newRow("-15758306387835159468 & 1") << -0xdab0c02b2caf03ac_long << 0x1_long << 0x0_long;
  QTest::newRow("-17164278698880046318 & 1") << -0xee33c489508c94ee_long << 0x1_long << 0x0_long;
  QTest::newRow("-2306304595203809779413599584378795847376036439572040513363 & 1")
      << -0x5e0ef188648bc2acf4bf899c0ff30e108b897a1bfc7df753_long << 0x1_long << 0x1_long;
  QTest::newRow("-4866900189233492888423849274342889423581841591541783334036 & 1")
      << -0xc67ccf12c561c4151cab7002791eceac2cdbed9ea74c0c94_long << 0x1_long << 0x0_long;
  QTest::newRow("10543047986915757497 & 1") << 0x92506e48de02cdb9_long << 0x1_long << 0x1_long;
  QTest::newRow("13116287971899744084 & 1") << 0xb6066a6ad8d01f54_long << 0x1_long << 0x0_long;
  QTest::newRow("5174377860448625714061126203383015877684421090769444211408 & 1")
      << 0xd307068ac65fbd06c04d6fdaae32f82bcdd39b3a133b0ad0_long << 0x1_long << 0x0_long;
  QTest::newRow("515841898829473843635243846372538173669137816504028331567 & 1")
      << 0x1509a405ef04758d66a1abcd854a9ea03ce1f448333f7e2f_long << 0x1_long << 0x1_long;
  QTest::newRow("-1 & -12066562273037303048") << -0x1_long << -0xa7750a74b884bd08_long << -0xa7750a74b884bd08_long;
  QTest::newRow("-1 & -8647107235825782155") << -0x1_long << -0x7800b237761b0d8b_long << -0x7800b237761b0d8b_long;
  QTest::newRow("-1 & 588071426964066188") << -0x1_long << 0x8293fd8dac00f8c_long << 0x8293fd8dac00f8c_long;
  QTest::newRow("-1 & 18218457333557518854") << -0x1_long << 0xfcd4f66b5a4e6206_long << 0xfcd4f66b5a4e6206_long;
  QTest::newRow("1 & -2042985429558616859") << 0x1_long << -0x1c5a246c8a23e31b_long << 0x1_long;
  QTest::newRow("1 & -11884874504166134867") << 0x1_long << -0xa4ef8e648ceb5453_long << 0x1_long;
  QTest::newRow("1 & 9226773452740141318") << 0x1_long << 0x800c1591d994a106_long << 0x0_long;
  QTest::newRow("1 & 11155457295938467144") << 0x1_long << 0x9ad0254e7773b548_long << 0x0_long;
  QTest::newRow("-17339754178082178095 & -3096872964423071358") << -0xf0a32e8e152f042f_long << -0x2afa4d8d9ef2b67e_long << -0xfafb6f8f9fffb680_long;
  QTest::newRow("-17117062223099728782 & -7971750894293678417") << -0xed8c0566de1e138e_long << -0x6ea15933c446f951_long << -0xefad5d77de5efbde_long;
  QTest::newRow("-139657039818077175 & 1649091067830597762") << -0x1f0295678bd33f7_long << 0x16e2bf96c44ff882_long << 0x160296808442c800_long;
  QTest::newRow("-7521726015190568666 & 14796517896179911058") << -0x686289f5813f8eda_long << 0xcd57caa19a838992_long << 0x851542001a800102_long;
  QTest::newRow("-3691343417155597416389019533032159017017399167494516410496 & -10622951902039497036")
      << -0x968b6c6b0f75291579528c4d9f76e30d3e4f0dc3d1cc8880_long << -0x936c4e78db1fd94c_long
      << -0x968b6c6b0f75291579528c4d9f76e30dbf6f4ffbdbdfd980_long;
  QTest::newRow("-3772245897093917920869931253772831660928372147237862324428 & -9342469158364967197")
      << -0x99d815b627a9924dc851ec174e970b41693c358a2aed38cc_long << -0x81a71e337562f11d_long
      << -0x99d815b627a9924dc851ec174e970b41e9bf3fbb7feff9e0_long;
  QTest::newRow("-1892380264468708543074644698443261569884180458560219600887 & 15343736765235969510")
      << -0x4d2d5f305ed2f587f34ef47c01afd41192b750e9ae8157f7_long << 0xd4efe74b1afdbde6_long << 0x4448a702107ca800_long;
  QTest::newRow("-1722033192306336268619863468046510558122930762072306188533 & 1898464943326126008")
      << -0x463add8bc6e767b24267907ae8f4a39af0195f10d69f80f5_long << 0x1a58b3ceb57c5fb8_long << 0xa40a0ce21605f08_long;
  QTest::newRow("11874382166297964156 & -5612166025372340100") << 0xa4ca47aac56c6e7c_long << -0x4de26b43fad58f84_long << 0xa00804a80528607c_long;
  QTest::newRow("5647851748409180178 & -1291331397510627070") << 0x4e61333dd7ff8012_long << -0x11ebbb1073edfefe_long << 0x4e00002d84120002_long;
  QTest::newRow("13073939776901443888 & 10097125068827217387") << 0xb56ff6f5590f7130_long << 0x8c2031c0d4234deb_long << 0x842030c050034120_long;
  QTest::newRow("14042918377664665591 & 15702934522110178597") << 0xc2e277dca681d7f7_long << 0xd9ec07c009987525_long << 0xc0e007c000805525_long;
  QTest::newRow("1157605068992568129089056091592453575095533758477343803217 & -17262632457898345776")
      << 0x2f35f5fa043d1bb9d2013060674f2314e183d377226a4751_long << -0xef9130c25528c530_long
      << 0x2f35f5fa043d1bb9d2013060674f23140002c33522420250_long;
  QTest::newRow("624877961846857728784995762621825558999030993846821641558 & -885160566653772405")
      << 0x197c07c3b8cd8c3aae3a496a5e53e2e0eb217ac5e702dd56_long << -0xc48b8d87894e275_long
      << 0x197c07c3b8cd8c3aae3a496a5e53e2e0e321420587021d02_long;
  QTest::newRow("4156142822023091185452752588814144329053005806578814564097 & 5127050139647444594")
      << 0xa98027dd63f236cacb8a769c05e4f4f2225a79097eee3701_long << 0x4726f0f00f4d8672_long << 0x20270000e4c0600_long;
  QTest::newRow("2458558323506454613705767676177850304970214166655719518774 & 4875837595141049069")
      << 0x64448becbdd2eedbefaac5746c617a99b4c35b54e5cd3236_long << 0x43aa7475a0e08aed_long << 0x825054a0c00224_long;
}

void LongIntTest::test_bit_and()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left & right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy &= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_modulo_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 % -1") << 0x0_long << -0x1_long << 0x0_long;
  QTest::newRow("0 % 1") << 0x0_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 % -1") << -0x1_long << -0x1_long << 0x0_long;
  QTest::newRow("-1 % 1") << -0x1_long << 0x1_long << 0x0_long;
  QTest::newRow("1 % -1") << 0x1_long << -0x1_long << 0x0_long;
  QTest::newRow("1 % 1") << 0x1_long << 0x1_long << 0x0_long;
  QTest::newRow("0 % -1770699962376953945") << 0x0_long << -0x1892ca3bf546a059_long << 0x0_long;
  QTest::newRow("0 % -432454144280382406") << 0x0_long << -0x60062c0c37a4bc6_long << 0x0_long;
  QTest::newRow("0 % 6332855643148653102") << 0x0_long << 0x57e2d2a78fb4122e_long << 0x0_long;
  QTest::newRow("0 % 15499707000004638657") << 0x0_long << 0xd71a056541e977c1_long << 0x0_long;
  QTest::newRow("-15226572982018307820 % 1") << -0xd34fa7740bc2f6ec_long << 0x1_long << 0x0_long;
  QTest::newRow("-4466748429463462610 % 1") << -0x3dfd1407df3422d2_long << 0x1_long << 0x0_long;
  QTest::newRow("-14983788357806466688 % 1") << -0xcff11c1fb8b02680_long << 0x1_long << 0x0_long;
  QTest::newRow("-7829500230553723181 % 1") << -0x6ca7f8fa2afe612d_long << 0x1_long << 0x0_long;
  QTest::newRow("1984053590226978310 % 1") << 0x1b88c63a74d14606_long << 0x1_long << 0x0_long;
  QTest::newRow("8044685094384947764 % 1") << 0x6fa4767884b1d234_long << 0x1_long << 0x0_long;
  QTest::newRow("4679040199854654419 % 1") << 0x40ef4a456a1c03d3_long << 0x1_long << 0x0_long;
  QTest::newRow("1629599025353785789 % 1") << 0x169d7fadf88901bd_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 % -2839331525391050801") << -0x1_long << -0x276754fa9a806831_long << -0x1_long;
  QTest::newRow("-1 % -7061561616767950339") << -0x1_long << -0x61ffb4e06efc9e03_long << -0x1_long;
  QTest::newRow("-1 % 10827053483569273096") << -0x1_long << 0x96416bc7744d5908_long << -0x1_long;
  QTest::newRow("-1 % 11972309267550395185") << -0x1_long << 0xa6262fd8c9755b31_long << -0x1_long;
  QTest::newRow("1 % -14936756531606012241") << 0x1_long << -0xcf4a04ed5adf4151_long << 0x1_long;
  QTest::newRow("1 % -8426046757515054156") << 0x1_long << -0x74ef54e202844c4c_long << 0x1_long;
  QTest::newRow("1 % 17115701519389365515") << 0x1_long << 0xed872fd958d1150b_long << 0x1_long;
  QTest::newRow("1 % 15520030102965714448") << 0x1_long << 0xd762392666a3fe10_long << 0x1_long;
  QTest::newRow("-16830114891553137642 % -9413712708520043937") << -0xe9909452f80963ea_long << -0x82a439d518eae5a1_long << -0x66ec5a7ddf1e7e49_long;
  QTest::newRow("-1128449249929184036 % -8529742136690190532") << -0xfa90e9d3115c324_long << -0x765fbb47e319a8c4_long << -0xfa90e9d3115c324_long;
  QTest::newRow("-14492578583748965634 % 1667378934465188624") << -0xc91ffb6fdbca7502_long << 0x1723b84e86c45310_long << -0x100238fba5a7dc82_long;
  QTest::newRow("-10821407277527261729 % 16207735929209848938") << -0x962d5c95aad6e221_long << 0xe0ed71f491e3846a_long << -0x962d5c95aad6e221_long;
  QTest::newRow("-2379758429185971365 % -3148225425513121651") << -0x210699aecedf14a5_long << -0x2bb0be5830900773_long << -0x210699aecedf14a5_long;
  QTest::newRow("-11418160897819241017 % -17665237460347954130") << -0x9e7574d72ec56a39_long << -0xf52787e030f6a3d2_long << -0x9e7574d72ec56a39_long;
  QTest::newRow("-11254226827500148899 % 1710079522703265425") << -0x9c2f0bac12d158a3_long << 0x17bb6c43f865ce91_long << -0xdca8214406e813d_long;
  QTest::newRow("-13673195848393563170 % 2795813774844883375") << -0xbdc0f32e2fd81c22_long << 0x26ccb9d0bbc5f1af_long << -0x228e0beb40c05566_long;
  QTest::newRow("14425781016153761292 % -14899321289713038819") << 0xc832ab67336b260c_long << -0xcec505c5e3c2b5e3_long << 0xc832ab67336b260c_long;
  QTest::newRow("8087751773054360986 % -5532036976702077652") << 0x703d77630870dd9a_long << -0x4cc5be5200a73ad4_long << 0x2377b91107c9a2c6_long;
  QTest::newRow("17229292890409546163 % 8904081404502081103") << 0xef1abe99600631b3_long << 0x7b91a6dc8e81fe4f_long << 0x738917bcd1843364_long;
  QTest::newRow("299338603527077321 % 2628707344466009440") << 0x42776dfbacafdc9_long << 0x247b0b66fd5b5d60_long << 0x42776dfbacafdc9_long;
  QTest::newRow("2692500227126619133 % -18016035563014006154") << 0x255daeb0eb8a6bfd_long << -0xfa05d0e43a41258a_long << 0x255daeb0eb8a6bfd_long;
  QTest::newRow("10349037015764033319 % -4575638672285811207") << 0x8f9f2a5593fbdf27_long << -0x3f7fef213222c207_long << 0x109f4c132fb65b19_long;
  QTest::newRow("125116328761128749 % 11119355686727553504") << 0x1bc80a35b68772d_long << 0x9a4fe3158e9d91e0_long << 0x1bc80a35b68772d_long;
  QTest::newRow("696499927083889104 % 15689275763720275250") << 0x9aa76fe53ebb1d0_long << 0xd9bb812e87b14532_long << 0x9aa76fe53ebb1d0_long;
}

void LongIntTest::test_modulo()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left % right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy %= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_divided_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 / -1") << 0x0_long << -0x1_long << 0x0_long;
  QTest::newRow("0 / 1") << 0x0_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 / -1") << -0x1_long << -0x1_long << 0x1_long;
  QTest::newRow("-1 / 1") << -0x1_long << 0x1_long << -0x1_long;
  QTest::newRow("1 / -1") << 0x1_long << -0x1_long << -0x1_long;
  QTest::newRow("1 / 1") << 0x1_long << 0x1_long << 0x1_long;
  QTest::newRow("0 / -3074943158447226545") << 0x0_long << -0x2aac6482c7c3beb1_long << 0x0_long;
  QTest::newRow("0 / -17626118831199672396") << 0x0_long << -0xf49c8db0967ad84c_long << 0x0_long;
  QTest::newRow("0 / 13475306033619708001") << 0x0_long << 0xbb01e7713d94a861_long << 0x0_long;
  QTest::newRow("0 / 1858048287010904540") << 0x0_long << 0x19c91d129aced9dc_long << 0x0_long;
  QTest::newRow("-5827341833324120222 / 1") << -0x50dee085d80ec89e_long << 0x1_long << -0x50dee085d80ec89e_long;
  QTest::newRow("-6808061765059539919 / 1") << -0x5e7b181acb4af3cf_long << 0x1_long << -0x5e7b181acb4af3cf_long;
  QTest::newRow("-11158607295172380974 / 1") << -0x9adb5636d0d5092e_long << 0x1_long << -0x9adb5636d0d5092e_long;
  QTest::newRow("-2084579882232457912 / 1") << -0x1cedea5bba642ab8_long << 0x1_long << -0x1cedea5bba642ab8_long;
  QTest::newRow("3007740963627857344 / 1") << 0x29bda478816df5c0_long << 0x1_long << 0x29bda478816df5c0_long;
  QTest::newRow("13714370475335222215 / 1") << 0xbe533b49147603c7_long << 0x1_long << 0xbe533b49147603c7_long;
  QTest::newRow("1163342445083872940 / 1") << 0x102505ca475bceac_long << 0x1_long << 0x102505ca475bceac_long;
  QTest::newRow("12755075111551408132 / 1") << 0xb103213c13729804_long << 0x1_long << 0xb103213c13729804_long;
  QTest::newRow("-1 / -10027291932299658409") << -0x1_long << -0x8b2818e2b3dc84a9_long << 0x0_long;
  QTest::newRow("-1 / -2308239925187694074") << -0x1_long << -0x200883fb7d2fcdfa_long << 0x0_long;
  QTest::newRow("-1 / 17792643336539477896") << -0x1_long << 0xf6ec2ad859a81788_long << 0x0_long;
  QTest::newRow("-1 / 11757193241109165186") << -0x1_long << 0xa329f0f5e3ef7482_long << 0x0_long;
  QTest::newRow("1 / -6496746923891164102") << 0x1_long << -0x5a2914e7f22503c6_long << 0x0_long;
  QTest::newRow("1 / -2000760906572752667") << 0x1_long << -0x1bc42171acc1e71b_long << 0x0_long;
  QTest::newRow("1 / 5502590471537966771") << 0x1_long << 0x4c5d20e140783eb3_long << 0x0_long;
  QTest::newRow("1 / 15604141115302508180") << 0x1_long << 0xd88d0bab8aac7694_long << 0x0_long;
  QTest::newRow("-8213179287447441383 / -2277367988664973050") << -0x71fb130bf0e68fe7_long << -0x1f9ad61ea338b6fa_long << 0x3_long;
  QTest::newRow("-295561594188835880 / -8036116442973935392") << -0x41a0bb436dfac28_long << -0x6f860553e5231720_long << 0x0_long;
  QTest::newRow("-38504348132942816 / 5345436829636509993") << -0x88cb8028c5a3e0_long << 0x4a2ece79a7c64129_long << 0x0_long;
  QTest::newRow("-7792746904351222046 / 771769486344253427") << -0x6c2566059261291e_long << 0xab5e0424208eff3_long << -0xa_long;
  QTest::newRow("-16640485349910033280 / -14800884909681204581") << -0xe6eee142bb7ab380_long << -0xcd674e682afcdd65_long << 0x1_long;
  QTest::newRow("-9018666583340998975 / -15432995641175290808") << -0x7d28bd797fb9e13f_long << -0xd62d03c4a467b3b8_long << 0x0_long;
  QTest::newRow("-6777886460282596243 / 16035841718884140819") << -0x5e0fe3d32912eb93_long << 0xde8ac114f07a8713_long << 0x0_long;
  QTest::newRow("-16262086609407564796 / 2982982520934674840") << -0xe1ae899c6c5fdbfc_long << 0x2965aecc5b82b198_long << -0x5_long;
  QTest::newRow("8920276116663529670 / -626517183022779726") << 0x7bcb2fddd02170c6_long << -0x8b1d60efbc04d4e_long << -0xe_long;
  QTest::newRow("13309069148582039058 / -8555159930911129412") << 0xb8b34fe04c57ce12_long << -0x76ba08a1469cff44_long << -0x1_long;
  QTest::newRow("17742080842682787877 / 10564013294881505843") << 0xf63888865c5ee825_long << 0x929aea1f03ea8233_long << 0x1_long;
  QTest::newRow("16811679222681944525 / 1287539949469001040") << 0xe94f152e51c5c1cd_long << 0x11de42c32a396550_long << 0xd_long;
  QTest::newRow("10410632369900552781 / -7327723259554274968") << 0x9079fefb871b024d_long << -0x65b14d7b0a199e98_long << -0x1_long;
  QTest::newRow("8098610272053270985 / -10712349943931015157") << 0x70640b22581099c9_long << -0x94a9e9847daf0ff5_long << 0x0_long;
  QTest::newRow("4786873513753124483 / 12555690709199014623") << 0x426e64194bfb1e83_long << 0xae3ec62d577acadf_long << 0x0_long;
  QTest::newRow("6983989026414007909 / 15831584432522930855") << 0x60ec1d044aa21665_long << 0xdbb516297c222aa7_long << 0x0_long;
}

void LongIntTest::test_divided()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left / right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy /= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_times_data()
{
  cout.flags(ios::hex);
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<LongInt>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 * 0") << 0x0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 * -1") << 0x0_long << -0x1_long << 0x0_long;
  QTest::newRow("0 * 1") << 0x0_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 * 0") << -0x1_long << 0x0_long << 0x0_long;
  QTest::newRow("1 * 0") << 0x1_long << 0x0_long << 0x0_long;
  QTest::newRow("-1 * -1") << -0x1_long << -0x1_long << 0x1_long;
  QTest::newRow("-1 * 1") << -0x1_long << 0x1_long << -0x1_long;
  QTest::newRow("1 * -1") << 0x1_long << -0x1_long << -0x1_long;
  QTest::newRow("1 * 1") << 0x1_long << 0x1_long << 0x1_long;
  QTest::newRow("-17605740059941135885 * 0") << -0xf454274e28a7e60d_long << 0x0_long << 0x0_long;
  QTest::newRow("-236176464879982596512777125579799828878 * 0") << -0xb1adeebe08b0a1c87081ba6e3456998e_long << 0x0_long << 0x0_long;
  QTest::newRow("-788526957195232555430820884383799809867111981406111031473 * 0")
      << -0x20289b062e8ccdfc1baad30fdc10e5a2cea89150e2fe60b1_long << 0x0_long << 0x0_long;
  QTest::newRow("-20110810852933879428777932199445658888959059815312952776046911923086115729406 * 0")
      << -0x2c7650c91c31eefe9ed027ed706669077f5a227ece3eda36f1c738333b5feffe_long << 0x0_long << 0x0_long;
  QTest::newRow("-79723265101559010828653077388843406218530631161918672385672209392466739928729670405407446021383 * 0")
      << -0x98e0e55e911f6e4b3d141cfe836301e9a701c96a0d067102ae06fec0e429975ccf8783b49163507_long << 0x0_long << 0x0_long;
  QTest::newRow("-16017503230168664941769792526383230557406942611825718602334006936456794211973681682684919545584862592549130240659260 * 0")
      << -0x68115c8c9383d86f13ad06273839fb4cc210128c9201b676efce3f1c6b9e61cab56a85b8bac4fee54f12adbc7cae0f3c_long << 0x0_long << 0x0_long;
  QTest::newRow("-543609180603439592267615855499766037300137596015151120406193914498281732876984415926311833994334536033600296903970036715043997510469436 * 0")
      << -0xbf76f5da34324d356730a8ae5374f632ab588e9a536ff1f7729cacaf2434bcfdd70389b795ce8c410ccbcda0c55901e4855ac02a69b3073c_long << 0x0_long << 0x0_long;
  QTest::newRow("-13302566674671746445588314064629720350877602258438460494193867459179919098762591396708830640778676573511459758579399330997699803855658930545305491975984711 * 0")
      << -0xfdfd9769e7af72c1ba44cd607d9e925779f82560a31bb6921a06bc3ab677f4f6f88ff480fb321eebc301aa87ae4e03537efc4121667c3344e8ebd1102ed45647_long << 0x0_long << 0x0_long;
  QTest::newRow("-174630574634070011120697878511987110935279489774618993244967938000851681985459940930556046796611508289062147582712678192058587164940115844405522024518784423694076159356185951 * 0")
      << -0xb4c0791a7ef8ce7cbc8556a9deafcd555c540172753c31ad61ebb7de5b3d47ed61c71efd1da660aa7326b86f8dbf8261104f2e3374e592fd8a1db20ef471fd911095b4ac53ba2d5f_long << 0x0_long << 0x0_long;
  QTest::newRow("-1125170440861542300129327102961676671596156142978643816273475653351861227911729004137728637128795571976304210110662865526961721911935920826875674978396259688940447354331206031598495281229621521 * 0")
      << -0x3f22386079e14c1510aaaa48338f51192c359a40a7dc5515aa866770426c9334c466f57c009dc872056837bd4af42e5164ec96d89e0fa916ef2478d93ca9d565b97f29e70019b98367582bf9b24c6911_long << 0x0_long << 0x0_long;
  QTest::newRow("16195796642693465084 * 0") << 0xe0c3073cce3543fc_long << 0x0_long << 0x0_long;
  QTest::newRow("313452019004068624642415325636916562414 * 0") << 0xebd0a9b74748c1b5789d99fcf14e49ee_long << 0x0_long << 0x0_long;
  QTest::newRow("4928544815352115998075190868524455590904853892789114874863 * 0")
      << 0xc90068a7929eb23e067b09fa71adf9eee71d7ec6e855abef_long << 0x0_long << 0x0_long;
  QTest::newRow("98616238655680482271773818671078563867003960844011903566053507693482785122321 * 0")
      << 0xda06d025cb07be02f8946f102582881ebd30f1cd8d9269de6c3ad6801ca42811_long << 0x0_long << 0x0_long;
  QTest::newRow("1469500520493928730133464786566508672045646182179743916187540532331051058659716093517025696912637 * 0")
      << 0xb01ef8a4d392fc29c0b801ba15fb1beadfe6acb0f4cdc434dc2def74a312392b8ee93df2fcad94fd_long << 0x0_long << 0x0_long;
  QTest::newRow("35025486821694167183138942842159889647753460964030432020083028040258020840268349034583064969838989436251234363150292 * 0")
      << 0xe390afa058877b3aae99b2f85d23d851c7e5d40d976312e43cf8843020cdfe073491f9f2f0deed829fd53740471e8fd4_long << 0x0_long << 0x0_long;
  QTest::newRow("108532726832138231718467866589802251875484975190448688535598038644426661222750136586055631739084604625639261443806398387524366031806913 * 0")
      << 0x2639f0dd8cacd165b2e225416086c6b69b0adfb8fa29ecb326548d76426c6ac1559ccb6a4acd5f7b6277df1a4c2aab018c1a9fd29f5a61c1_long << 0x0_long << 0x0_long;
  QTest::newRow("2660316035543657695009640228962442064791604843292222611605645594482208881103414514572085952831144660127174955037396709882994539042619974870734253299212865 * 0")
      << 0x32cb5a9a045c8cde234fdfcee1a8c344d7e65af9df2102bb721b78341d2c4ef01f1a47513f9e6d434c50bc290348d457d45617e8c41b1cd762eefdb233022241_long << 0x0_long << 0x0_long;
  QTest::newRow("157131402965013628617943089208268212691624408526633684878450431344702795058622480261794373584990344852687745969960201909716846643484886358718604155337922853198908484537720607 * 0")
      << 0xa2a3a80ceeb2f0477a0e2e7f5880a49565ba8d40fc242cb422758b2cc68d84f5cc84bd1085952b81f6508737278bd3a51968b190f868b9549b0ee37a5205126b1ada1d4371229f1f_long << 0x0_long << 0x0_long;
  QTest::newRow("3048922935106727729938253428990385258652336026116144279811893835872372166505502455191413857358450740401693320095281171192012498155378589181419497419538268660723275819171465749714842435137868512 * 0")
      << 0xab1377536026444e7e6d4737c2985a04e70777f475535dee051977879d26507cfe23e3c23090ab6cb6fbe377d4c9bdfaf682641232dff60e2cb39399a8041fa363d0c076f0ff4c7d8c5e5227ebf892e0_long << 0x0_long << 0x0_long;
  QTest::newRow("0 * -8553380209976514155") << 0x0_long << -0x76b3b5fbb481966b_long << 0x0_long;
  QTest::newRow("0 * -321905835647800038190787134535914275173") << 0x0_long << -0xf22ccf0e7b157ce46699a8642394c165_long << 0x0_long;
  QTest::newRow("0 * -3982535586226097494031567521879520646674258658663359688927") << 0x0_long
      << -0xa26b9c92513218bb71e0ec63eb1255e7414db19f70a9b0df_long << 0x0_long;
  QTest::newRow("0 * -50519352941043327841111480488135618332659573826501150222849199662904550653073") << 0x0_long
      << -0x6fb0f0c293a05f2186b949224afa45a168038e7d6b5e831fe330d592a3f47c91_long << 0x0_long;
  QTest::newRow("0 * -1361181429347717731290456335726378463111235117294224710733910213092397999934363086850124006908100") << 0x0_long
      << -0xa3238af9d02dab9e2a07e18a54908e1cd689ff50c20e27b882bf2e3865915cf4e8e6df06ebad60c4_long << 0x0_long;
  QTest::newRow("0 * -9485045612087619989993305129988783576179111153378461093793685149671423699538749788627400403593592331726908563604397") << 0x0_long
      << -0x3da0265466a8dcaae5b7c51fb194d07106191d4d8ed9d1d6d808116cf7c4a93af8e2d8cece8e84d578578e3b1e3f43ad_long << 0x0_long;
  QTest::newRow("0 * -133273957322529701734545649913799805704860331406458651543593522819035490076947258798081918497196899950256124536504417563647808583248384") << 0x0_long
      << -0x2ef0c0fee400297a2ffdf30240bf16e1ae2dd6f9b46ddb9c0ecbdf9a84c413238b7a40aa8031ebedd3997249e3e202765fef56797dec2a00_long << 0x0_long;
  QTest::newRow("0 * -6216606794744844189233960383674424871196058599273443069183564819674098027562333897142325161237728181960746954644397055576004430148938773395281463162416222") << 0x0_long
      << -0x76b2241bb49847c8461b920b3fa6a40e8ed313297f7f80a56c228db98838798c11f83fe1f5a905cfe7af23329068da232c33310deff5fa7397db44a7694bac5e_long << 0x0_long;
  QTest::newRow("0 * -85608387278702010405579826349709627834951998440254944120561726787464737595806790341977135728158876962216143193068852580587709860563508972678787019260631400941348168033090822") << 0x0_long
      << -0x589bf4095a157366598e1eb00cf69804e87bb785fa89a1a23adab02a39366f5ce31c1f35c5cbe94280887bec5f510d6ec8171ef41094d05ae1b1e048d6add94e300fced4a233bd06_long << 0x0_long;
  QTest::newRow("0 * -3340904706824567423446429700358010934414894962657963577108953829043858317244662202706965404829085731741813062790290100883086289183242363782983180296511727053668377990966490619637809192751265706") << 0x0_long
      << -0xbb7590185739a79ae9afe4af28973cc32f03fdb051700fd592500e94db367c180c9e81c7c29deb5fee164ac49f8cf9f77cb2ae27945b5685e7aba8c030426df8548b5c5e3fd265063913254db376f7aa_long << 0x0_long;
  QTest::newRow("0 * 17472250264999400688") << 0x0_long << 0xf279e70b480394f0_long << 0x0_long;
  QTest::newRow("0 * 213844761019769008679428494803722054863") << 0x0_long << 0xa0e100bc13c457faa4ee2b66fc302ccf_long << 0x0_long;
  QTest::newRow("0 * 4961744357401428040904770408522183891194493213380474671391") << 0x0_long
      << 0xca5b07380dde51371a0a209c13e4d7db368582c0ad51911f_long << 0x0_long;
  QTest::newRow("0 * 110030177754501266874812227945740487289727652684655060072399397437906339799074") << 0x0_long
      << 0xf342dfa8e1dc0b704c96d4e61bae1407ca5562625f3fc32592b0e5266184a022_long << 0x0_long;
  QTest::newRow("0 * 400950794954835334776034612881803477994946058882057224609210637715290702893939165325795250293464") << 0x0_long
      << 0x300de7e2454cda9b0607dd261144b747d5b9896972f07a10202459d2ed42cf822d824a80f0064ad8_long << 0x0_long;
  QTest::newRow("0 * 37598720665485018562668209372226468149570525344065491071641580921047014594094079661892980257160915536989018852142264") << 0x0_long
      << 0xf448a8434f82855164f4e5291c7c2b6b913e4e800a76c730f43397af57cc44b29c232d83bc3973c4e5bbb6251463acb8_long << 0x0_long;
  QTest::newRow("0 * 631166536692347505284463453676326597601374117227050714886503698433762352873306260718604967802870125836755935103836629705100287404658981") << 0x0_long
      << 0xde4da3d806ef0d80acd5f8cba7728c142cc83031386af282aced31de93467279b004e1ad4cef9b96d41280b252ff3f1e284878f0ebfbd125_long << 0x0_long;
  QTest::newRow("0 * 9488098254597048843333910258804545543566977344330448766063984185757319223399074384843852212987150567418293428821183239177265881773907105215421476086904427") << 0x0_long
      << 0xb528dbb35aba58e81f8dc807c863ecc542002cb02091d13edd0c80111be08debb757d2effd41bc42d8b4ba090b0795ed374d72c8a863d07d75124e64250a766b_long << 0x0_long;
  QTest::newRow("0 * 121414305013794066554032983740130379214339690050816952345352592231041853208474959280102569592053203713539732323251795746524890169805581725231624980074635898864986157956239710") << 0x0_long
      << 0x7dab92825c1f107c37d9c1ee71f6f715a6edae3b205e6c69e4adebf59bb1fc871e2de9a91a61411fd025529f0d92a0c52e497c45f8d3fe4a3503439b3f9ce07634798bfef644915e_long << 0x0_long;
  QTest::newRow("0 * 1960318343331526561297749328386747963221092736797371624369846839200716607147412312475175969536546394243355748574784199997751348736554421367038535697889933267324061747842554435241270015557399666") << 0x0_long
      << 0x6dfe7c912805ad5a67f041efeff7ab1ede086fa57d2ad503bebde377af89b94473207066ebe2c77dab11316f9958e94692a27083e26ae99adc8c0910938348152b81d442de70919992f2563bfb6c7472_long << 0x0_long;
  QTest::newRow("-8696987295385091675 * 1") << -0x78b1e7ddd5837e5b_long << 0x1_long << -0x78b1e7ddd5837e5b_long;
  QTest::newRow("-14114527029284608363 * 1") << -0xc3e0df8d1928996b_long << 0x1_long << -0xc3e0df8d1928996b_long;
  QTest::newRow("-155992810242252531260908535444534445113 * 1") << -0x755b1f57ee46a88092d6942b68c3c439_long << 0x1_long << -0x755b1f57ee46a88092d6942b68c3c439_long;
  QTest::newRow("-122956410148141579311091079801474776266 * 1") << -0x5c808b1031ed0f5275356199f879fcca_long << 0x1_long << -0x5c808b1031ed0f5275356199f879fcca_long;
  QTest::newRow("-3717823765747953089256243643199388305897748590224146777 * 1")
      << -0x26d0de3fb255520cbab5cab6d0527dc7f37da3918f0159_long << 0x1_long
      << -0x26d0de3fb255520cbab5cab6d0527dc7f37da3918f0159_long;
  QTest::newRow("-4832009694500264897022471695863943808133824707000502189131 * 1")
      << -0xc51088fd833b309b4fc60342780291e481d84b6247a9fc4b_long << 0x1_long
      << -0xc51088fd833b309b4fc60342780291e481d84b6247a9fc4b_long;
  QTest::newRow("-60991671497061914657929272679831345501529326968461206488703885073091651691638 * 1")
      << -0x86d8100e937a76c3baf36e0e6dfd950817d1fb6ba102366cc2d55fc5fec3e476_long << 0x1_long
      << -0x86d8100e937a76c3baf36e0e6dfd950817d1fb6ba102366cc2d55fc5fec3e476_long;
  QTest::newRow("-40125030410958439589854572012000869633115291703447302129356773700759461336542 * 1")
      << -0x58b5f65ff7ed917f2809caf0f713f497ba60517d642e306a67df27488dd495de_long << 0x1_long
      << -0x58b5f65ff7ed917f2809caf0f713f497ba60517d642e306a67df27488dd495de_long;
  QTest::newRow("-1015170368761063575247288939442959709010728114625283178041773505697337207885880551587889132638260 * 1")
      << -0x79ab49f51fe833ee1664dab4ca976e64f4da229f38f4883ac094c875b4b489764624d48220089034_long << 0x1_long
      << -0x79ab49f51fe833ee1664dab4ca976e64f4da229f38f4883ac094c875b4b489764624d48220089034_long;
  QTest::newRow("-818172818507429828626865127737676985805973059458182177609523482189330349645089363966852932861748 * 1")
      << -0x620f0af05c6fd619339c24ab84aaa76023c05f8aaa2c1485f2b683efc20357a16f3a47588af87f34_long << 0x1_long
      << -0x620f0af05c6fd619339c24ab84aaa76023c05f8aaa2c1485f2b683efc20357a16f3a47588af87f34_long;
  QTest::newRow("-6452856785478468767633823416338991134995387001787668167351831323198581699252660587196695337772835763512818950247387 * 1")
      << -0x29ecd0812cc102c7c8c995f2bbca483f32880b43ad3266b3260f86e1ffeae73efe93fc7be158631895e2383d31a893db_long << 0x1_long
      << -0x29ecd0812cc102c7c8c995f2bbca483f32880b43ad3266b3260f86e1ffeae73efe93fc7be158631895e2383d31a893db_long;
  QTest::newRow("-36699073845942093552729311221570538619742812213908619010417729686859508865810444068000728219939704480840402012396501 * 1")
      << -0xee704e429949bfc857022ec51cdcf735fcb54179dfa6dd18eda62a4854cfe848c056c256bc857a79305cbc84ae7adbd5_long << 0x1_long
      << -0xee704e429949bfc857022ec51cdcf735fcb54179dfa6dd18eda62a4854cfe848c056c256bc857a79305cbc84ae7adbd5_long;
  QTest::newRow("-329142425305992993049200365052587143562338451311179079647845250522667327988525795434551256624041869414771800068894712090556338401112186 * 1")
      << -0x73ed6470093c6963d3eb725f96bf5484260b8b7d329164e125d6e30899da92c785f82f8d0ff57569e7410beb6cae2b37dd84311a136ef07a_long << 0x1_long
      << -0x73ed6470093c6963d3eb725f96bf5484260b8b7d329164e125d6e30899da92c785f82f8d0ff57569e7410beb6cae2b37dd84311a136ef07a_long;
  QTest::newRow("-481084312396304284631078279867154524839035991135389403814081274694050925407203387925470919687781834382206771750189059393281615406949210 * 1")
      << -0xa9715aec9cd529d0d90a47136592e1e3100e4425a759c38b6d30e53f9c0b69178351ebbcea3038bc0e79843c39417e846a7ad3b07d31e35a_long << 0x1_long
      << -0xa9715aec9cd529d0d90a47136592e1e3100e4425a759c38b6d30e53f9c0b69178351ebbcea3038bc0e79843c39417e846a7ad3b07d31e35a_long;
  QTest::newRow("-4230127091437018493482803006005877352683721737409272463692005258355532412874773756189343356916195446836355797464582272000049863611329470024097932178589651 * 1")
      << -0x50c46e36705126a8efc0bf97fe48f0e025ee391027052c905d49b7a1d91c3170b1e5a6147830dde468db6b2f5fa00b9f7f2df943bf372a0aa6a25861178b87d3_long << 0x1_long
      << -0x50c46e36705126a8efc0bf97fe48f0e025ee391027052c905d49b7a1d91c3170b1e5a6147830dde468db6b2f5fa00b9f7f2df943bf372a0aa6a25861178b87d3_long;
  QTest::newRow("-11992062725230696757662027889166792828347325982523941618088559509321743201901478867091606037057596603425121049057446615659943891660596963030943187764484567 * 1")
      << -0xe4f7fb495e9ba627a1813b4bbb00c3ccf7b5e883c9568a15f5921f7ff8598fa0dfb3893cc2afdcdb90f905928c70572b699e62198469e2b3df8f60d1989799d7_long << 0x1_long
      << -0xe4f7fb495e9ba627a1813b4bbb00c3ccf7b5e883c9568a15f5921f7ff8598fa0dfb3893cc2afdcdb90f905928c70572b699e62198469e2b3df8f60d1989799d7_long;
  QTest::newRow("-32460508144218299990248385954427449521030474900813781006144329571152019771391538882160315310213433300691839124751738001404828906711172512462419116759003227828871601989966800 * 1")
      << -0x21992c96b495ef57f0905674f152ac3e2124478e85dcdf20afdffcb153028f586f5f6d5c641b5134ef8ecb751f4419f57ca9ec6245a8202fb326cb14c871bcd3beb1e587d9915bd0_long << 0x1_long
      << -0x21992c96b495ef57f0905674f152ac3e2124478e85dcdf20afdffcb153028f586f5f6d5c641b5134ef8ecb751f4419f57ca9ec6245a8202fb326cb14c871bcd3beb1e587d9915bd0_long;
  QTest::newRow("-229064186159054481691182720785860292299857631873127121215807625511341402697956689817317932135425175912073908276549924440210085025861043945598459234773460056174869932772687559 * 1")
      << -0xed17efe9556f11ef9c02a94f77af09541bf762bc672b2054ce059f200818ed3254c5d4d8e62e2c34bbe8f3c6ff3706e37280df69a35afdf3f7117827f9d51c14ae96dd3f9b2ffec7_long << 0x1_long
      << -0xed17efe9556f11ef9c02a94f77af09541bf762bc672b2054ce059f200818ed3254c5d4d8e62e2c34bbe8f3c6ff3706e37280df69a35afdf3f7117827f9d51c14ae96dd3f9b2ffec7_long;
  QTest::newRow("-2809148659390120802294852067423981043500457572388228614589304667696605012925221100122100566898840986226204995344002653173441710231188330232919366000480733357968694521896478026179418032152373987 * 1")
      << -0x9d9f4a5b35238659803e0503055f61d7c5f77903a68ea292a0bd2ff10833938b7fb50e898896a74b2dab8fb71095fb8f652867b8ac7a142a6a7da66f74a64254b0e77e2bca51e8da3010e1c5bfa5eae3_long << 0x1_long
      << -0x9d9f4a5b35238659803e0503055f61d7c5f77903a68ea292a0bd2ff10833938b7fb50e898896a74b2dab8fb71095fb8f652867b8ac7a142a6a7da66f74a64254b0e77e2bca51e8da3010e1c5bfa5eae3_long;
  QTest::newRow("-4482550552011281862521152542350055551837966785584238723966535360766524784919343382790837234226025325525323700584888161691685569973998611375432554627538160673831304529087743199589853100133027610 * 1")
      << -0xfb847095b1fd1c40731bb1e40994926c8c1602c4ff48b62600898d27be8455ca1b76cf146e0af1722555cd84e5e0f0d4c6ee4ddaf10aa697160cbdeb9a582f17038e574747191b69309ae28457338f1a_long << 0x1_long
      << -0xfb847095b1fd1c40731bb1e40994926c8c1602c4ff48b62600898d27be8455ca1b76cf146e0af1722555cd84e5e0f0d4c6ee4ddaf10aa697160cbdeb9a582f17038e574747191b69309ae28457338f1a_long;
  QTest::newRow("7507113403521739221 * 1") << 0x682e9fddb97ca9d5_long << 0x1_long << 0x682e9fddb97ca9d5_long;
  QTest::newRow("4416847904123737306 * 1") << 0x3d4bcbc4703954da_long << 0x1_long << 0x3d4bcbc4703954da_long;
  QTest::newRow("47372628188871771988599997486726238737 * 1") << 0x23a3a2e5b13dc742ca66a126af41d211_long << 0x1_long << 0x23a3a2e5b13dc742ca66a126af41d211_long;
  QTest::newRow("112942272882757167790074435436483013387 * 1") << 0x54f7e3f9fbf247e6e6b9c851c43d6b0b_long << 0x1_long << 0x54f7e3f9fbf247e6e6b9c851c43d6b0b_long;
  QTest::newRow("4458729117028948710723798026324373330842303708006662717070 * 1")
      << 0xb5d74dd5faa06dcd9ccae123b5b4a7dd1f3db03feababe8e_long << 0x1_long
      << 0xb5d74dd5faa06dcd9ccae123b5b4a7dd1f3db03feababe8e_long;
  QTest::newRow("918653584864938048251611831063874526832299353496707663107 * 1")
      << 0x257730e1e6b738f1832842281e1b4993502eb41345480503_long << 0x1_long
      << 0x257730e1e6b738f1832842281e1b4993502eb41345480503_long;
  QTest::newRow("51214202311436136115210991353380946881417523775416779783525443306363546950444 * 1")
      << 0x713a3616294a373f0f7d52b60dcc2b1835d56e0bef23ac3fe8ab26a3d456db2c_long << 0x1_long
      << 0x713a3616294a373f0f7d52b60dcc2b1835d56e0bef23ac3fe8ab26a3d456db2c_long;
  QTest::newRow("16796276045071285215329546875651309355787693595819241278795812456226120718705 * 1")
      << 0x25225af82674f43a44e1ed76727e15dc62361ec0b7bd9e5b10531f2e2fc6d971_long << 0x1_long
      << 0x25225af82674f43a44e1ed76727e15dc62361ec0b7bd9e5b10531f2e2fc6d971_long;
  QTest::newRow("776015629371952532485445601445369704814201803416986002289355717005123497748960342047897117931250 * 1")
      << 0x5d0195354bf0b99569d533374e3ace2d0b054881ff02afe5a1e20fd7ed06f1cef31e6b78876236f2_long << 0x1_long
      << 0x5d0195354bf0b99569d533374e3ace2d0b054881ff02afe5a1e20fd7ed06f1cef31e6b78876236f2_long;
  QTest::newRow("1828357717477933004945761104774680736315004547902840233496234237024858973771964575649102898828051 * 1")
      << 0xdb215e46e698fe0b689fecf8982278c5014d347eb50c72b0d0217e4424bb77f2a77c3b6572fe9313_long << 0x1_long
      << 0xdb215e46e698fe0b689fecf8982278c5014d347eb50c72b0d0217e4424bb77f2a77c3b6572fe9313_long;
  QTest::newRow("19591741324485154099407553866002653331911970092580752783441090628564267046021792919053362649086730215814734388998572 * 1")
      << 0x7f4a44c68a5a2e9e364de2f70cf46b85dcd5a22bb10e6fe46bef5035ed6a8428aaf6ffadf2c274acf85210121a7531ac_long << 0x1_long
      << 0x7f4a44c68a5a2e9e364de2f70cf46b85dcd5a22bb10e6fe46bef5035ed6a8428aaf6ffadf2c274acf85210121a7531ac_long;
  QTest::newRow("8919775992062126940823998410276034726826770584992509833295021622274584529366257502891812340858549689060704978758005 * 1")
      << 0x39f3f4cbace57addcfad4e94310bf6fc8895289851e89e12b5e2e597b914ba61068ad734c9bc94580f13404406a46975_long << 0x1_long
      << 0x39f3f4cbace57addcfad4e94310bf6fc8895289851e89e12b5e2e597b914ba61068ad734c9bc94580f13404406a46975_long;
  QTest::newRow("350284763163912464325166214214123917461171392992623129772187155477691986034413053656965317946891614956537424514369632361824841114329107 * 1")
      << 0x7b5fb55231bb92545719eb55b58e4fb387a9698d13410e0a685de380e7334600ae783b6e883c063bc972e31842fd3ac3014417178b082013_long << 0x1_long
      << 0x7b5fb55231bb92545719eb55b58e4fb387a9698d13410e0a685de380e7334600ae783b6e883c063bc972e31842fd3ac3014417178b082013_long;
  QTest::newRow("503348416235141481088886392564828018303868467659168187733039639804422408458012470987480461099308424357190572170682699324826845966944188 * 1")
      << 0xb148d0e93689d2aee7951e46bc3f821018286374466d0d4244e337d72ec5376784eaac130ff5fd56ef39c09ebc116b25009dc9298daac7bc_long << 0x1_long
      << 0xb148d0e93689d2aee7951e46bc3f821018286374466d0d4244e337d72ec5376784eaac130ff5fd56ef39c09ebc116b25009dc9298daac7bc_long;
  QTest::newRow("5626680436547357446840637640562756279160462071286569345610703149763246074000300678327709914440507588385169703437426523133544003156625753883838409124345883 * 1")
      << 0x6b6ea41d7101877b358f9010ea03354bef6e23a81ba5977b373a4e19d728bab926f62314493519d25828f0d55e0369adc7d61709a73cfe7673fb670c6477f81b_long << 0x1_long
      << 0x6b6ea41d7101877b358f9010ea03354bef6e23a81ba5977b373a4e19d728bab926f62314493519d25828f0d55e0369adc7d61709a73cfe7673fb670c6477f81b_long;
  QTest::newRow("10572848965355785631541275024098928727692769700297446944012393275873659121761509199540502929710672425255417181539088271007250667753058739912514377402330384 * 1")
      << 0xc9df025d08b9056ab284267208276a4f8b07c65825cb0f3ba4d89836a989a3868de42fac6ef92d1e93f904e913353e34a6742f962583f20c5165b20e046cad10_long << 0x1_long
      << 0xc9df025d08b9056ab284267208276a4f8b07c65825cb0f3ba4d89836a989a3868de42fac6ef92d1e93f904e913353e34a6742f962583f20c5165b20e046cad10_long;
  QTest::newRow("2494052341086840397759586728301441704689707612300468337536579763084268750350315166386419243793606534501860308529809492392813461523672530110281148417292494916701046616929024 * 1")
      << 0x294db95eda626de6f6487927abb96e736249a3a6ebb0f0b50a0ef456f3867ef70b6517416ec04b329a32670d34e2e854bf23048463bedadaec87744844c7904a9f60cf34b4cb300_long << 0x1_long
      << 0x294db95eda626de6f6487927abb96e736249a3a6ebb0f0b50a0ef456f3867ef70b6517416ec04b329a32670d34e2e854bf23048463bedadaec87744844c7904a9f60cf34b4cb300_long;
  QTest::newRow("70739509297429527330149067246482315233933215287378861748813499161827545983777619550743640269022038376980933278870280491326799310816138478646944598732690724349813790122274114 * 1")
      << 0x49381841f248f198ab70047a25a4beab64578a0bd9b5761c32d4edc36fa364645ae6919ec776947e8ecf34a89e10b4e1f9ca26c1d2a2d85048e10c10ab8cff59f1c38ed7a7d56d42_long << 0x1_long
      << 0x49381841f248f198ab70047a25a4beab64578a0bd9b5761c32d4edc36fa364645ae6919ec776947e8ecf34a89e10b4e1f9ca26c1d2a2d85048e10c10ab8cff59f1c38ed7a7d56d42_long;
  QTest::newRow("3279770552876579243188935531686757798048145112650247853133082402547613498100927177360913568568617121350871156323788219797447344145623123985717374319143094034333999796758496145187317263989691592 * 1")
      << 0xb8076ac763ac7af3f50b417e0bbfa6e73f6875d7fe99f1bec73aa5dae01c28133a6c7443f63417cc0eb6addfb46b39a968c5ce51660abfba237072218c89db189deb1af924dc18ac562da46e200b54c8_long << 0x1_long
      << 0xb8076ac763ac7af3f50b417e0bbfa6e73f6875d7fe99f1bec73aa5dae01c28133a6c7443f63417cc0eb6addfb46b39a968c5ce51660abfba237072218c89db189deb1af924dc18ac562da46e200b54c8_long;
  QTest::newRow("193315379376864958268201927774349995394026976519053211614653405941599424746681738427445182576891018841997836792394702398439156042919182193160049914498470851241543743917278071233775119651509695 * 1")
      << 0xad8d42f13054e57a95d665c535d6ed42adf8f3a58f16eb80d5c12895f86806c8ab9a0859c34dded63e79b7110803abea713d06d4cc112e2bfe0771381c4de48946061abc0acbf169a23db5d8fa315bf_long << 0x1_long
      << 0xad8d42f13054e57a95d665c535d6ed42adf8f3a58f16eb80d5c12895f86806c8ab9a0859c34dded63e79b7110803abea713d06d4cc112e2bfe0771381c4de48946061abc0acbf169a23db5d8fa315bf_long;
  QTest::newRow("-1 * -8806520467267574080") << -0x1_long << -0x7a370bb4beb0d940_long << 0x7a370bb4beb0d940_long;
  QTest::newRow("-1 * -203300033439580735403926375422970362150") << -0x1_long << -0x98f2298691db670c27595ce18a98f926_long << 0x98f2298691db670c27595ce18a98f926_long;
  QTest::newRow("-1 * -1041284684788077476552004017137720519957284554208739357829") << -0x1_long
      << -0x2a7784f56acf7e5bf94dde76a0b49bcbcdc1546de2747485_long
      << 0x2a7784f56acf7e5bf94dde76a0b49bcbcdc1546de2747485_long;
  QTest::newRow("-1 * -38227882169335545176611784534297693967797241249144277667637897951582967744014") << -0x1_long
      << -0x548436ecb3d9463a7edc8e8ef84a6241fe6faf0ffaae0f15b3f24cbb8bfec60e_long
      << 0x548436ecb3d9463a7edc8e8ef84a6241fe6faf0ffaae0f15b3f24cbb8bfec60e_long;
  QTest::newRow("-1 * -805665004173687703039237591280553067310725107996608240577228325355369369564277965594573022485710") << -0x1_long
      << -0x608f47b1084e4484e23b6b442f6ef46c28e31d2605e27fdcc3c97cef25b33381417b1e10c2c0dcce_long
      << 0x608f47b1084e4484e23b6b442f6ef46c28e31d2605e27fdcc3c97cef25b33381417b1e10c2c0dcce_long;
  QTest::newRow("-1 * -19055014651091775981459225681548035311006290870241017891653546580953990039370305740187625334475521148033559655901225") << -0x1_long
      << -0x7bcd8cb6a8b1bd342af9b694641c8c86e498eb8afeee515ba1595590e615e0ec9b0c3c6875d1ccc9c485964fed846829_long
      << 0x7bcd8cb6a8b1bd342af9b694641c8c86e498eb8afeee515ba1595590e615e0ec9b0c3c6875d1ccc9c485964fed846829_long;
  QTest::newRow("-1 * -317887414333460930958765311121613520346589276274680710702085375429037925076272276979926750119246356744189873416762628882473258316368400") << -0x1_long
      << -0x6ff6933f9e5b9beb14e65695bc7c6842788fb8369333f9c8e348110d36a114b15be8f1221edfb95c19931cc53e53e619c0bf368a0f4a8a10_long
      << 0x6ff6933f9e5b9beb14e65695bc7c6842788fb8369333f9c8e348110d36a114b15be8f1221edfb95c19931cc53e53e619c0bf368a0f4a8a10_long;
  QTest::newRow("-1 * -9651450361689556915667060789684622327681371247323161375398768602673509059203620842241935549783476130978085991039382252432657572689631820316380564940553194") << -0x1_long
      << -0xb8474e821a1c8931ec02b129f8bdddf0c5918aca200d90177d4cd15c6e3dcc6a47ddd068c842cda638b0a9c12b7fd1de21db4c8adc08f491b8649a116cce7bea_long
      << 0xb8474e821a1c8931ec02b129f8bdddf0c5918aca200d90177d4cd15c6e3dcc6a47ddd068c842cda638b0a9c12b7fd1de21db4c8adc08f491b8649a116cce7bea_long;
  QTest::newRow("-1 * -1971712899528855071630042138030744150808462958717974789117037587914522375926325450510833663377063240824484380935184686432415697567762912999207991975944896216419548332753031") << -0x1_long
      << -0x20a739f65ccfb3716aa606f892297531d680603f2b026c4e08aa33c73271529d9058bcc8b65492927160723fde58a34152a4287576825c030a3e04f0911e7f3a44d6a1b8fd30087_long
      << 0x20a739f65ccfb3716aa606f892297531d680603f2b026c4e08aa33c73271529d9058bcc8b65492927160723fde58a34152a4287576825c030a3e04f0911e7f3a44d6a1b8fd30087_long;
  QTest::newRow("-1 * -1593712633550233357814756772402307897628767111306632975560926053805812300556233815577351460069669826114990843648356712885713231127645596806001043695806002609281714503428952636141832622337453438") << -0x1_long
      << -0x596c793a6dd065fdbdc42822919aa20c52bdb6d23ae674041c19c49e4ff215a8416275c2961e495aaa59404bcb8c6e1e0584f0bf855c08f97a4d5b5bcb0db5726eb8cf985266c2d4350a5e82036c6d7e_long
      << 0x596c793a6dd065fdbdc42822919aa20c52bdb6d23ae674041c19c49e4ff215a8416275c2961e495aaa59404bcb8c6e1e0584f0bf855c08f97a4d5b5bcb0db5726eb8cf985266c2d4350a5e82036c6d7e_long;
  QTest::newRow("-1 * 13872058928500538881") << -0x1_long << 0xc0837419208f7e01_long << -0xc0837419208f7e01_long;
  QTest::newRow("-1 * 330622668887816682749599920035448960685") << -0x1_long << 0xf8bb9c1dd8cd0c7f2b0f697fdc6736ad_long << -0xf8bb9c1dd8cd0c7f2b0f697fdc6736ad_long;
  QTest::newRow("-1 * 3681736069310131201108157264128900049946149337745794933558") << -0x1_long
      << 0x96271e3ce8b2675d3b83c8d5fac7287fc92d2675a9d22336_long
      << -0x96271e3ce8b2675d3b83c8d5fac7287fc92d2675a9d22336_long;
  QTest::newRow("-1 * 53825348894242205892376199976561687080861570445231512358409953698687129526284") << -0x1_long
      << 0x7700115fd06f23be7c5943921d79a69bd2fd665c64ba3276b291731f87a0a00c_long
      << -0x7700115fd06f23be7c5943921d79a69bd2fd665c64ba3276b291731f87a0a00c_long;
  QTest::newRow("-1 * 1786420491196758645280950570941094584356250056552213663461959168462228444893404632630103846250809") << -0x1_long
      << 0xd61aa841601ba0085f923a73e76a8579fed6a3f604353e0e0ca0f06c42d9a978fe7c07995fe96939_long
      << -0xd61aa841601ba0085f923a73e76a8579fed6a3f604353e0e0ca0f06c42d9a978fe7c07995fe96939_long;
  QTest::newRow("-1 * 9986127309183439311826568445082241259716252394966270615887792229934398988213945807741411936482345195442013905933203") << -0x1_long
      << 0x40e194e76aa7a5ad4684897e43fd7dbafc71ab6191beba8ced792b93b9a6ca6ebecaf96a61031dd728015ce20410d393_long
      << -0x40e194e76aa7a5ad4684897e43fd7dbafc71ab6191beba8ced792b93b9a6ca6ebecaf96a61031dd728015ce20410d393_long;
  QTest::newRow("-1 * 170671998087903975246975094727934126542918467847057092721585833054140825590681887171885249240097413969000006527439680635596235573147853") << -0x1_long
      << 0x3c1cc745c29f86347d65a05aefc4efc0d2f239890b6ec2d4a43b7dd9de561c28dfabd023ff8fe88b97e08d81c9e45aba4ed29db3e6e9b8cd_long
      << -0x3c1cc745c29f86347d65a05aefc4efc0d2f239890b6ec2d4a43b7dd9de561c28dfabd023ff8fe88b97e08d81c9e45aba4ed29db3e6e9b8cd_long;
  QTest::newRow("-1 * 3608974548654343041713221574711885002739570559394120309175392168728905370331169279191801246613864320326264420129693936599224890555311112570978727009567053") << -0x1_long
      << 0x44e84cd591b10731eb73cf945b68ceb94942eac0588327512bce82b37b2a9d8870277ff014da33dc80b1a269f8fe8ac17197c7b59e4df7596911fb63d0d5c14d_long
      << -0x44e84cd591b10731eb73cf945b68ceb94942eac0588327512bce82b37b2a9d8870277ff014da33dc80b1a269f8fe8ac17197c7b59e4df7596911fb63d0d5c14d_long;
  QTest::newRow("-1 * 124544834274401206264161174212765772655979675296765742547235372423572308252196231424587776098241829876506268066584968400368751002727678119341335695331927284636384859183688736") << -0x1_long
      << 0x80e9145ead304095cb0cdb2dcf835ef4f2f4aad0503af1886133579c34bd0cdc3d6c44572c91e67896770251fd8f201dbeea1e4c33aa0b996f0a315c64ed0072d9314d5bfb64ac20_long
      << -0x80e9145ead304095cb0cdb2dcf835ef4f2f4aad0503af1886133579c34bd0cdc3d6c44572c91e67896770251fd8f201dbeea1e4c33aa0b996f0a315c64ed0072d9314d5bfb64ac20_long;
  QTest::newRow("-1 * 3324828399898574599783605915539753167675127369622904804714814108609516619028140953500128265686548544101210095452656176965881054849378793462582602397496450905150095051591694078212064546537905632") << -0x1_long
      << 0xba8ea38fc1618f70bd1ebf5e0773ed8fa34607b8bbd6ef9a6ed5d9a0a0808a65d93d7097a0c0e8e2814b75e3f9684158366ca6400828f86cdb741df2b39f4275d746ed3ac338baf614e7abce0b109de0_long
      << -0xba8ea38fc1618f70bd1ebf5e0773ed8fa34607b8bbd6ef9a6ed5d9a0a0808a65d93d7097a0c0e8e2814b75e3f9684158366ca6400828f86cdb741df2b39f4275d746ed3ac338baf614e7abce0b109de0_long;
  QTest::newRow("1 * -11118344805831207437") << 0x1_long << -0x9a4c4bb181e0ea0d_long << -0x9a4c4bb181e0ea0d_long;
  QTest::newRow("1 * -99975721297345055785203975050492189924") << 0x1_long << -0x4b369fa00b40a86cefca7e8ccaa51ce4_long << -0x4b369fa00b40a86cefca7e8ccaa51ce4_long;
  QTest::newRow("1 * -3794984091559730348135985442105723104517888018761041355159") << 0x1_long
      << -0x9ac57b8e26f85b13f7b3a9bc5219a65db76add048eb4a197_long
      << -0x9ac57b8e26f85b13f7b3a9bc5219a65db76add048eb4a197_long;
  QTest::newRow("1 * -72219184937357470375752255477849952789786815470010596311545694789086612743630") << 0x1_long
      << -0x9faa9c31ac3bc5d61d9716c51d1f370dad09cb0149ead71384b6a6fa71a2e5ce_long
      << -0x9faa9c31ac3bc5d61d9716c51d1f370dad09cb0149ead71384b6a6fa71a2e5ce_long;
  QTest::newRow("1 * -1792308753025582810232584322279324341269449012638962983227947081228909380562828365193857938301027") << 0x1_long
      << -0xd6cf51e64eae8959090d31960948167201a9e8ef7186dfc63b351d5005eb055808bfeacee7412063_long
      << -0xd6cf51e64eae8959090d31960948167201a9e8ef7186dfc63b351d5005eb055808bfeacee7412063_long;
  QTest::newRow("1 * -7931074079989666692316987445060146021861144486872782577453109780030737928799803260957403242634691632481413993088101") << 0x1_long
      << -0x33877b7df8779d2cd91534c68c3cc5b988713b29c72e70ea56ad84d2bfdfc17051302e9cba2bedc3b1c605818d444465_long
      << -0x33877b7df8779d2cd91534c68c3cc5b988713b29c72e70ea56ad84d2bfdfc17051302e9cba2bedc3b1c605818d444465_long;
  QTest::newRow("1 * -33984402938036635051481097389677410682494645283008465765091315363894565894919459118711019266269838965150155990315769292607922088589779") << 0x1_long
      << -0xbf83b2a06923583444b36d776f98ed59d834b31240912e9ae9ed131a82ddd921153bd359c2ea818f43fff30915c1f7569cd44262ed239d3_long
      << -0xbf83b2a06923583444b36d776f98ed59d834b31240912e9ae9ed131a82ddd921153bd359c2ea818f43fff30915c1f7569cd44262ed239d3_long;
  QTest::newRow("1 * -9034286600284960774235885513723332961745217744245893059199152122502461245472145645642255818723790352735416824556684084899454976386401357704226675920823267") << 0x1_long
      << -0xac7eac4cb7147fc02205ab64419ae073ec2480558e23b1750b0b152ddcd1ce069d99001ab5dc8ecd51a1e290206ff04cfb8724bfd6de460cdf21ed3524b163e3_long
      << -0xac7eac4cb7147fc02205ab64419ae073ec2480558e23b1750b0b152ddcd1ce069d99001ab5dc8ecd51a1e290206ff04cfb8724bfd6de460cdf21ed3524b163e3_long;
  QTest::newRow("1 * -752712816503101344672613485037882269869964860070746092953504947240874383763799476336258990543732905777168474440976767475359669305242664589179236301582886901875640827867840") << 0x1_long
      << -0xc772eded76b1a748c0127b396d832dd08092a451f5db86389455c686257261ebc5eb1480d55c007c6e11122036206b5f3fc11a7b63590ad3a00ef35604ae01ad1f939453f772c0_long
      << -0xc772eded76b1a748c0127b396d832dd08092a451f5db86389455c686257261ebc5eb1480d55c007c6e11122036206b5f3fc11a7b63590ad3a00ef35604ae01ad1f939453f772c0_long;
  QTest::newRow("1 * -3145890377728868556593860218946406250276537189920864706620684277110720222178744344399085730142405915608210157356900397920696280161671496924463468652609643460357342307027603371069033653199511725") << 0x1_long
      << -0xb0845474907b4aa044a5b9b3bba4f692563512f527eef9c43dda602452e69b5cb9a9e5b80383ecdbd8e48f22f7f86655769b70c0c796068b86415b19db71b45f56042f2c923e356388ba836a944d20ad_long
      << -0xb0845474907b4aa044a5b9b3bba4f692563512f527eef9c43dda602452e69b5cb9a9e5b80383ecdbd8e48f22f7f86655769b70c0c796068b86415b19db71b45f56042f2c923e356388ba836a944d20ad_long;
  QTest::newRow("1 * 15747569406868969901") << 0x1_long << 0xda8a9af0fc3bd9ad_long << 0xda8a9af0fc3bd9ad_long;
  QTest::newRow("1 * 150301505260213486718952029797063206205") << 0x1_long << 0x71130457ee3180d04f79ec5f60c2253d_long << 0x71130457ee3180d04f79ec5f60c2253d_long;
  QTest::newRow("1 * 591551694843519252398883737844871926917158795267327737873") << 0x1_long
      << 0x1820167e821eec3cbf265ff8f3df3760a497afc214094011_long
      << 0x1820167e821eec3cbf265ff8f3df3760a497afc214094011_long;
  QTest::newRow("1 * 110401287633928907220325520154285748519434933199013186510575107724410158293282") << 0x1_long
      << 0xf414ea175b15e0a594975308771ecded53cdad674fdf712ec6e0bf66bf7ba122_long
      << 0xf414ea175b15e0a594975308771ecded53cdad674fdf712ec6e0bf66bf7ba122_long;
  QTest::newRow("1 * 776419529785344890273960730081149132187647334518424601687326723483934393153608932403538880025663") << 0x1_long
      << 0x5d0df9a9fbc6692cd8dd78217c10201a234864954b526ef1eb67bb64064aadf1131fbf1b0e62d43f_long
      << 0x5d0df9a9fbc6692cd8dd78217c10201a234864954b526ef1eb67bb64064aadf1131fbf1b0e62d43f_long;
  QTest::newRow("1 * 30869487879425352283897277907941958407076411854109283816372241283975376936052314382432033969226109708434827217895014") << 0x1_long
      << 0xc89027f79bce30349801d4454367cd4afff627fb50e27fb8c6eedf396fcd26931f56910994309ef5312de80deeaa7e66_long
      << 0xc89027f79bce30349801d4454367cd4afff627fb50e27fb8c6eedf396fcd26931f56910994309ef5312de80deeaa7e66_long;
  QTest::newRow("1 * 349451824893280729993709817773730421619791404850429597450005323760718776557591396042740915346457312077826238498534611572388046399814976") << 0x1_long
      << 0x7b149b116621de6b5ca6647b0930d76dcab165a1a3be493cc1c4b0195f24a74badc461453ae042527ae99d87c9b8d028cfcd46238ac33d40_long
      << 0x7b149b116621de6b5ca6647b0930d76dcab165a1a3be493cc1c4b0195f24a74badc461453ae042527ae99d87c9b8d028cfcd46238ac33d40_long;
  QTest::newRow("1 * 5354358575009043255070093371545842757924808546086969546545586053324214328728506231952333023974199656772397883065816174688436616499484958354424476607718721") << 0x1_long
      << 0x663b8f3e2c00ac6915a33eb3b09f239c43ec7dcd7afba41dd662fd9673c1627eefddc035f4111b7582f575bd7ff17611f2854950b7373216f252e60865a02541_long
      << 0x663b8f3e2c00ac6915a33eb3b09f239c43ec7dcd7afba41dd662fd9673c1627eefddc035f4111b7582f575bd7ff17611f2854950b7373216f252e60865a02541_long;
  QTest::newRow("1 * 27396086961784940302983529346100959356998016324003724199323301201116750584059655820977891038835070962096296566260479613800065807104691006344833440560143576673028428257182182") << 0x1_long
      << 0x1c5b3c9fb7ec4d9cbc9f4d95fbff22e491b19044b473387d73607d67b980cb52b3051eb176f63e31deac22b2e4f50a6fe62f504fa470fe9ccf73b79473ad10af625d9c93526241e6_long
      << 0x1c5b3c9fb7ec4d9cbc9f4d95fbff22e491b19044b473387d73607d67b980cb52b3051eb176f63e31deac22b2e4f50a6fe62f504fa470fe9ccf73b79473ad10af625d9c93526241e6_long;
  QTest::newRow("1 * 4397420727083929745539921418380351626872171140870216899207005919794499591767323334797831176030997087789586286717201407125387750388099283054999993636316822398655716054649664702783693848377909417") << 0x1_long
      << 0xf6bd9d493d791a3fea74e8401069f23c7e6f84987d82307bfd5366f3bc0a764bddc83ae510a844c7ee502e7be76e2fc4f2826bf4f0bda577435cc80d9797f3ac4fa1e429a5489344001ade2cb17160a9_long
      << 0xf6bd9d493d791a3fea74e8401069f23c7e6f84987d82307bfd5366f3bc0a764bddc83ae510a844c7ee502e7be76e2fc4f2826bf4f0bda577435cc80d9797f3ac4fa1e429a5489344001ade2cb17160a9_long;
  QTest::newRow("-15023075878263059285 * -683369040532263428") << -0xd07cafea659bf355_long << -0x97bd0858f6cd204_long << 0x7b937e9d7b56ab916777ce3a6e78754_long;
  QTest::newRow("-12568800121791676104 * -150537343735005097557557005888376603040") << -0xae6d591e50477ec8_long << -0x71407013f94b3319804f5e7c0eb101a0_long
      << 0x4d2a2c0a1bfa19bdf79876bd1806a0bafaf114800c760500_long;
  QTest::newRow("-9405552127208591310 * -1386550685955502728239923377551373310097094579203138746624") << -0x82873bd3b2b00fce_long
      << -0x388c43bdff3ef737b4ad551045296bb52a2c533feddd7900_long
      << 0x1cd519954b809e31f2efce2ec33f4c9cafa707336fbd5a5c1f50fdc6924e5e00_long;
  QTest::newRow("-9715115417520238586 * -56442781972848453518025117832221222475399296690649155298656938603938865685125") << -0x86d305ffd536effa_long
      << -0x7cc97b848e5517e841e32ea475339585de45f4fc7fa3368dd06900aa725f2285_long
      << 0x41b853a4d4cbe5b7069bc57852555ff12c9819e46589aeeba91c8bc8ef980e425d560a7f732fe0e2_long;
  QTest::newRow("-3736015267144033305 * -651689138029846520092259549376143450564734665185787118985179963273801462099036373571807346127726") << -0x33d8fe17598e6419_long
      << -0x4e1b049f4bf101b8ce78d137dadf33a90d0304300b991a9c4c12db44a5169da6a83559e3b2e7736e_long
      << 0xfd1963d90df647c57a16295d7ab3e4037233432418bae0703cd3f83438c031fc68abc55987467124ff4ef8426b53dbe_long;
  QTest::newRow("-13324627067389822871 * -33638167348330317035137965239148694725270004228771525664348399228858872253714920108228672416388010667161500205633701") << -0xb8ea95b88c534797_long
      << -0xda8d3490e9ba30952ee34eadc88e1c7a40d9271826e2b4ca6be06b1991b533792766eddf1adcbc814fb0e42317fad0a5_long
      << 0x9dddc2abf155e8f25bd5c812a979b3ba01fe52fae4ae210a00c202ca8e38c474e64f1b7528a70f17f38e57b0e33937e4bfa23c5d964dd453_long;
  QTest::newRow("-8447565716984349322 * -656466344628745055517795290059369456402588301595884317283092664408603259412617946973821547049783222672268403675790409493804719124765861") << -0x753bc843319ec28a_long
      << -0xe736d14ee1cc6df9ee573cb8714b5107b27bf79da93f06873f3a4667a4d4757740f4f1771d44cb8b698a705bb323c86aa7a9c5b5c35bdca5_long
      << 0x69e20c2ace0fc206d705f0542cf900fc0decdb785180304f02d60dcb94f8acd03bd4b828a2291bd37f887201cd98b1e079ce7b04f2279762025e2123af8ffaf2_long;
  QTest::newRow("-9401596523279836021 * -6874910214322745008230169576068533300573894914408519442879701543772693154868174265991768117579868742109903539769806038072185336059161107033362622857334206") << -0x82792e39e3a46375_long
      << -0x8343dc735c0b91b4222e96f47474bce98c20f1eee91052c053cd7c51d139a322ab6fd921fba84a8a3987b86e88599986789fc49a15dd383bf5aff8d5c89bcdbe_long
      << 0x42e698b9a7b6a8a1ab0b36db148552b5e705a2aa465ce25f394baf4a45fda2149c84fb89516ed483896b5eadea259854406a53bf4b423f24239c637e3bee138fb4f504d6377d81d6_long;
  QTest::newRow("-17825078543837706370 * -123592181458021571187022691697948365688222802720669543004257917883016870120989867398627773520757677704254375838694727063066633990116889359293856973308616395297092402773195146") << -0xf75f667e8ae23882_long
      << -0x7feca6de1f8794e81136913dea1bc47df853f57e2608475d1a82d386605fad8b3da4dc254c78a8ae86e84a910794b35603c5a4bb7ab85239ce03cd9a866e0ca21d92b855d10f798a_long
      << 0x7b9d0109c336c2fb7c8e0a1f1327d0b805a4010cd1cd03ea86d7952ea2d243158eac4d03d82ee2c2858d40eac724ed04d9981360b099eab1c4c4fc6ab18327415fae8eb719ec823b6b8a16693c45e814_long;
  QTest::newRow("-14795449222522269436 * -4356512068243816137754783004126752436901178656462989487544066716706903748218467275870951075214365576447737242541666073200039810755509576849842135805763939811793702706303674419488821159981325384") << -0xcd53feada0c4eefc_long
      << -0xf471fe16ae1f5617fa8d3f328e771dc6bea02814cb67c17197a4b59b7e4af4850f5bfddf9c5f035e12c6693c3bed37c81e34e603802a02bb010e40a71de1538ea88907b084cb4c4f4b14a9ff484d9c48_long
      << 0xc40f7c9c6f700c7830a26a34df78982933ab1a7d5ddde0f24f46dbf715c40be72ca8c6f8675bde2023987c24896e6c7b5b712309963240ab22453348d39de2ee5326193bbad8bee6321c8a787cfffe7d03e09643fad0c6e0_long;
  QTest::newRow("-15011776582477384667 * 7666274958591365525") << -0xd0548b4416178bdb_long << 0x6a641475094f9195_long << -0x5694735670d71268c21c4b6a0d807177_long;
  QTest::newRow("-9024002882497379398 * 136731084673709331589198397864030487338") << -0x7d3bb2cf775b7c46_long << 0x66dd72f3a40ec7701211192528afc32a_long
      << -0x32521e03cc3514f4205f5572719e8e4d077a0d072885b57c_long;
  QTest::newRow("-12899928688635102177 * 3472425410899964855584354711165101103651222440008442496179") << -0xb305c0cba9f743e1_long
      << 0x8d9dd018c012f713af80b28f0f9ade6d811525e761b8c4b3_long
      << -0x6308873d65058e01034a52085fdd14fb18337ca4e43e5a5e5fcd5c013294ba53_long;
  QTest::newRow("-5342168605770482180 * 108747535474596173266228135687256229344826289500753152353213525409061388077265") << -0x4a23320afd318204_long
      << 0xf06cec828b71e6ffafea651abbcc5e81cb835c505893a7816c91ffc132a2c8d1_long
      << -0x45a08a41aa64de5f89fa039020b8b1183dbbe9c387e840cb9268fd30e7251c995d55568471864544_long;
  QTest::newRow("-1013137946138336472 * 1407883732688111031714710136835106687549809517336211538090335431231935139288927475648067611577311") << -0xe0f63981c0b5cd8_long
      << 0xa8bc748800b9f2ce2a19b5cc625ef5dfac53ca0cecb7e8c90057f81f64bd05d4772c192ad632cbdf_long
      << -0x944730f6774193ed27f55b3308a8479b2909f2e6c884d13e9c5308a4a09fca0df36a8a60be30e232196ad0222b52828_long;
  QTest::newRow("-15346822767328523284 * 30299082825487725420028964193780494065246884734250491120733930635971056877924630024764474581787576256816343990226799") << -0xd4faddfef57e7414_long
      << 0xc4db6bc937583aa23c3f92a994277f0ff883c5f28466789a0fa83f5cf6b10e7234a0597839cc8b52b30d8419a7ed4f6f_long
      << -0xa3c69e3f5eddfe8d1d77fcdabdf3e39264f3b06ac4768204d543ddf2382c9ca6e9f50c717c8fa1a055d158d07dbe269fa8ae590cfa2a80ac_long;
  QTest::newRow("-7562964726176924609 * 677430271791110439791738684496383350228319822351698481342459043706022771153694479245078670300679935960467136640746611345694394485240017") << -0x68f50c592095c3c1_long
      << 0xee990c0945bb0ca97b21daa8d2cad00f122bee994d10a8a4a463c0399c5c45f138d8cc52ad030a5908d8b62b7c5709b9bf82c3cc220ef0d1_long
      << -0x61d290de87580ead9a820b7ad8eb99cc04c1c2f562e80ff60dc5c98db8bd5b829e02720015b461d99e2c5ef4251c95f64847349cf0e9ef31614c504c5857c091_long;
  QTest::newRow("-11511399333737490147 * 2634176317084011804526181273284163130874073783557221600708403975383402681648769930891944940776799788274034747927266110244522033361574013005762254921181329") << -0x9fc0b4b43b1766e3_long
      << 0x324b95ebddd2787558e8e9bc803fa827790a7924ed9e80c75cb4c157f500b99aac848c78c4113ca06252a9b8998487a44d7ec59ad6deeeb5d7ae7f86a182a891_long
      << -0x1f62ce4e7dd75d09b9fce71514ccd82ba5ecd4ad8db5ecfdd3bb885a494f9a72e9d9a32ab891b1874da4bf0a55c42150d1ce23d8fbd858e97882708b517b54292d00d245d60c3e93_long;
  QTest::newRow("-17448335491452258057 * 60462682018329598051709407798482044563915207248028389436125157665425182488236574769478892026967772431888176776611361247288995923818094648425895584705554006598306004544887999") << -0xf224f0af29da4709_long
      << 0x3e950209232700cfe4fd9fa14f826e165315227e85ac5ee914747fdeeaa6e18a13a0b834461ee05f0fd988e5ffa60c43eb01b8da29b061c335e6c787e3bb16d8ed0b8cf737799cbf_long
      << -0x3b31e3b77083ff08f55732c6492e22946055cb275a60221e1362234690d33498b8762eab1e56a793cb49ff5bc3dcb6bfa921a115da4728133b6a55239e631d96ec8ad5507bdc910fb3d9734ebf657bb7_long;
  QTest::newRow("-6742493009600068656 * 7789176906951327382622959162741541713028806683210757219980745430724852547598400033337464757750771117600238100334910256468242133191124493141004522816746294109616201213608326222174688455997492") << -0x5d9225ab41c43c30_long
      << 0x6fe2b80016156add22e998f0b7d1ce85637e934189a7a74d397b4891e53089af24d8a66ab22ec6feb9efee110d585071f31010acec90c694d41fcb37c7769756c6d2a123ff7c449c03df40b9d8b834_long
      << -0x28e53c9b95d99fe423dbfb43e16fe95ddbd40e732b588bb15a7769f467abaf0b889c9985d42b4797ff6273733fe47864a621efd4bc129b4646ba382990603d432fbf8acb52f41bd094ff7fcd7403b0edd5e71fdf9eb9c0_long;
  QTest::newRow("-283265433599956354608609372652469267151 * -12258097614885315663") << -0xd51af025e136e27b48b0f6a6a104aacf_long << -0xaa1d82d5a54d644f_long
      << 0x8d9c746fe2d0cae2b695d07975a226014bede10b4e6c91e1_long;
  QTest::newRow("-337856503985490913674605992720155007118 * -257120060583334584903354325231629676842") << -0xfe2ccbb919cecf57c6349ccb5537d88e_long << -0xc16f85bbe04249c8053c376672fab12a_long
      << 0xc00e7fcab0f018ab39dde14e7eb841507a85ed385f3a97390a9d30d44e8fb54c_long;
  QTest::newRow("-183685958722735132181137367092216656280 * -5297907489110316899491627427358040978224646579987191525671") << -0x8a30a0faca5e341fd0907885b29af198_long
      << -0xd810bc2c9a2781c3d411233d6e6698d9c1b108e5e62d7127_long
      << 0x74a2107174368de1ab0345a12a28966a84c7b2dc717309ebd393ceca54c5c5e0176bd777a1f6e628_long;
  QTest::newRow("-238776189979721192988213757411935986873 * -86712524754065827189543099739299161099826983743683758144969650334617916931883") << -0xb3a29f15f647e29a2401ec4bb57d24b9_long
      << -0xbfb58cbd981b0834c74637f54c467ef21a064041e6d00898423bb2b4ef97ff2b_long
      << 0x8685b96dd611bf284a38d3d484af437888d2320f9a5715d5e13b0fdf68b7e6d013f56902e2fb1912cdf370ac83b87213_long;
  QTest::newRow("-82694788349792280667306326042083383913 * -165727228214751646342799792624824720899630324720513338348819419660189828112914760487007260954289") << -0x3e366fd983cc27c312ad47e58c60da69_long
      << -0x13dcd0b991d5a11943e60beaa8fb7f47bef4e69040b5ae49e430b9bb7effb64eed821beb711eceb1_long
      << 0x4d3b3ce975db97768a84efcbbb3d019238b1862d9797c661d417c73f0a8d6fdc1e386685d9c627cb92fecee7ace7ed84bca31d0f0058099_long;
  QTest::newRow("-212785668488412858588235906718629759148 * -2296059549084847633554857680896911287740919328649710256010356711782555502385616527904024482323604005988688847593702") << -0xa0150770fd3ed3a6ec451e6c1dfe08ac_long
      << -0xeeaf4ef5deeca90769d510f60ea0ab7f7c751b9a55f948555bb93bbdf26e120a2093cf5cb28e50ac130ce1bfd3e60e6_long
      << 0x95412cab49784c8cbcd1c928791fc63f4614e6c28f1b4cf45dda282e4bc037cf0a67ed302517654a89b849f78dc2d4ce87a2cb938f3d4cd4a5a849e4b244a88_long;
  QTest::newRow("-65270525529548198229189513223427057815 * -3080884204245212138774965644473746400605643813661561593275390974980502831534789190012843078062073697392467183827822948418695823696943") << -0x311aa55da7e5b5acab161a8e02cfe897_long
      << -0x115ca584eeab2cc0002ea323b65f750add5ff3d37b861ff5a470fd2ca269b8bdad10d7c1cfcb83d49216dd42240b08749e3b94e5fe1242f_long
      << 0x3548a4e51e8d43e520bb18740617772044d8daf9e408101f7a98b7a091ffec67ac9c288078d3dda35fe8b093824571457fea0f07efccb928665745a4ea2ba6f5f975853697efb9_long;
  QTest::newRow("-339271966691365707658906790035080866232 * -10496794574075492641418850674004921858428853518153853825587020826353873100829052300108738549764349741618188493925018600121428302791966707965787618458940151") << -0xff3d676c2a0a49bea8d72adddec3e9b8_long
      << -0xc86b435b42338635d57826486d90246d45a8c424af398b5db08170ec4451fe0e5b3089b94cfb41d35f8aba485c9a3ce1b5e5d941e97e0e36a03d917956a332f7_long
      << 0xc7d2ea9ec9f3e212b79fb8d95241ea2695e86f536880fb696723538d24884100dc8bf168fab60600e693839646f514d111b38e5663633033f2b48fbb295723e11629228e5730fef2b4e708cdd2d47088_long;
  QTest::newRow("-61478805278772553549523510163684253072 * -72695443610266599508043807160614655569615253308443903983622941465153647408926518529719260108561578398306162177544202112634264996062295563364405861765331733339159418156860213") << -0x2e40631fbef36466a29e5540f3c8dd90_long
      << -0x4b3e5d9168d69b3cf8593f0bf4bf77a86ea81a187cb07e08bf5085ef25a9cb0e94ae9f124feca61982e74eaa44986f090a375b525e54a16e2a78c3d8aeea1580aa30796068abc335_long
      << 0xd982189f80d28d9b7eb60a344e5e9c98a974ad1d19d6da0ac7f8110ea47a61800d08879524f1b8a73a98ffa9b8ba2b47188104250f789f538f3000b4ee257e01d05225e93d11438e88cdf36647545e42230b752f88a8ed0_long;
  QTest::newRow("-131320099393755056196356471624449289624 * -1366747687124450132870142169181719435595831851903958713399728292204660602683623459848475240978318668043717392749968025667744166414595026276589435478564609781152079677141529173346739074067564324") << -0x62cb54c7b41ac91cb3b3c77b5a5e6d98_long
      << -0x4cb04b4ff2769fa0e29bbfabced9f86df55b5eac8d542699ffc27058388c4ffd2057d290b2aa02e02e75a0bcb68b7abfb1d95d3dddf7b2be4da932d30188032241998eaf960fdba5a74bfe1fe7bf8724_long
      << 0x1d986605feeb6efb72c35b62901f37f7ebda7673e45619929c81f67377647999672ba9941aef68ae75a9923640a73ec762474dc15d9e1c8686be6798cbd95cdfa8c93585d0933d7bbcb27adacc3f30d36f1f7c8ef4b200a91cc1d0c06d7a9160_long;
  QTest::newRow("-33560847261222867041743696413879002105 * 4035976592146380336") << -0x193f95859b88eeaedad530fd66e163f9_long << 0x3802ab53b8ad3630_long
      << -0x5862c1a1fc5ad463a9b463230cd01bc664be61d5c9e44b0_long;
  QTest::newRow("-175920347331011956406524759924111108880 * 277815391415754499851119056230259768058") << -0x845906c713cfdb79c35703905e18eb10_long << 0xd1014c528146f41e42d6d177263a3afa_long
      << -0x6c0d5a56a350969afc8df5585acae4f155c8914c64ee7da56b5289472b372da0_long;
  QTest::newRow("-95488745251627438640036474569524545962 * 2355191309036235922937666469953533969210202287151206580574") << -0x47d676a04829328c4a353d87ea9889aa_long
      << 0x600d58375ff4420a71780c8722b2ce53ae7696a5b6f3415e_long
      << -0x1af42b2163fad3409b8731b958bc6cb4b7dc4f835d23a327da9a79518bca02b1624e91b46754b66c_long;
  QTest::newRow("-138328558350314493016524483468371733382 * 49106940491038982521081801201307550279524933738708835606973694922026390682138") << -0x68111c7c215e5fac06cc0efbe13cab86_long
      << 0x6c918b191ba7d67098b8716874d8e29b4efc8c10916cd387ce25eda32a707a1a_long
      << -0x2c226240ffc3ed650357c58f72025084278b6bbd95936d57163bc5903e1812471c62627693e725cc03ce51ecd087479c_long;
  QTest::newRow("-288263945750899881384405145172009159323 * 1847715232669940017460508408145885269482688017880028373347378245323487562508496769272704305632322") << -0xd8dd9dd3008e1a64e72b80b9b9b20a9b_long
      << 0xdd734ad6ce955dd57faedfe557f01e868447d97bc1cd953930faa8f7cba7f6d98699c7f684ca9442_long
      << -0xbb98fc331525b6a486755b24e6cb2a13a7f1178fa37c194e2ad86d2b2c30c605e2c99fa1930f4b54619ff8799400288665e69123185657f6_long;
  QTest::newRow("-206884802826215565529401132191139847035 * 27077715806017455786855703887758242878340112389491906225510591416942391195911160512532030972667503853132694190969338") << -0x9ba4904d57e557b5674cbfe6c4a15b7b_long
      << 0xafed6ea567f6f90544da8d716da6377474a4351b8c69efff1cf8f67fcbf820d3ac853cb0922969fb03d690e2bbe251fa_long
      << -0x6af5d943bcf7c17d742df2ae0da4ac2369b7ec4948fec77b97216887ac5d889220d3150737d3102a44198a5ed87ef15e45d7470599a8eea768c0d26eaf1b411e_long;
  QTest::newRow("-62850543701171423905489024687777092777 * 162545619056308119183376996177474225007848141375939140328736285222408315071633709770505078051119794913911522399686809170048416089235649") << -0x2f48930cc389d04777d4daddff3d94a9_long
      << 0x39400e901a7b9c1866626643a4aa8ac1970517690b390883519f5ad8b518160f626b15c5ed36e60a701ca348d4c38082b3f9170b7661e0c1_long
      << -0xa92fd93307c2f5630c604ae9f2c5f9161b5d8b094319ae1d7cd1b4ed2ea3741596540413b482d1fc300027eb1482e60b4304e7708eb01821ebd60bfd6febc671c20ebd18989f369_long;
  QTest::newRow("-71132110636904480686652962310959745985 * 6458446681278943973782509092200840805177856779453518978357304015672127550259281715219803726843590915657078813663001970954253816645263071515799178234396199") << -0x35838bd2ff386245938bb9df86714bc1_long
      << 0x7b503ad37a0f4b83350abe67bbaa3df51379d88b7b0bbf677f14a7e12811ba56dd25d2344d0bb87f390199c8090ffb95ab1cc6d5d556870a2493cc7932357e27_long
      << -0x19c6f996152dc8b1fbbaac833ec55f6610b17fd0ad5dcb963bdf64f9482897b2fef2d8e725fa9f9f10e9837855ff03767dac8dff6a2f796fd6c58eecc1192c9f647222c2d7cee57bdb0be5b29f808867_long;
  QTest::newRow("-76093296827165488450396960629012864735 * 126216676475200212951933182569454931255050808868042385148202863388788174386399994823081410130823087069884248162205341821554955776509607652263261442098938794464527897811202925") << -0x393f093042e21b2175b36eb99de89edf_long
      << 0x82a412cc9c5b746dda96b85db8bb4d0572971861f7b4870a399cef5edddb5b31f0da26767b898db3f8a2dbd1fa80493065373c51ed4c55d855c771aa0bf44dbfc53e3359c5b3b36d_long
      << -0x1d36b34094b93ed45f1636dd50196a9de099026a954dd0911b4666666342da0e8d00dcc96f30d2bbd33971c1df2fd1005de04b838add4cfd3f5d476505517c804a30eec75ae46eda01fefaa56702a82d28a702e1940e91f3_long;
  QTest::newRow("-204444006677862771312876720223215181140 * 957288447378018240481698118141524607774671003537289844857210952053402705399517541250473816662382837481383965925807669058543924829996306850837426960461673429809290028133993572586019396799229581") << -0x99ce7bc2cc6dcec42f83251283e45d54_long
      << 0x35b6b901b4fa72852e1ed43faab1382dda7bebf9937155bf70320bd7bc8ba474b06a7a7ae12baeb5cecc22c3c60eb1ba3fbf84b07efd5507fb41d1a29716f72d5f8f44f79e9a809204cd77dc6cc4ee8d_long
      << -0x204587928ec9fad58f3b06d2de4f053bf65e57886b839fd0ae235baa6a642b778a29383541004763a5ce63c164b6ec49575eb5464da473888e38fddbece555233608c8d71e44d7ce4f364589ddefd97e986a2274e936dabad56a3437d7db7f44_long;
  QTest::newRow("-375329128697558370642718870576133945793584238328697893425 * -17172757770859165453")
      << -0xf4e9e732988535779eddfe28cba127737a36f569498b231_long << -0xee51e43519e3b70d_long
      << 0xe3ffcd464fe8b946eea66ab9021bfac6a2ad25af95597dd87fdc0907d95137d_long;
  QTest::newRow("-141225815289306469240268446655819949629005094679144722989 * -223954828287135787080252592026962063405")
      << -0x5c2776010fd9d18504ed978bf9d6b20bb3473a5277e722d_long << -0xa87c218923a91c2c1b27dbfeec4b702d_long
      << 0x3ca694a04f152df09492bb5d3147438a56c427112365e2f4ddcdb9de7ef46527b988042325cc1e9_long;
  QTest::newRow("-2577214323647334110165060055266686173949063014751154540659 * -214413046808828019689704512812939947975854340389996950292")
      << -0x691b5f7e9d5dcdd0e2f27599aaf790c95cb3f65248011073_long
      << -0x8be939ff90d4e6d022522bdded98b1ef9c0759d61c57314_long
      << 0x39719e93afad486fbb1b874db6d6357615a0ec790d4a358a70ede6aaf8bfbee1d9ae566d7b05ed6a6bbaa5a55f7f1fc_long;
  QTest::newRow("-2747265274173762155826584182852338817476977753123367668450 * -67606168181422638035398968977540263105520297031745952848297013516952415929999")
      << -0x700ac9ac9012e4dd1e4f72507c10e7db640288bbf8ebcae2_long
      << -0x9577bc346deddf84548754666e261d5675fa3e31e7c08580231d9d5d0036868f_long
      << 0x416aaec40d7a5c86b7abb3db9961d1180393558787b34f594c61b3f9c95ecccad31383adc268bd30fbeba7f62ffcb0d3f35295224394a03e_long;
  QTest::newRow("-5769126512737570249128642464890982561746856576265918489630 * -637427487274874044585191359012975914521405011440630754316248434373633525516229284391127893611898")
      << -0xeb487dc05557d221bc4276e5fb651f0e0a4bc7242122241e_long
      << -0x4c6571c7a1bb3889adcecb5b421dda8c9170ee89f66fa8a6f7b10b090cc7d6f69d8a8a72e753157a_long
      << 0x4636c1812fb80d363c6e3af4fb36a8a0defda234bd67a9a754473064dce7ca3f2f1e24503fd344644fe77369b14a04c855e92e83a3ca682150e7abf45ef5ac4c_long;
  QTest::newRow("-76105309837048119300482672269293268792692876897554133516 * -1087101341088932121050722331605493630365464436617192979210913570747025784240368932847528447519461311570473806398877")
      << -0x31a93961d33d66a365c46687ff340ee6f2076c601a9f20c_long
      << -0x71023629eede1d132d00e0bf2ac9e48211faea870da6e31781b65d6d08bae9bd7d877699e62b31a97a6c3591a2f059d_long
      << 0x15ec2028758cfdbf4eb0eaf8752f2e5d2a012c5782f98fa253ddda68c2175e980bf2e3f813071c002324c151b9c4077a19927a85d4efb1d7d8b62197be96b6c2fc906bff27ad5c_long;
  QTest::newRow("-3235540056463254314235897776357506547777748957587318542365 * -564829263593846455893059806219655798871104980105756348499230457182006385458400953205618329239256235216932538518666116950955038714218943")
      << -0x83f49d47efec7c696627a20deebb3c18d4b16d72a058901d_long
      << -0xc6f049489d8e6b010294fd41d40ad5e6590c2ffea6de5e2d3f54522272bdcf830abdf29d303b19810ffebd1b24bee546fcc978831b7dc9bf_long
      << 0x668b0cbf45de02e030e0f97e55686c9cd65e227a59dd55083978989fce0226e154808d44bebe3caa74d6c87d40f0fd870f2c4fb100266d48e0884c9e0bde3403b230bde1f8070fd8cad5a1b398634aa3_long;
  QTest::newRow("-531730448708928346952645396235946737340687001845625054270 * -13407244479987131561342788669023500189974157005305031316688677391093856350343035082822531119724954407189121315755805743507727948134547994914626685818130011")
      << -0x15af8660eb522685f1b0123c22fd1bf9ba1576dd0df4e43e_long
      << -0xfffd3ef43814e6a80b031eade944aadd1101d881af4eb32275f3e899f17a578d03afbee47c00122e55875fbd67a28abca324e75be8d819335b992661be704e5b_long
      << 0x15af4aa78ac71c934fa5d1ab82beb0ae79921bf30c2257604677db5b1b3faa54a4b14b5a05eb0fc39fefbfb783bfb0566fb50c5e1a35a56fb56c70a4092e62e46adb97272930b53bc9a588c5ea1a24c0d7a426dc72b8060a_long;
  QTest::newRow("-3616536031570892988627923553780900341503725179207650725702 * -24132807969843074756141597544816288218849016177352434480309038588470364853274343068018574207352322275916539983784376978860904711466809910859016614273734315260686715019533872")
      << -0x937e65e0c1f522c1aa708975b6b2d16d8c82417443214f46_long
      << -0x18fa8dec21394b86389ecbcf8d079c28a9674f936c569da481a52a28808532f583d4b12fa8dff4948a2ed5fc041082ba14df3ae09843b43b6f8a43d14cc5cabef857d3a20e331e30_long
      << 0xe6434c139736876efe8cd7347840f76bb48a6101e9941f5393b703b754cc21dc3d43ca46233b5e294f9ce8a3113392ca2135ab061cfa83321cb6977c7745674a80e712c40a6f1f893b8e7320c6a4dbdd22a67f0f6a39e81b221f3ef1c7b1120_long;
  QTest::newRow("-4224890235266286456820693264737976332245066786017259234549 * -1437378322786171119135803825227708345915074496010549235961346444972183514944455484315418111938105389563645439707939269843675464338338443053276872421372661846266610958257861174666343535954289165")
      << -0xac4de9865b71fe7a2e98cc40fa070b1665964c4504e724f5_long
      << -0x50a6d986df10e0f8a649d7caeacd949726fc4e7b45540ab2e272d32fa2c72acbb1277e1d8a493a74a8db68a0d1608a4c4a8dabb9862a34ab1af73978d44d06f83cbbacec706a81fbf99482ef3606e20d_long
      << 0x3648a5e83b9145fed9f4c3380df573c884101fb27ba969c316f5199984e9705b2776ef93a648a914e4e632b94a7cd37f4223738e3e2cf854e0c2510d5a13bdf8bda7904ec31a03cb9878b17cb5039460297a6d9e2c5227034cb41dfb0f840625cfd197c6da1b2a71_long;
  QTest::newRow("-3050280040528583755691629069869251498063064617872249290587 * 2413242403002935677")
      << -0x7c6668d9252b0bd2a033cbbb7cf28e0df0aa4ddfb16b7f5b_long << 0x217d8f2dfbe6697d_long
      << -0x10463718bccbcc8b5a357d9aadbcb256f29fad1315b86935cd7eca705d7b826f_long;
  QTest::newRow("-5012511769328020530156324779950657563388189936097457013772 * 173919796478385570466552582751495084171")
      << -0xcc6d1090e42da8ef5e60a0314ca71e5b1a5daf6a0163040c_long << 0x82d7bc015f68e1b142e25edb6927588b_long
      << -0x687ba823ae5683f2c31d1a027cc1311d973cea78ecbe6e7ab0c795dc484152b1eeab600b53fb5284_long;
  QTest::newRow("-4123837319911375408748791408083688524796359453568637456502 * 1457923840013622232857214042159266029360961236786794893654")
      << -0xa82ededbdba5c064edc99f224def3616a5d29719d251d076_long
      << 0x3b756f63bc3421cb6d7921a49eb74178108a4be944b29156_long
      << -0x270ff3f65e80c4bd6a3a3eb6e46fecd6a2350ec6921ecfef05de9ab6b2be0a9aa1f603c3306c7da80c4ba875489adda4_long;
  QTest::newRow("-1939860798413032316919777480123718995974838369117367920426 * 77613204122012440444280448982090260698677179526190638222792129563644637710014")
      << -0x4f1d177c0783102f9989d52a23a97697e329349b63b7672a_long
      << 0xab97844d0a0d8398a97a8ea9237be87ed4627cf75905aeaecf92ede0a08f86be_long
      << -0x350741bb82244e5c48a90966d1d3e59f464c540174394101e10791dfc4eb925bdb630636a815419cd38c5153f545e35f822ddc32e2948d2c_long;
  QTest::newRow("-4691297471429521241415715689201123057716406811324569772693 * 2119822518933397780048475523078819451424308949423098454429831529407411241727453873514618014662802")
      << -0xbf536e5380a2bc71870646ce22ab8282d6ce24180be66295_long
      << 0xfe100b001e15a9730c33fc07b73d8d016251ab998f3c0f4cfa59ed8f4c4cef76ccc52fbff6340092_long
      << -0xbde0c4e66b130f154e849d75fc76b6f0a5c3e3e801cd117df712ed1d11efd19ce01c2f87e7f907bcadc8235d4bb5c6048db1385921aec9d3b7884b68fda838fa_long;
  QTest::newRow("-3754357006215337066622770681355789902970958365171186194812 * 275988164860716302619497685485185632072269938031549126783246571643197415211125532123034447886407318563071182374682")
      << -0x991d50ea51156ccb90e80dcced3975c608cfc6e17f50d97c_long
      << 0x1cb0aa6f882541859ca2b7f22b3dcad97bf321d32d734f8971b08269963c5474195718be1c39da5e901b384351e071a_long
      << -0x1128def16ed5a17bfabd2da20de11d6a6b5fbe13f4a5c6967c91816a85aabeca61dadc1189fc2f485f12381d7b784a5b0632fa968c9d90df97760fe97fbf35a7490ddd24cb07a98_long;
  QTest::newRow("-5743209998668382000326231966027084876043048294018300442443 * 389723464443365346882709068116921418010875031141483742730516386936944283875473659319489360126393219802700192857949183017414583605448658")
      << -0xea39e901d09e074e6da813726b1e7147356ad72312def74b_long
      << 0x8943bb08fec43dc5ba824d315ac86e679398c5ba05160bc8c2826a299bef1d1fff0a83f01a295208aead7287cf8317129fdab3a09e52cfd2_long
      << -0x7d96f5fa7c3ac8c1be97b69f57a62fb2aaf20c93ad1b4c3fdc9df2622490987335f199486c60fb5e87817c4e82c266ac58da3921fd99be45dff738165ac3c2f8c4d8095d58693775a19d7ef344e28086_long;
  QTest::newRow("-5318006120034486859768794230736582629319624203737009723131 * 8921399588481787514978372943283392785045716225528091117843779217026377760993524093431984223562016187837895257571940014492385109275667581878849168209640922")
      << -0xd8e29315ef49c47b8863914b5f6e27744e1c7757f6ab96fb_long
      << 0xaa56e4903c540e7c98e10bcf49d4dfc0ae2e166d5b9aeab870df7f0d848e512c485dfc155bc0cfc323008dcde7a96235e375570b34fc09f2f78fb3846e1c7dda_long
      << -0x9050136df7d3f5cdb125eb55458306447bfb63256246cdc4bee7a26a2b7deddf61173c4d1d7e2573e16b59c16fc41376db05fa42902b49f8e4121d9474379ab3c92973753895db2130e56e9ae0341933f260a46a344b20be_long;
  QTest::newRow("-1526589232318862898538258289564428650881194724986325366336 * 172515946777932604246386444843607651893246811389112703616739983048321997806532920221993122470974482073016733081497565164501199260978888030011632775833928386473818258066648505")
      << -0x3e4255d3b2e72ad9fab515694f1d456127596ba0c434f640_long
      << 0xb29027199cb40c74f05f01c2b213c1cecb80eda0eaf87086adcfbc5eb0d6e65d0c6aa633a4e3cfea4bf22e165e645338fa7eb38bd3e90c6e279e07955f94ba2f29174492a1f02db9_long
      << -0x2b6d2e7fcf2335ba417217b3202f27c1afb5bf89adf28f4568079bc115b2f764c8506ef36a2ce592ae06e72250e2383d6601fd09c8d5e67805b9c0c43eecdc907adf4515ba000ec9cdd7aa98f0e9755773b08589b0453f658104bab0358f3440_long;
  QTest::newRow("-362666275993223430224793210366053630056280281831445957839 * 136412878622498230059524186252318147454126954541063711653797178513390098253197500195869657818240256463183369300656820690239690992049134859040493398985044768379615842183973051516718331335950791")
      << -0xeca699fbf76895611af734f0cd6ab74cd85047e38f50ccf_long
      << 0x7a777b26cd29cb9646b8f11103b8c8783865a520220040f6b914632da470d21afcb2e339c7709dc65a0d3bac613e2e57e0561cc0824bc9468c9c65263102218bffca4057886b77f16e54d2e124241c7_long
      << -0x7135d8ab9266d04425dc1766de0e533173e01023f75018531620ce62fcbf2af56ace1219d3ed55cbba606df44a3295e83499a95380305dda0030dde6dbe310ec85fd6c46dce424b0f78afa35bf06d5ea0c53fc29d7f54b93f652efdf1a6265c12404da5a1b83e9_long;
  QTest::newRow("-67343671314733232981862352380837075016776716989273258143906428919429353069258 * -11793625991875123237")
      << -0x94e32ace813af2cf8a5932e7b4a790ae5cd4f0d9dbf44f3776c204297d225aca_long << -0xa3ab605ab387d825_long
      << 0x5f305009048d307907b5309632d1ae9d20172225cae7b9ee99eff4942f9803b534fb493131178f32_long;
  QTest::newRow("-1991463845318904276958931040421519129134779683924722419977245630903502145713 * -110722521235720912078735914709795687882")
      << -0x46720eb7074fbe1fe752ec0d647611871e0318106a202697df124cac39e88b1_long << -0x534c61c5492b3d214cf89b3bb0d34dca_long
      << 0x16ebff8937301f1ba217b3dfe709f769938e1e70dab337bad81783186c9fdea561c1ea7c52fd651abb8ea44641818aa_long;
  QTest::newRow("-91285564569243439977781236455230595130388670928129885276817318945295253546669 * -2151863535299242890734296126446906742939673418709923898165")
      << -0xc9d1cc6fb12e75d28c4cee52ff65bc0ea1ba6cb9ed4cbbffd22bfe7e1a02a6ad_long
      << -0x57c280eb076cd3cb2a2396955a8d3bbf3b9d800d67a9a335_long
      << 0x452fa31911841a701ad8901545b6077f403c3d2eb402a283f5379cc8742455f2f657f11d4d23eed4c0327c6b788504be006e2e43b5e1a8d1_long;
  QTest::newRow("-10941230709649495348174334417702919906179885762825702200987903388453659883666 * -31570687581558938506651612889525590705188067461386831491749826073890135998376")
      << -0x183084627176df188a3dc386dc2d4707658e6a08988dc7c3cbb2562b14223892_long
      << -0x45cc603d96e9155c394ad81ddd243f34c81dcb46fafeb7e8b37817dcf73bffa8_long
      << 0x69863700a7e5e9bdf979e202a04a6de65655e6f80937db49c751b6ab01c6a5f800d0c8d6896e30bef1f613cee59c0fd609f10fa4b450f5eb825d94334748dd0_long;
  QTest::newRow("-75575242027162887840260915739625025499546175154356615618892170628359283136969 * -1198248170300018950210892493544108287479311585289762885999686301545781463086607617012410161181097")
      << -0xa7161235ab1e494b1f65424a9afc36e5d0ae67225a234e2567f9092e4d5dd9c9_long
      << -0x8f9c739ec5677801477f5dde29ca57ce0926f94ed5738eccefa846655d13d135ae374a61808631a9_long
      << 0x5dbb71159def0e9ba67e4f7a0948fd7cfb3adde9e63ac53a629738a18d2117dc4f8643a0575f0c23c52da8ffdbe05faec53748ab3f19a63cfaacf196848726401cc6f78d88da3eb1_long;
  QTest::newRow("-95646795888321373469841334207593756991538846169649144431453277796217035293917 * -29812225864938554825219264597991657811153024410450765715185877679734253199292284640582307993857838599456187136234523")
      << -0xd3762b04066a55cee9f50b0a6084cf00f5f5007ab38be315107d261bffaa04dd_long
      << -0xc1b1a60c2375844a110285dea86a75f15b0d896f07201867fc907b855a6c0d224826545f444e202fd88323cb54a2541b_long
      << 0x9ffed44a6d5774b8e52c9a506c8404d6f9f2df8fd711aac57d7f163c8e89821e558abb79c3b2b36c88c71c556b5a5dfdc887e7366357e1a7d8df0648a8cdcd73a1e5b03f22a8352b0ae2da465861074f_long;
  QTest::newRow("-56709474691332133941708214911216769293810961244212721360998283170138953080628 * -601652174381006355806040798667523431583397073729553030363021066041835642948275777394544505311361922276569694145592105489765267954257408")
      << -0x7d606cdb45feba48e36467d926ae42cdcc36c3dc92c53956a732b0fee923df34_long
      << -0xd3e874274c73bc44e021b4e7ce71349bbca5a5a791756f34b55a358aa8810ea8c05d43e778beaf14e620eb38cc468229f0c4ea726ec0ce00_long
      << 0x67c851fe51dda258864c20626ee836b6aecc92282a177e13d05eea82e76e3cffdc219ca9241d6d4924bcbd5754fb39359ea550ac5dbdc50b4539a61a523e861f0229551de93ec63e1c2847163f600347519851929c9bd800_long;
  QTest::newRow("-62662029214099927141758470570726796907350746832324764682984483796966180166567 * -8564396820170830970301960499134114897474914311192506187888599287627036307328435507500541915761475614917711241200542963465089007807486980647529058945768852")
      << -0x8a8973a1c143f7b8c9caf2c964a67228690e9672145cbec73f8e048ba3349ba7_long
      << -0xa385e64f0e7f2b4f1e5013d7525476d86add6b08606eed73df17a4acce47f8ff18136fe9954a02df7208dc47913e2a4e83876b52e3d9dd1ed8769c2c21c49d94_long
      << 0x587dfaab573e078b2d156a3bd88909881c95d6d0d8b47c07b9667e7b150519e0d69ae121f41e9e929231e3e0e901ab588f883bd553091e63e5eaf6955589e50589011124e15a228e6a10dbcf7b08e7ef2af38aac57b45a1714b584dd50bb678c_long;
  QTest::newRow("-45677465253562526725203640236629599510335628933738344074490720895619259630114 * -143478592987879229792554049753585273837108431332610786130058581443350426058641366852375327643692173773578861831346369622657251509165772678210180653725112457896084779272816256")
      << -0x64fc8776a9cad14a09dc31bc69fdd2e75064bde85b7167662745a0e831c30222_long
      << -0x948206128f3bd2f30c41b8af86ec3dd89b1579ab4dcdad0dfc8386ac0db6f75ba19baee656dd4884c2dea64d347fbaae278258793567213689aab0b136783eea40f25740e1b4c680_long
      << 0x3a9548f2a1da71654f51dee6e0ae0804fe4d09f810fbbdec52f1941380bc083edc6915a1ca545b9285a86923bcc11c6c998d40e503b42f0a38c6d975e7d71767bd683a5757efa5d5244f589c6ea5e194160c65b9961d22d3cbb35b1c70bfa1beeee18313170f5d00_long;
  QTest::newRow("-52969965542663507554593746047977410761521931678844153714922138713789310671125 * -1556986995869957790801273607426602817550818479030240241602619950943944765919830385520731174228590232522891746793844580396402273955080786111060676048388555315271086809895161347362388572031551415")
      << -0x751bf023ecec6cef09abf9492e1330756121eaf8f8206fee351891023ab79915_long
      << -0x575cf0073163292c911a852b49b176b6bd3755f11aa9e94abdaa1009fd938192defe66b35fd7ab5cfb72866270219956b6a5cce2dccc9b9501c04e4658cc55bc7d8a86c88ebcde89cd8f3527e8c607b7_long
      << 0x27f70273fdea72b01da9db4c77bf4a5a01522fb1072d0437ba5ea28a6e088ce32135894b0e364fc905d94ef2caf478b1aaa4f5229ce29b5fba130e145762b5937f492d62b390d5cc4864bb752500d66b89d65198b5954519afce547ce39ade67b6c7ddab5f0f5d0615db30216cac0103_long;
  QTest::newRow("-4330509439972506974719312675412810352228520796412068175070007343202672594780 * 6012362263929016558")
      << -0x992fb4280e948c3fbcc271321ae3c616c897fd5191044d8e1f3da10b3884f5c_long << 0x5370339fca73d0ee_long
      << -0x31ed9b2becea5bd962833a7149964ba3fc675ccb2aca22e7129f7375131a5558ac52063e7888788_long;
  QTest::newRow("-92352763873558200644087240688986804945277168608538215359218808895710387374311 * 47007064911391747999724082141794091434")
      << -0xcc2dcfdded87af91e09b32de453f560b7aa78f624e4a4fa09b602d1e6a8208e7_long << 0x235d3b3c71ccf5ae6aadffc674f341aa_long
      << -0x1c349f4e9f81664339d22e1b290ab3bf815f31c3deedf48dd8f0e59e1f7c0d8b4e5fecbd2c62dc06c700b05edde19066_long;
  QTest::newRow("-91508829182215898158948908497674761214504084059305948248701977537342722791501 * 319823866766111517832677306586582689299672784998108847119")
      << -0xca50297072e46e089af2ab559318e1bd8779a5b3912ad408276a61f7177fd84d_long
      << 0xd0b1df1cd38dcedaf87fbbd755773343c191f5e6ae95c0f_long
      << -0xa4edb36aa026a980ae4dc3fbe6363bd15898854739a9e6c02ed893a71dd3453454cbc33533f5bd4580d397afe50f46d4bb79c1e124e5883_long;
  QTest::newRow("-68424638541067606706675894412430799886563062166475415596161741778278301409073 * 30524448088345548831936233128539276808944496184484571134797993210364280236558")
      << -0x9746f91559d599d8d1562a7d6a795058f8953b7c0dd39a15f9b4cecc85a59f31_long
      << 0x437c39b1f4d0372322ed4deb0cb209e837abab9aa019d5f1c93f865dcb3cea0e_long
      << -0x27e0fba9330d1325ad93789cd4dd9903df200ddcf61fcfb1efba0478c9da03c0ed203e3eb6abf631acbc36526664ff7db20a7ba354ed27f177616432dd0d7eae_long;
  QTest::newRow("-72942506802548302712314788459919646675905994097939960883670464969960631232821 * 1804619232076505958809654688565757037412541194847481682612360457947008527653609206419292838619674")
      << -0xa143feecc92472839894926ec9292177dc258998948564b1e3620b8f283ee935_long
      << 0xd849072ad189d79f149e0c7179ac8d324498a60f14a3bc3873a2cbe570908db4a5153a555272ea1a_long
      << -0x883f5fff505bc0b3bd9fb86416f82a16ec05bb4a0fd76218148c1ea71301b80f748ba246a6fba25fcec5b6e2cb93ed50f82566b252a588018d88aaa213fcc6a89f3c8aa36b282162_long;
  QTest::newRow("-36136589994936388769086073007037673005015296938287969179667481178581391840803 * 17462780482757564603391793222026492708874560323971837433612365383296658735634808470430720735687530210757873169647786")
      << -0x4fe495cabdaa0a79a5a610ab824ae1ca1ffda7a77cbcfdfa1f5dfedb9dcf1623_long
      << 0x71753dcc8e47187b991f5ebcedfeac483fb1e9b559b741d34208a1ea3a3d47a1a839ff4ceba6aad20ea745fd7f4cc8aa_long
      << -0x23687ce041a0653724cda5988c8d6282222ad430b3108ac7d83f4d59dcc8fdabf333563bf3b3685dc092a70404556cbcef02c81100572de4ac658cc7a791def6e214c19f057dbe880178b62d84340b3e_long;
  QTest::newRow("-93611634151188817392722602394344178606388612238238473874731311433996853784865 * 492053733523358683532863664865834417063104644635711277374122575285132669738648015184772686441716535235431903033121408536530686650936865")
      << -0xcef64eabb1e51e142c14f988cb049251fbe0278fd58c5476160b76b8a33f3121_long
      << 0xad4e6c004545fac0e909370df9c42f3791e1eff210f2b28fcda446bb7028de1ba3cf5843d9a89cb1715826a8d689878e347e3221f6ecee21_long
      << -0x8c1bd98620b96e7f6dce1ebf48f54ba6a3a3a569141cc078003a11b640599bed8dca2c2aa7b02574b388bbeace455e2bfefe2310e43a1d6dd1930e630969816fb121bd6b76fd62ff290235ef18fa3670a3eaf449cb3e0341_long;
  QTest::newRow("-17863173541761970884989754257829357305553622333072202326381423775721115486065 * 11563467699608789011149062191335467765813063071598574234152722130732493057122667045057975395385684117418633517900673788651891473154179698792194902226970737")
      << -0x277e32abb810969b7c7ee413da150dda0f3912e05a56669a0ebdedd3131a0771_long
      << 0xdcc90d807e43278708dcf4bf6d7d8b17c7d374e4d8cb1cb1106af9ceb8a559b794c0b5e3aef21501b4924cb42123fcb3ff333484ea1ec3d2cded94384ea52871_long
      << -0x220f77b696284db9952f3e8e175aca084d0cb4bac599e67ca082fa8014f9f8315d69ef64d7c362c720778fb3480b4c71bfba2a6ad26b4e3fe61bc002a25ead26c695c6cc6dbad9af4595b85e82ee9031f982e06953f67d26627827eab97bf0e1_long;
  QTest::newRow("-42363662390901911057552671511379209059387242393813997431522022780692391455264 * 114495373656007417029088977748273995180796638395292807849672282635721660131823796206914721182928294576511822469011498677031079830674107793255404550324276734957941283573701499")
      << -0x5da8fbb30f4e3d7cb7f8410add33cc7875354646c2b2a72b7b8f19017402ea20_long
      << 0x76823d28c2e84f577a226a75636bbeb3214279c16170cb6d8266891b5036137759a4e27e022791102a3c104c1bd775a27d1b4724d2d95856a21c146ebd36d694afc56740cc4f9b7b_long
      << -0x2b5b8a3487abe19bb1aa41ca32ab74fcf74608c90a73c6765dae9b5eebb1d5695070270d610534834b423705e771e8b1ee766cd37f2102fb20ea29908f1bec12fce7f19860bf909c72bc5bf7062189ee9116085acb6b890ce69ca40e2b57039e19576c684107dd60_long;
  QTest::newRow("-92470700246380051377568367609202563984495592693995578979188586951090570788722 * 4304919773604090161383088924900169834676618507901789380409172503801015499939458701833492128928559047295429124960725411070256282220700595346798724919221194969199693259208035841414296443994016135")
      << -0xcc708fc51f595e08bee3fc1587b081e9d316071db6061c821cdf63f7fb4fff72_long
      << 0xf18ce88908454f34235eda7ce97c18d412fdc49545444e7c21bb9c73deac4a69b3fbb6bcc2049e4aa1d8ba1cbfb4880822b0a6dce994f2e1cd8b8f970337ab3ae4314c7547781b690e4bb9d0d75c8987_long
      << -0xc0e67e9aa372b961b51eaee0ce8af16177796e6b6eadf6615e29664591df5025f8aef39d019b99655f033517ac676c9cd0756b82496d8d90da6629d5efe85cc7f2e2b97a1b54ce4455a9c83eef9b38c2df1b4dddd12ff430de9fd256106f80a27690cd6064d1e1910a7adc2be1dbb71e_long;
  QTest::newRow("-1150068498154639958727549379592681408938524842411130522980948269507578485752670727001962356753428 * -6797947274470542436")
      << -0x89d635ff9066c6ef62df402722c38f48e3cf19f6f729c2746f2dde568954856ccc32654178014414_long << -0x5e57290770a6cc64_long
      << 0x32cb95b78108beaa47edb362aa99e5d6f9a166e11f01f997308b12cc941b8c2b98ebcf673821c6a23010285ac7b687d0_long;
  QTest::newRow("-410744818580494202955340499937969474764244022079485733789139306475946308958895158629413510365468 * -151452545247657489901242754382670444646")
      << -0x313a678715de813c71632c97793c7ccc9c632aff76386830ee1f0259a6c68b9587c435e98892c11c_long << -0x71f0b2ff12d076881f541d7dd651b866_long
      << 0x15e910df5812f5ef0b46c2cb249a39a3d944a90c819196cee993591a6060f3a1045e8bc041ed18c5f439e91ee00aed3976b4afbe67211128_long;
  QTest::newRow("-479861716743239970172866207719785962772971675709563896952241617093668559865667588294628351119992 * -5079303605350672419006708966608617637262799922161406021599")
      << -0x398309a0efaea77f4d15add4ed993e0d5defbf708f98a26d7bf5fa865dd94cb943847796854f9278_long
      << -0xcf26676da02ced40c254bffd35a1c7ba6864d70584098fdf_long
      << 0x2e899578e958a52938c69a4040dc7420dd57ea85f8656c81e9474bf67f2db810e08e5c9f50c5d3b13a4a7787b4f5676a8d9167457696d91705a99c3f99599e88_long;
  QTest::newRow("-1608299419860395553058247495919853221834668814838537065706294460813499995268187925170061582330917 * -38926065902647450863166693680642879560796193276439996923850935566128310059857")
      << -0xc0c19379c3f0d24966b9d7109384b8b9c61fc0aef589f0f765eb8510e109fd8001d1983b7dfcec25_long
      << -0x560f5f5eae7fda07f23f0857764fc554dc8900edc2f28733fe32372a86b70351_long
      << 0x40cc9ab1ac278e9d0b22f71fcd22f75e6bf93900cd7464eb8cc02218949f07961c6afb690f188c989f2202e7d3f7e85e036f1b8308ced4893d8be2c55f3295eed60801c7003e26b5_long;
  QTest::newRow("-1116885844184150900582626645248899815869037970019409670722274637700014514440568127157939977165586 * -291000827052399571598955446332180024364182948825410618292403751282864297677386531781518529499376")
      << -0x85dc1b32dbf4073e23d0ad3583f1205ae4bd936713dd219e0865681362dbc8a77be9e525fd959b12_long
      << -0x22e07069df81597da2ee8dc0ded5a0916463e6b0a99a8855a2b446b3a47d49fc4b61b770a8f990f0_long
      << 0x123c96fc35c2a4f9cabd9a4b37f3cb35ada41d6960cf530dbcdfc2a683e4fa535c1a1c34eb9827fc76b18c221ea2dd8964b7a693cf81882bafdbd1ac8d829f6eddf34388493c725377a9bc6987fd80e0_long;
  QTest::newRow("-445868065070887226233736651551446186218621238183183736997818621362295120420958115610550900039774 * -8046812574656073374217460602637155090542329950729879355390766814532825657781070279755597859781149981209554972582506")
      << -0x35700cceb1b5014f87404f7c9e42a41dfcb83a9a5d8a38acfe747483345c8f16e3e0a3cff167205e_long
      << -0x3447fc7a7198330c2aeae381847a8cee02e3aade9fafa783ed91e726bd96c30297e0f0e6d8cb4bd0754a2821dcb0226a_long
      << 0xae9c9616523d9bd1602162c66d3ccc0ead3e5acbb8b0747a72bc916340fec07f4b841842a7296b5c3c928d39ac853ce06be92a7c7d6459c6c618b6926bbb5fb47a07d47ed43a7c55d486e7536b35c760fb5e4feaf9fe2ec_long;
  QTest::newRow("-549152347063812870293783214771795397452290054102765447273074438928846629488192697292415963379567 * -151911448768246001090390242548239167047431972785670373925787506765202521192839730594669254785100232433280182544472398279041733551773061")
      << -0x41d100514640480088b06a9bd8e98c8e97a95911336e3880aedac0472ff7cd6bd9af86373712376f_long
      << -0x358137e54b9f96dcda91170bfb98a43c07dfc8d2c8d07e85a111c51ffe645eceb2d76356f5101970bd4f6f0bb79716ac34fb77fe3254d585_long
      << 0xdc17dc0d6f7b6c84b96906a5283484f8010d9b388b68596c6efdcfc7d051a89e101844e5839c1e0aca53e47e6eff57e7518c89a88937a81c345d7e3cf26e19af8589e18bfd7cf9213695dac40bd284b3e253cda90e77b0af768e571a30227ab_long;
  QTest::newRow("-1168794310404429257493605393692170711919025080205647321741728117941730659609223386932332572890456 * -9321645199473618105243762589915694163944251404837150607458121331170712746140875271571153429742414470308769013001953928516925947029249013967353810810788104")
      << -0x8c14c0d180efe5eb168ef406f61442c4559e27cc20666be0fd06d09350b4d50100de841fb8dad558_long
      << -0xb1fb40abb4aaf68caba284706624b7200eba5948e74de68e094edf4baf7b795eadcff987cb67e6d7b1d50a16084221109a17a7fdaee5a52f55cf680a28335908_long
      << 0x6163d50d0c7c999f56272a650fa9bd6de5e807ef3b322e50e9b1e6231e21960c8f952bec221595dd9381199d5fc76c01491e938916c5d1ad04ea73249e404cb8c251cc8d79112ab140ace66eec0d6960e31e33568ef85376e7c26dda6ad60395837742a01b8a42c0_long;
  QTest::newRow("-1454855736079063465087280924164281462883324829527038167669686935552479470973838148828016928771959 * -109644570287697935230516230629373129931382725674993832283278875598762117057697216280989747755299535131351136719710354329475978204383162605599054310824167628075979309665798528")
      << -0xae5da475877ce5b405732493263963c7107ff65e64c6bb2fa6bbd8ca7f219cc81326bdabbf224f77_long
      << -0x717ce793c90637d8e9767c78dc34200e5d1176716a404bdf6881956b14ac84819e034efe1e259b1c43139c89a9656be9548fef522b45b504795fb1829e2aef8ae288d7d11698c980_long
      << 0x4d4c68aeb1d300fe3815fd630786c5d94a497523b01b175310e89940f449990b2f0a32daa4349c3940f3d4e49da9131a740ad927a491c4f6fb50dac74bbb0af5d7fc1162ece23c77ef7c28840240ebfe81d60303cc4ffa687ef3920b53035bed0b3bea13577308a47fa8ef4bea342a80_long;
  QTest::newRow("-275075828064767595162863130873073750021189795283835317128664000042386165354498722795680780708365 * -3082062267963810196982586462047459310585137704218762214559875597523337430713790769914313968067127495903263050349654462973774133315154903375796780952523459209448688120651457939570403877390532134")
      << -0x20f7d4b853665322434dd1d812065828c7725b3b8b1ea4d71169027b88487d1ff30a16de24e6ea0d_long
      << -0xacef7ccd1900e270bc847ad9976fb511eabd1836ef7de3d4a34e869004a3346b5b2191b81b8027ee761525b76463011f94dcf65e7373c5ed41640846fc89f934689ea6b18a01ccbe0cf089f07cca3e26_long
      << 0x16455a5de4d58d524a0e21e403c3e0dc6e910fdbc007939145b6090113e385f1f1d4f5185eadc93b7196e651271c6806e7b2b26af91e6ee086ba410ecc84e8da576e479b90b228d4a8780cb917b58153cb1e13421df07bf5c21829d3acb62d75566dd9d2a9a4194869db8708699fc7c05e1e8aac6137e3ee_long;
  QTest::newRow("-399775205298277545731664899891572362045834350989715099190681923797826695568317801302873041430688 * 13966306591818094740")
      << -0x2fe9d6281b6dc57b9d10146a462d4b66803c7ba8d310c964bacdf39a94a17e5d925805bfd1f668a0_long << 0xc1d249d93d839894_long
      << -0x2446a618405f92fe6d936cda21ef17e8a62d8a8c231b3db56631adc07e3d26be033c5bf4410b0ce13571af355a737c80_long;
  QTest::newRow("-1941697748646296960872584768468938130596414062279979348128438318369703808567061672439129801826028 * 246864325171007155420433906166805025064")
      << -0xe8b6d92ac9b91db32a0fd7fb2d8e5ae4b75c80cb787ced45051fe032de70f4e7dbc19599e01d1eec_long << 0xb9b856f056bb81da286ae99a2433d128_long
      << -0xa8d3b563e9bf9bf4959880d89944f36823e72fbf8101cf0ebae1a8c8b3569b620131c87592d5dc9b36dd0c6422cd34a4d2ef242123cf80e0_long;
  QTest::newRow("-1864943447442320282828970232971001798900092291001600901774741731777449401617288247824736842121328 * 4530993063505906916140862392413904063711482561745404788922")
      << -0xdf83e2b4a109e0e01111fc603f05883cb0ed7c1628669b5da45fe9f6817a028bb23d303137278070_long
      << 0xb8c9c65c9fa73907e89540366e3ffd8048f90282492780ba_long
      << -0xa156f6afb3b3a27c78ade26dfb77241c895451a957fe33f85392f5159ea9cdc27c3e5e6c43a8ad4ee00a3f3a4fe5638426ca17345b1ad1a636c762da53fb5160_long;
  QTest::newRow("-1134849653197642952966077303830171167562738132653995117629065433338392959516344920743323793670864 * 89106383933155859765650489559674104863029867641955846255018247097860107637723")
      << -0x880344d39a44cd28e399aa8c0e3240f3aa9d50818131c2fbf061ec3354e5d450fee90d9e3fe8c2d0_long
      << 0xc5006d1180f6c4927767e065d045b5fd741f6a107af710086e69f4241ce193db_long
      << -0x68aabde986c15a9b4389e5e1932a88da480e640ab7595af24086278dd9e6423b3511bf62d8aeac3aabe64dd5efcae8b6ce224dbe96ee0f4742ea3f0841dabbd448fdcb354ccc17f0_long;
  QTest::newRow("-978806823599302855727108005454622698445873396658449832194478544316690882304908736812809744426808 * 1596964736094525712538164529925167087364732931751778623898452178251658897202798276820028033385346")
      << -0x754f96b0c02b26ce5524d0075c0ac8668b9c573334457a359fdfe4f2454576eb587f0dabd5762738_long
      << 0xbf65cea3f39e4db2844840d3e6119a771123ee7edb121dc14e97be9dbdfca95492f1b48cf29cc382_long
      << -0x57b508857fae46eadb69739451c0881b3be9e4b1f48f96fffc82cc1490393b6e14a2cf4b0fa1d36740ff1c1065a24051d05cd553873056a30a2fd16f8e6665c331e4dbc79f50294d28576c8e3bff9270_long;
  QTest::newRow("-304420866853791015858093740770192486293953135061873383420266732360968709124953036303951530432734 * 21221367402615881026712391577988709824457705287577757708219433884641245026621030805289515475089573979935770513581549")
      << -0x247c30c7f4911b8c6ccada79e8930d2fba71f2b01ad49c92b82c0ff0e4b972bfb2248bf084ae18de_long
      << 0x89e0c503d9a375a85e635524c7e99ed16d588b1950c3e291b62c01cd4f000e11880d63a0a678ed7c56f09c00f39d25ed_long
      << -0x13a67ed9cedaa97317dd0397ef5cfe7fa223023775f34db9717cd288a0b031b37064faeee055c831168c8c628a64679c38e07fe20165490ebb835f6adb945bb8cd8bbc2956a933766c28e85f33ace36a4fc93937f8eb1b86_long;
  QTest::newRow("-1997578152074012577735146532027821219559105235633585904010578283197217869667601093732933423027155 * 205425102988497028619968103630126974546793953485447274555280991631929014266436658259789735927137875046171957757073008574792092643142190")
      << -0xef695c907e690f28c36b58b82047765d8e9ae93bce79e8fff91d7e5f0342aca0a8f7029faa1353d3_long
      << 0x485a51f568523650d751ae86097d719711afe9d7c93a2d2d14a051f1be17090be275e1dadd19adc4066cd73629fedaccd1f9ed37b972aa2e_long
      << -0x43aa19b90608fba13116c074a5ea10af080d7465b1bc10d938c82cc4c4283bdecdc03e2543a5525be7aebbad27c29e3889aa00a60b78f74a6df8f3dd0f7b2953429be4e70dcf7855b1600e770b5a02b05c740d30ab0b83182b1e8d2534192dea_long;
  QTest::newRow("-524752732105020601190922337486113732051906039192419929356639659481114092917971481761562355569177 * 5409981423005907545058790660344151547308936548554637050770725660384390840086221747163789027980844360286741795956149332121004432885706031729645477807534039")
      << -0x3ee460553a20d2fcd61bd81fbf69c00fb07df31010cfc5fbef0f22b5d71bf61d5bb1b81e6e101219_long
      << 0x674b70385c5ab4d2c6ff7286ec45beb199a3fc353b70e40d544c0dd73f16b7f03cee900c1d1debeaad3dcffa58389d71eeb70d94cf37b647821b1d0b8c0c2fd7_long
      << -0x19606b3c4625f3e97885455ea16841f0bece921ee31e1434b6e1ad067771802843e828ac3fbf1257512bbf23b1115cba7be2d0ca7898c1845c2aacb6440d2a8233a0c351a9fef08bc79f6192d137576f0d9624056565733276c9cd3b617a7f1b100dc67ce7fdc9ff_long;
  QTest::newRow("-1499230432612282650348529333057631850063499804788750315808218413978642899915817481303401891034226 * 205773045609800419187747458718716254063161459338225403877010520853995189758918930903797800117757389463214174822422331381045781322198366587481379214857636990416404577384619416")
      << -0xb3af23b6277aabdc49b4bceabedabbcf4f07bd0eb93e54ff0b5d2a77f4e2849d27abe75d79eaf472_long
      << 0xd4fc66fec2c067f1464715d105bdbc47aa012ee25bddc79fd581541abb860b2e7b2feb3cdf628e7bbd5650191c43fde9b6125bc7b6b0b15dc2c1d591b1a3c813fb851ec8d9135d98_long
      << -0x957e324498b23ae9492dc78da6afd5abca17eeedaed92d607e9a44b16ad55313063ab7c0cf12358b3d38d4fa556831e1cb78c7ad36715b1c901bd3e35d1b7b653e5fa4c9b18f63ec1c53503f8b7c8980f1ab910749f58a45a992439d7304a2d9af03bd5bce791c1cf6d4df7f84c48db0_long;
  QTest::newRow("-890363541515199802255906324799037689300485462318833729872658826997084775165174373120173556034971 * 2755322316807706691396738634460004809467450021323187048424065696648155603325492125823550394296492054800499561173459960047071856398989077895557982109374271217290885039939661684240995993623663596")
      << -0x6ab5fc8ca7384c95ebb5ef5119cbda81f76e1b0f944b9c50e513affe73b8026dd701eb84356eed9b_long
      << 0x9a9a1da8cb9e953bfae3109e0e2c07a9881944c669a67ae81fc395c39fc06e24c95e615d8346e1cb38e8d6a92a4aea1e64c918be4bcb123bdeeb724420a9de893dc5bfe0fddbf8de715e7797858b13ec_long
      << -0x4071b7c3831e8af9b386c5a50ed54447aa0b0bd0fe330db89589986bdd228941dddb1c43485134c9dee7a43bcf34618768bf044ddf4f4ea189565b280559aa53db3dbdf083cade1dcf22dd26964bf27c1ac001e95ba08c3d1f83b61e4fb6d05cf80f6fa30027b3a24ebd0c7c83df4b76a996c5f2080e8be4_long;
  QTest::newRow("-19466180982149032419222956916798943921596630454216346553666238469972029049664582485071855362640545569577248990863670 * -7352549256701110019")
      << -0x7e796daf9fccb9a54d1c1d58aab7207857d6b7994e8cc1ffc72aba5e77aa0f4340ebbd731ccbf00e34c1365bac22a136_long << -0x66098097ef3b6703_long
      << 0x326913809b8068ef9654f89740924fdf1b6e4ad939164b974d6cb12b16fb1a959e256098d189db38cb3d1a422373d1427fe59cab84b69da2_long;
  QTest::newRow("-23435449010209974384941266424042865853920332197134383973280179941592551540735724724106790478382560310068537087723390 * -17200405936750263569040151727340937112")
      << -0x9843601261b3331964d522a75fd0659d6e5f093050cf1a62f4dd1a46ddd40fb3b2851c79da9c20654769699e7ca3877e_long << -0xcf0ad7cc249d11a9b7893b476ea5f98_long
      << 0x7b24edaa9ede9b5ace45def6eab899578708a308043a5c547a1654c30f04ba9f80bdd5b113f2820ce7df6fa98dd8916cd5181e386e4042a73f272e09d8c34d0_long;
  QTest::newRow("-17575769213488979949833386244404337843965411740313468499347511360134880181175039991032646244573859877682473274124784 * -3858281058193431763530494270296907360249282960807051523195")
      << -0x72312bf2635ed1d3e07f483688b4d18e97ba7dbeb3936c2ac6a912803c32b2d12862e7c067359a25cadece6209c329f0_long
      << -0x9d5a5574367f8e1bd05016ee9e672293f9bbe3aae1edf47b_long
      << 0x4630735b4456bfe5d47e78de0526cac4c8304321a55de68d03d6c6c43129afd76bc968d98a6743392275b8f2647722cb61996266eb0dc1a35651b285863c9f1aad33d55277ede650_long;
  QTest::newRow("-21427270728893336746416555964559171547666978050972887779995258305693848818674872651439886278618529413884151781021328 * -89414709933699714927798948532979427859306699226272666242415495438251048873754")
      << -0x8b373dd30fe04932ca939ee78f14386fa3e7e4f5d408fec99e6358cf9d5f2d54add326175c0c4a881a8761d34ef65690_long
      << -0xc5aeeeb07ae843e881fe157281e684d62cedb56d37451ba4868025658a44af1a_long
      << 0x6b80a3ecc4f7bf17c76f6211d66cb5ad8f420ead47e7552303cca75c865cf720e135dd5512e63557d2c709e3c7d68c8a2e0658df35f32c5db2fae2b2f493ca54053bf32b4df0d6298c041d5908713aa0_long;
  QTest::newRow("-10003768883439954956116074708136299167580132080495140911746797252682320035592511251684039185399039458674407207285426 * -1424720828667530051822595796041350987202023410980682123706612740226869589287253046455983037343219")
      << -0x40feec9d8d8b7172530fe1edf203ad57c02979f2dba0402ab1268e42f67e5643f494416202a46dd7994b7d57a1c332b2_long
      << -0xaac10c55f812865802ef099de951968889d3e6ceb85659c04778e2519e20d7974cdd0648e6d5e5f3_long
      << 0x2b5a4c72c97debaa0764b81939e0c0e68fa4150742eb5b875d320b3d0c9dd0ab2d9beef0e427c4b79578b53efd3218ebe35ada7d2a32938b941044c60e11cc4cb6e6f2336d17a6dedf20c30e5740ca30bcc6c2e742bc58f6_long;
  QTest::newRow("-14680966940678117630388373647025518150130028346496072537773243189711099420838437353722247059436111705173596877832874 * -38104121051436860249593958984419305836259547919030820945144845701481261512389000335061143031619456966814377773887518")
      << -0x5f6258c3bc22c4ff475c0aee7971c6903afeaecf60929a318635cdbde65800fa624b066480a65b43212b8ed5a2bf42aa_long
      << -0xf79145b7b38076106852f1f36a3fc5f0c4a7a9de71d85f3ff4fffe7c68baad8f97028a951633c2aa0c774434acf3f01e_long
      << 0x5c3e0453157ef29f6ebddc311c2210869b79b5c2bbc9d82c945d40fde51322707401042e1dcc02922b4e022efe3ca95273af6a9e00091ea96ec9ba5473f1a1706d2b1e7b31b01d4ddf817c003fe57bb6ceb5bbfa632ddad2a8b9b47ae0472fec_long;
  QTest::newRow("-7732147150194249406031950752632713676434803281318427099417598026314983913792997849398265820668879634665918652290858 * -345166826567782739757609665909697494878413284459053234769765479167457797396278595396043461333134820455269973833422305065689828017903839")
      << -0x323c9d344a2003275e5a51a42fd9196a21328146e72acad8b86caa4dc12fad9f0022ae522d6293dafdc41c545e2d172a_long
      << -0x79923ed2bb7b3afaa24eb9aa2c8f89d78bb8176dfdaf9b4e0c9ac9fc882aab26915357b5c8c63dac6a163166dd9fdde13a9601a6434118df_long
      << 0x17db593367717c1f9c00cb2b895e8dec04a44219610e6b17157600d39cc03272f8d69074235ee9de7bc54389571fd74585697e17d92d3340f551c392914dc10674a2111a0113af9dccc0070171df12bd811671c8114a39cc802226130182cc6b0b7e7c11231d1d96_long;
  QTest::newRow("-25140273224392539849790541728483243397036686831200270000361628166673606303752515532081712300475948575611083500125119 * -7000412053830590628744532368170813784611824114533354785037634549197520770812341159435560709724385028480604517685924811312593681114021642911681596037318684")
      << -0xa356f36029425af9e4acaf447096f248696520903f97e29178c9f80d21fb74103824d324bb5a80c59b5ff39b2dfd7bbf_long
      << -0x85a94d252a9bae090bcaab35f85f531695366beb05cd3e23ec3fb7682ae83540db1b65876a642c6f0b81eb957a431b2d5ce7c37b259fb5dcbea026aef5f8c81c_long
      << 0x554832107ddf67fecfb7d1c992079496751c2870a77604953e5b7eedbce51275ea250faa8beda768dd8d978ddbc90e72f7166bdf74dd434b759a4aa92a8f4c9b997d88a830c30e44c6242e752ef74f107522de6592b136a6ee13ffa010d2b7231b714b698b16afcd72307bb6bc6ec0e4_long;
  QTest::newRow("-4950973672706593821665506228602062318552394140574096182866015360003874660123469443159380428614032821220636135585458 * -12125644186979243479863330239324246779281523301564829210896403943710195669791597026300925311312954490392639565283043171593697893985038548244313381694796861259114642336709001")
      << -0x202ac8b4ec6755bce1a3c153b50f50b9bf48464e4cd317e3f4347e80ed6b59d63fbeba6c73dc879fcc9c7d277754f6b2_long
      << -0xc8cf96a1b8080c04dda260fe210bb5ac76bfa292861dfbe3bc7eff208b6ca06665433a9d4a170631777b145b60d86613c67010437d26c295d78f997156cbb032dda25e72768f989_long
      << 0x193b8253069de1f20aba97bcb98eb8e420c17328af021cf3d081d633eb2bbb3037195c009819387f163188ae65b769c0291e25248ef13cad0abbaf171d8d80603435102370021943d8e4169ab2342788247e3f9a75f1057f8dbe6062029cad0dfdeb23fbfc8d4b4f5f164b6d83213d5e3971de7d6bb2742_long;
  QTest::newRow("-36474639676442015644421203170764656921253096269759575963218303669652977262497803982646672161155984116738158030263025 * -4397170819561169896267982828708426254640887754082254330419355649050413277610222506289299776432716341536607480771803415082075440810073891170286123254950613517132666780636231207938641485585063241")
      << -0xecfb0317943ee3063918da2ee1a1d31d174403b2c308cd3d6e4649e94a5f91d2cd936c5910e4cef55c4522926d6092f1_long
      << -0xf6ba06508f1e8a2804e0e8700289fc117d632e29cdeed09cd751862bbd27ab341dacd666851bfff927258b165e13bb1552f44f45d0b45ff93ae80004c0ec0c7a7d69cc840a7680b1d9e23296d7fa1d49_long
      << 0xe46569315c9624b99e5645a262823bda6e310b4fc19a97389777f22ceafa80c0ea65739d2c6e8e49f831c68ba5d7383ee28f994944974a47c9e701e8f06e46473c23e74045dde7981243ee1682e588faa43a1505e671236b5c3ee9848dd1ec7d5860685bede9ec5c90725e2c26e6a224866103252c5d5a91d6878913078933b9_long;
  QTest::newRow("-22158373349226283021457925632575187504877666474752686434911615795029570127186957682560322792733765059132857205877031 * 3759933492705629417")
      << -0x8ff7426253cdb8de2b87f7818cb08934872e3367397d6debca54398e5ad1b6ed6bb3d50abaac61a5bfd2b414c2436927_long << 0x342df79733d014e9_long
      << -0x1d58132f3d56d2736b6cd93d7f38a5734093a0a519ac84e11ef98f0b0c517fed25b78256a2f437a29237ca530a8cbecd887b71cb4841c07f_long;
  QTest::newRow("-11353273979530307197320891845791657778414937493255124522473167280103758663571276218220266127696669998487541186032091 * 41631049408926607476520228074823517401")
      << -0x49c382773b0fbd80d7b592ef05ceecdd67afae4815bd702a3bd06ef52f76a52c18f0d94168fc9cd19ad3ca51875ff1db_long << 0x1f51d9352705459ac0aa048dfb5a84d9_long
      << -0x906423ec22ff96d21657a9422040b3eb36852dd7e379a210e24ff5f3f5a3ec8324b3b442dd759aa538dfc233f5d1602f2536dfb5b252c326d4ad464f906eea3_long;
  QTest::newRow("-19173811150943510173180268902474398486460046976006160746337144518768582475011854153894862945836681282379206165769516 * 5627414660769802042082640151871418223880410611982536274292")
      << -0x7c9323c93b587b552465c5e9eec3e1b14c3733b8e31d02f664b433164135fcf5303dcd64d032f3ab45b65ea19ffbad2c_long
      << 0xe580f35079f5eb91fe8d94e568b42b4e2b3c17de7eb7f174_long
      << -0x6fae5efbbb003c25d68c18846136bba5534526c6bfeb8fe3c4337c249170a5208d8ce77f3ed308c5e976a180ebdc6c2a991935bbb0af61c834689b3f9c55c030cb1f6524de84e3f0_long;
  QTest::newRow("-27047152307876198601017645049422167448955177586975289230154317233959528775844125580563362727337985318182380478624613 * 90902458169960763981533947445993797395637343823766121565661154606865202878713")
      << -0xafba98d4d37d1f1529d1bc47d4cbf0b1ce25f0a2d51f5c6d140b53d13d93a3091ec1974d3350699ce6d60280999b7365_long
      << 0xc8f8f7d190f56f79d97daf283c438ba0e8552de181fa11c812b7a90c859518f9_long
      << -0x89f4ae4737b42f5e8eb6e852164e271b3a2ec455c50a5ee26a985c36f41cf3cdc0b9709a8da5ef5302dbbb31d08dc1d3a128440ab96057df1d37003dfafd24f23ac0a4de478494b044b5bda59dcdb53d_long;
  QTest::newRow("-27312774620830180199251730613903930704993947769915566596708559083470192609093796680306233184245677599418768183415589 * 318707995506104904583206359379123412235768120951348559151093957009748104423910016081417116534018")
      << -0xb17465bed70c57d317883cd3e13c600213667c3dbee53587f87afdcb69bae039895aa516d579ef69e7eea4b4b7da5325_long
      << 0x26328bbdad28c648bc689e04690224e1d953f39e37a951deff71d80f4d43855c5bb884f41a8f4502_long
      << -0x1a7a50b3e1677e7f43b26f147591a5277a0e1d6b89017587d7ac0b06592acb24c4a12849a5978de92ad7646146f20ba8169c58031b05cb0d4e72ecb40ecd881894a01ccc4f6733ff72145c87252a3b31366f31a17bc89f4a_long;
  QTest::newRow("-31422376838519937533755105376758306744095417903534313453981634225287881804998677381867646000176400935228698104494165 * 15275692018423803386018014189307620553989790602843782650152652600879269998208807209183404952006065207378614423943033")
      << -0xcc27c1dd9818041b38e5c94761ac0b6ad4d513430ee77c2afcffa9b1546bcbaca12c9fcca80983f28a73ee848884f855_long
      << 0x633f8850748894406fc8e04ee8b2fa06f2d9a2813d5a3f5e136313478535c54ed56dea29bd73cdab9ca7bcdb96e47779_long
      << -0x4f260a76afb2f4bd99314d11ac1576cbbd194acbe8753a588f3aa7c0f4056c2f52a37570277f0fd44c26a9088eff1d0e280eac77ae9af85d0a2a2dd5d44b07c819924b5b4790351b7a84e5a8d43ff22ef2fa454d64d1c07ca644b4c04ffce32d_long;
  QTest::newRow("-11360368495749892389460936204105995035286983956651882372313800267938191091644650000033587295490916959011391679095529 * 293434486205470856332768951269940548988838106217170702867729127483639115546343167321015278334041027275005315864259584783794064854527442")
      << -0x49cf4f48422bb30ca43f535db7067ded5cf2b4268b98274d6f5c079c9863998131973b45cc64041ae23530a567a5e2e9_long
      << 0x6759c1d7967f06723cb92e6fc10533fb1e330f6630bfde7c137e8ac2fdf0c5e7b1740e4d49bcc4c315664bdb506cc5fc1e97e904ccb6add2_long
      << -0x1dcc49dc1603bdf65177e51acbeebced68016b81ac5f2d223967902b72e54b4d7717d67ef090bea92ca49cabb4fd97f4e7a7489247a00ea4abf80304b241b77e5f2942631749b12750daa993a7d32ae88b2f42c1563cb9110a761aeed7364937a53e2c1f1e119822_long;
  QTest::newRow("-7228994246504987925850943749499787496996298979085436127180128707892762361252280611528191170204073887210388924178887 * 291903169979763314214950536808794429989131682359138536718473279685930636077061039285934601420075567970012452373122503560975076169998432902926128897420802")
      << -0x2ef7bcb7f15fb1fbff062fa97d80c52900796233511e3e0cdec4557a25b61d599c58dd7d5d81f9858ca336ce0de0a1c7_long
      << 0x592cb0053d6b5512e1d9ea36bf116de5cc6db962f597424aa475b6fd32d76eee0f3a60e537a05db5a41b6f11532da312544822c2edb48bdeb08ac8208d96e02_long
      << -0x105c537baa619ffc221e7533a972bb0090acb0425cd8e4eae8cf03121f88b341a91704de15dabba9c099229892166c21cd6dd33e74d78573732283a04f01b4ab7330b774d84916058f8c3fc5ef0a1d225577cba9e4ff52d749b085ca27a07f51b471750c74af6f0d3e79b17faf3c58e_long;
  QTest::newRow("-38981361445543692362073849337623265944649299614983011729017305801283515479237160660731022511901195661072337272993377 * 191266737026806447091814217914425155473383979804396280088910292161428715915485998146452475531900846968112953784158114503119286305763419074499727790310241348763418881869392209")
      << -0xfd445b27868afa96d2cd0f4cb188f0578dea10f13065fc4aaca9c8c8acda74c2d3d48a0007f6073275b17dc7e34a7661_long
      << 0xc5f89d76b79747392ed9ab5ba9e2845bf4087cf9819d5a4c421b34b20f8d0621f6878093b8b473adc2858186ed44ad4c9fe25a1875804667476d76b01fdefad43a52df7a6b36a951_long
      << -0xc3db902617de12259f699c4c9ada0cffa28b93443eb3965d8d3660d65d0d38928308271f665a11a2c935eedec09d2d0acc69e44308a2b1bdfde97430a6c4aeb4c311c1e03cc8cd4099d286603cfa5831a85082835444d025137b5e8386d216121e46d4a086e8250244c5132e2a7e18ec9108bbb4962b7db1_long;
  QTest::newRow("-32417982646191378594907438187897684606211078658870617306965843140828409627619499019812709468079895938351344738124550 * 415421143515921996487088781963077622647779540034244700381914157321020344235805063547022381597361832251439635681989802801372338528973402269059987321357682702984594822837606524223452100550306362")
      << -0xd29fb6d1f5c5289c63dd1d6ca1fb22b5c803ac38174bf31b8a449762cefe1ff34a984c341c0f2d3d49e57f43579c4306_long
      << 0x174f35b1164714bb6a6167c10d2e31e2282a429c288cf6573b9c013bab4c0bd3775b1e148ee395f7c69cec8452e483ce17853e2e9c2051880fe6a1e49f1f848067c608db715bac7c138e21f8da0daa3a_long
      << -0x132d84e30b7aa29abfc87700995325dfa89596d935ccd9b3e6224b4938a3760398c0a807a82ef94e465b5ac074b9f9dcf01e0bf674ba805a627e77964f789c3ebb68a9127dc6974cf9907e305dfa0bd1a97fdb30aa5933e1eca524282ae324f5924d663cae6bf37bd43402088a39616b185a7f1f94f5ca1296e0c54221372b5c_long;
  QTest::newRow("-194455973444361973165510056219125335523033883758854427959448504334427093035172379002368324890842269496543536424962140260583177711004486 * -573509079805495510")
      << -0x447d479cbe76fde47927e50911b64a2d1c9579efd035e183de91d6744171cd2b0078e05e4f70e2424a0c80857a27c198b92f6ff945d82b46_long << -0x7f58378314488d6_long
      << 0x2211c0715c4a05a3b8777f4404b5e96da2f2bc520e8c9a1323b22b331a05dc42fbf21aa468b29549ca88ec6ec0df517497dd3e6f31a09bb25300fff1e495c84_long;
  QTest::newRow("-359388294912009264398057853810277157334790331562669047867303242370784560262160753381690728171758439594906888008452670104317994836399651 * -127967599426746004103582574879328414805")
      << -0x7e94891b23a4f24be6dab09cb0b67392b23a753d68c4c347cfb3271d1e00a01517d8d10e0a2983c47c1e2830976a34e5ff4a3e93541f9623_long << -0x6045a9c529f43b999eb7fec6ef2bac55_long
      << 0x2f9a2564ad3d6fbc4e5708364ab24703dd1d8002648c49210b0fcbbc5674f2929333715448d9a4e382fc2a1dcff11096ae6d3f98480c9e67f1af3d7e475c4a5b08643afb0c3d5d9f_long;
  QTest::newRow("-269310320544722125608419104750212089529926201625551300451945372686985878602870848392325617772410634372416906287073921348852814189489752 * -2223455518773056798159488262501488925981423309594679658405")
      << -0x5eda9513edb8ea60353ce4e498b58ef73c7d3450cbf2b4f19408e42f793c4fbc5a14469dcaa020c40451eb6311263b2d72645d4f860cee58_long
      << -0x5aadf571ede72ab83126ea823175b29f36e7fb25af3947a5_long
      << 0x21994d1127588bbe307f4a128f9d8a14fe4094b6e6c4ae4a5f760a07d50ec77b3c034e8fb635f98ff64302f50f0cd9b16d4db06891c1e193d931720e6d9d2cff66421b5cd55f30ad62df9cf6360806b8_long;
  QTest::newRow("-487775157223078953377266468765863771408647105080639830610448762678765616270608482131529873228051817563619320543738446241846443530162506 * -65872846706983711058703575533390211693607189317488594069650632634270759127304")
      << -0xabcca3fe08a50f7066d3e86fe89f5379434df5b1a030043c0ec2c7b9c4cf82cb51fd6ff132a9c893dbdc3308d73ed05472ae7999c546914a_long
      << -0x91a2b5c1b036cf37b5aa40257b1ee33ed4d7a8ec6c94d44feeaf0c5d8c5e0908_long
      << 0x61bc1a5c5522adccc0bd18158108186b12cc60a35f9d2f18b7633e839839689a81f07bbaa7d5c1928bba5f75ab024bc37b13136db0b62bcebacb29b57b2bf24df9e1d8cf7d492cf5c5c7b958117df77e8d1b7bfd767c2450_long;
  QTest::newRow("-568984967973671678787629514179140158372308220712002492215127901354877911217928668582774397237420782357077563882269831815490823352348174 * -376255905071219542434058396797550682231507953905352455169544162379459344779695209601338493399081")
      << -0xc866fd1b9c73ec80ed25a833aeae010a11ba9cbca4578b1a9902d8de3cb3b3f1bfa429017a6788f118d6f0baf4a12405dd27749ac13dee0e_long
      << -0x2d1838a5d526dee3dfd5e2b6a88964c2dacd892df9a661c5793dc6e59e641c937586ed4b7eb47029_long
      << 0x234d107dedb256d34588b0dc20cf57d76a6713f58d2fa76da7a166e80a001a6dec8dc6bcc0f687070273902ba635cf26587cba2335835da89725814f6a95a78264c1f27ff0f30d1c9838d7b7c89ed9072648ce0a57705d51ca1d702450e9403e_long;
  QTest::newRow("-700970263917175107047937818895158756227203571993233981055160465353567962443697863873585111499909791475823366029794708793092314985808937 * -29483564282361150845199064936346539085144182848235670420742860091509965461086437049385724132985506865109243190148998")
      << -0xf6e38ca56898838fc16e877d75e88982ddecc1106323fdb976ff7d74576b49627ba28a6310708c0042dd532e7ecc2b9151d9a26246a24429_long
      << -0xbf8eff43f52332bb80f87e756b6841f88b00de846ad7b724f12d6eb5b9a1ca7d0e87bb873f1370fe900c13ffc1897f86_long
      << 0xb8bdae559fda18df53ce1d6e6eaba9e3d2c0a32e098e8d16671f6303982ad91ebb644a0fdaec9c8d7d666621cdb46b3aa5713211893392be63edca11407648b3b1f98021fb599b5a82bb08e94cdf5bc653fa61bdef7cc31c3baf019153fef85275eed28bdbb10476_long;
  QTest::newRow("-254763501587831725459403115428854875470106971302404480129954967761752638995133584522477135924047809119591475990320987230414436928596944 * -680360263374255074726502949908711621348324131232554396624109779017697166398653638397658431717595000150946840171227919980006763318256086")
      << -0x59baf4e82965dc1b8a7677bf183e12c24e5af2b9b8316101385cecdbc58b71f98c2b61c933dfb0c1998d4a2654fd845f4a90132924cc2bd0_long
      << -0xefa13b690a554bd362ae878985d5caf0ca7bd50dbee24b401bdfe283b0186fc9f483af9e5c87389c9d8e026410fd2d57b239d1e817eca1d6_long
      << 0x53fe0e0bac674988d83aa5bd0ec02148d3baaccc195b205948fb8c8a55ad4d2aa535b3f0429bbe897eeaaf48d6ca8f0199e9c6eac67207ac0d837d0aa1524a3be2bb0db9265c361e59d330dfd98e8d47a0910935408571c4d1017fe85466833cc05c5df2d753d407b6d5ad313dfa6fe0_long;
  QTest::newRow("-459830926786209980410464926488139968082168869060431704108324731746419103491117232818638223291397794856812784001609747921977576877233093 * -7383851083652729271840579579292050928513937068702905852981893924857856235122787415628491304121210757414665943971114865715633760134187913063873155611359255")
      << -0xa1f506c97b128efc47f716b5f46b7c57857ed3cbf33895ee5a57423c11d61fa1b5b6f7625c3014149d5811cade95711cf7e1a3afd51093c5_long
      << -0x8cfb83251be015b95c10e64344f98171b195104643799e1715506bc52582c001987cf7cb3396d625e6d9bb90ce52bf790302af97fa512ab50bf31ef6cf69f817_long
      << 0x59311debb35f8258ffb5466a538ff67171edccb74ab8c994dc93299df1cfb825d08dbbe4edc41fd938ef69883d823c0b5769aab0079c3d1da1c801bd9c0e3f930aa82630e7507a300dd33b52fcd73d038b09679eebff2b673c06a499a921ecdc7e018bbb95cd09430ec559bca8aefff1967cebcb1a711eb3_long;
  QTest::newRow("-83889636108024976998847550552224249356766958245226708860225286165400164906364053022818263033529706634232876927036983068651936673286841 * -200248299397392346934513728811055572865605620137863239879138953500779028774757096203074731580673438565053555935158707747488582268912650652055411237250842262431198911483608323")
      << -0x1d8bfa0a8566e54e721dafafa422350ddaa259df48b028eceba4f12a832e90dca522dc3da4073ed0b82ab8156c28092898cf02cf8909cab9_long
      << -0xcf447db4461f56aa034228fe566477cfbde36f893d683ae23201f6b1730f9521af32ddec3a1b1319132b02acff3fdd74416d31fbf6e96a6a49892ebadb27dff459b45238671bfd03_long
      << 0x17ec16df1444799b2e80fe889b4b0fb12f0b336df93ba2f3215fb44c45f0462da0cd025a5880bd44fd9505590e833fe57e35e9d24d9e7690b4155df1d1760ef41c46f22276acb05ff208e66a6facc0ae783148f8458af7bcb3bbad8b78ce87486eb3a0edd425a3cb3792a86e9bb82f7ef4b682ea4923db71246221ee18f9352b_long;
  QTest::newRow("-148108873764184287748560190859320989914891899814135682562337442992986047633612611297615023894746266795591037489834558102790378285879540 * -3690940029322279008213599857864653594110325833313447985627881888460986768104258032415806939823710135198609698858133864833631191655458998827789809958645382054403555763489429741080161423563813454")
      << -0x342a5b2952fdd6be300eebfcc42121ffedc3f6bcf37171f8a32730ded458ca586779d3ddabe87427aaa038cc046c9d333ec96bb1e246d0f4_long
      << -0xcf198e0b9cb7da7f4464699fcde761be80b560714e4a2b2e9a5709a360f82eb40e20493e912e6a1a0b4a8697d04caf1dee0f22271742cc15e59d5fa2536e50e27c9e76bfe317afab3bc56c642fc9f24e_long
      << 0x2a3374cb2d76789779259de007b0b52a9ed78900cc1cde808e01c39aa900af634168d713e1391ff5e0587df5b183df064634daf01dfd19bcbe3e2b2a773648152c8c2f91eb286c9bf70eb1981883961b34d59e5eb1aed5d02d55abe4b17f2bc64d4e2c65b04e38e4cefccc317ec5c49e67900c2f70ec43107bb05f00eaac8c780bf73160beae5258_long;
  QTest::newRow("-507886702849040358933293782943760102932302955500472471826973802919052879397901764053124881722202356125632759243675857848601015615226432 * 17124641237160924697")
      << -0xb2e203ab4de330ff09bf898b4ffeb2cc163be9c39765900d483b9904d4011da5a59fa9807b0ce8f9ea0ce8abdc9fd230a2ae49d9b46c0240_long << 0xeda6f27996fb9619_long
      << -0xa60fe56295fbbbe854eb1c20089c612820160cb5bd0d877459f709a97ce3fc93abbb19788ddd3530000d20f63faeaf8bedbf8c11db2956cd112385719c9db840_long;
  QTest::newRow("-82565259584783682963756017999510214807719350360507963376713119561332737369697863294779891493708277262437220232593296488830119582958893 * 334804470671471977261103111798949106813")
      << -0x1d149030d7fad8e075ccdeffd81762efd94c75dbd5ce4e651bf32a085e5274a8bfec4a3c3e1e2789a4a368709c7cc5c9250cf6962581052d_long << 0xfbe0fedce520610901cc30239d17547d_long
      << -0x1c9cb8518d4360f9de86450301f0612443a5e6a4c7e733218b79d2ca3156d1dca3cccdc9940ec84e9f06c2711c6a98681a4753931ddea76be1509d802a8a57bd33334f89b5bd4af9_long;
  QTest::newRow("-155001899965276608208401321698197029300496203980513563904347945984367262489329248334970645483032744437554726982930469817603084950201470 * 4531835225382089431232913804392481479317237030717847430223")
      << -0x3697df11fb2d4d4dcbc4a7498f399f15c436ff6dcf5ea0cbc702a3a2ba470fb2607bd4b64f1a2cf5ccb7bd2e5b21d68c6a1f2162f72c647e_long
      << 0xb8d2914329a10fc90890198d5336447af9b591fa2f5ae44f_long
      << -0x276a0fe44141d74daa97b0e2c44e62c4e6378b6201c1705d036a93e1259cb3dcd6909fe9559d638550d7fc9cd75ab692b63ab6ad63281f5bf35ca9811b0ba02f2d23a9a23b7f3ebe82defec8467f3ae2_long;
  QTest::newRow("-476955647731945680117949216941549145948580726053390862344107585759416385486719160378949580391600194813643474767773582350984823356916750 * 27628017760267946780636526294552686019035105238979988358196636463444485306761")
      << -0xa7fd173e2b9d3e23414e748426221c7e75bcc193ee031bc1ae9d30cd929d259944ab21c28757b9b509f8663a8db8e75a8db126b9cb36040e_long
      << 0x3d14e76613addf7b18618350642959673233e51492a7f0aa682307f901617989_long
      << -0x28150627fcfa1da015228cd9d783a37141d37460fc13c9cda5926cb03f71951f70567300bdf222af6da1b5c1bad454fcacbff770ecf4f169227f90d335c150e65c0b54e47178f94f28c8c1b8e74b484e54dd1393df20c97e_long;
  QTest::newRow("-433416252555292470562997287485950678117034993398277207126281288647724479624989998704083607139274507059533316034296199642645508691759591 * 1605589743361536138879675384359839526726954560106251082031495442431780206674084619099165803427783")
      << -0x98a7537b29ff948add06a93c45e236146d358c4770a372d58fa3788bfcc8cfa4280294c5a6b639a1426bda6498f6052257d8b192f7ce91e7_long
      << 0xc06e702ff5451fb8ecba186fd79426ca248019129871bca49a156a32ed4ed0949dd840307e8437c7_long
      << -0x72bf59680beb4c1f68460cbe0f5965ae82575e53217191f5108724998c7e9bc4777844415f31ee63f302d03f214603ac3d80b5cb40b8c3d6705a88d4b316e01f0047d07c6818bc4a99b5c094c1ff4d3761a2dc0553a52a879e752a1ef0080b91_long;
  QTest::newRow("-671940244439450521595361051496559808856888151560890554692137090924552716493981113241104397274567761684377337035050467206830763726145790 * 32169354260371183885314496141514327981219739214548550434926654287345900770922368965217206087883184118162169552012201")
      << -0xecaa08c5fa21116aec0e73c89e953b6f86395abdfd4d1d764af5b697b6f4abb621a90c4b2317f901ead4c3ceda5b154895f70f465a3108fe_long
      << 0xd1022dda1a6a3ce65b88c2686c89fbd6d4cbcc96b2e07144ea335026f5aed5b010d79950d075b016fccba483d6c983a9_long
      << -0xc138d4e13782b4a1ca985a5038e360ca0b8f1182ed1813a528e080e4ea8773c58944c669a78a2a4413faa3b21eef39fb80222b53a6b8f802526b7b38247cebd956285baa0293185e19525c8acc2ee7bdfe72b30abeb74800c6358fe778a289bff4d035970566e9ae_long;
  QTest::newRow("-664400409054097475328810430248461466799461682567387894074497038468335794154008760577265410503801156838230824927737121464693943312534388 * 151072505863341050560781313294013553348960033296826036668961767167898586808651634058185081917210977470238509369946758928398442416321868")
      << -0xea0232ed15a3c497bd44fb43404bbc027b5d90cea59ddb5c43dfb7190e20d06ffe7b7992e9bd4c4e394de7997bcbb5cd5b25f634344f4b74_long
      << 0x3535930a7a5013ff84008b2bf078820f9f5aab49d315e727ad09bc4633a908b2e362744dd97ebe78b92544ec0f4af3303510776b1098354c_long
      << -0x30a36d6877b2c287a0eb0a040289793efce86b0dc762aa62193f4bee62360f5b5235e2a6b53fde81e2b04bdcdd29ad312a4d434d352dcbfaaa429148ad7480ca520d7437490b9ce0b777db523e6a558d2fb39492490aa97e6ab70c3f9cef8cb0ee2f9fc7542b1839d1f95f9bff096a70_long;
  QTest::newRow("-78874487329659243719581431606919578740359606318298616833871045507309536182382859021213727301485725554450034120048487662057185925793957 * 3569715857662076089124868392601692875429730032375488141421522581737557808082165421099446807811978338701030104654902765388921802806024296282200155156556245")
      << -0x1bc7c82333c8569a83b5a50e75125bd078b9762749419d5b8ada2364959c4b1e042edbb7a7fd8a9777174af84262b858709f5c10b15608a5_long
      << 0x4428685bb7982fa3a8cbaf0e029e852b896e6cfeccba45ad124a4320bfe76ead88437d347cfcaa0beffce8f186ef589794f4cad9ace09c35b9cf8d82244aa9d5_long
      << -0x76573b3bc8013b6cdb57231c34094b283652c808ef37311b0473cd951d9eee400276a9df0bce6f868c7c49a855e9e412337587dc080389a4e610b627a834b880893bdaa1cee5fb0030a242433ee5af1a42fb97599b6fb791815da99db6cdb6cd78d3e06b08f4b3b23659ea529f9941189003fd50bfc1e49_long;
  QTest::newRow("-716568178640283895751905728969177596018298595020732728809592969972578764558525976823658192329134596382515037239378493534441386412759084 * 107285165427044118096780850999713363395172993240725357417672020169806135694099518734233770787861576312052436014829781035286939848537731327922923016395191170831682450448421351")
      << -0xfc61f2adce4289a7f7cc5cbea6df597d197ce4b77a094892e3bb133c638549a95348c03afab69f57b4df987e5febac19a9eb13d1a93a582c_long
      << 0x6f0bb9901dd51f1516774d3e50127b94d7f581214d1aef5ce405518b10970414b8f3280694066e36b0b7a4244d222017c8956c25a67d15f2f8d833827c8d40cd896509b52daf91e7_long
      << -0x6d7a075fa6c806ff1b1d3646e5a66502c3f5d6751b2aa861d2d128b5a042fcf59a4bef14bd429080b44e3562f1ca32441f832e34f3dbfdc18be169e3e17ac45bcca3974e792bdee618ba1ff506deae092c1e2d514e36cbc95209b2305df2e055693eb5ed9ac90af898b21e23caa76a92f015e59398bb4934e9207687c1aa7bb4_long;
  QTest::newRow("-445977402045176288665023015563441533740168981261260694466458016548738249313691040099664105534152061028196177040259666990482593281263158 * 1147410459645056960546951273076571631383051291959000512486061890723879650294230255566528416580034935643565407868368509327931701618686968292096659749718671302823747122913276587321727284341053754")
      << -0x9d13e98af17559fbf77eee3a2e95d4e80206dcd6550699aa25fa93e795a4f4e0b06e583d600bb2d1fc7d04f9a383959679bf4bbbfec4c636_long
      << 0x4061ae64fc8b9ee2055da89b9132b665ef87f2436b0ff152d0557ea66bbc9335271a17d81c008cb5f10104f6c479e20df5e12626de9342dd0d9fbe03d29e3aa431a691fb28388c11326f1f18097f193a_long
      << -0x2780e9efb97bc38bb87c5387515efb0fff6d20282d2a6a74493628e7a5ef6ee577a05b347112b8a05fef4175898235262cf8b130c4a91e958fa89613ea05037b6fc76842b118738b4f6ea4eaa9665ff0776f16e08d8b5e83008b041d582ce6e862848dae12ccd02a74e625973ff11734b408efd6029087e8ec24e36bdb012aa3a5d1f21f2aba2e3c_long;
  QTest::newRow("-2088557097061937523923191851888165281708580276095611012042890380067212704130357597976378004985163127241577791588789078172032270277573860401190417668059566 * -5923637383664629981")
      << -0x27e0a7892d2775c85b7b3958266bfbfb288fd107d5897bce4b54f2f0405ec72784731c573f9a4356120556ae5d950595cb810b731fa779fdaf8e0cb4b17531ae_long << -0x5234fcd0cf8df8dd_long
      << 0xcce36ada41bbc9de34f466099458eea5b56a6b525106e7edd3dff4ca8be39e81b8f0bf2a9227b24ca308fde637090a44e7a73b0edc21195b46b43c9d0e766cca46b29fec9227336_long;
  QTest::newRow("-6270103832697659827312995257781160330337233445157584574907205071713646742410338674613205647560281860986729525524726379479303726508972786562339028443741964 * -92430632835987099268768454554853350101")
      << -0x77b7a10e286adfbb5a1334480e64b833b548d5023bf489edce0862941a450ee10b0f7eefb5b1f684cf7ef4775d736a4306aa0a48d8bb22b6d659732c56423f0c_long << -0x45897e0b06bfcd678ee95e9f67a09ad5_long
      << 0x2084ca9f8ac952d58971fe834b018bc6590203a400b881f181349a1205eaf24584a39209adfe3bcb04b1d5b05a828b8aa2377460ef699d2fa61fe887f877b30c094be6cfa13ddf9eea57a100da8bacfc_long;
  QTest::newRow("-6378248479578474670024923479545423094766434063170832913708009725257637494763291348706173742258619963291587303536727200591152796940350571463763818886240264 * -4434644755937235363826165492484774907941465486981444615363")
      << -0x79c83aa9412ed44f16019afabb21da301af4f9f28986018e44935b3b9af167e491d7c637ac462dcb0693cf588a83a4ab0afac08dcfe5eb7787690511bb309808_long
      << -0xb4dbda01661e6f8ab5d418e7383f74b2440ebebbf2073cc3_long
      << 0x56095f3e5cf04e687ac7e71c2c91d72a97591e7142ae4bdab8c3671bc7d43605d6b1059e39c321acd330f29315941654faf9adcf6421f7356fbbaac7ff5a4e24a668272574e76bc37a1c251bdc68b1eee6641044b1ddae18_long;
  QTest::newRow("-704748651713088672479847493213027918811487079205499856707857847210430674852053951608425936735546720604505884851642373076359348912784149533319456323434356 * -62914996125491735531592294725457107998579552542857553242315314538547032747559")
      << -0xd74bd59e9625e6faadbcf690e620959911d4402425a38beaa984a5a0ce51f35e4109c5e435f71ac2219dc475120bcefc0a5740122c31203352a66e3312a7774_long
      << -0x8b18a039fdd270a6e1ad825c8786f63058bc2dcda90b162103356c28b859ee27_long
      << 0x74fae2d94d41432f5f8b1783ce8704df21cf4c3076a650453e56df757f2b579a5784a0e77acb113f71e090dd5e48521d9d8dce15dc1fa3d133677bd09df602f4ba159a289a55de205d4966547126e432484ac411328a6fe457b1c10dfda0aac_long;
  QTest::newRow("-11125408655474182533778222384628320823988798030831539569725736773027389787429053344611966608680094654747777167771443010149619867767116274906075799461137172 * -359912056934462168757582496954915418651429392349649274669670653429386147948338491357378606726346")
      << -0xd46bdd5f616d8fc3ea948722ed2a0944c1c1d0b6351f360bd727373633a0c9c9f636010ef495faebb29e59f60cf3eccd964a460332c2b56a815acfab76fd8b14_long
      << -0x2b22c31535676cf50cf0739e4cf24ea9d0dfe09412e5cf0e98749b192aa7857b5f7b5396a726fcca_long
      << 0x23caf6622ed14e601ad2afd8e057a6e6af6d7749b31d9f24428d6077ab260b6a97ca6515dda5040b5d05ddb7028a630902911047930f6ba249fd8ee0657e7c4f974436dc7314970820de03b83fad08cb1373af09ca64ce19b31f6526ac9d2d694f6aaf8229ef6dc8_long;
  QTest::newRow("-1365272936649095734628456441117485443941415878804458869717019008128979193144672589034548185187325156582796221182566196745661233285434801239744029840904586 * -7950865598938506002172156416463359592872707276073258686646548926811836787352004168471333518209820773047564353542453")
      << -0x1a1150aaaf269ca4b93db2896c61f483a9c4b735dd1bced54ee09bd1a87bc01768b1626d7db4201aeda280a584de0eacab451beea0d0c1f8263e58ab97d4118a_long
      << -0x33a866a4300de943bf8e810f42cb3b3ca5d85e29a35c536c2d3d4c68a7d2e494bcafe27739557f4c8864498236b61935_long
      << 0x54298e28f07fb6ef61ddcbcfd0785a444289f00883fe153e886900c9172f350b093fb729cf43f83c3c686beda9ede6a18a12e29247c7cebfc757dd89e1193dd905e0b573000154c3e6d1e59270b63a92ba2f3f868becd7d7fc3306de097bca43fdad58bbfc253b1fa2f0be5b8ba1b92_long;
  QTest::newRow("-7342047459172971716438632155848227377762187379066770754902053878606829313372203169046399530409228141894304186302755772641454468605271338752491118906893458 * -582747565843333431885764578925223033272696409750511814126367074642423163804011641753041059761687097175787287550500764700860303134101755")
      << -0x8c2f2e3053a67dc33a65f8207098470e03591f40b2e3d9df2f4b1e18f95dd13e0295146aba2bfdca28e31e93e023d5bf36d21e681377338f4ac62e7e597ce492_long
      << -0xcd3fe789994d612878301c26c58743de6b4d84d9309c468a3f464ffae99bcefdba0af6f3f276814fb33d283ce06af6fe565053b29a6b10fb_long
      << 0x7064c662fcc0ce06189b255cab6516028fcdabe5523fcd976d1bbbba7e4a22dab8305ae8076849f3013b4f83fcf3da93b3e6cd70cf06d56e606fe352abc4aacea0706b8913edf579bc0ef9d64520bdd1339d45194aa41c826066613226ef4ed7eb2ec9e8806577441b53accfb3664682546e47b0e8c33b26_long;
  QTest::newRow("-6128375365811344104686739643763912364617767588340973294288277115230549808632620203805694883860719708340524001943077715146568110149372471600734097663745011 * -1202545462369518902786708269332287231003194875375249881081124821551878710217801224209752699213808348508224475668325091906791341365528894085801752770880983")
      << -0x7502dff3551794c611b7b77dc35ad5bb7c2fa901b5a87764cd4d7b9e68fd6623a48c4abf8e359ba1ff56a2a92fdfc64ff61df5fb5e4c0061771ed2a77e325bf3_long
      << -0x16f5eb769fb5a6eaf9cd1639f589e914653e132f3e537c397a15c02e74343675c94895c2710595e897f3b7afb09b656f193a337ffe3bd0eb8ba7bf0a613ba5d7_long
      << 0xa7ea69f1917e00c026ffa1d42137c79af32fca63d68bce2ff724685b8d28b643d5c65751c126366cc9231ce424d1b71a2d101f6b7598ddc5891f217b3aeaa7d0f734678f112926a7c008de8a26e8883f8fca9ba4216c5366eea8881b34eb6712206474e07b662ffc40a80a519cfcb34d47fd86443c4fa18592aedf1b58fd815_long;
  QTest::newRow("-4585523102188430138320503197929802298681311587002200969511321377293977279767477729934843449903915699708242538531172579965943463196204235233361188540161434 * -128881607151109451196369420102343172695457530502441999667011119607877443914056389371508072200014110025029808344047646974638086166543191130226256697213010478478388546799524037")
      << -0x578d91edac90ca3f916946d02b7e49d0ed5976e7bdf120678e85c442ff146f84a38f8f5e2d780d5c0f7174236ae02633297ccb26f0b137aeeee5af3667989d9a_long
      << -0x8566359c8da774d959018385ca35ed066aeb32c6aba4e718bb688312f36a1c86d4e162fa57aec132fe9f52bdcf7ede5b568d30938863787223e7ad8dc296a1044b9e1d452091d8c5_long
      << 0x2d9f818e79475b0353a27c5a0096df290fbed32e666480af6c3cca0f175c70967edc2fbe7bf6cb59e4ff4524fe34b561afd41a5c344815e454a7cbfaaef9175bfb661224977f6549511e4f60ae0e10598b8ab8d559b925df50cd68cb61274c665ea0597cb8f69995cdd108140d7404a0195cf42caff8350d414d695e49b8d35a466269ed01a53782_long;
  QTest::newRow("-8322435240843495001002251111533280080572419291247713822599705897763787456269330590377866037567696200409146897092342939527358040496236576274901098110875563 * -546473742797523487678864985231534071886311183975910278856136704735723196585361733815360498706108955181688817747513153871702126583898185101359536345056341821778549397598868213280477176141049521")
      << -0x9ee737510825340144f4c204b4d5ea03a475359df920cd778d413855c3aaadd62a9885de5c58befd33efc5c74680ad9973a2ef1d9cb7b656fd44af8129c377ab_long
      << -0x1ea9ae52d47cd3518efb30e881cb4509d9aa2b4441599798be42f602ca4f88d09dbbe06d8894e3fdf983510211e02a97d6ecd50d6d11e6614ed165ab10eaf2b9bfd75f73717fe16531fcf6fbae31eeb1_long
      << 0x13086b5395007d1e78adf0c56b5e03e1d71c1844302a0bf14530a4e9974024d264ac8b8a8218199ef4c21e0c4a0c2054c6068845df499d7f61752e5cefad3da72588cd7291b96cf478b21abd5bf7c70b6d019b49c21403d6fac87b9d99d418d8ee79a1c36a1dac1c1e3e006441926507326faa1a646c26aa8f01b69c1aff11b06948866a1b975498a8bbed8abb21b73b_long;
  QTest::newRow("-3296991990283305021426851381773568060419374048835211865850190312265704363429626855594338077703535827220877174213949406732403826257442997437594667359072561 * 13770716873793311602")
      << -0x3ef35c7497905e6df382726fca5e76dfd53aff205663a91ea7832135aca08608b1c0b0e2a2850a87ea845d8ca9e181054837add9b2d86e79e6f4eea3493ef131_long << 0xbf1b6a094ced9372_long
      << -0x2efe4fb8cb21e48a14d9267881577be83d9ce975d26d3612a218e286196b4964bb14e7a17f70e7fe28c9002dbbb6d6d5b31b87ed812c77f036c8b599eb87692987434b5e98e38ad2_long;
  QTest::newRow("-7022428753008125311159976255239009856272915665861435577688572963799937042315151769395985316043301400358655437716539519783304653613583148656279398889987024 * 197944811916632857431286160675155767179")
      << -0x8614eaaef6cbf7cf0265ac510e9c972fb1b27da4cc668fcfb3e0c91334881ea968e1ac67f787da28fc438b47779e442535824ab3e8b84c5d1c88232ded6e9bd0_long << 0x94eac8b8329e381564a68f579e546f8b_long
      << -0x4dff0fec7b7fd463b8c3e627dc6557a272a949b9e3fde1f7fb37aa7a2438fd4ecd91d09be5d884f2bf4a9d90a7e69124d3bdd5e52da00b99dd789a2ddfbadb31908be2b2c05147322b48540860ddc9f0_long;
  QTest::newRow("-5673886170737970346108280708348623680165999706890385510515359225380606344034823431263714986108535367813358679205414338555704307272367446599096299359337805 * 3928013628126252525810233636618081853939279894037835363141")
      << -0x6c5560bdd413c8752dd3e40688fd80015207ae79c9836f8fdddfadfb9b6a14af5eb8f34ab65094ed07fcc54f78e48dc4b25723a6a1a09602a5ead9140d287d4d_long
      << 0xa0326034bd88a9eec17dd02fa90432c4743ac0d3c3d93345_long
      << -0x43caadd9df737cedd3422d9981a210f408d7c1909218f2dcc92270dbf29280d2bbfef5af98d3a973e6220173b86f81821b9a6ba8f141e59d1832714451a24638fbf43e4b02431a157da36219a859bf7d475b86417a251cc1_long;
  QTest::newRow("-11392925484757385748989972525798847501896506245469464750070167940689305665194044783812009781333344750250788845747486504614744790706269436317167021576814326 * 25278478751215883464908530867317208574570551525557441805988487359433750885904")
      << -0xd98775b2d58b7b7223a63ec391f261a86fff4bc5ed89d5467312501a9751b1d920b5a96b4b7f5881863f0f541316b7be616e74733e15c54332d8092dbdfdfef6_long
      << 0x37e31ca8a3eb83bf4f150670b61c0c8a71ccb3ab771ade23e40561cc1ab83610_long
      << -0x2f7d15c0e6827e282a87a7f2bbc7891ceca9de7e62f4072266852ac3df7ab8e57b73a7f79d58a0031422d28197bdb19fca52ffc3a71ae5ff6da60c44cd4b88beaf5154af43f620933a1d39250de96293f8b713d5dafabf3db46cf56bb077d360_long;
  QTest::newRow("-9438763621369314661242053094392799093163847975805347312002533790079442788052623991215194467559908071926757807581321297606838888659012490029305232022858615 * 1430986923713343681681616004053798033050656183620127124223995010433740240780413988634630218477867")
      << -0xb437b72db9404836855667317b9fdc96b259b33a58d18b085ed6e110fad0fb332944682093783c27eff323620993ea8de59c65ef0b92567f9ba3739c90b06b77_long
      << 0xab814db09703514996ee7bcd1eadb5644aa4c4a310afac72bc28fee46b6cce61bdd0b7cc76a6712b_long
      << -0x78bc3e1feb7e2cb50d5b455723b2a33b1a87e8b56dcf2057dbea766cc31083ceea144e7f2af43ec9e111062705cbd9479c11bd2775cb070a571fe939960b432154c9eab2f4c418a9dd78c5d66e2f572f58872693238b477401783934b2b2736001cb5eecb63b93fd_long;
  QTest::newRow("-982169142091071968887239964348932030324870489035946938225533993887319845405432487083582883139306473325273679206828855479134899192306023661628340664245623 * 6962289962601628740005630621608706549901929988934946585434863252804042016045725389224731359910093773635881079209341")
      << -0x12c0be25c2313df9fcbf0fc9db0655ffecb20b914dc6e14212a9109505b4b4874c3f57c72522328ab57ca3823fd20bc13e1686dd08d605d7da5378ff87db9d77_long
      << 0x2d3c231b03af0591ed011ee391e266de6adb04534343a7fe8ca91d5921dad7b1e3af9ca716234195614fd57e904cfd7d_long
      << -0x350492b8894775c9004d2182ae0d85c230bc057b53f19930aa3f7c7839a464dd211757104bfc045eb9a05907124df60a81f4c4ed0948ceaf4bc1af2b686877cbf910baa8f437e5a06f122c4a0ac73fb1da64190f4cd5e2fab313dc8d5693a0f58e4c564a4551c830872ff61102e7e1b_long;
  QTest::newRow("-12578852886043734970657203969272161084516431509532712692892931944933848657383432932432923300809435748480156555692657702552717420338396474269802402677756192 * 46379092340631049209696433192788679855013955190233927860529328841874115558819616444646821874950683903392483318305859623151918777613397")
      << -0xf02c26f330e0e584d17f6fc594cb6180b42875ca92a45d52937a08f9bb1e3fbab0082cf658b42f47059ddb3db0739a776afcd24d86fa44df526b9743d3cf9120_long
      << 0x1055ceeb73a5c648708f673e40511b3a92f8bb8e9ea4b7c1bc05ce3cda80286f30f7760fc81ed598d01fa959ecfde9bf7271ceaef703bc55_long
      << -0xf5343388e2c1791cf2d869fed3f5e5251736fbb81f3d16a0f25d7a7284ce8d171bf5ed853153917dd4a766fa3e0cc03fd69b6ffb4df11099b8103f073d3b3f2f4d31b8cb8262429e69a3aa7feff82a4c6af39b47a657132dea85dc231e9b944a6486e8c094043691c6a78a554805d8ce4f42d4655deafa0_long;
  QTest::newRow("-6599420842454968787306440218097369710165903614854875951952117190589036283711542424057654598281299015916351100962977098219908909524281357702835079987719557 * 7178482219628638422073087204646244449921401566999607184157356442530519545666735399347728061591312329210831326959325817954085389697560339737821842890745591")
      << -0x7e014c11118912b1b805dbaaea0df2ddcc483ea5cee16090d82d2d842a960facea19fa859bc3097d24add97bc2ef735a6b12e8a235d528c9784955342e6ded85_long
      << 0x890fb0b02896fa6468421db156fa3ba1134c9c740ef301a81637a122dfb5b97ed5eaa57199c90d1872c087fbca2f9aa24c245528994539cd731bb5ef5d72e6f7_long
      << -0x43766ac0308cedb76bd5187a4adaa2fbb846c191d54ed2b58cbaf39b6264992ab4098d9b6769a583ac7845efd862586ad3f79ef178dd433852de415aaab81f4ffde5d3140ac0f1bbde629d2881057ca8c4db7a019208757fb5f65e3afe56c3c811dbafd3bd00481fb5311663d0f5462f096b163f8a8d1967b4ff7b77a5afa953_long;
  QTest::newRow("-1264458811119234082936307499668720180330142315208341520616661868842102660727671157609695352155474310572237305691289171347991664628120795075944841455703702 * 168659693060184373307123606053138294968230590320260089692067062293072655392191992519943673784916911362408279339805973676512085500910389537009409521413379596089456569918698162")
      << -0x18248bc1a5c557277b918f2e3616be47d2d54abffa2e4fb77dfbdc41e4f3419d77c343ec4b7e0e55cec9350cf3f95ec94dccc816d6d93910469f4f8bf4099696_long
      << 0xae92590465fc1e50c85a1cc744ff6e0527c7ece7e5a80fee492a627ec424dc5a30e944e47bb386d312732365e510eb141d07760c081071fde952c323b47b5cb02fe86574318432b2_long
      << -0x1076a43a71e35f699c9af33d1c759a73b4a8a91f392a494a9c64d9d4a511550c4a61c9097c4fff6c75b8d317d76c0c65759382177f4356d3f610b9026bc9e260a3cd7e1b27d4230162907c469d79beb92e73bd66aff8354aab9bfc5f22d41701d471d9f836e9c67f1c9e0ac0eb287afc57071cd5536d3bf03f084be7081460a364dfb9b5e96c004c_long;
  QTest::newRow("-4641204027440126616441956778585838732024724291577591368982305717089499889399473184716350087933941246983521985672299380481178748664179459591325939073543054 * 3862794402992150428562402462727247260124977097593741420601496179535705839252050580954111599794096934872428113067676639785524888922631362555504909592594470902169343871219010067360769076029473453")
      << -0x589dbb93f0fe0adacdcc21666cb70b4ff8a8d34ed94cd8ab8b5d0d0ecf7b09fea01ea501abfa91d2b10007368a6e9465ab5e4eab0d0fec0434c1dd80c31feb8e_long
      << 0xd8be1cd591e6e298f253978540d7cf31a2e28f807e88bf22665cf4ea5838577d7f4e5c94661aa7b8efdd4860f6b4446b58db50880d37e15a079c42842bc53107895a83da9a42da7516c116a7831ac2ad_long
      << -0x4b06e5513965b98d7c245e22a49f62246b98d3ac75b4bb0d454e3ce72eb4c680b1ed076fb5adb8deb165679187b070c01a4e44e35b2e3ef68403107caaecd46e4ae68cb4fce3d37d46572901339c577e930afb35dddf5001c9835ac02d848910ecf9bd8e1cc6584d2f62740daaf35c0e3ffe25fe72b2a133e67ff8b6bb00b7230b38aa36a92c3bd4c5ea484ba37fcaf6_long;
  QTest::newRow("-102484250932393662912632882674241857300572172410796751117423038723137402079105609469140039126318830499849259743496150320539872038475278180885587770408866208040488872859717092 * -15549485237112240221")
      << -0x6a139c1a88cdf0577420ca5643efaec87b19513093f0ce5e1641adec499e520daf59b55f045817eab0ec90ee0d22b63e5164674307933a2fc44d135031c6895d972d479a96a8cde4_long << -0xd7cade703e41785d_long
      << 0x596a87bef99416405238eb08c8bcf71aaf1ef4fea2c77a7f5ea9bf792e53ae76ffb272938712a1ce15d722339eb346579a414c61dc4c543a1a28048a6afb0be3b443e70d6d4e2819020e68415ab9abd4_long;
  QTest::newRow("-141500618005660295965156692367260934809489432203096896055136373666999264303511072577241314147182056729914240800129296264673102916137705978603104075389648497696527481909295541 * -90816758120668945951054005131057456146")
      << -0x9275e9ac3341159e8299618a3739a079188b6a8b1219f7b4f8678d73e8e0be071f2131829b719ee1c69e2e5a01b9c05cef157e7f6a2aa74ba04cd09ea4f2d3e774f893f70aa439b5_long << -0x4452abe0532f16d2247c71e569d66412_long
      << 0x27169e2bb09f5cf770c424ba61c8c3d613da47e5f8d4345b489eefafb81cd0433e466182f20ad6c5dd2ca227a2c90c631fcb42c713d9343ec412a906ac143d6b65edafd62f46cd95d021a92e6a0b9845c133ac636064c2ba_long;
  QTest::newRow("-4422588522061030957147148898618969156486432393127318939656634823227753547165840489820307339812557062611834386913938132258065724554902338152623210859906459917379350497088066 * -3582663371378923517263725641377695587298912649517393432748")
      << -0x493de6489911e49012db005139d25d80dfc483403c8cfe80313dc0cab069e57d4abf6809142d935a5fa5f71b870297fc044ef760fd01f8cfc7a58c0c6f0b036c85f527ef4345242_long
      << -0x921cc03a2741d579eb515a06ce3f205f1926a75ae2f2d0ac_long
      << 0x29cd8719a734d56f2decbcb050b2fe55ab5e9013c80faffb916ff20da2788329d9f2511b4087ddf9ad3ce32acdfb1f5f9d493894541d6f1e2c78d5aa9298a1330dc654a77428c1f598eaddfb22855aa0be85badf2866cc6c68596fe9c60e458_long;
  QTest::newRow("-62862079124982117192048557028459954624865429950783222625398819806988344006209527742358467053158349927993140553309369188179473559067853152262969492818223189617648013304246847 * -72852898262850579781838965854878518783196642058038136364000541407344074130709")
      << -0x4110c8da43c1263461bf71db84ebb845178e56b04767fea208562df5f55698b141e428dace88af45437038abef87e7c7904707e5521bb797e3288cae581b4425bda747da916db23f_long
      << -0xa111477751d812df847fa2c9b2b0439229ac3313e2225fa9dad61ba369d38515_long
      << 0x28eff298966a199d1059dcfea1b763a4c33e9c0a7f07a045f4a4b0b5ad3b65ee916db74e03092bb50b03bcd987eaa24ab2df257d90a455d61568ff6a92ed6c4651ff43664de4f9c10a05601809000b238e0c8e911090d20a8356c26aa21af58e2728711eac875a2b_long;
  QTest::newRow("-195402518831117212417837628218438777490851311161213554918363720724358049904974479762142649195256272295037309425371489617758053388930708039629899954340172937651042791994215741 * -1377398067709022181281564236284888433078104028556848813436964418759317078077508331975889028345901")
      << -0xca407cd5c693a9175f25ae979215333dd93bb0b159f2fec4dcd05437ce1d2a298205d125c2fc0f60272cef6ff62748520843db66580fa471603a7ca47fadba1253d6e9acb2e8cd3d_long
      << -0xa515195d836ae1f04b44c6764e2815e6c5274162aeb03b41fb63bf3d6ec335795655dd3e2217702d_long
      << 0x826c3bca33f8213c192bbc834fb9d3e020dadbf7b58f4fa6181f8b1aee2593387e7d373830f396277497ee080281c48e7723f3bcf8a528947bfef9d3f32e801126c59ceb67f8ec0295a2ff2db9fd2dd654c6876308fc6482cdee132d2da8f69a3513457d57efba98a219fd93d731c3b9_long;
  QTest::newRow("-153539131521386066040112203749507567523312249412744417918246862289416005951584804766732158092258851404214713879062231468027598063705053511966980537736223220252101182363947866 * -24744551160414792702176490670735239583375493091005665361301203956928793031184377140616469632941038591385621153208186")
      << -0x9eebccbbd3007a7a1fdbb674ad88bf24570087616a8f921c27ab570e8c835644f2f6d506ffc406ae92364048d3ebf50b10b037a9e980b7ba11e5337a9eeea0078c3f2b4bdd92535a_long
      << -0xa0c4c2828fd7169a815aa31e94968c0aa2dabd5f34d35497aa8e1b67896bc89b0060172c3327fc4de61aab017d14577a_long
      << 0x63cd853de1dd639fa6d251ad1764d844fe9b1da1eb20ebae343c8a82706c90b23d961ab372ba7e2cae4acfa6fe181ce05c5c0b4ac9b6f037eeb876a4afc6813c164d927730bca2edd98480561ef7eb87b2b23681681e9d44092dea6988e3a37775824177de806255ed35d28ca2e31b73a9529defc7174ee4_long;
  QTest::newRow("-197788052660992883176320424814847609559491312979667143935087678934239790775173929614855901507954827148284700672760070199696397615583092116265816665961035252938913356389023974 * -105979956705081805141549322715589183874055895026552334753258603903406651396570884359188607011754825062512271300353318025363828871222231")
      << -0xccb89742e7aca48dcd4c57075538a94f9401b2468559226b0ffd73cc109c213241de3ffd2550c421cd8e06812a74844c14714b8863d7bebbf3a4e2b94afd36d8abf90f2559c000e6_long
      << -0x2553c4af78520f3bed8d2f42f23ea3407592af1c1dece964b093f492d334d1d4e863020c739362539247b9adc424e1fc430c00b4c6db53d7_long
      << 0x1dd9aaff5c63d714f30d5c5f6e0200846e1dd723e324080434984026f7a437d62575a164602fc3fa65207e1cfc6542fc474f3b161c7eb212a1ebb24f9168127bf8e31f9d5a2df036d3b14db0e78214219ed8aa0ce596175cb6142925e0bec91f5eb129cbaa0782865b0c4871e1928940175778b84d4e33685e3bbe22494d532a_long;
  QTest::newRow("-192125997564455851782812426585119434726607870488992091914503306738935223475436191618313932492770909715298798434978130955172113788016732819091230077917700689791476868202569162 * -7331290411571666105825633342614780896486967433545035405945200233241443251729200044013525001634125276896197112275324577226320910165873351632854576979146207")
      << -0xc6dc4bde13e2c7e6c5023ac6071760599fde3f846c72d5b3895efbe25df16670da09bb3b0227ca5010dd18525595a5e7e10adf9ff86d2c9c152258bda194181eb0b77b4de7cb1dca_long
      << -0x8bfa99dfd25a9380d2ebe03f1193b9f7668ea5e91b3623229deb2c9f7c305464f69e2931474b4b2debe9475ee8bef3610f89826c57fdb6edf0e00c56a60e75df_long
      << 0x6cbc47db3250709aca4b12ad2da560989ea1995c068416fc140e2077a4375b8ced7fa69bec99891cde695e59f2b90a370c28cea1af40f5c30e66a183f41e17e77b5aa22a9977b9159d2942bbd3a58b1762eb9ec40f4b68153bfb02bc4a01484857bda3f60d33fa15462135a2db53556d548517014ded3f5b1d3cce80a10a2e2fe220e0155b9844f6_long;
  QTest::newRow("-214760031230515512902635447936962464573587380381642085808892061352310636908528177149412052012629152486229136390419161130335789520065980394939035975243599770062293540250451128 * -11074115466022519490791619775155897498498307945124202357527285993952638263578199481722632639873353398078254922117656495410453636348906127766950962172891505376733958776433030")
      << -0xde49b71cb2a239d88212858e67972e5682c0ccab265da0a98753b37e34e38ee16e8357984e853fb4fe825eb9904e58e8ebd6b22caf0b673b264a0e01d41f2d2db0a9a8daa095fcb8_long
      << -0xb7658d789d1b35abca77132e1258a36abc840f96e3461022fa584bda481c4e6162479fa8e4e4917e9b92caad7698e2059339ea0d08767a924689b6fd1778aab1213ff4aa2d62986_long
      << 0x9f3edfd216d7eadf04d6110db07abe9188825ce566f06a24a2211a49284be38591a41e50f74eab6727ecb557fa11eee90a4f9c64e2dee0fdb98e0ae2a584bf34c04dd97b960aa16ec481bac909101818dba105fc982924243d2ef52647f90c4debe03bc63c416f1991ec0a1edfc930b4b109686aef7f7f2c6a58ac1c528679c217902a67c3f0cd9a8f8e2a5c5cbc050_long;
  QTest::newRow("-132671075139784125774326915515241567684808208291046780886690874266724333734335681433849826806020878959891139708551593173594399081137001164967767419878519040824172829153378345 * -3050413734177427882422816153307343427697431698327052309165818571829088303395264201236753031468709665391373073990529157165638433898894664462430987702077363614616682146353170160207813046117328948")
      << -0x895251675d1839a4ece4b4f06dd6f6baab696b293b0ba4197ed8648aafe1efc59e8c9a3de448d221be048acfae56892b48f65e597df84f7335eb30dc7e5c80c8f9ea34146f374029_long
      << -0xab28e15c45af695c4b9216048b335b5be6436a7fcfabd8ea5e19facd83ae1ea8338d25623f64da47f6ceb42283cabced41dbb6c255ddb12e554355dedf8bc64e434a3fd9578e1bc67170f6f18f43e834_long
      << 0x5bcfea1f9bd81bfcb2a2c01b7c459fceb4c846d7b1d93a519f1082ea94407caadf7160231689cfd852d167adc02fa3f5a9822849521a947d3f337bfdb93c39ae8b2d50bf27baa5ec4b1dd9b1c47badcb502d50cf8dbaecc108a5b611290afde086d921e11d6dbae704a872e2495f338a068d7aa3eb3b9d35b84c167e8324dc3d651f064382ee17c8eca9f2fef7802f0203d8ddd65b193054_long;
  QTest::newRow("-201117921276328951003435464611528834151619556567036907136428592743553716218353162636350694440416490867048172467317118718558212578615628784718701366594445697004781037230777034 * 13641406962857504670")
      << -0xd02aeaf3766c2216989918f94f42f8387cdb37775f2d62838dc15f4e5c2a5a974141559d7fd3fe7f6ebeacda5765b6d83657eb3ee08a996b6cdc28e0517ec40604b4725b373062ca_long << 0xbd50035b81a96f9e_long
      << -0x99f0bf9a13f49d6092515645c478bb7fe9635786b34ff221272a50c30963bb63f967961743f93b8b05c1ae9ed9aded0f2ecbb994fb9ba12656ece169c0d74977d2779c41914f50a0ca766dc10c0c8eac_long;
  QTest::newRow("-52919818683837266837811796908875254644392560199414069256823396278246391008972181705929631415454651215228231732875919772950079300589364056283332604856815540003309546876782380 * 318362890809188154316991336992527465442")
      << -0x36c6595fe15389ffdd3384501eb6de88a67b4630bc99790f00fd6227d915ab27e3c13c94ca16791c0313e32571bade39ef7fed71d6178af1e61f07e81d25aabf807335877c45472c_long << 0xef827663b860ec06ec172fea7bfdbbe2_long
      << -0x333f177ea96779515bd2918b3af6a6fed76dd59ef9c7f87cd6f40c34a08385763c356f132b61c39ff8e27b8fb8e627e9ae7ba3b0b64555b0ce050d62be3a6909a9199f4000ec554e7b14c5ae5e8efcfdd1c27543caa1f8d8_long;
  QTest::newRow("-191896981100415298827103764212830224799364445820966260900676407706696624633453789606621726058773828290010870282812970077193413490627575612515796905416014215173267469020241846 * 4530921994755959374917348330625024116301539462820681418530")
      << -0xc69f9cf1d970fa0ae97d284810f9f00591c90b89d1949623c89741689b342f6ac5620f9c438536c23e69ded20eefb8262058286826669ce96dbcf41430ce79fd7932fe3edfd11fb6_long
      << 0xb8c90869696201f2c8a21509037287dc93e6f95075530722_long
      << -0x8f5eb2a6d44f5d6626788435a32dd3031eec9a371f9eddab705fd6bb9f2e2012ad3d2f10d6f861bd34a77aa29755c3b943e885dcbf37e0aa7b9bb62603a5aafa28b6ad9baab9fdffea4ba4b42f375a4f9dc4ce92670dbc8e011c8fa3e7a6302c_long;
  QTest::newRow("-226939277740441459603797061738632992406971783272138931257951799187330352188929329896328770450586746273561505626792093998826009534018739663972057242375079825959516015349930927 * 71872523995286026730050928042287210583491897016323630681716868481037351876377")
      << -0xeae4e48b5ec7da8a0d96e81e66416e76ee6d7d9832cc8430c0e52f16fdebb8a183ca397830484c4b7755cd54acc2533e3c7b7f07d2ae5265f65261db5aee2a2a8636c67bfedf1baf_long
      << 0x9ee66830affc34d5656fefc5588f4d33c880e643e841b0abce632c3d3ed57719_long
      << -0x91ccae4d02f3db190d99cdfff677a2ec4f792f46fc5acea56226f2cb326bdfa6551cbf8f86a2890367a5bd892ddc3a265a42f3d815f9c8dd425000cf4b36c85d23ab4f498c24c4af886e0538dba3d1fc0ba014fdbe138893cfc766c0287353fd591aca9f04430d17_long;
  QTest::newRow("-145359746410951742768990888890329804062627260341719270031738476534398848789465193848862258991556799344125834144461942011937007238020510412245461313477612269973383622624818264 * 120367462136185720742184991643076364770427737109603752181751654852429649093597509309295891666409")
      << -0x96747ac13bc009ea0a13f521be5ce6935e72afa302a6f64354587857e8c7221ad52547814633cf411352a24b9ce6a9db7d4400125fc63b760ef730ec386e23356f1ea07260503458_long
      << 0xe6d1831e469aff4fbdc1a19fb0938c61db6eb263dd426b7217433627d1cf2653599d8095bc155e9_long
      << -0x87a7c871396686983506b0ecd626f723dd63a89a673a7f233176502a2bbcb9243360713356b47305380bd38fd65c90ec9fe61a0e6fc65cc8a5db6ee2e3926e107e98b1fc48a04d73fa02068e5b7e0045987c03c623e5858a460bab17f1134fcaa316aa14c37996d7c31383f08b8dc18_long;
  QTest::newRow("-42344118288748412512705515821920322074287788754820205908218422798100016069191573444343737054963304406687524481883857578871228720210633739535580156417110903907876377384004159 * 28462084805516323209965198575875765546710073577745692529826117844989302445711423030516022453300437967903332959547647")
      << -0x2bd411a0ef17dea4c08fbce65ce1fa62a9b692835445df31aba50c0f53bde882d74fd45163b31766c9046985103962f0100da62b7d4c1442747cdd50c9925b10b48addfa096d2a3f_long
      << 0xb8ec01680f09dea64942de68b229575a90bea54ffa84c3e1eb2c4911f53041b590376ee2cbc75f0c0cd03580782c70ff_long
      << -0x1fa8d469910179f34fdca351fc7ed2b683c734d08780570118650fb851a8d7b01b6c79ba36304d3706f31c63fd3b4f4a427683a23c2eb63908ada60e489485a3e5c53115030f6fdf3e46ae2763500b4d35b7a4f324384163f3eb0df07d2076ac3fdd25bb358873f6fd6cafa924e108258a59753ff10ca4c1_long;
  QTest::newRow("-138193200038375909736095144651519616949389919424949890987280659849193135767702106356269622036964528919352548801299184594768279302319260740064913846939475515627275476839987277 * 255517378333021893932508640384692700757758977425074938257234938952392943111101873608139972592259553273219345715025113856079377775287824")
      << -0x8f0988e1f1487fa3fc41e0d31624225c8504c27b93bc8c9de20d1f0c8f51b3495a9986e570b780c3b0de816319cfbdf146149bf4995ea0e65077d2e2ec76817ff41cb9595168784d_long
      << 0x59feee39ff6b7f14856fb314a917c55ac0e742dff8c03821292243cd78f1008dfb62384846518bde4d8eab7c60ba16cbc253ad2c3f995e10_long
      << -0x3248c127a227b2453f3246a952dfc06afc1ef67bf9a737a5d0044769f46e40e04fadd5219ff11cd6ca58d89742e2fcb61dfa35fd71ae8e1ce509269196c07564c267ebe4c3fc70f693425226e87583ebdc4bc93887b4775d7261c9287e25998dd7eda37df7e4a89a735d254a9ff53e2ce4e54f922378d4df817c74c04bb8cad0_long;
  QTest::newRow("-110180038365382544284121384549687871364903770417454657225933445822218689905081618633466274599976184212813108339579666301354131731837426654166621602809402134051020779848453047 * 12963521379994443662743097544386360851665060856346428620163193632663404054721359620254206189733464605630851432127810688399530187111662021383615373530843917")
      << -0x720aca190e82d962dff34b2eae527c04bee4ea3e0f6fb2a996360fb4e1549f05b603dd5f640c4cdb33c6e9ed95aff2aa9ddccaf2fdd2e7b142d7eaabe9fa44c6024bb9a6d19fcbb7_long
      << 0xf7845f616dd6666d2318945c502535ab62dd0931aadc3cb97f8cf17205d120780a22da083334e01e7cb4f7c645646e52c662396d0bb66216245b7da589a34b0d_long
      << -0x6e43610bc9efb5ca122f93aed06f584a9587d038f39969b82b5c8131462d0d64a46cbc32293f4d362ff95ded526360007841c2d0259f628b4f115ca7872fa207089b36e55dacff42c558dbb7ef3a562b521f84df3fada5662b7c4fa24fe2cacafe38a8cf3fbdf1157b3d46832ca5f9b237521b9e1f77e118119edd0fbe3726591125f1991a50f54b_long;
  QTest::newRow("-48406536394257102715592022945598656939074631541649719191049361468317854630010013130773209369774391401697031405348276304587808195155828821385342218840117983551867255805689936 * 195900194706642397997399806466198416675398273392198039310276109644602020920418025765962949419606553111362773044104277318568863496138446536902308710109296876312822112230707545")
      << -0x321a72ee9d34a36ac09d9c61461b6ffc87be49a12d11485258f1b7a41ff260605e3ad245e7d562c14799ec0aed55abca151af38bdd4a395d7cc98459e7e7fc308985c8803993c050_long
      << 0xcac45bca040a0fd4472cc49d0954ac6e182112846ba4e9ca85c056bf21b6c792b726d169a5c43ab445ef81a02427c9151ef29e84af85aab6d8271a8b752d308ed78b0b41ed961159_long
      << -0x27af4ce7373fc9566baff317bbbf29df45c9702a3199a3b297ef98ba8815d735191400dd16df3154016e08c18ca4d15f43372ff53707f7ad5b47130b6d62ca83746e376e7492c2202166102e0400676cc0474e4ecc3ac0d15d30ba4821b1354712251e25c43c86e5c70d500940e6d43350841850527884e60a5bcfb9062185ec5f693a8af5cac628757a025393032bd0_long;
  QTest::newRow("-146800100286262814052528618859661708651313875373605307918987407275099897492974458167392294298199593360724991480239781529186181459391343528587692571040480993323273609317652201 * 2115489187937293053324762967992523550260733663711618549963013616108778664582003753229824977649189893413517541565573695087905873463932336487601234112221960932902527053757227828331154632339884671")
      << -0x97f222965127adc61e168c275ccc7b92f6b0bb007a9e156a59172846e0fa3089051581b6f328be71ca5c8f3435732e232af0f82d9385044e6e2425bf8a2f89e1ba77fe1ddf8716e9_long
      << 0x76b365ead20b8c9b0e2b0c3d71d89d52a22d1616fec58d47cbbc41d20b214f537e597cf7df1722944840c3da45db322029c76c1caf3da6f6e4b4a3e84532c4240fad29c3c245526c924cdee6dea80a7f_long
      << -0x467416bd60276f7de72f68ce3607aa9ccd7338e70d5ec41381d36cd47ea4cdacdcdddf3523d0dd42378abc050a8b534162ec2e160ec1de345443091e0d80b47651c62dd29c38511a4b25cd6deb0992f5ce3fa57dd8f463aea89ae5f9e71c80ab1c99f5782ea53e663019ed0160e30323e7ca5313d3334808011ccf4443440c5ea237d1d894d293293d10b2b206758f86854eb56841d17797_long;
  QTest::newRow("-1885715714460287413904035557836469520670804772490696745872239827088040027758199868974730770739200298290833810094357402703140705898026955450476363526579759863007121251943380698780407690033301350 * -1061620071539060594")
      << -0x69cee05b5573d45a526f6b52433d1acf3b1312a87a963650aab57623bc3cd2d6738d431b75162e20067016f67432fe7d717fc23357dd06dad0fdd9213000ae5339f87c26f102fd7d5b044caf6b930766_long << -0xebba1d49282af72_long
      << 0x616dd45d85cfd1f3990c3e9d027c7df512bbea245c3a54dfa87bb419a4fa5145000ead7d3a94f981d9eee8a10fd4f04c327536c6259f5af84721605a20f51bfdadcc809ee47318c6c317a9145fdb1affdafd2015754056c_long;
  QTest::newRow("-1302567508440398424800887259112584315992360274496013354374018880607554337892089833720837468627834431104374118654402944805693931952541357965196145054775797428320029426133636613743307142462562965 * -20910816694837966084620458951786077829")
      << -0x491665039ecef8d0f573c8357480adc22a992e9f9821f3782116d5e1f8eabfd19307aaeb9e75805b7b21501aac76ba605f9fac6eafd0c86a4f2e0a62d134cabdcb39d9313c6698408054c9c54671e295_long << -0xfbb46dc96bc25780dae0b3e6c7b9e85_long
      << 0x47dc78219d9c4a1e1a2a3fe1da20d60af2d51aaa5cce42e32a48d079920d239138a2e57e0136630cdc09bddfb8b787a68c3ac81c87b5817e8088601febe86bcadc566a05e24b0798860150abd4894f94db5b87e20d21722b2acc05c9c99ad69_long;
  QTest::newRow("-1778727430184600454602127327717314000031038610235443719221461927564729384032450540798567142471509804711844050766747533718881479403173785220623980548861127111678698268437588076055371996751605969 * -1421323632032085190505192001669077159723528859557869405378")
      << -0x63ce1220dc86f6f088443c67e0dbd5e643162e744a1831c932cd130f3b0d7ed6d968dc438fe85ed1d4756e695ea2ad1cffc2044ea08af4c6c197995b03067827bc442fd77c26667e34562c5fe31230d1_long
      << -0x39f74fa533643c40e549eab52641ffc45c4973dc3cac44c2_long
      << 0x16994ce9ce41c808d38979aafd759cc0eee85a52ec13c5b08c04857ab456e7c1f03b6ee23802fa7f0df9ee0ee11508c4b90420aaaa9a660cb2bf24b08aeb9317e9030f3eaff9658e58bdf5923b37efe3e7b86a508daeb1906967f7d0e9f09bfe2de4c340b12c8262_long;
  QTest::newRow("-579931100667498575693307519639964412592825322267450695974115318795468027615055292004667401172675187421048031429254382586865644616602725336470227005811725197288048772073805784248851801290780640 * -16956511940105827498417655599467839928842774298214346019414358642956010581870")
      << -0x208a454154f562125fc5d30d119d302035010bcd8477902334861f5c60c0ce7492c1a13e3405cbe826ac055769f085277bb755228fb47fb074f7c49e4bfe707b284c61f46b62453737b609354a072fe0_long
      << -0x257d0bafd30f4f50dccc7515c5a5bbed96d7c22a46007fee4021b9b68dccef6e_long
      << 0x4c3e1028c810291044508335e60b88c3c4b86c0a691431376b4a74087540fce55c6a88998983f5d840a0dc4a2893d5ea2ed1721aca2e6469d7ee2d180a0885517661cdcee1336f8c3e1bcf090bd44c799741df2d7233f45e43f10eefd06ea7f1cbf5819c268fa6591a2915b0b48b240_long;
  QTest::newRow("-561298655177645831035397884310949160072725769485646006064229631218797297702608178580237173938834416759378896874940299758336526878516632217841180372846582458657994265666023142936863958019736632 * -1261391474051542947691557905607503295034090265241317696849888866699952296176944195992467657737855")
      << -0x1f7ea12bf0d072bf59e01ff53707f68116da8fb4ba325223195f6e38dc97446ae91e51da242032211b19aab577528d8bf8e444be31fe82cf3a93cada918826c4fd881a75eac3b3993d01dc53b87a0438_long
      << -0x972dcdd3f26dacb35174234c495994e34b35f727fe847848b2db79941fcd2c75375786505c24467f_long
      << 0x129953a5ba0681e6be8bf5659dec10d34f1e9eb4c415d249a7d77e64a315e4acbb61c5525605fa1e4d1be0f6c7772a2d20f19f579126063c24b6d57e62dabccc0b0eda12828cbbefb8fe6134d78a059f20a5550d20de278990b0e4d25ce37af8bf7b4a146f8904e07d98ad1ba5ff61d5d39b9e26998f67c8_long;
  QTest::newRow("-2535139443537030493849711495848717638886747606030173359449028111492743427827220934191276856977813936262093652797754664647388982943932729063062431766721383110234912127094784631909077612620731946 * -984170551608887425712269050951071287483643585663925905327856415388357113715605550766906481142723443262424407478735")
      << -0x8e3f5b1812937cd4ccdc656b1573ac49e4b9d02654f76f221b87ece007ee3f1dac7f6492944867371ec5ab0664fd59f8fea9ccf3ad10814ec7c05ad32a2a5d11a8db28c857624c08ec8f81914500d62a_long
      << -0x664efde5289bfb4aa9e52806c94f94107e67882caf12820ec0e5f4f87720c0e27685bfa715ef134a839cab6e24211cf_long
      << 0x38d922ad4b0045cab84596677dcf37b252280580138e2ece1e3f18ce6bc0354bef1b407ee6d6b05297c42f991c6934b5f621063a7f2cf0e4eaadda8f69de008c3230825736b43df5714cd4f7e1c971d33e983aef9ce57960ca2907e7c8c3327653bcd888ad8a2dd654abee44bc18a37dfc163933ec4724b6cf2573024b9f5f6_long;
  QTest::newRow("-35311778756822733197603011222257869980283437316819238912992197278790054002251298714671287449739988562221007256595736198858344519642611990608950329198247950119002183845399140164990451395590967 * -235978784218610653293631678799602481468295935580240493746572896634205359279360254345735391968822608409282347888736099846773107007945839")
      << -0x1fb3a17ddd18a11c4bbaa6c322f420783ef75578741fbabfff8e6e195f359ef8f430e49ce6162fef0288efa0f8ef597e4aafee0aa50669ae532f802726290164c5cf236052dbd80e817e3d749d3fb37_long
      << -0x531d37ac1f605a0d8e3d9f8fdc55dc6a9ab6ef7989eaa0727ab9d1b31b58926f7daaaaeebddaec5709c69287d5c5f8eb1db4cedac03bfc6f_long
      << 0xa4adb9a02364228e567087f8be6efa1783c2ecd8672ec27eaa44067758f123b76505db9665f7810da720751e835a6e992b2a69a36b9a4665b3afc01e4ade736375077ed7e5dcb5da5a88d995abcdc60f0837f1d05423218841f8fff5ff8a67bc0470203fc376e306c9fdaaaef7040b711cf450ca9829f4b8c770a149db8a7b70f6e61fd3e110d9_long;
  QTest::newRow("-59903017700002864077246828143286537578029812191184417983824054454115442425793846246839545748132225632831970836497748539468189744078839925180751614931472702632207342133038091934617481973602193 * -5347399483094950146090430324728926469434884297984645473995735857274258249909851173014406899524600298520580697891730629182928956287736818415305365343383103")
      << -0x35c7620217c128f02996ec344e63843eebfba539f7277411695ebb98584a86fd513cd065dff90fc001236e3e9c0ec5766240a6380243cdae38a62858c52a7b4b335ff6cc0f53419b162aaadc7341791_long
      << -0x66198b5153c604e0a8facaed4479ee792394e20ede382ed5e8359a5fdde9fde05b27084dc8bf18678a3bee1c7eb481c606cac033bbc9b48ba3d74c624f232e3f_long
      << 0x1572cec9bf91abbee02dddf3992c092ce72a1c3cfbe6a4e247c495887c56dce8a6fc3f9e3a2d444cd5e9a8f932a6a787fced68950ac2bd8c57b51fd621ec8c53f37b8916a4f3ce503f6c17fbe65a384c0d90135014e81d528f5b60cb63e3947c956ae4abf2a5cfb9909dafc97b1b301918575794580812249cd08aeac45e38b7375957efee248812ee59b7659e0daaf_long;
  QTest::newRow("-1245877319818426490121670301677846488750405482323801687865048041481211229243886431558556876438967346390823629814553143938052727153883657099789494766369081597934399144258901041422563439210796861 * -196918558256860756714662296002907455766696723593582472695165180410123187844635286046340409798017872521597309115798755043724985928055754535502568534441471992776772136189688272")
      << -0x45e815404b2811910c26dab59f6f1a18fa1320699360151c33fab2452ec6732efbd4dc6cb53633e3dc392b80fd28ad8b1e5505eadc775338e00b6ac302813936e9f0fa9a6e48b066645b6e88635e173d_long
      << -0xcbd232a95ad930146d122e5aeb14936f94efe49084a17bfc92fd98175754bac05fabd02ff77e945363f72c7abebfb182f97d59b0894828787304cb7dd91ca0c2ab2c6a89f5e1f9d0_long
      << 0x37a86f10fd81e93f9452feb5b58d4d9cac69dcd992d066058a5c1520bbaa32442dee95bb8b1c02636c514eda782060eae1539ac1faa3c23560adf66ae35a3602c28d8983d3ab9075affa43b111b033ca1eb966b343edff75653ad0399a7bed0cd24aa0aed22cfa6c078d3cd7b729a3528dbc5d16ada4fbd2d1c5b44b142d6763875981aad24a3855243cc9955cafea01063a8b0c0eaa3690_long;
  QTest::newRow("-2484294218696914356303283014556795618430781364584567649754858008819584992756551133108337006819762689714435895491902036968824739126695974932782073868995296389983148197512467260189563089545252388 * -1288927658634328540105125933588253673218390012728373312222838622826493372030837668001524998225959040996710460123891922710998078875905996645335124518912422808765694519530765691343002809549530540")
      << -0x8b6500b337cb558b0fd7e91a2e989335cbd4a2f8f49b0861cf42c58041770369010e77527d588b27377d4c7cf8511481091696a0d717295229a137bfa69610e2c3912d0b57e5d3ec7673114ece4ece24_long
      << -0x485277eeba577ba5f3e1035ed235f932e91c930f4f2c95759db7fec8c33943a4bf94432875dd7964a3214b034cb6a74fc348cbcb81181d8467aa64c48bed33a1fb3694563829b4b68bf8ed512d3525ac_long
      << 0x27614fda91ca09e73e799f366f8992cde4e2ac5c13334a86dd848797c0fbbd5b41c616dff89053abca78e59a4b2bb44264ccc47bf393a7bec7d5bb8a871ae00e37641b7061e10dc1f542aae5afcec80e4987b16f7c8393ae9c0a3f891ae3a94a825ad99022b5b79dbcda8d14a56c37c286944f7985c082401d70a5d8456c9c3a09308e521e2f4183b789e513dea4dd01bf1ec0663f5942a7210b22b50231b430_long;
  QTest::newRow("-342966648196028542819173215953636314976535080708923982064314896036173384384619986461233167521489474688265273876985778366217916356102385558048236971917449254369099712067088465869191729212077188 * 6655126199833058057")
      << -0x133e74b25f89409aea0b4724042cd8e335e6fe266da29fb67d9b6ccb47f1305aa8ff77a8381b8a93160a51f0c1b773826a529f5f8d36c45aab85fa09aa597d72331626b7643e3e3cca0338947c08b484_long << 0x5c5bc204b471db09_long
      << -0x6f157b944b6c1472d37065da66d0a4667496efa0c93b6a6032bd79b423474c7003868732c51ab6572b26a9eef64337b07e875a1b25e6e9c0b3d1547cdc15400eb11cc0f77b0d00a7cad43f40e964070601fbc284cff44a4_long;
  QTest::newRow("-2321450704384365790956496057507836976925753352941119433815416434229353671123436099438429116929643797210461211709553987477345654242914490898673175189191815872686000085033598189976926013587798961 * 63389577510379665272942455958746106644")
      << -0x8241e10e834beec80a822f6949aa2611cf94d0714c71ce4628dc70ccb05be50e41cb2805999dc4f6692e7da151fdc2db784926fb4665ec569118fbc2fcb94e545076d859e4736a36efc2eb87f3513bb1_long << 0x2fb06377f1517a813c3b61d470630b14_long
      << -0x1843d838e586e99c4f637caab32352d6bfd2d8552e19e2f69bc915cbe8637fc3d6cc3634e9722929d0098adf4a85f2963780025fe2c3a2c6a62f297d33dbc222ef9fd3b3ec1dd931972e199da5021999ee0b740b4f20c3b3300e602f055c44d4_long;
  QTest::newRow("-4132235315206004118889978370846600251601687507428403096445863359832164654177580279931063296592284138474660147551479279822798688602336071663076948223194897688943782084230477912471560164702480829 * 2520158031962198349781333695290232954309669736393299676731")
      << -0xe7dc6d521b7675546548373f3e2139912f04e1acb1c78b02a8d5e4ef389e4d96d9418914cd01be1a23731d0a2a1100c45e30fc3021e3e06594642f8eef64e3b20bf8e4a3063990c7686e018d15b0e9bd_long
      << 0x66c7ad73a18f6aefd799482d001cb31dc537938aabbb4e3b_long
      << -0x5d16ad0061fdaa026bec1869cb6fc4cd3e7322b0bd1be89e4df092cfcdf98aef10661519c821393431972497e362a8be65c4b97086f5041f4193a8ab1973129412d296dfde6af750cd70442b92d11bab783fb9f38c5971796168713c04232af6e58fe35de30c748f_long;
  QTest::newRow("-1419049280814891122665894704949120321858231389899278912359049342303341810910939220855573552521677878702515769317390074771218356636409780032808669458910384406711126845023307878083957885439040087 * 20399168907805857144568870332681529585911861642631704752853133927201228459887")
      << -0x4f9f9121f393a383577f56956ffb2433d9ae4386d5c70d3ff042d6bfc4430004755feb556cdeeccc364232350ed7f1f4a99540024ba6656f9a7d8cc5732217c515c831278724f0a03b9ca7875387da57_long
      << 0x2d19853bd14476dead4ee35ce7eaebc5a883d48f77977d3b1cfbfa1045300f6f_long
      << -0xe06fc88a565645ff93bf5388972830fc8eb49b9cc279c976b9cf026ff5f91d6516fe44080047fb8cf9b3762381e93c92e31581496edd6aa9132bd3411b2f3e41122fdfec5f203c36979a790c08d80ccef0be904bd1ac600885635661b153854f436242fa5ad4ea864a474549102c4b9_long;
  QTest::newRow("-139400427532813508745635287881762882137793433279749094571391222402750252641007575234053858045065975943870017860663614507721576473543659752026713680064742082994808486681274946103180145929247996 * 2123736309832349965183736598672849810706418344165773395126703164134554177671999367022697553993534")
      << -0x7d261a61f8427ad097c3e8e51c3170a6e33838ce6f02d93f8a31cdd836bf2dadd66b36da1bc6656b583dc3b1b0348cff05d39ea01ceb0162725a60fa4bc3de4d0dd8f09872f12a5a26f5d8459c45cfc_long
      << 0xfe882010a2a2434346d1e7abd2375e477edde2ff9ad7b6997a1aa8eddde5c736af52b8f785d21f3e_long
      << -0x7c6e5a181d8d2e04967f8123d1842ec6d3528e16ba90ab9a722e5e777f93f79469187dc1fd79575728dc760f25cf6a4cab88f84b9fbb2b2d1d682cda5879ad1afdf863646be3970ac854b435ebc19c795f8b2ed3333365bfd0bfc532f438c61b073d7da2ff376cf696b3a0f4977868f18832b73b7890908_long;
  QTest::newRow("-659507285111214641486152823614260813050973281318931189074934503963091724626021768800894481168723139995338764079146944726602842672087651675366374218576785389796442706890240176993375438176543992 * 37842408001437983412455655280932333102632301218604002350210573977820988674029211420947834440655460063283127750145640")
      << -0x25015273c4f5721b98d1f3c178cabcf92ea3e94e1565ce7dfbfc439a78adb2251a37aefef9473b15e18a19a0801d78bdb8dc34ba195167650408c0d00299c34c73cf24a7e6df38d72333d82a7ddc64f8_long
      << 0xf5ddf95a18414fed5e44cd1774b25f23268e63d133dc6b58dee1fba64f83a09e1effa5e2bb67ab72d71adf3c08e2b668_long
      << -0x238a5a18489b15fc6782531f0762c27f9dd63224de236974f9c4b0dcb225dcb321a6b6e61e0b724cbb0a92f174717bf5bfc8886fa35d6aedcddaaaaaab6c4db680d26dd27e3deebe174c0375a8df08341adc89c5f6e32e2510d8558f2fa68c1caac1da4b34aa965d6425d65dd8b3f56b0d1626717cf5ea2a56fbb896b44154c0_long;
  QTest::newRow("-3963118521682895560274696800609448945135678587808856217655938125875412070388929747187490511787603060764710134473934816188061363635005739305356154966395137584274332512285186325526927862585521137 * 127065513723088981743838788473725653961271693965560393652218093110567952440928514710068910689929929018517256865902604245520696701938630")
      << -0xde5f3149841419d8fcb3cf520807da579baf76f64d36fcf76567e1c776a5740a4a85dfbd214f0b172faa5d337e11637e78aeec0e178f066aab63c367655de38fc25104e8a898cca6068587cbe6de73f1_long
      << 0x2cc0f6ed9bc4f2e787bedf620018393c44554ff3811c29db9112398c79b4a32d0f73a8c4e3d8c55850cfb093d10c3af4ae13aaff709cebc6_long
      << -0x26dffa5b78a280379f47221e11f77f560a7fbf395125879131906e27d9d55243ba3dbc6194f3055d31abe9736853476ef9da6f0d60c75560fc5a5af0dcb599bf0dc5cdcf355f4fa342150546af7389846e9157d48fb09b63995ebeb12c46d8e672cb0573b184c4caa2d34ff35f108bcca7b2c7909a263ed4c0f5a0657ae5319cada7bdf9db57e766_long;
  QTest::newRow("-2693674353910682971579987063613269419366863497865335373658076109600543099974546583197063550697919746751743691563217826809633038268260824274196625035733800984286173203391373713564129505031066528 * 4535853361115742700311119941370545230592196798506053670660312449801705608822481833935427021934741481221790467240020724147690080700288758570608859922408387")
      << -0x972496f0f8c0cf584707b84cb6139e292e5dcaa50091443cb5ffdf43bab944d4e3110e65cca25077c2cd90e248d2286e19d21c8ce75df03b5af18a73af99bbf2723d48d0036334d2a58cd1ac765593a0_long
      << 0x569aca15d7d461bc2dc4c2312bdc096157dcee209f28cb7e7f2b7071f74b53406354d8e58c2a8668c4c832cc072998f4203980b8674cc2340552dc737375a3c3_long
      << -0x3321ae07850e0e7645f1ab11d1cab1d978b88eccd1ef27241434f65eb7d1866275b088c7f581d8477a08f227062e34cee72d9a417d0e7d0f02b3eed1fb2a9d78ab3f4cb48d824c1f5e20f394e304ecdb8e001270fc386bb760583a802b22ccc3cf3644bfb4648e15a6bf2b0d22d88e804205a1963c3aed79e00387e7621a9dd6428d814784987d5f2d4ddd03f84e52e0_long;
  QTest::newRow("-3581184781516271173361676774664047423235178365540565389695369418537603360175526783506182191655942343306617023645052852681962025294869087415069466447955835302593550610389025206786219160152467339 * 14747762776392933447381836364170859268814579706709721854538727972624058477606967693935369229375968420320011594422513636594627337896158857911010154495353321270781195748081053")
      << -0xc8f10102fe04f5d0309ea78d026144357d34b765a64c1e314862690c5f5a60607e42461d7737dfcfe31d19d7198ddcff80e3e300896f9c830c54fe5adc9ed010a18c3eed07864789cf3be5128196678b_long
      << 0xf43c425351d8eef7985a4d6949367a6fa7038513b78ab9d426fc0e1b5c575b036be759fd9ff7099304835c55e16776fbf22b1c4c367aacde72fe70afd6ee6c8f3f7de97566f7d9d_long
      << -0xbfb501829f74e526e2129e0393ceefa57bbd9c66ea76160103b72552f60ee7e3dd8007fbfa5879553ec79cd219f16dbade0861c947cf2e95ef253cf09259d051466d9c5641651f5569d205c36e138bb3992f47ed7ad3ca4134a60f4a86d3a1dc87d74e185e171327f0cc2eb1e4754868e3b4b07d449bf60e7c2a803c9019ffe5c409d3fcd4c95cfd46696ca7cbfe0ea96c2d99c81115f3f_long;
  QTest::newRow("-988647284446875383493069050631560145171903247711858130227544607842447638379412925208244177372288084773603670362670045060673294141763624357768576235199223266946851111170309033571245574291862148 * 2714792383683412339671803741795593269339504398192001984165109601550321219146070775525423603878438853073406210433754733748515502926798416121368251781196129689898294236768337850411077718518101625")
      << -0x37792b294cdacb2d86492472ad643d24602253df6beebaea93ee5aac16ddc28b039b9985fe034e4500e5c267fb183e43fe93bb6538b5c74280c967ef1554f8f80e8707c3a7978b33fcc77ecd4c323284_long
      << 0x9853ef2122dddb61e874f34074dad11e82349a4d1df465e472467350f199d1e6d384b4cea8db29676ae2b29b8c5ba9ac577301b0c6ce5c3b7d78367262287853f4eba6f26391678d37ffc8b006017679_long
      << -0x210221bad17e1d85b172e69535627c2cb953bcc26a230c5468a2bd2d62ba06e2c97dc0b5a731fbc913a44308cdb4a362f752b4b679cbb3c78e844ac4397229c0027a177df3938b84a866be27c69528b6af1ba648d000ba7b637b4d7f6182e9636747d2c5cf542e6567eedf776ba07ac4c04d45669aec0fc540c6441befaaef2516b2815c31cb1eba0038aa35902bded3a226633eb4bd9a1104c9e4497186b864_long;
  QTest::newRow("13931810007747389653 * -10647979141571859973") << 0xc157bb635e03e8d5_long << -0x93c5389d2528d605_long << -0x6f9a53df224fc5a3bfb65d6c44fd9a29_long;
  QTest::newRow("9508611444108552611 * -290019466326820871384714679572293500529") << 0x83f55fbac94de9a3_long << -0xda2fb7abd009df1d04f413f9ff283e71_long
      << -0x70778c3e9a493a57b0d929a08f8bace080ade6a498719af3_long;
  QTest::newRow("15191637557741761945 * -1628225297386939695886997235329077462471812303291439367148") << 0xd2d389deb9ae3599_long
      << -0x4267771d6c6463ca43bda880efff30e75cc7e9c542dbc3ec_long
      << -0x36afbec074ccb06e3890b19273e0e3493e94a05ca3d753fdf23602592b4ff40c_long;
  QTest::newRow("13506222953825824693 * -73474248529903345278740897416211173706038275487896545661188555976869687220234") << 0xbb6fbe37ac03efb5_long
      << -0xa270f371a47d50e19e0c2865f812d14c0f3b152f0e3ced98faa6b2a8ae9a580a_long
      << -0x76ef6980b986e4e7bb369447cef6826ca6aa7d46330c0492d6860b97c530c637d0c7e1614b6f9512_long;
  QTest::newRow("14667319450405075661 * -1534268398028287698869142516880201158650066853892128581402945095411425811107978315378792162610655") << 0xcb8cc95450927acd_long
      << -0xb7e22b2597258ddd8f96fa52e42398ea2d449a5cd091d2d2314a7326125253eb8e075c25a8734ddf_long
      << -0x923578838b6000b7be1528635c3b793aba77637dc6ef8698e205907638b558b2da47854c03941dbac8da7ab2f09fa193_long;
  QTest::newRow("8695104633750266077 * -38223943978372572011355713787309396061180754901048820658189594343689164752262862123962174416899284764317097084749224") << 0x78ab37988389a0dd_long
      << -0xf85891d6b2a14f62af7ab75c5a536baed3e11f1a2f49618bd714d0aea5d8ed2ab915b82630cefc6eea11a601fa4e85a8_long
      << -0x750f9d7509ab7ce5a9ec4d2755c410cf00f297346c4de43034bf754ee1ce417941c6dfd600ebc72a8132372aef63887d77b12250a83a6208_long;
  QTest::newRow("14152324579799439579 * -3851804362241381953454817350282469982400006943395464744715923538067062988695816519620775633295505830844897910399409726469580870852975") << 0xc46728391cf998db_long
      << -0x15b4d117b87bb26133cdf697cf1f50bad973a0e2b816e24dd5fa3cf807c541d23b70c7ef068dd1f750027bba5a1782910d0998abc13216f_long
      << -0x10a72f3f622d22267e445d0e8efd29c99c2c296a894afdbc2bb20963df0ac9e60dab5368165a5dc3de8b5492bf217803f7ad052438287600f458954e92e81f5_long;
  QTest::newRow("6610050207221291572 * -4940834167025750434823154569557736047751593746881459535646103199363123057597802160342243477966863847249223500056355911170008484891097456652278757250495871") << 0x5bbb9da454ec1a34_long
      << -0x5e564b59e7a4761078bff0247378e0f2bd5478a964fd2cbbffe2f50dd1f6b0a50655791e12fa15f788c9550f7796eebfdd2c23c5ed0ef8a340b497aa6432f57f_long
      << -0x21cdcfe97acd65b13eca1d50711c76c712e0e597340c8d4a529f6f002fa8126bf6ca109a560252180ebc938f760fc00e7fea7c47eb6a255d082caec303cff51420045cad845cc3cc_long;
  QTest::newRow("18415825594757143435 * -185767118485589839433883784649392585845494204391840974194855497760645692649515333415401420428230644307049688972167990795547254529215349625096209847296298522859396647641475943") << 0xff9227cea50bdb8b_long
      << -0xc0475ca9d8f3a82a1ecd720dd49b3fbcdb0ed27ddfdbbef25576df9d13257f79541fbb02e3e1a66394000ae85bf1512e03815a55087f3283290624581dc15f3eee1afe2f17fceb67_long
      << -0xbff4dbe61c79c6e17689ed09852ddc1b7e4ab69aabe43f29b20ff1ebcd896a999e836c433681bb368d59c104df53e72e81e25dd240852756eb5b47f594b99b984a91f07ed1d7812055b67690e421eded_long;
  QTest::newRow("622936394288125140 * -2122009406316386482804884843717309130917494504146981195452330767372805874643670206086610626303129825184834708868759766818037903809342997306282121512600184883736096765937272427915628934456114881") << 0x8a51d59a334d4d4_long
      << -0x77110e5d0db427d10e96819399de7fb75e949b22a10ebd4d16ed08072ee1353526bbb02c59f9464047fd021833626279f292b7e6aef2aea81d5b28518874472d7b63cc67e7b4fa1ebeebc41a771f7ec1_long
      << -0x4055417c9de6ddc42fd13bdfcdcc96cc3dc3d432a1492d70816fa0056a30ab53f09dcbca2a080dc55eba03deee6ca4c436dd6775e3ca3a7c178eb336f85b2b0cffb34f5e81a0c19bb977a5970c56d46be917ec45d40cbd4_long;
  QTest::newRow("15880011249080888039 * 6455092429185202953") << 0xdc6122185aac6ae7_long << 0x5995185d21e5bb09_long << 0x4d1e1e5c975cac28f8e6d10589c97f1f_long;
  QTest::newRow("8616578911165226224 * 298107266754574350991958193932312162412") << 0x77943cddfb201cf0_long << 0xe0455f04e12da251020ba1b02a42b06c_long
      << 0x68c21c98eda6b702160a3459ab17feb36f672252db513540_long;
  QTest::newRow("923411768901895683 * 1619822981015759240370783222373155262561394109194997553381") << 0xcd09e1c82d00603_long
      << 0x420fbdb343edc89e10b1f9f816ded5a4c7396ae5376f58e5_long
      << 0x34e927b9b6566cee7d0c5af09c87c1aca951ca193c2d074adac44a4c67368af_long;
  QTest::newRow("9339604115101166106 * 39146831771067027693456115747939870093048521906051546341865929296913011107204") << 0x819cf0759761aa1a_long
      << 0x568c5253da076cf26156924500fa3bbc1cf875de83e64e3eba21310ca4e8e584_long
      << 0x2bd1c449ba74a062c293ffdddf97325fbb3e28a3fc906c22543f45b66cdcd370130de1bf3b14f768_long;
  QTest::newRow("17073010115340866261 * 61450808594281684538460804666175390435484472600444062817289622317503600064451374148274165193509") << 0xecef843e438b12d5_long
      << 0x75d6c6bafd81c976bbd7f0fa9d3de2e5b78b0c6cd7455eea2c21c63fa13a030db22f7617c1d1b25_long
      << 0x6d103f9751da1830d9e190f85d43eb09807da31a965c0b691e0d19f6a8870faed3760df23ecbc97237d57b4bc372fc9_long;
  QTest::newRow("4775108139425022226 * 20257046205999584517306749040061103311542612097871498410405941812697287691709508386163179813488441382950065530358099") << 0x4244978d9e814112_long
      << 0x839cd8ec177fd19e8a86a398d4f85575a7bf1714d5b48b71088c63423b2006389963f43cb424abd5ee2cba733fea4953_long
      << 0x2211b380cf992f42fd72675227c0bded80252f285078a9d62e9bf7f1da0a2795d6d3add052b46cc459989ece67b613717558855c27ea3ad6_long;
  QTest::newRow("8682205253480152700 * 468117907834179136564175997474290349359024274545397224641961217734704366924784535882583971098057033150706765367846666549790534654181895") << 0x787d63ad80b6fe7c_long
      << 0xa4e03a9586da0c0879089b6f259d1d6d80aea21ba951e34dddd10430ab35ba11e898f4ca0ca5efb19930008d10f73a317c2834f6d4d74207_long
      << 0x4d99dd25274e70e90d582bda91ec9f321e8eca97651202a141fe4ab06259000bdda4d7290c4941677c49f6307389514d6f81d6efa4b1bb64b358d4841cc0ed64_long;
  QTest::newRow("10998356977964735887 * 10208379619579508164283817173429040245637617338095956034632510440794246439986681689081209549575869698386647360576548976634583768003213820491327157005529921") << 0x98a203665086dd8f_long
      << 0xc2e9852a7dd273a1c70c6b52d62d53305104e580dbbfc6329175a1c3789cd5c900538eeff7c9230e3b17a3bc9c405c22b528aa9a2f0e2a7c253f544540413341_long
      << 0x7436016e2282cac647baff05990e7fd52b979f747d66ff2b2214d9579d39746c15bf9b0c866c3693d7c11fbb44ffb9eafc5c16b513faee8d4b3903739367f4059f2a0c3251b0be4f_long;
  QTest::newRow("10899657009925375564 * 180370628756958176441603445075476826781791738261278598399803433759420424240957315238698997960747123257519498564001891818450569042474070098286129011903828991386287210223861862") << 0x97435c4d3a32c64c_long
      << 0xbab16f6c074e991fdde0049bd8e4150de2d33fb0048100c6862442f5ba7f0beb0349afeb5316ca605700bd7b0c9789abb200d3446aa6f94bc46f397f4bdbdbe6c97793c3f3478066_long
      << 0x6e4fc878f76fd685367d946f7603e2cc3f3e3be1b03fd6070f883a04165963271cbe82a0849050899dd753a140c4a55dd6a466803751275344ae864cd9ddc0f8ebee7e7fa0ebeefc30856a11b6750248_long;
  QTest::newRow("6265563088927462064 * 141258106526726829901716448149589576208051420071118600506354062235472083096667649153599365044713807318703837908200942894830397015260984907426943804589178125288379862697126082959034045371942401") << 0x56f3c06ed95212b0_long
      << 0x7ed10ca968ece51256b3bcd01ae5eda8db3d6e685001e6bca97af31b10f4b5101c7e2dd66b9af68802d3608a18a6770a4983a8233665e9736df212d31f8c2a73186d9582cae52f959fd823e8bae8601_long
      << 0x2b12fa03a1088941e5f1e4d8e7c0e3027247767409ced1ea091d4c15db2b76871279371fef8e681a0f670b39e86d8212ad81f4e942cc3d06af1b72b9c6c87d453ca344443e73e995c29f3f55bbd61ace052f2be12ba32b0_long;
  QTest::newRow("142705804317317984491179336577602994390 * -4101013213108384719") << 0x6b5c235f95b7977dbb9b2f93340ec0d6_long << -0x38e9b9ca0a8233cf_long
      << -0x17de2c836b6b9dc00ec0f0b32801661695839d4851048f0a_long;
  QTest::newRow("325119494957799047678206771929243208198 * -270031138139690766021553520239822260414") << 0xf497bcb18efb3572d36fb970d9484a06_long << -0xcb261b0121bca44cca617570fe8c48be_long
      << -0xc218baf3e476af2e13714ba7f65efd5e1628b648c12f57099c1b0c7807c0a074_long;
  QTest::newRow("173739764732630358068522034012612910485 * -1980544810469106606864035971655801582337083872343648527710") << 0x82b50fc1472418159b4d7f4f8ac6dd95_long
      << -0x50c5da46b39b0a0257efbf1c41fb83dffe61d604550a655e_long
      << -0x293d99b3ce97ae7c6d3ba387d9f1bc566399dfc1bcedf51714e68b209556cec02fa998a08b4325b6_long;
  QTest::newRow("186756998441889109191893635705618764455 * -98634673164503686309565836137383456236368132208272736620369698786255552946200") << 0x8c8016ed8e3eab1bb90a9ab776bf12a7_long
      << -0xda113f23ba6bb87c68aba8622def6848955603c160cd6cb5e1895af27acca018_long
      << -0x77ae8aaef25f97cd5db39de3c7f4cea818280c10573ebe9016c7b00bc58e8d415de13b49e3c0c154e208326f00a61fa8_long;
  QTest::newRow("274865989048389233315093252774692458166 * -979625316869801270188163922149338034692767870538836588324167658494197732744443690088020622702330") << 0xcec9438ef68067071fb0b3728a890eb6_long
      << -0x7568b3961cd11b50c4d25bd14dbca5b6434667e4caff34cf2408e3bbf1c4e6a453df0cda1403f6fa_long
      << -0x5ed68eb3c42e4b24965578e45240b55e26006b67bb817f936d059c5ee0ed90c6d63600ff52a4a3f7586f534414e4de49041ab2b8621d41bc_long;
  QTest::newRow("238706434589557239121864261243510546047 * -18297754692685840909440216001627632654809610815482876431600373201547526079218919317277685908078664860401285563246068") << 0xb3952fe1288b30bbadef466827395e7f_long
      << -0x76e20676e174f724881fc43bfa595e418f681f6a0fb986c6d91ac58f798e11d6175b4bd882a7dcd0190785c6326965f4_long
      << -0x5365524ef1817820a37bed1daff0ac10f779744ec359a492bcd799c946e84ec4245b0606886b3933cf1df6b7c736150fa474f90c71d4ba5088278ef5950d2c0c_long;
  QTest::newRow("297749131776407709022576887985478549332 * -497258262651029252012204724390636493381918686076635012276286585597346218708221837859160702830633151769324292108905526152139537117630301") << 0xe0006599f3551600f4f4a81de45bbf54_long
      << -0xaf23b144351f761da658b111185cb8febb6eeb017ec8858d2267170a7c6d9f6f9622f280fcc67c845398f70b1f84aadb199533e7d9484f5d_long
      << -0x993f809e1639793e6dd8a8674652b02208d69185af3cc8780100da67318df7dc9b34d7a28ba3d8e63692d5e7bebabc71bc4d50e0311a062b7c1e48614d6a8caa0187ac1c48ff6d84_long;
  QTest::newRow("142496447559279353156765384743342283182 * -8747299093121743570851613675283494244753417255915205527270497091918088671406893516684631599407936243766700349382786891502840134590837158193724621051925083") << 0x6b33d149cc5b14a8620e8aef39fb99ae_long
      << -0xa703e846db1db347e5f25855bdd37751a10a792ec267b7ddda82faa89dda2912ab152aa1c292a649514d835b43dde894a87135a0efbce1e817b34dcee4e4125b_long
      << -0x45f0706739c4aee7afbf6e3f0061ef717f09f0242730583220cb776492fd9a0989a2dcedf05865976f90ddbef345114f6f4dd1227c6407fd951caa8a2bcc3dd1a6e48f834ff691cd19fcee152435dcda_long;
  QTest::newRow("271422256507637672869307450091329750623 * -232481244766377324367799268555298383928100778940831390906939012943065394385572476213696677020152999866840488979513776285146606788617052315843160169115682723646596246969692471") << 0xcc32066f73b0bb7ad5b1e20f5753065f_long
      << -0xf0a15dfa7f4b4d896170805013a6e1e3b217f8914b6449793720d94b0145962dc3dad29afedbc54413d11cefd5e55588ac0b458fadd162f8e98449ab8d7bfc790b079c5bae66b137_long
      << -0xbfef9c74834719790cc31849b9715c4a53bfb1b429c1795d3ec405b1342957818f163a6c2821ac939e764d3208e0e6e34f96627bbeafb0e9892c14cbb15e3960b4f7acffbbbb8ed7ed2d9f4ed31971c749f98dda46180d69_long;
  QTest::newRow("111289757359674540351311054305081634593 * -3795209017883653315457573245292869201794694236044479633238470871163264354238377482507519234938168132475112289288972127748261324722343478698177671704213775352832588401731053286417714239722586159") << 0x53b9a0abb8a567f9fc86c6e6a5db2f21_long
      << -0xd4f34cc1398ad4ed694f74232f0211db06376d4de9a0ad5378ded374c0c53bde2a24e3325bc42f57ca75821a927f8acc95dd8081e4c4de3306378043143f9e107d64e26772b05e46063cc38c8821802f_long
      << -0x45a54b5c056017de3e035b7376722553b380851f1a1580959196817282962d7e8586a0b414a779427560039079aa9c75c4429789cfaf1de9734d9ab0e1a24a641781b908450018bad14b5951ca88043211cf76a586d1b62b6689929ca60f270f_long;
  QTest::newRow("165255416766781169710032657624697336990 * 9876691800076366306") << 0x7c53091a9cf3ed999df32bf25b42f49e_long << 0x89110edcfb90b1e2_long
      << 0x4290b89ab4c9ecd396ce198022352650cd4634565f1d317c_long;
  QTest::newRow("98565674791909961999965325380783805240 * 112526032434110560906698395783910280646") << 0x4a270ef70a8299d90f78e910b1259338_long << 0x54a7b9bce9116efb8f75c419c8824dc6_long
      << 0x18856630c49cd30e2c03ed60a903e991bb4f4d559e3f7e975c77d8c1d2c7b550_long;
  QTest::newRow("98018448847634621968103692248421731574 * 5460367160120847439503438843404911757928988958982520865878") << 0x49bdaaa494b40426838936a33f638cf6_long
      << 0xdeb0e4a653e03177988c8ac1bcf6aae3153ab3795b368456_long
      << 0x40256e3cdf3aa50d6df5d0ad6a5d86cba2f05825f8074fe311ba3fa5a7029fdc2d95ebe7ce0432a4_long;
  QTest::newRow("29966307172223878245144673876341372637 * 67218257686642911286427732596141133038699479443896153836499548138058020887687") << 0x168b4d033b70558d54655b125a0f36dd_long
      << 0x949c2f847f75041870dbaee39671831dc1eaebe844f18d6f3ff511f71fa11c87_long
      << 0xd1649980a85e0b93db58a0eca712f0284af002501463b3dd038e35089cae40cc9ab9a542a21751ae2af1ff86c031a8b_long;
  QTest::newRow("83743065839408528113529430518952267387 * 177503835539713965781807967908966067828625553379149556306871969296500429993456517578995729457333") << 0x3f0053eb95be7915ebcf0eadbc8a8e7b_long
      << 0x154624abab36c5303b3c09c2ba8ef8f7bb1f8b6e9a0c85bc77ba1f9383d7496e1e0cc131596860b5_long
      << 0x53c49ff90db7416e7881ee8a13612f5c72667b063438c3a9d1d55b596e17013bc90a54185767d1a819a8eea865dc6965fbb4be7e85cdcf7_long;
  QTest::newRow("296204181711211373907562720778232809255 * 510004503614497155836866451622950336253256247383411775439500792964321240776442238199458337489398292184001525664967") << 0xded6d9aea3a82434b3886d7bb7b84727_long
      << 0x35045de950569190855f360b8ebc3fbc98676cd886cf3038182faee1679147a80e4404ee7d4ed9c248301dd62154cc7_long
      << 0x2e26482bb32b6e6fb53c88951b09179221a3f374fbf2be584bfba4857624df60d336a263fa797834ff5e4fe88816c5384847990e45021f59e5a06bc4991e351_long;
  QTest::newRow("105027050486554347595117082632156707573 * 341275051128031114253023203135775027248361600397079869187722444669177017928945036833364273018188244013163445639172632585077135309632589") << 0x4f037961e989c9de07e16208c55d7af5_long
      << 0x7833571fe73c19d31e4fe0125d6cb4a5bd17737c859c8a0ab2c80aa4f635811ea8d859a256fdadd5eb39eb3d705bf9912e59bcf1b9b5744d_long
      << 0x2519797b1b04c59cb2f7dad46f2c832d144231ed26e1bb61824bcc6ce233da4221873ef5ca0ebf07ab00bec48284873eb07e1bf60152622786c836b10ee8dc1c5e843ba9b50dffb1_long;
  QTest::newRow("268176394639041218988624791098094886267 * 9604336374416664851580408931073073061678397387105546214765685432383847219511606809164225434740368550474603974441702482461003746645976509526441253650559061") << 0xc9c0e516f1189a43eb48fc477ff59d7b_long
      << 0xb76104af4eb717ff0f35151df08e6dab6743cbe5a252e084fffe02c47132286b73ede5cdd78df630606a5d83e558305ff2c5b953ec174e076cb6032ff7c7f055_long
      << 0x9085598b6083f8a64bb91334351b1b0dff3f43d78582a3a6095a3f0a90cabc525b83ad7e4d6a8544915f11db9f8890e22fc9adaf9e4edd6aef778f459ffdbfd79d7b75390285bd51dc2b9927d7cd99d7_long;
  QTest::newRow("305574793009095368261362693591758221593 * 192157955447693804849493338308114256055138236760837863366113272470967215705525046152331910287557301528565153013540871786040950488780908654142853811258289080086248926667815028") << 0xe5e3907d36cc25438bf6c8ef41033119_long
      << 0xc6e4c3ac650cdbbfd46a48319949a0f78efed5a429f2a5e7a369bf77027cfea7aa6f49405862003a3291d745b4deb1826c56b7a8799e5df2be644da27db9ddfc315f8dd8382b3874_long
      << 0xb29b7024ae997b83dc95f07b01e1df9f5fdbc0a4f6ae9a18ac578c14732f2019e5efae4c6c6a75118ec0e61fd4c374833f440b5ec137d243fecd8941b3f3216a4b404a82c5dce54bb9f5030757561e801c333300df62b754_long;
  QTest::newRow("17070777251336213186127942103302805586 * 4533287398579088209131184523260150198865837006793982505869093040509051333162738831952117430727963440411550675335437849465343521632792545045597967132360328449460470492249268762442637160389430731") << 0xcd7b64cb99c94324e7e233724f61852_long
      << 0xfe5d3c71f5a1cf7de889c16891c2105680032fd1aaca1754aa9dfee77c8fd1bf511865acdc74f04efaf1b19410a1ff256521267a6d922b7b993eed1b287e4bb76f9255efb471cf4588a967553d8e4dcb_long
      << 0xcc2b445a04ccbd4324ae89144553d58352f5a222c7e7c79a4e2e8ef9a7fa105f8db32bdaf87735bd7c40dfee4bed0961083f2d2217cd16ccb6474cacfb1fa18b2f1e4e1a90512b8929f43920e13fdfac3978a212ba01e85c2a3b85f5bf1f306_long;
  QTest::newRow("1259852438586003598085025053993496290836204044680972838940 * -3228856748610348254")
      << 0x33617923454e2b07e79398eff4e0298cd65fcfd45381a81c_long << -0x2ccf341b0b8ae4de_long
      << -0x8fe57183da27b158695f1cd9111efaf30e2c5650fe2ffba47b15591b740b848_long;
  QTest::newRow("1072263244827429256133484855596784608583434592480573014508 * -187323428902868817772620162653018909684")
      << 0x2bbaf35c5713e729b68c76ccbc6fc56a8883b9bedb5841ec_long << -0x8ced2e1b18408ebd4c694b264657ebf4_long
      << -0x1812c10a04b2502a1c65b41802007096c3c01ae4d933af9edee2dac5a0619901dd1bd75003d678f0_long;
  QTest::newRow("216040757214686008275729053335125614807236749548303640705 * -3837960088436884481931963312914262902029910509656797916678")
      << 0x8cf921ca09053210e06accc1b16f631c2b17e42cc5b6881_long
      << -0x9c862c487a51736c4b7adcc34908a89c87ff8fb0e614ae06_long
      << -0x5631b361887bb21771b984faa2a93b0955c95ff3bad1c529e59f8f5082392f997b9cd42bdda7ca5c2835b2efb402106_long;
  QTest::newRow("4491025135999626181324937102507330419214596288303602378281 * -97916850543023093868116387400790287911561646759959110801907666932566256233424")
      << 0xb7287d7ee20db991ea0074b4e529cfcf38fe1cb75768a629_long
      << -0xd87af932e6b682462417db997a94500075e5777b75e614041eb5c0d654c3abd0_long
      << -0x9ae22579aa3d308303139f28c39309650da3596a2995b6494a3d4237d1d56ddcdb44cc2d47d56be62c642a70fd9c6e57eb125ddbf13f6450_long;
  QTest::newRow("3554648344951021668031645213797523418686705690244584115310 * -756844330505875346333526547534685799611726700836808255878347454617022293233160848562622472066963")
      << 0x90f842a73653d128ef3235297b031d2d4780b829601d0c6e_long
      << -0x5ab55f4a9a23048c06976ee283ad3d36c2c145f47429a2b2c381b53b564431fa89a2dccb453f1793_long
      << -0x335dfcec491b5ee6f4f6e8265daf99e928cb0cead7a85e5dd6bbc760786e8c790bf83e8a282d919afad234ac6e5564ea10933ce8f9be439a01df561e81de052a_long;
  QTest::newRow("2716422562991348962134655399664415823748375416059193540925 * -21507652722800873624807931654173236585367120951919491639843909419220130292047370182509722739886595024341513489282119")
      << 0x6ec8c65d3321f36f731b99482c924e7c60ec6c37fec5413d_long
      << -0x8bbcf02797538e798ec73c5ad9621b3e70a76b648f7c9a7362483a99a4ef5230681edc9d5ea60768ae6da1141efef447_long
      << -0x3c78c713a33f2a0029d4bb9e182d78b13a6358f1ae4ca5bb069531026982de593cf21c8427df97dce2e65a952cc5422d3da8fcd075cd2ad6fc428bbd402893d85a8abd7b8b693beb_long;
  QTest::newRow("3789303827657071381454856846625594105177258447990006493194 * -236415650763945838396182011396378787645794791302144483292719054830164570123532560908159659702629701326434748567606209951305534247770914")
      << 0x9a8a2d8bdf802c5d918a5ac15e3fca61938bb1f46304300a_long
      << -0x53449b9efc0dabbe03014d53c9920dc176601bec32948d21703613ffbeb37235ba5700ea6942cf76c441b67e813b07166db643da78179b22_long
      << -0x3244376a15a1fe9babe9b6153563b17576bc8a67f26ead7b59c7cd0e027a68891c870c52ff21976d85a972628a88ba21d4bdd2bda859b30fc115b0228805e5ca803369f09259c6938beafcd1b08a6f54_long;
  QTest::newRow("1137550921753194125309386848246522103126846589767196251042 * -1502264857024962858054116206309861851393423212039972904306691902850729395353898362370984471656600853243127395423130887240026870796708331799830356604821397")
      << 0x2e6495f5a800fe8d79d2da933d23913b1ba99eda97ce93a2_long
      << -0x1caeeaebf53dc5457dd2109d58231f55118e50fff1f7dfd769c4d2079888e714fee786b054656f8a8f7432c9f75b13c3790aaf80c7ffd49574ce91756acd1f95_long
      << -0x532b3577f31f5d273b47a8a18258aa76e5cb075124c86fb54150106f67da8de35b870b8876f3471a51797826577610e293d7bea343c5bf07e56f7a12978c6df6ca20c8fbd6e8bde59958a58ac1e54a8f3414233abd68b4a_long;
  QTest::newRow("6044584761667835892158181488620140924815538902005681431922 * -41127043130359195583347402414808896321903254600034276068046684423987800116396215715849276420127178618607065393657526092152309523353731321300002512618886153998695684960936945")
      << 0xf68468d690ca85c8d78c9b4e373e2a8eaca11498363f2572_long
      << -0x2a9193825ce97fa875bd007361f18d1125f76e1c93f897e27f511970b1fd9d662597a32047919f676c1764e8a63724c6e5f65f8fa06b1e93bc93008f82ed507c007a2231d753e3f1_long
      << -0x28fde83e26321de0fb63bf07ffdcbd6bf9382b18ea8c608a59996341bf7b1f8f01e70307936fd2d84f2070fb971ec4e44615f799bfa2b7f7d254cba98171053212ed7a11c16ac77765b4965867eb270a9708ca59916e998f79334922f19c5652_long;
  QTest::newRow("3761191909858772273781054368924432048658778131186538833496 * -2282628983669796641372060607288561835602457620183016808878805981240081458993927522013505870516654256897204798176954940647558639866072569007069393706727883641291677196752704561132998261554468053")
      << 0x9964ad012a80bf8eca625416f843898dc6a4dd0c0f54e658_long
      << -0x80143c0b388b83c7e8068d4171d275774bab64f21fdba33dac4632b636e456dca81d4a0222f73ff31e098c7b6d7c3a7b80ae4da35772bcbd2c615ef64b094ee6043db81350283196743df120b1d6d4d5_long
      << -0x4cbe76586b190551da86288bbd5d523af9a9c380209006d1863905868bfdb3af384f11d2dab9a54ae62e21ff7ec8e00a13e297098ec4d18a4f9d3063e013fc1c04ab1750db52d1dbd5329456b4e365c64a17883bf661cc7d4d7204386612d13887560ef675f48738_long;
  QTest::newRow("4332613023272820559371663074091469660759378931460004917426 * 17258562609672301567")
      << 0xb0b29730eb3d010503489a33f9410aea77f53439e6cc30b2_long << 0xef82bb40f35b2bff_long
      << 0xa550f716bb84645bc093b5605eb8c102e19582a35428d5a7f6afcebf76d8674e_long;
  QTest::newRow("600112722732621297921712599828856496573073359755193806870 * 259200402976378224427976224449369962948")
      << 0x1879781b7e60390d2e945806cb6c279f25fa51587df6f016_long << 0xc3002e8868d8284bfe472fae9f8b79c4_long
      << 0x12a48aefcf660de8390d3401b69ab0c87e0760ea979090efae0809255a8ce7a6e36718702e7c36d8_long;
  QTest::newRow("3505589084220790616952245951326028182633540501653287882531 * 5497744425921650333401993750809732058263933351529951235492")
      << 0x8ef80ecada0df14ef77caf7d7b09c1f638a5f51bccc04f23_long
      << 0xe037214965ca9cc693101d89bb90dec5f0c8923de54b8da4_long
      << 0x7d37d6d3a3de6f37adb1503b47a40e68af9969637f379619fee616d6d497b98a384d7b996232ae9379eb2a0d9509f96c_long;
  QTest::newRow("5906130951499620421163862795595829017327564632400775901612 * 80391963985922674266200966905914540155020997959643380194044617394021432577002")
      << 0xf0dee2615eb60a3b2bc47d35be9d9c4a308188ae3b4871ac_long
      << 0xb1bc3d38d302bcccf9228094795f2048eeb0c8d593b947b6c878985854604bea_long
      << 0xa73b37ce253a6b99151145036d7d1adff90cb2862dee91301cc1f65db292b0ede2077f8d08ac8cbdb1e9fd3448959f95c3412e377a054b38_long;
  QTest::newRow("1845345268207978432552619718866843148605129247136716350003 * 1985552119002174233096159517792501061667942539520606163441953107455552705549187859584574346578380")
      << 0x4b424db5f71d0d25cf6c5c80e6adb7f341a9cdc4cf0ae233_long
      << 0xedf8617de9659a868f7eeeec2d844bfdd585b4c862c04276960c5ccef966c9e70417d181cc8149cc_long
      << 0x45f566d5e17c651d212a6f47ad8f9ac3f2f3e3531ddda461bce77b4fe2dbe123b991495f96702cbccfc27e4af43c868be71e9cd14701a3d799e2b74eb6dfcba4_long;
  QTest::newRow("3787449158312029204468853458187436877948455197922391660723 * 22319977535431810099766416476176855939887187661494396163105907217276693305789497652138729336436364660974493691393134")
      << 0x9a76d0739c5ef5c01648c6f10557edba4cfe4a18f71698b3_long
      << 0x91040ccc2de4a9839153cec0f025f1634232e8f6433480549cee97eeb6f650fabccf76723f5a764c6ac56ae070c1b46e_long
      << 0x577fbda581849ce07e5d386f39bc0de5093649ca5eefab537bbb4693ea3a9aa0f9d71d4e88fbc69c112bce44965c71777dfbc29c6ddabbf7f93a94695fccf339d90849ed7e0678ea_long;
  QTest::newRow("1401210274567789806675361438290351173834881764800069742886 * 366456090705202450315852216869965740164579035688499450675150158427519236347021151878063339264768111136099405913182241053828806177098996")
      << 0x3925515f8f7ff8ee5f5ee2573facfa1da8dfcd4ac881b126_long
      << 0x8111cf1fe5898ac61104bbe68b6f2c196f51488a36b040b872d17437b0d5564312cf601871ea907153b9575b6f7f778bd3ca597d6ac28cf4_long
      << 0x1ccfc7b7da363947dcb34ab2078d07039b0120d5d5ea92eeb9820bfb179a92aa1c2edfcf88cb042b46391b5fd8d5e64411f3e8bee4791299c95f2023eeb529a827754b168396736cfb2bec1e0349a038_long;
  QTest::newRow("1975064525165971110892021847660587944915589871316923448494 * 2633321507822184826109012147471872052071043676184976153506395947628125732192797566979714848810935709174761104985835916696871454276037304116205088417839416")
      << 0x508ca2c3552ffa90fb816d31be1fee51a75ee91ca7d5fcae_long
      << 0x3247684bffb53cd8056b642902aaabec734963c9db4d62d86b1e17fb35d781bf5a7c09cdc86eb26926ef85ff3dad65b06ad795bb91b7ee49758fcefe401cf938_long
      << 0xfd1ef9c569825c8d6a802a2a4b20407e7f31e5e308c14965653e3652505e01b9e546b21a69c5b27ca4bf5a7306dd191bbba1e0dec89a2d259ba119bb4a05a6e0eeebf030db404404be53886db574e6ef96e70bafc9c8410_long;
  QTest::newRow("6197352298385363683560748749200814903760143704849241087289 * 109561623462489863733450720595753745319751909487111027684615691884488138721308230362509472669897981145501748663111444859950851967380475114945390736878922466211643091877637168")
      << 0xfcbf6084e5e923e36942d786c6ed6ea784c36e5a30c41d39_long
      << 0x7166ed070e13e9fbcf2f2aef6c2e8c4f6d444649ffab67198d7ce86a1c876976377ff75f7c455dfa6576f4b14604202ef4ed9780825f1e4b0657de544d2e4452a19f83707cd02c30_long
      << 0x6ff617df41ec50b50725add3cc5db3108ade382b15f27437ac9dc6f867e3e2466634f33ee1d7d9e77f25acc1bfe5d708b0411d69fba4f33dd11a9f83748d587edac57d5e2e30f166b4b93ef9241d4366f653c88e9d6ea15284aac2ba341b46b0_long;
  QTest::newRow("2013566462887412699810694027981084304892678873531025975108 * 3742329344478125167553517140853338759012081955188313500361778373839419169012556278875435207211999164228175132669571269563112875613040073391776815722388076103528912774963808049332053936323017267")
      << 0x521e9d622882b9cf1b696ab05c307f7a3e5921236aa7e744_long
      << 0xd1fbb9317587606f142c68e64fb5e2d7fb6066f463abae355ec8d05481ba43719dabf82eace0c38bdd0a3b7694d346e120492eba29fb6173848756ad0b9e8d8f34ec909e350adecb802d90d37ef1ba33_long
      << 0x435bbde96f9bebf074c7f7ba469bf60b41e097382344a3b384a72dd3812f905b2214c4180813d3f05fa614601c19130f6eee2b96567850f60335d1f2d661d63b350d1f9677110971e4cc21e6f21f5d41f7bfb60b404a3259ba8a4e8f200e111fd0193e7c6c7e7a8c_long;
  QTest::newRow("59356521601313801867279059049655343155321153100101593944665270568982315089705 * -237213457991921525")
      << 0x833a99c611ee1add00b05102923e59febb1d9f74cb6efa1ae512f4e587e53f29_long << -0x34ac0621b8cef75_long
      << -0x1b0015c0359d16d77be6a586f8b855c3e3be99470a2246c6a4139d295f48e253922a37fff2924bd_long;
  QTest::newRow("106738726790607943172777351530489413389792115340024387513140654792459652960131 * -295182877874757372975065610249485222561")
      << 0xebfbfa7b485d35fd25dbd37b9f6c77d9e1da8dbdf0a3177e4cf61d93a3880f83_long << -0xde122783efb75d1e31594c95098d02a1_long
      << -0xccb53f5b877f264b1340ec12140723190d254ad61458fec8647b606de4e6751fd22ada0f5fe726bad86b86dc0ed7c763_long;
  QTest::newRow("64910639072152533996778653515271747492189453946063506747522462540984550930374 * -1267243197309944044561752817838470910849891766603306167078")
      << 0x8f821ea8ea2ff649b154b62cd0247ec914b97c8bb2bd55de86811b16e6ffb7c6_long
      << -0x33aea2e5998fdd24c3152057f2a99aa6883fd9d70202eb26_long
      << -0x1cf8d1dd8a5875efef9dec13afd15b4d98956b432c4a2196579adac1c37addcfe194f09e0c018fd924fbceaa168b36b70c48062c03340964_long;
  QTest::newRow("59005345477441395781282952879754578806947419558457070534574313770574186494040 * -29887682643110167060434227881109110771636090575965337622212771904009469199709")
      << 0x8273d78faf019ee01b8045b072b455f3a2143164fbbeafe67d27311621533858_long
      << -0x4213d432e56bffd8b40ad830234b03282ed5332cae0ff9ce6cf732761dac855d_long
      << -0x21abf84de8d427b0896b4ea42192f2d3783b0f90184fda2f171667489b29b60173ad80295396470dd56c1f217e46e133fac64a3ebaaf513b6aa74e362aa12ff8_long;
  QTest::newRow("102939316511506121786506357609272375105732402949312850662815612949981820185678 * -1358363381534544658112490348157765381732008680589531908301294365235218863605091005119459999104648")
      << 0xe39596a38537741747ee08036652b8383efab02b55c1b8017ab190f0f6956c4e_long
      << -0xa2cd147acb5c30975785a530e75f91c16f60c3a455544458fe9764374409336a42bcfbb4da5c3e88_long
      << -0x90bafa51f516e89ce8586193527972590fbc917858a505f04ff9d0a1b9e5bb7daf55742687e716c8256091f8b2577fad6c54b5cc431fc1cb0691b1e2302b92e2ff8bd88087a46d70_long;
  QTest::newRow("80201670005350039343471992360651757371263586053960243797609323716523649408492 * -36391048051391937682575355299437148793870202880120769841595093105013764410924795646972512108505619053080429006626821")
      << 0xb150895ccadf78f588d167c0233640267a7610a7e5e465bb78009e26f0101dec_long
      << -0xec6ffa1d26266b89f0081226c22e770238d19a381f8809389c2d9be9565cc2405bfc1a360c886a4c27acf77f47e32005_long
      << -0xa3c3cdc9f0f2b8dd61af865046eb644cb16982f45c7fc7c3997d1b9c99ad69e92bbefb1241671dec9281dc335d2483c79acbba509e510fe60d0d88274627319b281537c175df60762850d76fb052159c_long;
  QTest::newRow("111615974345656261792552072533672947424062743301103986717848317702455697122599 * -339657486676752552348968284653382198368414541669908502239427700326038970392485049505155706683679460411886033014523961962260711432418596")
      << 0xf6c46719942ab0a44f29f15e132758986229a283b19c7db11658ab10f378a527_long
      << -0x77a17dc796b33295845c6b566c6b39fb724c5500ad452745baf9b069ad9c6ae594cba7d839adbfa57b95faad9c04d4191ff8978a33827524_long
      << -0x7350f6b0053d79b00d4ecc578b5187ad9fcd856f4a1e72a6b860a11e952f98ff384841acc136d36db1b2a8e4d127f8452bfcb7d705792f365945548d75943a47f1ebebbc534338bdad9bc39dc197bba708fe81d903400c7c_long;
  QTest::newRow("8352091234798067560515044971242846779831152066271518292724714702081012936672 * -7456390061888248185252627474097380480208776858410288183662970748085309779720092158871561739092838765014432704297830513410654055871502149529767088433414135")
      << 0x12771db9cacaaa411be74889762e6637dfde64d11dcf77fdf5651d9abe522fe0_long
      << -0x8e5e134f0a25b6fa0818076b05e8253d4eba87f4fce07ad795a80e4843678c8d6ed423638d23a082fa518f6f9226e940b12b8d4379ba31f12d234f0749b83ff7_long
      << -0xa44db9e836736d08660b48180054258798bea4de9247b93666334978461f6af4835e6cb358fe8d6721ca687ba78b74de2ccafcb1d54d3ab5728bcadcc750c37008030ae55ce067019b20a964072cdb5b87ed135340275078afc4efd24145120_long;
  QTest::newRow("46813513888979970408449056624146382729204323912176029073244414578648635387448 * -182216436347303214955549822067904249438491260322975004186197321606766916699686154809213087067707557856931313927210371696134018029714376030368407886361077282500567930772953536")
      << 0x677f828885e066b4e75feae33894afaea77e9b266e79656b24e3edea5f4fae38_long
      << -0xbc9a867b9deaf6c60dd5fd9af9d24f1b6848c568e18432e39de203a58b9948561171ee464fde10899e6c86b76c730e6e92bf73710fe92972f436707ab2b9bee9b09089da96f499c0_long
      << -0x4c401cef80e0b3760fdccbd1c1e1e422619ea410de4161f24c4af9f99b2b75caa82730440aad92f100e7d7b34d505b7e8c38a4cc2d9d378ffc2f3dd135a0a11501090a6b2ec28f0ee47f6d5e3263efeb09be837985b7bfc27a003532ed785c3548f55e74f8422200_long;
  QTest::newRow("76972617226335957848451411297934707937559279345202846104176464686863151926507 * -1745480225174896658139564655842860073754709104697095619580432509151981162039924734071535753082271277734191441705254924797145989364558908665906953123873985615488000674413673958492991919561589844")
      << 0xaa2cf51c811c5c57bb0583ce5ae5b5a2dadc4d1c67a69b50ecdbb68255b60ceb_long
      << -0x61f07ffaff52e976c64c5fe4c488d2515b2c23187497793702e697a31db8c2513c0dfc8c67953d04bcf8802f761ec87d4b1901386b746d07c7b0e87c33d7715df1d0ae54f32bd69e90a81bbc2a734454_long
      << -0x411ae818bedf3136befc31f3fe26abff7d4c78b7cb98c73dabbcebda861704b541061096962518e5eee0e2dc1d0af8bba60a959516461d3834ede4225558c97547c6ce2641b9b98cbfb58cf2162f9cc20b1b5fa3c1bef0e5ca2e266a0c8f723d947b2079d51cc0a442752602d6bba91c_long;
  QTest::newRow("53996317643720017791991425421824827773642214762040565089169480762776567594814 * 11093279359266185089")
      << 0x7760d52f2f822f7fa0d893182774a8f66701d99d71d2bb34bd9543cdb22ebf3e_long << 0x99f33ecd733bdf81_long
      << 0x47ca4d9cd117768fc5bf0525f0354907f4598567bab0bba2cd5e8d820546351f2d5492326f6f603e_long;
  QTest::newRow("43207178161302346278011944504618739055618452457089278919535387525158612645933 * 279731857437431393037961797190891933869")
      << 0x5f86656de5c27d6d3a56506bd4b6990e63ab659274715560a24cf906dcfe382d_long << 0xd27265646f9ab5c9967edb65512910ad_long
      << 0x4e86eee2d192d6bbd913d6a6ec229dadca0aecec0b00cd5d3d7d7c811622e7ce65d8e1af0d69dab33a1b34b17783c669_long;
  QTest::newRow("101203712850569163594906426449227304195277376423706435826005374146900921387825 * 4164492539730122807576120759856709570342869031771592288459")
      << 0xdfbf4585c700421ffdd93a233cfe7208a03045ef2b0ce18d58f1d2e27b6f8b31_long
      << 0xa9d754b214ff4e81e701200190ddd3b317724bd8712168cb_long
      << 0x9471788f1be19ec19f97af46db188e3282c857d32953b67cf0a1b364fce42580fc89593e8a77a5fc99490131f51c792c23d32de6c45047db_long;
  QTest::newRow("18274165318551096330197391075795183689782956668875222073804881772333305453337 * 93287477763804457031607462311531632717633609446572010074614545260231042386785")
      << 0x2866cf9ffb8420fd1b39fef21539e57b14a4cd7140031276714f651fb3205b19_long
      << 0xce3ed75f09441b2916fc43ba1e26a7876f9ac13d2adea133586982b48b85cb61_long
      << 0x208ca5f65d20020b11464d21a511b61d627ad902498fd356ffb54e41a63486230480fa13a50d1a8131869174fb569cf5b3bbbf5e17088eb3fa43d4e76e7c5779_long;
  QTest::newRow("109784138371304388903998591550742762844437559531470762084376675881640957188378 * 369504198513022273994374149337827890609637541671120711503491809090209054257336487726207872961437")
      << 0xf2b79eccf296b11711b23c5713814b2a9180519e797b0942458d62bc50d6191a_long
      << 0x2c491108bb99d4664ac41b6beb15187eafc7360a15ff221462f88644f35fc6973a9987d4f7ca8b9d_long
      << 0x29fcd5cdfb49a00ab655cf8d3595ba1f4c507f1e12bbd6451f1e898daf96a59dfca15f52276ccd7acce2b7d5ae4a589b913ea823a88aaf7ed2fa4660a73ec3cac3fba811b77282f2_long;
  QTest::newRow("49006743297628455779871462926730750287234554702264497718664329109459437885130 * 7964565164049695314674345156816423139381113323776582621884138186450376261766538735779629339071033125214775249119397")
      << 0x6c58d570a5b0e2e096674ac3d02c3b6bb76391fbe12903765c039884272416ca_long
      << 0x33bf2fdc7551c92bde93c5e9b7687c50243dd8e4fb5844709130b3704d9c2dae2f8c3128e648f53afd33f5af049ea8a5_long
      << 0x15e69d0e4d3c2e323644241dacccc7a077a2d5e08e4b26226a01e8d31029b5fc9f1a5fe8fab61c8f472cf086251fea209367b3750b06de829dcccd7f20bb4a0ae5663479a76c6e8c544da59421e34032_long;
  QTest::newRow("70623908731088419595419694065689861265574177396872780801407935979234961336711 * 210867385138136352568985744991239970598037014192299037267473651054148364623757342269466087947938407264898606391479541846604068933919960")
      << 0x9c23b73e82683354bc25a7b1eaa9b64b65e9bc21de17dcd5cad04406379f2987_long
      << 0x4a4507253a6069dd47e8327a5773ddf9bf4c9ee89a922941260f37da32224fdc1ef5597343247b5144f416692efaef54c4e69d612ce8e4d8_long
      << 0x2d4c6cf424525c00848633259c30fca2c9212a7c302cdf420f3624d7607975e5fb6eb93d024f1b4ca9520f642735fcfde6d0f915fc72e30b14b5715f4683933a886f4a12444b9ff9d0e668c6a00e6a01ae913950859f45e8_long;
  QTest::newRow("6627468604689068112434554217770859757309430690848890390864048555184364989151 * 9079424458147088022637410433584681808620573450422676119593993681383685961294572893759553694192209861216522534656536529205159129153329391466184100120888732")
      << 0xea703a91eb8a16ec48180fc475c4e2689735d5e11d957a635bf5553a7542adf_long
      << 0xad5b4d6376b692e1a8d1036abed2f36e98e2cb5f7d241e8e7d6ed4a52e03786c1bc2b627c7a7fdebef29b7e78a388180f472979160f803394a8b27edbe00059c_long
      << 0x9ec1745845c6832600f4aec71cbbb4f7dab3251af7007912260df89a187559c315d563608137c5deb420bdcefcf348b6c95d5e6f2f7c533381ed05ea5963fde4e908c71c3da0ea6e989ca360e8cc787665f74d94c3dbe580bfbc2831e207ae4_long;
  QTest::newRow("55234807198311223566247149415298879356706731240453178894481702347051166970320 * 239832006384656866640585730973608270664958162314999343538919849891349724049038268810310799685034290822322516707780560473213953849186669194121493352900334977880097996867856994")
      << 0x7a1dcb01eb8b92e6db5a0220e4e1bbd02f65df7b97a46ad313d2d7c36d7db1d0_long
      << 0xf83d1fc34c1d312c9862dbe7261ea718b180e67f4cfb9c37b3b89ee8ec7bd7b6881ccf9516e961ab539b073241ae46a69787530608a6dcbeaa7420e87f599696a4c291e1a43b6a62_long
      << 0x766a04ea0039f9a7826c8a985616bd37961402c5432f12d938cb69839cda5ed6e6382a6847cd3c9ac2393b5dfeb9179f14ef725b7e11d477bf99d2700bb112ad492c635d784959839bb4ce25c4601ef53dc96afb9fe07b5a57720a40546dd1a53d0c5dd730ae31a0_long;
  QTest::newRow("46860450565959335528644024894708562336725429415298942823039361379532616912348 * 3364948857062369710787084840401401107266327991814362735535175410479064554120921482032162152494327052348703125444925863300699437513314884176043212060549010706279036419512595618328687170141436219")
      << 0x679a133aa1e51cf4915d589c84a82839cc01b8c6300d2f7ca2ddfd5ea1564ddc_long
      << 0xbccef05900fc29a4eac082ff9ed75e3ac134e0f6cc7f6f20d82cb3e489387399447aa8f5fc8aecb03cb23513a1304a624f2e36fc4d3096dafca271829e2b8746cf43cf087a3c752cee8096bc9fca393b_long
      << 0x4c68e55eff103b4f53dab0a9e9879dcc721a36c3e089fbf5177f1eae05c8c751329211982910d6efa78e50a9012c93b4d427b1a3cc60a9a4738772a56fcae7b85f911a4764d6cc5a3eafb816b8d6f655c8f3c24d3e8c40999c2bdd6ed5c3200cf24198fd7ee26ee52c7374c079d1edb4_long;
  QTest::newRow("1772669185392758995581417439188260174576796315903908024006652479446710580650901382941890639806139 * -9771311563027797237")
      << 0xd474bdf15075e3077b6260acca18cba21a86dfd0c25368b2d4253dae9845850f4b87872ffa67bebb_long << -0x879aac188ff054f5_long
      << -0x7089ed37569d2c5fc461a871a4f229291a659edad66a68d4a064b1767a98eac9b291908e972b20b8d2485969f42ee4f7_long;
  QTest::newRow("1842590386514305247261441111259294443445578605386075708804602260912634100445080834758282609974427 * -240095100845244192473425709654947096006")
      << 0xdcd60d7b26410b80dd9798c7528df09a63f2b8f2add0d43127ffb85eb486be7efd18a349fba85c9b_long << -0xb4a0a26978760b35b201c5c2745765c6_long
      << -0x9bd1135d741b451d1b73eb9205bd0f3c2f8cf0fe9ae61a5843cc23d16af835959dc1b0d7d97f87eaf5678aee95172b4be51bc025c56dc6e2_long;
  QTest::newRow("309160319067034936821219914240937030006501734197802939931098536402684291967119497939229403615113 * -1881318306223036199736352203819486552988809927917481938596")
      << 0x250d9b0b159659acfafe42ba81ad63cfe6f10be620fecf683e1ec1d9c0ab69fa3f6d2c4869318f89_long
      << -0x4cb9e12d651035d1e39f0eb0c9f7baacd9b56123041ecea4_long
      << -0xb1af173dcb4f2015b2049e93ddc53acb06eac060203c937b7debac17855645c3473d776d0cec175c8a7181c142437f72f814e09293f415a93ba45d13b4e31c4_long;
  QTest::newRow("1792619761487685995524526576895804177357067240942045160037551211458729558872015592281445777656381 * -35554771493717282865680564973741080896934653325324536644965761139195007409191")
      << 0xd6d8dcbb23a16e1c18bee973c4171163a6bcddba6c1a78261deb507042865c98fb85d905747dca3d_long
      << -0x4e9b499b1b9a0dbdc7a7740185d97b2e44263e2e68375bfb67930aeead7f1c27_long
      << -0x41f86654ad92ee06a3e5dde4c1426e661da2200f7f076d3828e6cde37e167c2c086915642b1294423b0a60ca513702bfbeb91aa4e2fc046b8861a4bd30b584e8316ddb5b0e8b7b4b_long;
  QTest::newRow("625219415364550648169855848663089122929203285390333972942166665006037586808124123944326840416302 * -1029772083383028034275590799739996271152591160742198679485473822279846236636070730752724587642872")
      << 0x4aeee0dfc841734ee5d35b2dafa50aff5e2c701e730c8ed999fb4a2cc2869d111cf73ed8b4af782e_long
      << -0x7b6b4bd9340f9cd0f1583cc4a20f20c23f60fca1959f886be2ed6e53f1f2c48f8127663eee89fff8_long
      << -0x24202e17125b6ab162374811ae9636b7c2e30c9a73518b736adf01a70c8acaafacf52778659f658e09652c30e9dcbc071d7b92937ba1d9968b39dc2f9244bfe9d3ce4b85fc716da29a7600afe7503e90_long;
  QTest::newRow("1632051061133324916322958093486279092117972789117295060188236569034951728811390141843170308194671 * -7210517353365605227049482392003092992167943882463099051098321385596712120723618139252876592270776799104577284055973")
      << 0xc39a51eb359ea2bc06c6db8aa0ce0f273c0621e43ab4f1e5739f98d7cd7c6d9c6efcd6401b41016f_long
      << -0x2ed90154e5c94af3d496c84929661e760b57621ad93621c2fbe0095dcc4e21e22be1dfa221576c69d06a93b87747a3a5_long
      << -0x23cb898c2c8a99cf93865deaf8ae9605a27b98f12dac90182935ce5605f049eab30fa88ffff77b22c942f1eef298beab5b668419852df65510cb352bd9ec5e298803e8913e8259b48435e7a2f065e28b70557425f398998b_long;
  QTest::newRow("1812962309779272484769018550415391433300804456019809561479583658025281488490175118272154097275285 * -524705321569609861625155857878894232719989803270885434042208577844180902538378272683007053073023405704281211355046476764230957250460751")
      << 0xd9490248d060d049ecf3aa37985ae586da850079dbdece1f628d459adf73f0a4c391afcb1f65d195_long
      << -0xb8ce7a8966e8468bdfe4cd5580e047a88057c7526c2e6afda1010c729c5260db3fbf732c97a73582f80ac17aa6a5cbeaaa28f6c4a6f53c4f_long
      << -0x9cdbba6596de6cd6292ede7030828099761a887e25b4f146bc95510e2f7603d302e775bd2c2130e537b2c9f29dbbe7941f757028ee621a116e083693ed01100b44539f0d6ebcea8e022ee9d40d0e180ea0d6e8d77e078911058b9176bf2398fb_long;
  QTest::newRow("357946337389015012379054555311689485107106738914169538818416499579038367733989269460762615166600 * -8961036418867760824954189256539716905581514130117445932744505130233076443913779414214242786783656652566705874913883967931594662179713595849850282266827563")
      << 0x2ae6733dc4e9299812f4ded98628e4d46cdf81899af49fed02ba9b02972a118fdcf2babfe9093688_long
      << -0xab18a234b9c39deab7921ff3d47a446acc3451158bbe19b50bd52addd38ddfd9b2ba0b3af799a2d1a9dd54b78c9486d4b3344e24fec1b3d84e78817956d39b2b_long
      << -0x1cac0fc3bb3005141c08f4bf353caadfae49776cc15f0b3ba58b056a49864d1df26bd1c83e39e127a303e404892b68bbcb9a9e00cfda4abfba8180a9fc87274c1287010a8038ff1c2a79b34a78aad059265fcf1d23fb3995e26b579789b9d38f41e309865aa880d8_long;
  QTest::newRow("1859414184687687172778252095818550221260508577250510338133741360328862858289438892324522748336930 * -46331948619525218996993171852404307190426922068475587014193306789392997495756618870607280558773625472266325832255693918492501771692130276720076359258361879058396853245251749")
      << 0xdeda3cd65b5c731555d59497c375e61fd9ba40ee5fbdf2b740f4faea228fe2a7cf008db27c80db22_long
      << -0x2ff4bcf9dd7c4820b43efe5830cad33913377b43a0c04887fd183f62e76ce451cf69533c0f4a80a44fd64f8aafe903d4e3d6d0d328ba9b3421a8e167a0a27a6737f47b5437ab10a5_long
      << -0x29bf1daf1ed63bd9ba86de4c2ac379706ef57bfeedfe60d9952a16150ecfc4c13f05c21c1b9e1f9a5daf3c15caaccda31e5324ebe93704b434539fad0cc6c65adb94e0736036106d4aa1de4ca45752d5569cebda8680fa138dfe5b61f1756504f23236b0bb63efde61289220fa755cea_long;
  QTest::newRow("945589004418604766925021901278978156128807107809285305275088995333398894634594598590750012492211 * -3245172385142230093664349166589630298399114783643113491972884395746074414778220085216020884082111832558194386576062148226492738513125526400096017818977992622373280521246997602846441301601109932")
      << 0x715467af15402a9861fbb09034fd6e17cbb0bfdfe6f8a8884db71594fe645abd0d449b1d889c49b3_long
      << -0xb61670cf0fc1bcaae501825c30bd489478744986df8dfbb4fb305d02c87175f88e490839854bd3e8360bf1f0aad646a55b1e05761bb5e7a7f8b178a3fcd3374e7ddaf813016cd7389e3962e9956f47ac_long
      << -0x509bf0e7f9bd97e55116d8c50298ab081b07b58b495d20edb41693d51d306cd37290524729c3f5a7dac9393507094ff20e06baf37839c4df5b4a6cc2c3f4cc28fbdbae983c81cb9de9c539fb18d26375f3e12d148c3eff787e45dd063ddb36cee257e1f53163b89cafb7a4d72a98e55870bf354f450f2944_long;
  QTest::newRow("1616464559383470463937470899067897793188916672773716401340747332573108974122262337045695279176497 * 930127869020065689")
      << 0xc1bc18f7f40c342530782f066195222a23bcc3bd784217b0ffb6913213a1f62c84b0433542c89b31_long << 0xce87a5e6ca1cf99_long
      << 0x9c4c03d5952e1c99dcf7a133231277140f069ab8645da4372ef0d26b762aeaf77a50ffc6bf9eb8fa062337565325f49_long;
  QTest::newRow("89503807875968230960641054721244941812596456142170034640574162236617545958170113757316277839686 * 273099641201514577036704117182646393407")
      << 0xaba2417e7d2a70201bb41833b32192f0264aa4ce9df978d726d252eac4f4f1409977a47577fa746_long << 0xcd7513e2c7b8e71a1a0e947ed2931a3f_long
      << 0x89bf6cef4f0b7d9ce9e73da0197d77479daafa7e1014785d3920e700e4e5e8806f48327b683dff220b916483f2c97f89acd1869f899463a_long;
  QTest::newRow("1055954388578445882352680941839669653689369960807104940142222727572311479092319945640786171720970 * 1891076627998295076103489936058269726669913102376822148179")
      << 0x7e8e9e0fd1e7b608990a9bb7a0a315f4dd541cc135029bc784ac7655b05a45d5994b2a8d96fef50a_long
      << 0x4d1fc2e019d20e62848d37731f2c735377aa93eaa5208c53_long
      << 0x26209926c3632d4299030e78fee061ae78d7b84b7ec575f6bb553447219777ae22e5d93f14d59fe4fbb3daf02ed45be7b38321341dc5fc7d2d0e276d75eaea3e_long;
  QTest::newRow("1463071459594541273129956566870284969157070881318425966624516880230406695950418251701078777320466 * 99095472275806168515603420676374864228819672669417666034549759129474875062941")
      << 0xaf59b74438fea83c91c893ce522f7181b5d493190d4bee64c5f7e34821013d80b5673f392c22d412_long
      << 0xdb160cb8b4fabad53ab6b299bc4b82a8762243b860beeb546026c2cdcd28fa9d_long
      << 0x9610da33d5a87df55a8e1bd72556ba5fa6a1d6ac1806cef4fa58983f1a351e3698a5cd7e843efeff749cb6b05f5ef9d5bae9c948746764cf7d3c97120f491badb49bdad7a145a30a_long;
  QTest::newRow("1726675936251855072459907117720596559165069307956333780900799688277481070139185338160237966196134 * 836276699655086145880715709853515172396089658957430231528592299483640212941772941470885883311497")
      << 0xcef195b044814ea7288ef1f84a17655e1036eb4e178a2b68f4f3a3031c14690d207836e6e346fda6_long
      << 0x643a80c5347b3d5e7d4be16c5799bb38cbcf8e88dadf8752270e867b91b5cc9be834b89287227589_long
      << 0x5105a94cf9df0d0128d094100957295807da0b92ea8236a74b7b5b14fc2e8716ec67fadaa1174c7e0527e41bb8884fc634da70123dd8a7035bc2fb31d3adfe4136cfee21162a8b9cf8757f4b4cf69bd6_long;
  QTest::newRow("386972507000090140731431320419184990071197263989613979933903248974137104289509615428086710545009 * 30675963673401799028135346726067863040856416230323698883729581985559421348236871270672546938678899613583999168812968")
      << 0x2e6106ba8460de81023d9fbae4c5644fb1ba384c53c13eff8ae889918bbdd259a8bf822ac1a22a71_long
      << 0xc74e46233280f8bef86a96abb2a1f464b5c311ea3fe185a701c115aebe153fb6bd35c950596b0528c7c29fd0a03e17a8_long
      << 0x241b9a7ff1fcdf110cc860bf13da99f16db6bfedca331349554453c5da1bfed78eec82f093f3dc26cc41bc0c01ffbf649f779b60bce9cf0f490fda9039f5e922d23a68b52441ad214c98a6ca1e6a9c473e802e118b9a0128_long;
  QTest::newRow("1665506924345263174184029767858830353872345653074343770576252284923416557546446398584149726608517 * 601171039173404600539036007945892488495171498807199228749499961471064792259745426358143225891446795365772203518194143479344256460222937")
      << 0xc79ccea7688059dda2c1c3d212b916abbfb7c1af862420f6b3ce94da6affae40e20f659ba0063c85_long
      << 0xd3bd12603470f1e20fe9728fde37fc9836e55a680826435a19ab537dfb9d1cd9dce86b15352ac60b181e20698a52c4519c8529d7b78b71d9_long
      << 0xa519ab6c96f320238a1430bdb34561d8b1d48b171c2a216e42afc0933a7b4b50e8e93d9e0d7ba396c3fa19080cdf8cd5fefa341f380af85662b7cc44aca503c190d0a1a7d807a6d4607a962d23c7fbeb2a7c634efbf4454eb7d24be6553701bd_long;
  QTest::newRow("87034341184217306025969134363545748768227637036326814447944209783102331289663553237100615261998 * 11363565084005888336982929936281894986888734353336425843088145407244934625167439052713664711183451629321422556950655977056912175399482623282104736241143559")
      << 0xa6e5f8b7eb77dc656514bfb8226d7b90dd5b9f141e2a64ad6b260a976ec3ad5642c34846c595f2e_long
      << 0xd8f7f2f8e9849c095c9e92443fbf0962b0b5b24083d21e9e90cb0c4dc7a8c81d0045a1dbeb442527ea83af47adba0ae80844eb9f341323f2852c8cc95db7cf07_long
      << 0x8d73b025d445e50c7fc0be9760786d6790d781052fa1c1469b3e0958cab08ab8ccbc9cfe6869e79e91a873b1f7b331c79818e8a6e8ffe33dc966ec37d096d540ea708bff615ba45a60c4b4a2012ebcde6f12a6b23e11602e4a7dcc68b5acb0855d351cffa49cc42_long;
  QTest::newRow("1434858460823700031893338267852597283082993134079233411794450541584679254020727416997591603266811 * 176137763002517366202230754008181300966156819113637850947131573716822216882260452677795850242524062094346867552273518749018481170563714024502794553966277754412936982400683683")
      << 0xabf816deae8b8f3c01328066201894ae80df72a0648525943020992cd6d495c5ee910bb47f30c4fb_long
      << 0xb64fd688c9261dfdd28272bcbe8e28c784642a377fbfcba6ce39cfdca9054c0324853e057d58ef67e777ff1a301eeaf2b9b6690f44413d2e15249ff6f5faa2e203f8c1217c454ea3_long
      << 0x7a7801eea4d8c6091886fa965022d8b9b9c8228ecc0e883de1d4b2c9f97429d6f2ffdf6e4526ddfe30c14e96ef45a37c250840a7b2d23e50e79a9888a2eeb3d192e6b8d605d852a81c20e1e35eee6c23b257389acc4b7accd11a02f4fe12b48d5362060b159655c69b1ff99783b8e5d1_long;
  QTest::newRow("1638365516550831848123628433623519423823922443839102299231807249568141389048169956597734183232230 * 3933134606716793025527230349987519359514938469308237666391829502668682584791477153892948715486581017814490214283246420514857734313020878882537892268473185835962437919133544059758431194872630233")
      << 0xc45c0f1f2864ea73507aeed424f4a4d46a22e367bbd6df5cc4d965ca02e1ac81b920ae4ed6f362e6_long
      << 0xdcb07f0f250aba1fc3088c72f22a2fb1b5ba21a03e22866317a4f7e685adedd6c24eaa16f3efe10017a22bdca0d5db95045f086b052655f3110522b452b25352262bba2face4385a2a5e0344aa014bd9_long
      << 0xa9467dbe75715f450e733b83f6bf420cef90861239e9910ffab2fc9509a64ea6d8065f28472ddb9024a4534e8c58505a59c5719fa661bc5d0f5180d051e135fb33ce691ed53304ca941e7e688e263a2d4e05a8e2160ec36de769bac10dfc29ba7e62df6717fac2d0a133c6eb4b41d1fd88144785a12e36f6_long;
  QTest::newRow("38105543257620386672223826769282331505726390818807974721978479409164158746242304679583842836820446166284969639546657 * -17659040308580419602")
      << 0xf793a3498a23cd14ff6779bea2e5adf6a525ad996c2f1196809d9df0b4d5d98fb408428fc941b5b84900c669cf920f21_long << -0xf51183995b3d8812_long
      << -0xed013b58151ea51a7beb7e9e2ff5282031008111f01e7fc67a1a221cad4e1a6b759a828c190215925c1be0b755b1a516d1af789d862b9852_long;
  QTest::newRow("1428972481570030945675964231649303587989647631427837563812592354041908255413692463441842102628191871786740892285592 * -45702552200768316703256579602993048574")
      << 0x948c2be703e4d7f78ad448e178e2d5c42dacf79a198952a77c8d6afe8e37172be26960ee0435bc0a2c5dd3b7ce3ba98_long << -0x2261fdcb333c425ede865a2fd61eebfe_long
      << -0x13f37a35c151e18a74f763e027f26279fdcee58b76efa7f9373b38ce0a18b913360c8ce40ab69eeadf5135eedf1b89280f3e0598b986f5442becf3de40caad0_long;
  QTest::newRow("598916075879390110051638450664539207377663328553918094305794371180942854977688323803309021569916177200491146202973 * -6166315785438386694392134723446040181241437706622991218762")
      << 0x3e4280f532e01da00046935660a25e323adcbab4b6a8adaeaba32864f6e9c131b58325e8088bbe55fd2306e293b4f5d_long
      << -0xfb7b5738fc96102a52e88bddab379ed195cc826dd77e384a_long
      << -0x3d29339ad47eae7ec81ff2f12afb02b4da8765e63abd89830d0793fc960d7e7ba22b882847ece0a533c252f3f3e9b9f8e55e79d0b960adf346f84f6de404e9d13dd384e0f4748e2_long;
  QTest::newRow("8839142382862304910738981826252854481297628973845449147191004811429262424638908305600493035752128976953996984878620 * -86400314114198365955307259835412782849291627766058632947238330746525892750950")
      << 0x396dd754215e5c6af2088a0632772415fcd8e793e6e44d7b751689e8ddb1cc9adc0fd93a6ba607c89a8cd305632e861c_long
      << -0xbf04d845564c0ecb534c90529ab97b151a0c8a7c018bee6eac9c34be33602e66_long
      << -0x2ada09e35ddbe885a7690a8cb941723226472b16f0e9d5bad9311c3c3b424dfa2d043558b9cf3ae79b2f753f0781e0673aef38eb94832bbff2c3e1881c36866ef3bc952cecbe392dafa3bae9bf227728_long;
  QTest::newRow("11317556527987572220705377424253241268101999909073367949272859485099646231133811517579475000394010003073803052869282 * -959607701141997493084777509040152425072433349025418077011389889995509830800665744519426787598665")
      << 0x49881a1e4a2cbac0c555bd79be057f9a23a3eac43240db2db478032510a57bc924ce5d7836f4798c3aa6ba5bef3b66a2_long
      << -0x7302863b5c8bb511851198308ba4c265aecf417dc895eff099c569fc5ce6ad6a127f3108e6d16149_long
      << -0x2108dd5a1a2d9657e40b43aefb8845c7cf4c0979c4a949456bac435b007aeeafb99cf85675c700a6569615dbd74423f730c2e879f718a81abaaa9cedde9fde5c1076e5e0c4ba44dfc22738c6cfc1b92fcb03dea11015a632_long;
  QTest::newRow("23489977746029299734023025797073775418048866845903054713904916517625788281046284821766203943573231803833022956307268 * -13210153248542313738171477896331123315909613460665564267625505005843882695034013333117536891903794451932727055566366")
      << 0x989e1230435b84bdab1a4cdc65798bc97f69bf69907216b61f7a920401dc0bcbcd1316b07a065958397cc83cfe660344_long
      << -0x55d3fe3386144f35a7f0a12da7b369b5576304b904c6d0ac91a2a497c36e8fb39669826f33dcd7b782d8e80b880d461e_long
      << -0x332addde919d430b0e8fc94db6869a2f8dcbc31663c6434c78413cee4bb79d950d08128bd0f9fd3144cb9b6c12ebc625fc52455b22a8050d97ae20715b6d9062d81a0283dbc12585d5c582ae44a42848c15967bfcdc694481857058bff4cf9f8_long;
  QTest::newRow("26564691730718406370730016406432755797158615683614560600375950758129712865424237854385769285808283168550476182259055 * -400729862212366085105139489493927788569460158424819613277375507310011281901388203659787870150478486097469776133766491829479060595659431")
      << 0xac98230e1eefd5fb9516bdcc1353019843ba5becad129faaa6343bbc452979cb94047df1ca629ef6a44b06dbf51d056f_long
      << -0x8d24219f8fc5064efb9659d8b8d6f7bb06b820b8fa3e3bad79c5b421aacde338e041baacbf8cbbdbc6ad9c318deda56ef6d1a7d6e7f9d2a7_long
      << -0x5f28275ee4f6db4077fb256a41ae31daaa8e7abd71aaa27d11ef48027503ee914bd245ee16dcad9d0b51af93f2b437298a6258dbd27706c1c55482e419ef0179f6128532593bcad0343f8635527231cdf711d677454158ffcc97a6e989eb9f35cd1d757a265a9969_long;
  QTest::newRow("20690516617175187037615339037448610605997496046964510130942139958763727811747969782675987984620593664982210374273066 * -1110031061906515129905934826061539532446271373141790791733170504498895696227728944696116966559963694227194033184862172243038773499238139991614108740075026")
      << 0x866dd2e1eb36acd9fe35507ff9c98c3454ca675e20eb0253fd9e715db3d6a85f90b4a3d2f46a3615721d3ba20974082a_long
      << -0x1531b803de0d31972d9f135bb79aacdebb800c6cc0059ac3531b46302e2d00cb73ff62ceceead2bf45147c3ebf3ee2ab3d9225ffe404c2c6376bb564e8c3be12_long
      << -0xb211df2dcff85d80d0090783b16409094d81e6472d679c51df5be2a801467589da1831223544f967ee8daee15566904ef8f26c7ce98a12a7523dc3306575a8ae83a2a26ec4cd58ccfc2ec64b2bea27d8e9cbfc46fed407e763dbb63e8741bfb802663a66749043a27f5b1991035bef4_long;
  QTest::newRow("27373743933555520604307729658241123036689357406723342443275295415311325973645139276364975744062236292677120916997182 * -198911023416336734684111309226761980477068933753128927873376870865095743173046936337571167228053506048301256381591829333052475199038692755151439604281091190283694022043570149")
      << 0xb1d9ce3be5c2a7e3d0902f78b68840bba09e202f13301e73f1c60dfadf52929e7298f299334d92661c32bc732d14443e_long
      << -0xcde225fa0763203916cc5190b1f9106512a780ed17b541115d958c20024b532b6037beaaf720e0389affbd617d415c076657edab45a2bb083e33a887f12d5786d2179734f8e70fe5_long
      << -0x8f0886d03681973e6f0cb5cca96bea017f5cb1a3c8ea091e3f7f17a21f72fe973d7d45ce5938be64718037b7d12b0a1c0bff42f365135536458a8ccd7c8498de2a14f9054ee104c0889ef204ebd6c29375915c719179eed7c9f57a132f539c297024eaea2750391a1f7e027f5ee93792ebf710a92712ad76_long;
  QTest::newRow("12077314108979027782303043552858063287342503453884744585732609939535830703029073808315533885715484140430974372992276 * -3403624925699468371781402569515083718283146563368482935641724003016840008807677894892643365534998086505689682391828371320967759028990820190463533725970629868919293418769683674101884343502354226")
      << 0x4e77c7d859c2f39f4f0f16724dd22c5cc2162b019f67db1a3c30c971830e82ff3253bb16eb5d620c85f837b0c5e6d514_long
      << -0xbefa7dc3143f67ef50e975006eb6d2dd53d27684bbe6b8dbcc5cbead43bb818b6928e2ff12d889048a7aad8f97ed46d7da9b987e1cdcdb55472c2f90dd34097e5825e08ca576c6989e319531a1c9b732_long
      << -0x3a89add803ed01c557feb1c95b7a137f282bff2554decb2e358dc5db9038cbdebff9273ee83ef877a1c288995cf6fe7527ab689b5366e0689903ebf4337a4ff34c05eacc052b3654c587668180026a36b8f9bee7e3e5447fa32e3d1840768ec407cc71a5e81bd4a24bb0cf4b37af51a2e63129a89a6545b6dc9339118a1ae9e8_long;
  QTest::newRow("3849900999609856536126318649253563033037707780535050941714043009009231317188440495129115299306102635425079311047230 * 11404142060063599114")
      << 0x190368626a4e5448374f1ad5dc3ed23c4d4ff1820c67cb7242b24fac014dd43a3f8c5d8c31babe3b8c0d7b9e85cd9a3e_long << 0x9e43a6c82a2eaa0a_long
      << 0xf76b69cd3d6a6b09d755ae3ae2f3841a45fde9cb355940e99fb97b3746b377187e12c931991ae19fc39886d410fa2a621ec93bba599326c_long;
  QTest::newRow("37094558833487214463331008350635065721349451346030871899921661589213775960335461338034389134713931417019849923946116 * 328389792882117967326039390809573569879")
      << 0xf1021a2df90221008af2c4c330b73097c929f0b3c8c201b46ad600f53377c71bcc2e9cf8463dbb67aa6ae75a2d4ce684_long << 0xf70d92d474083a491bd4aac888c43557_long
      << 0xe895ce98e57f4bd593acfdb2525a9e3e197f5b0fcddf7722b0d16e7dc8b1df33e925c52798a48a1a477c702cd7a0e6777555cff8ca914f6f5bcd937cedebaadc_long;
  QTest::newRow("19914485721880376978940811911362749130041228227455456430514678638803717210114111245028797934174340079541647240615386 * 115834435933501232837495223025453807125471693027638292704")
      << 0x8163140b37ac07ae2d4174acf6e380eb3e8ca00daa3d9b6bb81f60cbd9f9676e92d92c29b658e6d9614b0d853c3055da_long
      << 0x4b95e314cb17e7372b58d1201b5fdab7ec3ffed0e9cb0e0_long
      << 0x2633c84f50fff6465f51f0540bca36faa69312bb2099c048733259c588a2b6e6d3c57484466c935e795ac2ceca510076c9337906a575d62113f26f6779c7e8fd0c460ee2228fec0_long;
  QTest::newRow("6394875118990990021059709399517229523723148258686454158500528333416596261622194444538146970142276095779313107300817 * 45438855090557004852208650756057178742929312968914066154313817515097132159589")
      << 0x298c6024d38e7f3209c3160b12dfdba8c84fcbc6fcd45583ba38e5cb2496681734531007cd331fb3c6bbd01bed2771d1_long
      << 0x64757b07d2258349ad562b0688155524872b2fbe2ce7f1ba8a4ea90faa98d265_long
      << 0x104de6ae0a9be9edd2eac3a2e62f27a9b429793efcee985d48220a84dc15d60c3bee9aa3f2d9ac05f87840145705c2b216608f33c981312ed838a85637e4ffe13241f4c542064c14dc01a8ce4a055975_long;
  QTest::newRow("5612497754411463297642479098413271390575136030398974537698701313888900810418696718871951685865020036309926578541296 * 127973015834424850704331712635842084837836350540015812149178161545700469077782894325262219016142")
      << 0x2477130108e567ce635c0f1b726359c732041936242b6610e57f7a5d73d9e3c005271a4ef68b0f1ca0228ff346f8d2f0_long
      << 0xf567264aa8f82b1b40f9a231c7eeec5dd7d576a1afc35f50a3ccce210f8b136f907fde24ed0f7ce_long
      << 0x22f4a68cf23d443ae1b2648a64abb86a358ac73a8e5078c82da0355b9e00a76d460bbb774b6d2b4a233f8a6f8c20767ff5d0577abdd919aa349f3fe75ce8ca1cb26084de8bb06f1ba4c02fd00d151fd0eae718db2bf4d20_long;
  QTest::newRow("31415424611767660719629644714925221057001701943614725433972917435851269685463078601279318539840822516608887305131086 * 4590029226625371475889919771424485268143807617926930827502037450191102905784503682510431855476860981326939017483972")
      << 0xcc1c31a2a7ad17c19d35b2893ac0e082fc4051103f37dccc06ab52db0e846f2c7cef2091049c62eb1d851849a2b9d44e_long
      << 0x1dd27002da4c1264bd9af653666cbdb272fd5dfc99d28780a2ecb1900802b2447938c71d811bc1ecaed84905ed1896c4_long
      << 0x17c6fa0ec0685d9d02214e82d988c188aae62fbe1c3c9d5b3993230a5b52feabd9d48c5377cd936e5c1517b6a7419046d2bdcd78d869b023d592a0ba53ac8c3704ee031f676bd4c7ef2b9e4c81cd1ffe71a6dac3faeb151c59aa6c3795fc3fb8_long;
  QTest::newRow("31373024564730732739514523359396739667864608145747296613219638331653053322706540701305883924580453252868784098705874 * 653203653652221142306352245621156045407669293448166202045020052639675314234414996784938490338831148113619533985446732293338925590484903")
      << 0xcbd5abdd995af140853df9f57943afe29f9aed3cea5f384e7d2cbd9d7be91807d057d2085ace919f18ec1402ed7101d2_long
      << 0xe610a26b070a98a580c4fef2a3274c90f52f526c5264f68e8ae797ca1cdc3c5d99123758a09d7d8e569769cb59002c182d264751984d97a7_long
      << 0xb72f3716444da2b01c903048af267761929c82d1b263f44856befff1bc524e19448f5771627941fef9381c946bccb287b07f0c4f5c331fdd84870c196ba801ad3a6c91430dca1f70bd3a6b0174244156b7bc95f911d95cd0a2b18ba8e1a005efeb1a1d7ac8f50dfe_long;
  QTest::newRow("31905555213002608857942037498334656460958598644595174170923288062307194141992376051890587512332415745743578100058964 * 3043337270309245780128919735620015001288916396694669092814430567766629259924015152496793351630298069836282869005787599447988423527885097121207486337620363")
      << 0xcf4b6946ea4f41ed9880f7458e43e459f40170d8420751c8fbdda86fcd0d69f5bac528c8fbc696782b0ac178d4cacb54_long
      << 0x3a1b85d04ad3a40c94083d6dd9aa5c22a6dc0e2a735148bc37643c8e3f6bfd9dd18257dfa0135fb9b2ea72be2d2d18999b4529ddd5e19af27be82ef4e249998b_long
      << 0x2f0d5f29031f39121a48f9acbbce71784230b51b9d9d68456e92dbd0002b4c8da5456c0ca2f9833d4b08b9189f9019f6b8ca039af76b51a9eb0cee7e1daa69553a9cda090223e6c08374f72be6bd1a7075f5490c194c48ff1641486c0e4d7f9fa3fbe0337aa06c1f85badd2ce0959a9c_long;
  QTest::newRow("789861201658847031095815224493313060865611406250258828579948518099833604779075371691191835253949768396068733611250 * 29162010301259421187999412103440536477767127781188716304665038440323972099324327844534246141234250249537470969596148523120352415475547932224062573229991680393626503485318558")
      << 0x521bfba42f88d984929d2071e80eb3e403b609906fcd870acb887930011fee394beca72b0cb9837e1c4812dc8806cf2_long
      << 0x1e2f28e11b658ca78aaeeb2f207da3166299d345bb98088440b96139cdc04cce1c4dfdddf4d45eedb4e49a72d9f051728984b9a43378caddb6240f45908eef7a9f636585666be59e_long
      << 0x9ae67bd036a1c0a44ed8b36b60c3eb4704ad3ee1e54f3a66bb7661c7600f4534c0161e49f9841e298d0c6dc09e8d9d12044c16b7863e00c8e32a246a6d13095ef1bfc7dea3db9e09a204b280aba55d010cb1f21ad0f8ec330b2f2c5218e5c10ed963016890cf1eec5858c25791eb98a025bb6c95ddb75c_long;
  QTest::newRow("35806270529335474038598366135171542406482465501677201501356754723480652179013065869995497052496327837355582052406480 * 2851043493344319498500833995816722007407373304117060990971946782183075676878710113677501158905477924882019531381299977720190469337228720610012598885959820304912662940432885262432460812042788628")
      << 0xe8a3563185237ae632c18f4769290dad5ee0264710ddd26dce36969b91b87a7694a842732b700c9fa380f9cd25a894d0_long
      << 0x9ff913f65047a0925b086b0eb65e05aecbfbe91853239a42fd07d6d24a300e32495734a2dfcd383807fadc17ce6e92e86619ecb05ec5737d5882efe830548128e246d4133cfa57c2b98192be388e5f14_long
      << 0x915fcb8b8d2a2b768cbb99f5eab70ae2ba14484ed52db935fad0118a387c297b7fc641ebe53fbe6572292d93a7138f5ded7375a99c850e3cf946186f044e54cf1c7cbece40b96b3432fa3e46baff757b105d6f0783fcca5ba1b235577b1040ff9dd00456e34fe6d1608202287922088e7492257ad5fbcb2e779b7b708bc4d040_long;
  QTest::newRow("151591012472496404559682136521051069203657593086938679611520498654533095816175155227319269736324418970421246056714640648379657585742528 * -10023646312793051031")
      << 0x3564537128112c8f1048f3d07f1e04be63f2c75991905675ba905a8d2566d7970fa9d7b0885b551f500a64b4cf9a49e936d1039fce3cd2c0_long << -0x8b1b2536c42f0f97_long
      << -0x1d0322a629d42238a382c1f8411cc77f4d493b0634f7e674f66e603ebb62f449b44a778ac6ace922e3f51801906dbdb841c2cddb8a91fd485e47235de7798f40_long;
  QTest::newRow("26239111942024678385504863518833773828265681734618009934298369106887915755409193581576660586886726769173805422932352290012618856888183 * -168139131496996697362315193635901908679")
      << 0x93ddee6162f18aaa640d5939e37bfe86fba534b80ff1bca8bc525d2874d47a804227b2aed8665c3375ff85f8fed201c03dd5e498d587777_long << -0x7e7e6b379cdbcc17733c970b986da6c7_long
      << -0x4910407d248cb269ff065efb8702cf76951e7cadbc594436e2a5c56bfc067e51fe3b7bafeae135002085d97f7a3f3945076acd88c1610a3dfd1ada6bc2e1325139e058ac2e70781_long;
  QTest::newRow("113206865429306496918319916911063888852398671116950917189064088964729581433275413914008825876895249391528647403159936602467796303168432 * -4163772721770502045130319085263679829917209201734038609926")
      << 0x27df636b73f8b6bbab6d12ab3f561893f714069e4320a7cbfab553602c516fe95f75365ee8c89d978aa9ee5dde3f05d084d5b782e14343b0_long
      << -0xa9cfd0caa5d22fce9e153ca30410c9464e7872dc88186006_long
      << -0x1a72d6c864516f873e29a2931832f311546ec1d5cfe22bd055ddb2edd2240bde589d3dee41dcf14471bca3bfc7034e4425dea8817eb540d5a1b5548d174211a6838ec1f5c6ae174ae236c70e59759620_long;
  QTest::newRow("654775763020024486086345317557706910315835449542896819674941624888065112065796586364521119583072376012445841235196799043854193777820192 * -108498533417227104537346755590835074075678552579787288797466457413147372599158")
      << 0xe69e628c6bd801aa305a3a319667eab225ffc3b4dce005831dcdd8647be9b193e3c2d085f64889cb693ae98e97c0ad6bba05ddc040a5c220_long
      << -0xefdffe62eadd05e16163f662a1f0717c045262bd978fec7a53b433b368e4b776_long
      << -0xd817a72332fd89947f65d11e6445f0b39508da1d2f183d12f9256ed9e05b8a37f961426c4432c295a5f68f2530eb9268bb864793e6b68bd0af11e242391569c6a81ef7fa126a8d301ac5cc9a518a90fca1c8abb22eac5ac0_long;
  QTest::newRow("663924696218739050002380907502108695174065757324227797284214950771144093075228733165648952137613074307039297163504864277864864142100288 * -1169243125106267769603554613049787732541570944609761689587913405253050933461122343266883053220178")
      << 0xe9d74e4f5d63dc129b0bf90417a6d841cb7a87b8848102abe4533dc67c52f872d47a02c65e484aba7b7065db3ffe8f1416c5b546d2408740_long
      << -0x8c22860e4168916232495d9517caa0f59ba74dd1dcc2742cf888a99c3dffb03283f37b2d5452f152_long
      << -0x800147df862005fd649534d7bba5ef97867bb54d6bb53ce454cc5a4efe267065eeffda3cd2b0efe2b290bc5585e5986ce232aed7e8190a20f4232127d460445f614cc52578c1d4b6f17ac917f4276377f4d336bf4524d01cd0bbc7ea6a7e9280_long;
  QTest::newRow("25547498203784038305438224383567494453925251532945165174007325538273418312283281355978800627187996528917547038465094681958633295661871 * -21424960581983149743460342951668500975759024069016345839435313547660999475754980716862525205778457782397234563902758")
      << 0x8ff82c2fa6c27a0ed9235b6ca31458e6ee36eb9ec12b43fb80dbcc1fe41ae560705863f07dd1a863beae52cf3eca641998b68053e714b2f_long
      << -0x8b33662c55cc93ad767b659d03f08424492f4e04612eb241032688c8d611185d28ab93069d536e29758ad05d5031ed26_long
      << -0x4e48a7e47d8cd9229df8d1f693be266f0a7d8da699e9834318f5f401588f3bd9c3e126b3e27ebdf815e9a10f3e61d5f331c31b96ea5c3127ddf90624c3c7ea430c6b5dde753ba86f2d0dc2abc371056d4b338af03672dff47b1d8a203cc16ad251726d73b6aabfa_long;
  QTest::newRow("161092295478408435478269664831583606406279999632500327781225392181386068069723633916856516560371182860297882100896823737350961135972330 * -311192824094715211538153858420547005761528882040089842310475283315189722989019526741136278576613759722588678129554257571060281823854412")
      << 0x38bd044c922c309d2c0b728aedad1bce3a21ca651b24f7b31354602ca9bb4904b5ddaad36b46ce652d3db44ea01682ef31a392cba7c96fea_long
      << -0x6d9af3ba28f00667c4f2af99c6cfabfa46aab2bb865f55b61d981ffbef2cc7960f8634fc95372395b58da58c35ac59061d8bdf175e15ff4c_long
      << -0x184ad28dddc948f5bcfad9cee33b3f60e7aea83ccca7105ba3ded59f55a18fbbcc22cbfbc6d2084126d72e6accc4aa24ff4fcbaf6ba0bcebaf2d5b5738a0e634370bd03eebb0d35da6bdbeb6e6a706fc78d3a451042bc50534bf274b01ac88e23c578d7cd7f4c0c44fbd0f3b90794f78_long;
  QTest::newRow("74482365107636776609373758614941420624128016075630826566952992910291821934167293752511067981721805107422266625037054113770505948949731 * -10248891050909141936560068523261798140109677273146276219253073853374607224273414827146785744584386494262485298563893827223189977709458562806368816696496076")
      << 0x1a3bc3360accea5a818301b38c2dce8e5e30eb071b7ec849060f6320a284778477f556dbea3519dc89df11a1315b2857aff305bd3e38ece3_long
      << -0xc3af8932c8a51cdc86d22ea6661816f48fa966f9df814fa0c0b1ab4b71dcba4c7a41baae878a57fe9ae6d87fce5c8b480ac2656f3b27fb0d35e8f1f7eded8fcc_long
      << -0x140d829bcbdf20e916c1129bfe88f2ee01699097cb69362959a6c2dc59106d5f6e961302c992c559f493a7179d2c7d4bb09ee9ec924f18cc5eb09a5f6c283581553f2f2303d7092c6acf371a395d73cb0d77bf4aff467c064a898ea62951421bad57b5d922798db1b1a81fbe153e77c8c550d895d6d691e4_long;
  QTest::newRow("242526793862400989664149509983237071960824453937359358711478533593906861507712151423244097633774859252308165728916186380253765699048543 * -24358534321987235529539515212828972607597576208662104332217747919814629242089380805819185488181989708712724738420770420769644163363412076915858438978109261610348460529712112")
      << 0x556b9fc1430a22467251baa4dfce1afdf2d715e5b8d83b9a904f1451b48458aa98e04b952071b6f312ff4339ae21eb4271bc61b19827145f_long
      << -0x19365daa91a8ccc866672d6e8aa2bdfa9628b2f850bd043b0f39e384d541fc47f630d66ef769eae8097969d3d31c8a4d43818edbccb1b0c48709a816e28d7e3ba02e55b8e0287bf0_long
      << -0x869a68e956bb59f3e8f4e5d00fa5990175c1beede9f3a48535b4355513c228a07124ee2bcdabe0aa724862468ae8fefa00e239d85defb0233349a987ef924c6933f95e80e9f0a59463c9f5e76ab2cc2206712ad15bea954589b0d737c28f1f28f21f0ccec5c1b2f605f7d1a901a4461b53546cfadef7cab2b5a11cfba44be10_long;
  QTest::newRow("715118470438288283351767144286664161056044581593923332690268669783377066442616777204049612540799992341802196009438156138672924957567721 * -2586211175918382308034846707376414691912576639099181085548690358495416557519936792672160206737925369660619189713949646968610373785393076387526586893916781783023331350389775234165327851855072289")
      << 0xfbdf3bdde9f0a48347f930f653b83a84cf8431fd041a3ed49f5dd182ec52181da8d22b642db020fbeb3b5caa5dbac7b04cf816fa0fbf6ae9_long
      << -0x911cf66973ae0f3937fc1b0bcf1988f914b78267c5c91d3e9cf1a3e22aff949d23e2b507287e1ed19e42d0f8fb0b8a82cd71dab690ed7c66480127b1f97896ae6973063615a11c637235499bb614cc21_long
      << -0x8ec5efc381ae38ec4d2115cb9ac6110013c8092b7bbb037a27bd10bf31a6429ae415fa21d3368d09590ae806635138b2c0d968dab70032ff5a32bba78b9dde64e3e6b8f15999ba9b93f618b8e76e4904d854f703b87ef7153e979e074385d76005897360adc6b9514f69ee0824a032ff4cdd978a962b97be1ccf4339b27f2b0433a4b7d191127409_long;
  QTest::newRow("373001450807077337011889948455325083055024462780055644792757715470863236857933407538953476626720963040793553082617499445151388941905198 * 9154963864826772436")
      << 0x835ffa0c9c6f577b3e5e15020e5a1c9c31b0fd7ecb845bd283366d2f7111613c1d12ddb0935d917ec52b0c004b7c42f0a047f5f83ab36d2e_long << 0x7f0cf72146897bd4_long
      << 0x4133445ea806c476019f140160dbd4a647393ac728d9f1b8327d0d2de9f10e9df022bb2a65f164fa0c208a702dbcb2ef999c76609a057941704ae492d3a98418_long;
  QTest::newRow("22854351432532801925784327064809322132734990112932800364665337953991046244617681858047172410397805649938198481357830293701287467213431 * 88639409024005102525711218075196706951")
      << 0x80cae58624b25779a9b037e0c5cd26460a1474a9fbdb6a7482227e3977be89a509f5278beb4bc0afd818e5532cccec8fc40db3b69e6e277_long << 0x42af54470e0ee8e05217b9675ac3d087_long
      << 0x218c8445ced155847a43b27b69159ff627b0e0804af1161ca579dd9376c03a90e29f37da7c9f5f29f8ca37945d955f11fb576b6febb61911393ce174057e843860ed5bdc7671cc1_long;
  QTest::newRow("3889284761713478091153762740761365284284871057582462809263987984800351483896275555154690201267130771277516106827805697903918239328114 * 4562449342863816407394538783342805019631181209909569141071")
      << 0x15eae3525d3d3c7af3a56c2294a12e10a7519a0c4ba38f9e35086db92e35cef06ff512ad114920f9c72bf3b851b25fb48e1896b94562772_long
      << 0xba1231985e5ac672c4441ec2f5becf80ff2e332bf402394f_long
      << 0xfee37ecd496ce095304a16f02048268247287e53fb940398ab355926b2530aaf4beb9c41fea5b035afe84430fd61e1ead4c176d3510f31c489151b09690a47f814de5f283117e80a3bf8a4ec428e2e_long;
  QTest::newRow("117445396725270220199218862116221117274430271748045324216226440296078433374749503034840167266347471545844284721317059761415040922417455 * 54746777074422248290727153497559427775831179823890317307604157088170035840162")
      << 0x295d8f17807f34a045bcd12d5811561df6f1760a77d5e7f3e761b46ba06501feec31d72a55f841e2e743a1013e261019784b2bb721fdf92f_long
      << 0x790993e68c2f9703639a5800c0581a9c9b496527f36eed74b42b8385543704a2_long
      << 0x138ec4d21d6f8d13f347d396292a7384a570f67042511d9da868b5c53e5a736c90ab768e23edf232f6ccd0479a5bec5dc36066784c4e2c5c9bae428651d17230a0b74e19cd3483ab63bcbda405553a314e1aac2a6fb56bbe_long;
  QTest::newRow("584536901201146192084272708977632614869772528574079973624839217551828011491743315428187326109323925916996914629788525736181098610690577 * 1900823246119297447739934786133396621679054538092516785550360744679262475748827841070927923777497")
      << 0xcde13dc6764759a8d4a2d57980670a5dace8b668f526882e9b3de27dc2dd2f929d0be4482e575d26e2bdf60817766347d33a79187aa00a11_long
      << 0xe3d0be5ca7dd4d6844cf3918527a475c9c76be3c01015ede5913d3ca03d45bd6af794c30a85a0fd9_long
      << 0xb73699e0dbecc69469d19ad2e20aa4384b31d35d5d8ad299c0530b60137e396dff763e54ec4a23e148b0c1013763f46cb9ed04e0bc2b4efc3717dd5c391df31c6be351f71055a15dbf7561beb9a8bd44f52b05b7bac9ca03fec526fe04398769_long;
  QTest::newRow("54981931704736834120802261374746999806804713620152114481371690434164085668840259754684436599371312393178545940374214036525501359480543 * 38549325280151141516281505727489909020364965111640944777238812420082034656022990222703558432671129822011561550095304")
      << 0x135d7d7fde50203844a7faf8248a6e6702c1c0cdab42718ef641854c7257be747e1edf1203dbf9970bf27971dd4f6b954ee93970bd1e5edf_long
      << 0xfa75c3e3e613cbe57aa0b612903047e7a3d278b177033824681738e1092f9bbd58cbddefcb683e39da0496e5f63923c8_long
      << 0x12f2351aae7106ec8700b5a073dcffb58b2653f5b077359a127147612a7100e26de1bd7d994be77aaeded7b480041cfe25b1228f647f6ff8d0e4d549476c1deebf1ce995756943f64da3cc19748dd06b615f9e1d9fe54735b95bb04c2b40892302221c5750599b38_long;
  QTest::newRow("91718666956328408923380053075543686904009576714556888284983084921349336086899365873461808678897036146200193225119986788152224402810140 * 22946959384241036296390599607429620972813953986297867000814739612994987923294311972603235451499328358962510045656669128246406490867971")
      << 0x204de33a266f79050720c37d666c3efa2be6868c5d2776a2da612161cf97e4b75555d50fe7eb261d9b629eff26c740ff06486d6e50fea51c_long
      << 0x81507f69dc2c0b8265a47bf023f441692e9f47b5356b24663c9fd178f7e1cac515e1299e3f5c7271107ae753ba95033d1232b5045efc903_long
      << 0x105167eb4efeb8d93f16a4df1f2a08fe867067f1e7f58fcfaf9b3a3b54bfc9e5de35e7946996f9d04e73588b3e25757d2b8a05b7148d54773cd845e4a2410c802b53ba3ba6cee5c97fd2c6486b98f9e2c0e8f6f1702bf1bf55cdde04ce5614b29522a36a22eb84d5aba72df93c2eb54_long;
  QTest::newRow("147727461264956577113511596116390697427980563010040750445607477705021213044475340476223457048422866263570770735614471669252821806466033 * 12187568486281767536941112522774223385566204331397150597031393443719336708326386063297556926989055306299981313657958973512389913262609813059054979809002556")
      << 0x3407f73a50f4ab1e7e0402d60b4d9a3396bb5a83357cbf2daa482cff3eeb781d4dd259325db8ac7ec4295d2e5c99e0060ad4fa6dc06fc3f1_long
      << 0xe8b398060b19dd2007ba092d38b5e7bc931a967f65d9ca418dea254fc3267c99a1b8bfec80722abc123aef6701840175a0c201e5063260495a991e9f96efc43c_long
      << 0x2f4bb884ac605aee7d068ebf58964f33aac8bce3e57283202ebfc2f8ec23ffd84c935b1b1df3687e8c6bb2557c9012014be23c9ec2553cc41d6cdaedf86290631dd620bfb18cead2f618abb97ac9d41b39d133acae114e4f4b7ab139b81f8f4cbe28b5209ae17af77dc9227fd8dcfd672848cee4d035707c_long;
  QTest::newRow("450915022218087778955845306789536548794932229543866096179789983739218773310079638110789208901437871959257527148831362102118814798527633 * 227575494287135100280964791553595325755675269504708675959793363691050359092503524802781225330494476772010250225284242325198489601391691669803836104235176725794225582799964550")
      << 0x9ed11de57d6abe98c3034d250c9e1803aa2826013bc5424b01ef435f66a360f85bc6f1f5a4e29aef39e7cf8011418cf20b22e130a9bb3c91_long
      << 0xeb8d79284e3ddadae4bb44d1211ab48c220a575029c20cd0fd2f913c8187114c482a7d94679184b9bb0fc09029d3e9075f17e01b13030b844a5104aa0166fe61380b474fcd85c986_long
      << 0x9221bac8f9df4b9a2d40237bb48713cf727772516924de8d35c8b23f16f4e1536cb4c5413e46405e19b1a1d8d87251e5c01ae04606d8b9644f75a0c1a50e8d8cd3e28c74089689767782785ef753281b52457cbd2a7064d5070a10f61f7e7dbab90ad7aa2178edb8028e28ca5a6dfe41a3a0cf04c3e49736ce131a426ee48ce6_long;
  QTest::newRow("715859537665160085544035525468040639541815847376532340599536616676746925960139755172568972367218679658738868270635612766549955673029754 * 1169136022881370528949642894064814737752708988861039671224957039424120741070063474386625631565739795801950060876443330806362017736574381162798880514760141859553925931197897520428378954417881616")
      << 0xfc220d82f1baff4e6b901cbfa9392fe7c8c20bfb2ddc31fb3220b190ebfb8745b297306e4392d662f37a085f26e44e38dbc6dafde26b7c7a_long
      << 0x4199c0a1eeeb63b9adc80c3d341148f497121a60960e91dc874befe2361907ccd9d03ad22509d41a0a5d83599016eefb5c71e8c21953b8d28ed22da9cc38a5a458801da14bcb4c4ab0b3c7309e14c210_long
      << 0x409c1381597f2645f4307254c53f8c189f3e367d9ca5a4f3080bb23c8dc242400a56a3d3a801c86ea4c7ed729485eb43148004245dbdbb5ff75bf27ce3bfbe1ca83cbf55aff1f1884ea059b2ae967ce68ce65126ae746d2e08717d8e9b9666dae31d305dbf7a9288a3fa4a57d80c50d7bfaec0fb19697569f8b9a3abe919b568272e498ca0943ba0_long;
  QTest::newRow("13147546601524093801764696711435367534933304423924309295305260745895730610545609844994532480708120875313897794300609881052400239488713806919261369562560078 * -7200075971199940000")
      << 0xfb07de7f0c04b442fc14e580fe7396c0651696228bc72e0a9efe1d7bd267f4e11ec1179155cf784cc8be4040425def18a6cfb365fa6ef23561044b85ecfbf64e_long << -0x63ebcef2bb32b5a0_long
      << -0x61fb4632ba50e2f63e4c7599a5db8debb6aba13ba72d8d947db0589aab3ad1b5a56a8c4190a380c8b3752783978f59daceb279a88a959b64a2cdd1128c4d59ce4a54d41f57db16c0_long;
  QTest::newRow("2432320864921853398631844042978072979592981731358163430277724148707706277242817490256761138857177603270602911152702245357962187451800981766291637942722442 * -187262845653570699985379987901882258063")
      << 0x2e70efcdb723bc233d629c61424af714b89379bc8ebd66afb6097b2d4c95aa40277e9d0ead40490d03c0108b7b2160d66213c0afd2cf46b69bcb729e0b219f8a_long << -0x8ce1831efc0fb00e77f381173747528f_long
      << -0x198eac30ada1e4bb32231545f4846622ec879ce09937f4b742249df257a134d9976412cd6fc608edb7f857aa477da96c0fca2de2953181e1b925f9553f72db8c99d4c335b062a46376fcd4d8e2285216_long;
  QTest::newRow("389774501860460219985268507427833890387063533220801767453889031390049577891294983280293009443595355362457710164643964545501375516243274645452712266518679 * -4951828646784248071786713499192796001634603449199241926714")
      << 0x7712d9693cb2798b311f883e6351e204a4f59070b083e3ab2a54fc1377cc51962d25be0a3c55de08080fac7da95f6973d49b9809ec4e4558f63fa9788dd5097_long
      << -0xc9f380db884cec40171a07a210495fc68d13f42f4117183a_long
      << -0x5def0f8788c725337583f65b43f950da183f7f7e55bcc936a7e68b51a2b7139ca29917b090ffb8375ea4bf8afade6cdd48232d365fa5ae0638ac16ee12c12894943fff983367eb659be8f33c013e14f1129303b56436a36_long;
  QTest::newRow("12792899537235564451870217257804529020813652507894667805561062450439048937439104490378824684976031668692548283031610331199912478599208596056417730723930374 * -55071485601199860809793956515150541037405342150806728856489479872729332810796")
      << 0xf44263f04ccd33c0f8486fb2a39fe26fd27901cbf9dace2b008d29bc511c1cb818115161bb37040892a68c2919b396e316e8b5454951cda61709865e0ca56106_long
      << -0x79c15b3331d41da5c3dc2cea2429ead9c292d0f72733d01fe70c27715e4b842c_long
      << -0x742bde4e5ec250bbe8cc7c8f22f9a9911cb3feff9dbfa8fa2d9a149781a8c0082aa2bc53dbebf407c2efa55286329ed3cb05683b126f28aa88141035f7f5e0069338ae9dc9ce9e48b650e93ff15c38e0e38109e2f1c35105822dc2691335c508_long;
  QTest::newRow("7195149082437611042518238257049308568181099088943291525809058589735647561540081484767807053914905613732390055584371460177328000855434370337176112432172860 * -1656226185756155483899432388793198636167004980596561446775949164984498748892870056263992679812756")
      << 0x896127f73e4806ec1807bca1fa46b0332cae4601ced58d113d5f7444d4aa5a18c469072cf51adc8e9ecd966b5150d4670f860ce160e92dd52d726cef590c4f3c_long
      << -0xc6800ea2047a75e56971d6ce8c26876dff1b40908a8faff09c4aed660f4fce9ca464af37f0ab4e94_long
      << -0x6a85dd5777dce56cd726c918f3bc633a01aab7faa8840094aabc0fb3301b08a2a58f657fbb21ea959f4c5de2d3a94262f89f43817632aa3d817137787088ad60308615d5967e06128602b82a6f4bcef663ceba57bb1a091c28b462c18c24561339f2f6e6685616b0_long;
  QTest::newRow("6334198384181945533917084712002478243713816270550391488031024371728693759049372100484387951926246037922594605157660822740807313938032107839116212317075170 * -27385064215403560046953905180417321656460916967939702826657320047091643403104398702892007973412551312855339637282598")
      << 0x78f0eab10a849909e767f11b260d8710360c68b4c939e9a9afb519af82d629a20e481acd352cc0eafe72bf32de760cb3fe8dfda8b861ece9421ebc71ed3a36e2_long
      << -0xb1eca25d516598ffd1f2a2a46ff4c3f876004e5768a71ebf3d516bb3a47bf4dbb043a837611e1df6a956a4bfefe61726_long
      << -0x540e5d114df8e49c2bd35e12226f61aec86c25f61f17202a1cfd977538f82b307d501fcf79900ac7b16893d3300979b0a2ed1e498ebe8bfebd984a7f4bfa9024882da77a8ddd902542566e9eac99c23332b272cb7d259d2372edf5109412705f02398868f14b450b29d66b61be9e738c_long;
  QTest::newRow("6377414073500415840093277411700054645024810652151312903865276741655119412285812794015911041803356604083023093576921158061361793047303927555006166236366048 * -616580240839496228353084166227725338468947293727708167682148995009761809029471456481919251519187540472547091323818036168204354861101193")
      << 0x79c4269134c1742bb03d71cf26fcee13db39349c4225100ae4bf0a7ede097ef94ef343a766e6f1a20a94ece574353570b1d9f23be3fc695cbd0d944a042784e0_long
      << -0xd92a747315bfda647b201fbbd41559d79262f476db21bec9081a6cec000d533fcc1d7ccde5fd7675f5145c16926d2d58d937b52c757b7089_long
      << -0x674b7643087a1abbf6cb73b09014ca91b42523f0a156221ff113cffe87d3be76ecb26d8edbd0fba6b2857834cedc66fdaf1d1459dcf6be3e086e8eab7fd84b1de84ebdd1622d04a9200a2f57d69d44a7282b94a429459aec7149d8cbe6e80f7295275a0af7a01b8438e7c079d70e426b447802a4bae81be0_long;
  QTest::newRow("2826174441200087691544546718020102703962247444099151305758156175776211647309659151833693096967381056527156081297094366528664374448562464010730744024139284 * -11142790106021996622945742165901312493112524499711739179111629488285335158446654600313250136586749008532567743152995014807440109866845912755001212938019439")
      << 0x35f60d8ba476ddcbe2bc6b47f4960dc04254b7ea9efcd51d4c56a403907ed2bca6e63464e43e01a56ef1ffd8e4fe543e7f8c435f340256d25e0ce67ada3c0614_long
      << -0xd4c0d2d0b5de5f1705c38c6f75953612dead78625ee45d2eb6413733c0e60bb74eac2364806de90cc2509f342896a0a33dff7f13475d6e336885270bf288e26f_long
      << -0x2cd86831a24b2e30f6ed4592502c10e55f7ec805d975a5e7bf3869dad2243fdc38affcac6c6cea3baa45f032f928cdb510e8a480999ac9a659d184eb90f67b12f7cfe26e5ece5fa23cd54b001ef620944da462e0077c065aa9f2379b6c8ce2736a61dc26534e6f887b34bf64d0fcf6aff403fc6f484fb5228c86606bc0044aac_long;
  QTest::newRow("2394488379018142774632505868269277240331857131694089282416458437949780518237161962890299511504137240827247057543622618496898835915957108471243164778101963 * -15571046296537015606449272082213761824930445951327394518945428290197065883926346505191088320880763888679344430376066479161981975021732721013728255884378690706234510266846705")
      << 0x2db803f0d6d1b71cedc3fb221eb9e55559c480f5e31b6223c42c8a920818bd2da3d5166241a4be2c9db1ef6025aa263c68f86b3f69b3c75f9f1ef458e4bdfccb_long
      << -0x101dea1cc4879c3a277d72e6afff27374880d709b69dda1222b0dd64e8e539cf7d3cf4e3d984ee94c55c2fdc62f622c31af39aa207d5f7d8eb022aff205eec468ea00be2885bcdf1_long
      << -0x2e0d7e6d6891edbbb12979fa9004a9b1f53c2a8e8ce91544debd660ce7b9bb8e08f0768067962b5575b26d44ef570b55db6b557bdb03b024db84945bc62c7914eb0b97414de0ba1c89ec3bcb356deeeb353227a9d48eaf1c41cd695b05d951f736dc5aee0a6a452cd3c1bb376874fbbb1316cd504e1225378012d0bdc386a075d6358e62e728a1b_long;
  QTest::newRow("7769458122561473855538129994366916353657458214906765563235118085441394943595317919095909797366686929220303794263556046516971053611873547944048233209643341 * -87877639531995971441084856000591484709893585652667888883729665612124569403226330711241082926940334514592671461978213455434019551330659097590099920613640039093828180920524505083880006118771934")
      << 0x945851fa8bcfac211a9be540b918131064e690596ea7c8f7f48a87e0d858fa35ad1966f926c2bbf81c838b96a6199d086b9a87baf140a436567866ccac97c14d_long
      << -0x4ee4bb048a69842a76a09adf57f52b812a642c9a0c1c33eda24a1a25dec6582b0e91965256fe2f7ccf0c3887b6dac25aeaf236b45b9cceb03f6b806a08b427a17892ea5466f255d2e9abe5b6c3b8cde_long
      << -0x2db774027f35d8731a33c68aedf0a039f64aec39361d3783565d4a25c77d62a4cd907b7ae1858f634333d618b669371f526a06952f363a452a5b44a12fdaf6a474da8bbaf6f317c02916554b93626693f0d10129b1f24088d174735752487022b4df7542acbca04a7d7e9647c835c31b1e2302936944ac3726c95d33e6670ae7a76d8338c8cbc5ff857bcc5b20ebcc6_long;
  QTest::newRow("8993919979787333500110978948156774285452248010218874107347038316508417041889486274331566145208361189450785599864369519877287898002167738578149563408981589 * 7894286499390719838")
      << 0xabb95d782764c1369dcc8d901fc84c585985a54fd3e23f65b4d428e02947e7160eb8ac7e7d4e02351e4f17f9562e0ce06ba343395dedac8ef508204494b21e55_long << 0x6d8e23bed758875e_long
      << 0x497d45985d3a9cbd496b55a4dad5776574376dfb23a61b21e0a23d5ba74dc040a1a51e22bf5ead6ed30f04d7497ff5ac70060c1ac16b3978b29ed31145fe728bacf2da62579df636_long;
  QTest::newRow("572958484916442096634658094046540433909612620847719546576390360865665948897544140887064013865612921484784448192653838527006104021688120503630777047767894 * 326083750991056820049638445318643727077")
      << 0xaf0900f80bc03a6cdb2d1527eb7771d7730b2e2b42a479cf3c1ba7fd1167020f97a6df21b851a12bf21c09a0832b8255501f4bcb22e34bd28c421b2b5c2db56_long << 0xf551722fc1335357dbcb23796ce93ae5_long
      << 0xa7bb4dd95ae934049c704dc57478ad0b7933c174d041e8f1763cd9f6e5c7647add64a526907b67c0bba3a335939ca5b818130f56d2567f336b978ba481aac48bfe7506ed29f7cde03b2b292a645afee_long;
  QTest::newRow("5059061142322962765531739947644032393191786701331746954151698854706507891334927990260682786696315323101502580113919201027902942309652837987118517106212228 * 2814610358729466998540670945756695778863999013639191526572")
      << 0x60982cfe7c9f0bc44a67d627c68cf4a4411d7aef3b77e9950a7cf6385aed24079eae5fb803c9b9a2f46d5785dfd84aaf424b88f8043a11ac54ce89d181c77d84_long
      << 0x72c9e73d4e0a6308b257f8e71264db3e332a2c33f523fcac_long
      << 0x2b4ff2c5199d503a4920bcaacc783b64d2977e0f22e363913a6c11dc245a4fcda2234ce848f3fee5594e7d241cdfa86d70900e145bd1c5d81f69d18b9168685066a4b5d67b13af39a0a6fa857c729725ab402f350ea244b0_long;
  QTest::newRow("2380136499580971806472972040706480226527935751779864163691598132173386222041249365939278955911851818718384311562295183772428100549400059994034396933121670 * 113356509616884711996107448722500194244313648048068894040105697705518165124470")
      << 0x2d71dd68019c8bb7be53dd02bbfc0756e8909bd69aff117b7b563e69fe866c7c92a9c7b094d7f2ab1cb2db00106f64e11a3807958a7214d0b3254eb7c6c3e686_long
      << 0xfa9d82c2ea003bcf895e9c3bdb815ed967e653ae0e53dc805426cde52f13e576_long
      << 0x2c7d2842c69e9614fe17a15e55f9688be24c7bdef4972d05308a3ce5844ae599123ca10f0ce313376a2ef58e8483b0fca4b867d2dfdaa565e40c74ad3986b16896a196e67576e7e4db44633eb580958ed5a4a379a3fe35f36478e93d91741fc4_long;
  QTest::newRow("8895655501525320940922381158240359162061172099428760375131448164934457839167251823613353428772231283010042534065232394465187892690991505720065168434182454 * 923542131269425112824029383894037986796726981216407391025939829668327639769853477613159644455144")
      << 0xa9d90ef00739a16c6407715b54bbd5dc5c4094a07c748c1527e613adc77db6c7b9d81020f950464356c3f34cd3a95536492727752a1181dca7c1736db74ab936_long
      << 0x6eaff76d2cf0d766ea1a4a6f1082ad9611de9915d71cd38d87d2468c9575c7193e780664167ce0e8_long
      << 0x497003f535d5bfe66ffaf4051917f67d5d83b13395ee489d8a8920a09702f3f7ca7a5004de5de98307f188df813c699b37e0e3968eaa50f488ad57b49a50231fa9c9b5f1eabe0c2e20330dc30cb8ce624588b97c1ecd845957916b111cd561afe20d6d03d7ef18f0_long;
  QTest::newRow("5875466150020651846880937976991468274777705663273326823859529018096138062805177715825106532155538062953373579401330360609189671111924718248199194556718017 * 20389037808819363617409464788440568851631385800642742934070513567490936910735004980089946332444353436793699274131710")
      << 0x702eae28d824244a8886baf783e03ae7f7ea50fffbdb58aceec04231f3d61eeeb04ff65749653f7eb77ba566b7727f2afd2f22f1eaa29bb1968dd0d1640f5bc1_long
      << 0x8478626aa8a93a64da8506572836cde10df6ac22bd1ec28411f17a5175874e8393db112db120665d73fd4a2c6fc108fe_long
      << 0x3a0cd2cf4e807e015272c29f695dbc0b2001c3f36fe7f8690c439ae4e86969d74cba5e65bb2521757eb2f12b0c924bcd808396abaee4eefb5b59fbdb1033d836859e7be894785e06c6a2c3d2e838e4ad3da2baf310d2407e99eb9e7bf5d2acf1e50b94adf24074c90b61626a9d9c117e_long;
  QTest::newRow("9490703001649625406395357903395700044228016217037511388118044594265451005830468936336404428410652266806078135660807439595519477597975280449379637658852394 * 361500697657866402307066816236268676880981644321608651982099461930468920429965304939079329335062059651833198669001054632611687142140354")
      << 0xb53597068f9d78d14b7f22da5c72c56b10f3f23e148f23b243bc673af4f80ab4b60624b3131caefe55cea1e3a93576a26b501eb801493035b93a953abdb31c2a_long
      << 0x7f5300878ba021b20148cd3978a9515dec9ceb59d06584eadf228436ad44a0c7928a82c496d21434be415d88742109453c75ae16e79629c2_long
      << 0x5a2056ac2a77c5cc99121ee7d84259ef3192603cdb7fc5c27f15be16fc5fe4f6e9b1d4759cbe8363221aa16f4d5892240328d451ee654a26dd49b94ea5444b78a69d17ebfe23400f77b50468fea1cb95a17bcdeb6fdf1c589f3949bdeaf71f4665aa036e98088f90ad3fb4f63741071ff39e3bddd7da11d4_long;
  QTest::newRow("7230796872350088172406916617885634896507157494374878967331963533371613303757233201465474610972247308882562867371173151475109693277247669685309076709183154 * 3719362521507526779571284533803791916635387007678088330754990680589578284756160170261104991760031744351956687197434115926236374358782077280944681979886593")
      << 0x8a0f661d40eb67e05e694641d28148edea02256113a62648544e5884ae7379569a06de1772c1da5756a0d682fea095f6534a99783b5674588d347f9a284e0eb2_long
      << 0x4703dd84aab6ad236a37df3b127fb5a55e168104c13223dc1d04ff6ad02a138d5f3c6a08286b82a8c8146d9565ccf98f7f7a95e1b094677e98bf60c39ec63c01_long
      << 0x264c5af72681b2d3ab2c4619c4519f0ab9be3b941a950b83655a458f2cd4de64fc0d767b631bed85fab3f635b63ad563ba7a6551392a0cc47817bc34f74f153aef90231e2f7f0fc43efd1110f690698d0ddfec67445dd1c378b143952852d009ef0c7cd20bba4055b2aae3dd694123a94143b2273a4518e950fdec13ad6bc6b2_long;
  QTest::newRow("6598590603780267648273974345900882600306945912208943349969137307862617683603355724880732169673971292895568434617068814077091006134873853311050497482325550 * 144273666416404303984204208904739615397247440900001704155149372442649523157579876517738421964545005540353966017829116434640436974825746767957199999175057316489237339553901352")
      << 0x7dfd3d2ffa5e785651cdc39a278195217f51e56428220dbbb2cc51710ca394ddf1d8ce3262c204e0354b7ecce83419673c19b5b1216ee3f651372c1eef787e2e_long
      << 0x9554b27556b54626a6538f530fa173f56ad9ae06989e87be1324502a8aac74d73e2f8a367a681bc944ed985981921ec0506263935a5ff4e9d21ae2e31e00d8b495cc451e0307ab28_long
      << 0x497e1388d46bbf2d7bfde8cfb8f0c299d774d05869b5df3818affbe7423949bbd167afa04a78f9b8b76bcb0221c91ad3b26117515c85d486e22e15e3fd198a50277c130303a6415966e3007c6757cc8badc7f9cfe5b59d7d053e5a810c25f44273179940de5590e59c6587b8777b9386340fb6a52784f442fb99987e66dc04bbf987b3f4e45e7130_long;
  QTest::newRow("8441292173549008299253281994350986227466952858978112190854106427011766355130333260591403655870175240126813672055107856789973008442073899952528068383003332 * 3383189540399161318066656755290808744624404355034605558127021123917914995092015186598028616012707657567324138519371633972483006638089881426809436238676695956380841833086480946065846048897564023")
      << 0xa12c2d39f23b91abe3719a93c40e008d0a38cdd6057ef814a3556607de94f49439fbf1dd90e8c2deac399a6163c8505c411795c0e241f7c7264fe3e30c5ad2c4_long
      << 0xbdd4f3d3519fa00f6f35018c47c94f0df2f04e2a49a1e3ff59f4a961d0ec041a98b9dc00ff916f0cc4e9e626848fb88e747eeef457f63a00b7fa2b7a4fa2139387faf9dccff79d1852f0622b2beefd77_long
      << 0x7783af7b358d55167c232360aa4a77b6f1a9f7b2e889e6c2bd2cb0de97b8869d4aae3c68818617e0c58155f29a32a69141ad2aafb61a96d82e1d491b3cb52611a7931b1202a05743d45ce920e916a93d588bdbb33e926b9f0072b94d1d5d3a424033989f647eb8f7af05e85b7f8d0b2907ff86d35c337c561940e4c31079628eb8f5c3944379dce2fb337e835ebbad1c_long;
  QTest::newRow("18415402997011271662748118308506133346465301090443194717876289719774478704701865375068923608191104225217719205433192247825443158697137887556068004051333120791228975112305010 * -15706758687831277649")
      << 0x130f97f7f1cd1141b02288c77806a7fa8f12ff55a464169b0951fb56d62383b801a8f7a94ad5705fb8db8bdde5d13a06edcd0e738591b4bcf5cc8376dc78bfbbc5dc60544d90b972_long << -0xd9f99dcf00f6c051_long
      << -0x103acdbbf602542b81c33a869c834bd4f992f8c9ac76466b974ce86fb103428ffac49f4a527411791630b6a9febc0cf602accdc46aa206d7408907a304b918f4781b0c2cdc765745ef9f1b19496c2d12_long;
  QTest::newRow("36379834727207475982606165275968842843430059628091192133962961164212219351128786299357784217788318968299264719299671295541004067371901327950645760845394342171585563427509838 * -202825996133618621490166453976607813188")
      << 0x25a7b11b5171666268e47269e4af244c06d66f8968641ec858fc18c3064ab44be5026022c0bae980f9c56b8b6c93887f99fa60a1d2a8beb9ea57553f33bde9eacdd8701fdb86964e_long << -0x9896ddae98dcac94b4ec786424b0ee44_long
      << -0x1671c20570b809c3a2ca66cfed70aace6be7445e329086d9fc293e8f49eb94fb812f377a88af2c8a8063aad09fa85b8203f7f0f262833d63ea4bd22fc42f67c855528cabed81b4a961535ac296f16c81b57086afbd1c70b8_long;
  QTest::newRow("173134316257256621002745175571899850951002333732129193431533440600916230649594180972113777553941044422585222885165821709672425232778643112555387531731000170280946729122568133 * -3441145560275676368315733788303543266737773964157952818287")
      << 0xb3340116d1de070b8a2ee19210bad4483379ecca0160cfea65b45a07a2a6fa7331355dca96c821ea361da6cf8ba45bf04f5b71812c609e406e791d645699b28cb7676609a19097c5_long
      << -0x8c573c6a718ef607c046b9a32f4f95085d55ac995fcd7c6f_long
      << -0x623d818f8cce927eb76f1b000ff6766b12aabea79143e34b71ee8bfbb02b5820e89467247689b8e77aa6a394f6fa1d54350820d6dd15b7f20acfd6c8c0371738c4a010e036c91e893fbc8f318250dfd08b45a3c4ddc2d81f8eb90247baf63a6b_long;
  QTest::newRow("25904131301876469724636074800570748283015790504198324626361709920941774703996988217189900843301450894271544511799370461532807588581121625680318499660413627998696340895922443 * -81085489392023419377176245171786714173760871542064706685921807967171606452130")
      << 0x1acfe87a061cc5766f49b3370c9570ebe83160ff26ee9e24a9f623c281bfe889f61a476214a7804b30800a8d181a79b9f8a9da401ad28bc7a17edf530ef49308fddabab9cba1790b_long
      << -0xb344c2b7d80bbfbfa1a86e28918eb54f751b6a3860a29f2eea9f403008ab97a2_long
      << -0x12c6932be21c0cbd92616c83d43de3102117d52cc3e6ffb4a416b643f1da2373fadcbb19875914fd011d4b89ab76850d280eaa3dfe01b45a37680a10eb000c72605e58baaf9c3462f1dc4deb9d82cfa2154d5de47c726159ca03c1dce7cfdd03f96443634ced15f6_long;
  QTest::newRow("199595314666861451270510711613281388973301535416685896508480512916573543621938905737970467828712388603323677220529350102600586941309856577977248142612967288992106719393220593 * -334733540159850329140217669171987556538708789585645649469182525744162818244249968836950954703296")
      << 0xce9777a6bffcac92b3bc81e5d212a36d19fec7d76e4ba63cbb7eb3985a29dec520e017c056a8241792a983151b0b2a2c48f0aa4692bc8abadd7b8931b7258b32c338a55bdf9607f1_long
      << -0x281e3d2ce5ef12d5d4f059a064a310969c4ff026107fb21efacf30a0fda4804d30f0216c25b179c0_long
      << -0x206011d066a3b39f6e85125a2602b17cd747ba883845e70ed2406dc4cdc2538754aa3619ff7f48789f06e353df775bc6ad381156ba95d6c6f6616dda9696f331f8b85cc9aaffa3a962dfa0d3d6616c77a16f211748bd6541ed3c1a4f2efd103314fcb0a22004ca9f18bc2222ece7ddc0_long;
  QTest::newRow("87077227396677646408535654457037966165689156122474959203317383734277667684231665496602660277544410978211727829415410766271916494302103747608141676279615360672869359007672330 * -11313846259592646949711084748457719994291812697501298137901136444337381183182946867148166398606041440402428093689762")
      << 0x5a21282ea9bbded3fa9b26974503bee12aa5c01ba118795b555940f0f123842769e3e69f8b619cda2b48f6bb67caf59f1245bac242f607c202a2debd05658a5d1b61c8df81e5a80a_long
      << -0x4981ee4d0a38466b21d2017582fdaac77d25d4b0b72b2a45cde2dbb21412d355d37fe20b86253648ab62403158826fa2_long
      << -0x19e1331080d7ada8d789da8a04a635ad3c265c4326fcf989b702607646a6441b25025c45458dc6cce088734a4fdb021190c915e0d92fe237ff9cf33ff0091d870deced6ee5de02c859e6fdbbbc871d9380650da9998b136572fe579b6cfd1e9e3231eea57cc68b483bcaca3316b045b9d8ec990f8c44ac54_long;
  QTest::newRow("93795644484383178791257055179834141929112725222230568100946377251589813598329926445597025604303029298877710108333080383829771273794644838697554112012219303653585990296360642 * -583095599702471048698618660437934793539359166884919866038720367267433551246088381222800782538784777390339890168939999030496334399738961")
      << 0x61155c014282488b1263b50f6eb3e5d3ef8cb93f6c19cd1cfbbf636ebdf37cab261df750c16535d11257e4bc733f18781e62a5027ffef39d8c73d9899628f41796f46938ec0556c2_long
      << -0xcd5f4902ac8064c724085837cc25b006be96494d9fa2bcc8b9a1d3b362b5fdb86c3bbebec3ab28b6b05ac1560af2c496672e59c9eef51451_long
      << -0x4de23d4a418c2120ab8fdc38fb50c4d8bfd118e7074023f9b1204b400513ab23f6bdd45b7f74d729ccd9edb3b118b32a1fe99e55d00d9bffe2108a99a5ec340c77f413db46df5145fec734b441b41ffc548bd53dd7c6f03cfa53aa9ad1cab78e0a9bf378ea9ea26f5877dbf47e81d5ca8a1ea24e858f19464aab25897c219b62_long;
  QTest::newRow("206207744118616500299325777830720614677387013158469734747057063924197590010033118358214301363896335338267122067737071029393484571539473572391781749380621758840940238366399579 * -11406823713318425300360140137919245616948351218602973693697253359314191593245499596424478392676864491514174361093128855372196696936871138222763294953807724")
      << 0xd56f95fdf6783eb46cccd6630d03634bdfed9eb724d7e032f7b950b3d0562c4291d4cdbd5fe08d5443da08cf3e8f03a3345e194ddbd6f805b8a9c1a1fd81fba0abcc88b8a9615c5b_long
      << -0xd9cb64942fdd16be63dbab81b9ffc22d34b9966e31f6f281f2e9c51ece0c84de2d76256b63a04c3ad3b750889795281f82ef49274a81d197cdd571d66eff9f6c_long
      << -0xb595297b59501a6e8ec2ee679d2bd7cfa24c8ad9dcc37ca85a62252332163c15a1a9f826783eefa6d4b4ebf43621c939d61543e6aafe7419ce7110560a06f923635076213e8d63001c9c92c9f95fb84059a2d5606a06638d4385cfd4522d559f24ac6455bacdae51e6c8f4229c2959ae9950ee97da693439ba8d950520466cbd53cb4bd706147b64_long;
  QTest::newRow("77502022736844176042889569271430652876088402863602161647282860954594409858214403378589041180786668252133070062373986152788487158589724247691891998456339195582402334294137582 * -226264996670263325533851213888934305078561800576473296939637530676004396804428814062357394913015535563290168859529022917438399778907903260373045409125364766569789328735622836")
      << 0x5037fb470a393e4183a4f7dc91907d339d2dfe9175bdead2831b2db933ce0a316080ac13b728cef4df9440e97853b581208ffd6cd69f1da5ba0412fe24f567c51f699126a301daee_long
      << -0xea3239e476145782498c12abb95553ab9eecab8c8696bd9529fd1d4e6534f6bf70da70d381337e9abd8b61e9549569f19552023cd2f61defb2258a96515010bd95622e1d15d056b4_long
      << -0x4962e8c211071c401f1a5247212c8448ac451e3dce94194ba800fa9608397adbd9e5e084ada0c203262fb3d619ae37320a2b597e9be17af46b9e5f4e8934bae1d46a183c847282e843a6634a34168adcc8195b5d73445a3bef1750004a4d6bcbb6bcbd117cda7de92fbbf8e68436e4dd02a99c89151f65cc15123bec9ee40544311f36e6ac48bd58c969335aa439e358_long;
  QTest::newRow("165761420413219412739325037197409567252668680290624504285383724006212488020937251299764547817565399150161846624112422569581035520118451047476694946522852206271336362890589361 * -272610769960315306986899830452524394061788485432443748207588202813530390312999293291345558180921075464523109666317375313290393773757702263210849380469152283524064212477370553166194853401939078")
      << 0xab9261de7d1d95062da0bf83345d7a0a508c9c5c9c9cb99fc5e304fbe32e25ba3b45b017e58168b1d5df53fb77395df96861e3dd138cdbd4516876fe2884548e475002c2bdb574b1_long
      << -0xf4bd8d534d5ecc169b7ea80e9335fc9b0774aa156835f6dfc60b9c085989a789e50570fd4e4ea0ea0b6428f6ccc7a38dd27fc77acda0c03bee961c4f1ed564b69904879a7ac5cd6352f865427c94c86_long
      << -0xa4068f11c4ba66e46cd4adca63d109188e386e811e923454ed28c226dcd4b3d10da28644d63c29a8d06e4eca53fd31a43dbb0adda98cd082518201e7fa2e76b7007c457a83b25edd8fa3710294e38a8dafd10328e79d413ca267880cfec018c9541148de3a3088a0dc9b17061a0ee9c8fc7bb07e04dce39216a5b130b4fdb939bf1e960bd00a12a82eba5c953371285369eca94c198a0a6_long;
  QTest::newRow("124818290151676660178352257494551499062585472866363903529682842422155181298330209640082977898200458129530084132315822214703894096022007481528355334900280775778508978335770211 * 1348318375068470736")
      << 0x813189c2c4d010733f2402367ebbc1284b914177733decea4ba2e37f056b77a639a122453c9ed555cc0a49a9b63d53fe7275fad25d77ce6dee49f2b73c6624dec3d541fd36e3e663_long << 0x12b6306b1e168dd0_long
      << 0x9716d56fb06d65afd596838f988ee5f0aa9eebb7744b1bbb60a52856139709ac5c756b1e3842ce37394d6e7a36ad037f132a8b3f4d7347434ba3b277458577bf156b05329c7944457a55cee8591b770_long;
  QTest::newRow("43556245256870086473373644565987459226644226044702500411737876143985607679722860126534118132325769801762995883923379564174026400658348165416958866250408824559329669059365885 * 45744615224557945154547390214406873052")
      << 0x2d154018aeda0e5f53c04f1bed6b8d8e8405f6454c96b5b72fd3d7c8b39255053f05bcea9d8c3e5a7aa003a77f6dae6159bc3da9b66981d379923852711abf57a4777d3fff7ecbfd_long << 0x226a17a93354658dfec846ef7f071fdc_long
      << 0x60f817a8644fcd3f8a17b45a065fbf8736061c58beb82cdb04de4b70b863c400704bebb4a3feedfa73e8dc36c48f89badeff0d38a64c32535fadf07266a9589ad871ab00a55de26abb41dedccc6d60c9229e5cd0295f06c_long;
  QTest::newRow("22543391634429619341733756278404949038719667765614160082273736721796272930864449411005821914217478759733886763042234875247490099379797615259616557936341251584432613047458004 * 877071106009965406888580224022548256173372824992958883976")
      << 0x175566b44cfe88d51c84dc2f4650a9fa11d2da52bedd23ac1df498d423059241a0fed1f4f36e0481c1d4cfeb06b25ae5844f7ac8791d8777d8e93c22181c781c97f7a5259204d8d4_long
      << 0x23c50cb34c6dde17e9c9f446147f5bbbb9caebaa6747a888_long
      << 0x342a2eb07c4ae5ab1f4d773c5b2544e0fb60a1f65fe61c8290f01a1217db64e7f3bf396615f3420c310169745e029688b64c9aa478c1585a703c8a55a072939cc6736b7b4344c0d267d8ef0544f6f3eeb29810f8806fb69e0a66f262faa50a0_long;
  QTest::newRow("133779486427319244312237395175133769755851508068958152360028779548595703660744066835108563858437385988676099410458342325886838761044603771300665276526044954110410740118819168 * 80442144613959263030491716160281148825247198418101907004237804325649142639554")
      << 0x8a780480ebe35686e89496c699951ad54829575f30e8f1c7c501ed77f019b7fd8128dc4fab71fb1084c9e56dc08aa36990bd3aa2e6da2e28ab58a195f04944086a6c9d4eec539160_long
      << 0xb1d8a3efc40e90b40f706a96632b4b404f1785d51d77f61c8788986d7df5ebc2_long
      << 0x6032290d0ad5457a1ce52218987f79278189d1d358e3b0b2c48ea1f77898c94de27ac0d42bd6c7432e5c518b9fd2180cde7ec2886c6e971b0a841964f2291052d1080c3e60eb64908d65d0de240a1d153bf43530966d5e7443afcde229a7c64f89898895cea74ac0_long;
  QTest::newRow("220982871672027998408357018928354776531886126344871126482333120485300613283104550560653968197032985593281365694826416534788201636079849371290539183307526100677484513973454305 * 912853981278132727954276071066659897262714806026452825817291160657236491974642841828278881725472")
      << 0xe4ba9a60cead369d9eb4a0a85a15bd53172d52117e26f19452f5100e68f8a7e8a8f72330d19435d5f7877ecde30abb98c6bd8a65a4f3ce3deb1c03cd44f0e6d3ed6e0c0aef0745e1_long
      << 0x6d6808d2a46f914691c05ec013fc75faadd9c6b22a784466ce68f2802219f4837e8ffdc2bd27ac20_long
      << 0x61c0676bf8249a19f3784db7cf6a817c574a0c8def3d55ecbb727338ef3480fdfb57e7dddf75d4b6f7f2ab8f947fb817976f0f2d81dc346e741a30006c5ac64db5f4fa0898de9fff4896b1b09537cca334eb94009994dc827b03f4a46b448afec0da6ea6d91fe6c6a03cf42b8622e820_long;
  QTest::newRow("14556747861627256983867560654931858385985928749110328501450085630121977662953206787219667535033841172335677870860708921925296840406875791712542573747310201884732094294055515 * 6479763053219076466603171312923649218599422889655475064210000274809753973587703039417528550458263799373075591805714")
      << 0xf1126fd62f5d9d1d942ee6a71f786621c0fdfec3455bc83248a4de16b5f0a2f73266c87b2cc09d4ed714bf2c07e9148617858e198dc7be3235a40ebf9132d0b4146b93c900cda5b_long
      << 0x2a199115d8ae622e1f314fb0a3b5f59b803846aef1420056a89237f30ae679f947206b4b8d22f4eeb6c60dd39da53b12_long
      << 0x27a519c613973eaa53e9beb52128b9ec48889a7d84762a56d984703c4d3b376046108d493ff6046120d4564b4725245bd43701ea9b3ffb1decbdfb256392b3d1933fe15fb642c7734729a469d296a55c1969964b9c04aa8f1f63473e7e9b7e264964286fbbebdd41d73dd32e11f3f08621b4da8a2e15366_long;
  QTest::newRow("77833709308324232784000549668849301408945307829448808006989877328280768943297192750953662559699079547027276536699309861696013348837824068865154715279405083624072106069264717 * 71102823437099917261250522566789657596245832198914008055276149076971958666986444357401432229078573633015507110471868900923791929477357")
      << 0x508fdea4c3e95f81dc726f059f4bd0b2a73447c78c07fe9fdee8a26fa7c93e56c3d3d7ee4905c8a032774eba275f15ea18d363f0ae009b6fa255f9ad123ad1f5e30129998c09094d_long
      << 0x190b0b1f03832ce9921de3c1e1e79625a581989200f4a46d608089768670d4402dae6addc714a47f639a85f0bc803f45e60c5298e91788ed_long
      << 0x7e1866c994e3716a146321485a7e5b386642b9c8c962e83e4537f4e965c57acd83b8497ce778842076040b5694f3ce809fc4b4e226d1c67ad8ccd556444bf9096ac6dbe56775e76cd378e33a3dbd3ec37db6280728354c55a02c7120b6192db356fab2df2937544c28d23adb64954c1b7d0bfd001f27ac1eb61138a5c398449_long;
  QTest::newRow("170928344788414003016197906908161702143960734420979375741776515353097615807817420764253393257291494760306752441630778186924974931968175259836366594682587815371037715850731295 * 6271961057795255310429767468048998568169974327514975153241815027501517687433619108479920115956277746521095563463518527532604335105225259917719446635258646")
      << 0xb0eb7af472e606c453a22941bd4c6b11b12ac926eb5897aae82fd86db92ccc82e0082be4e908fe1b3050b4b65f17689c5a567b453b8f787fca9a2bef2fd3ae566e164a1e4dca1f1f_long
      << 0x77c0b501318118409a8accc7e946e1b70c500940bb46130fae5ee742cda886c7e3d9a247a8e547846f830739910c3cb7f1fd144ca85e62b0576d0f3619f5a316_long
      << 0x52c2a3db29cfb3cfe42d1a36e55169a6b90f65217cc3aa9c526836af763cbd0e7cf843320cbce3686f6a83b43a18a17899c4caa358ddb9a3374915d301ce915e0dfbceb499bd7d85dcca39b916f07f1b29743c3016b5f3e9e3e29591411498ae06f85aa30248eb75b33f4d27d3e85035d7a0c731e1664b2037d4396f304d07fd955d3b2630da69aa_long;
  QTest::newRow("17616474376832602824432621270381637928515162481318349920433295034689835245479723306444929012270242034216640526742971478660912519159310874387086149682920910189814999915286703 * 183689454977684003450737823707796559349992532985276160452411606608895377811123892945359953167459569442572158847553218212008162618380620548167832384219133651678399392287461992")
      << 0x123be612985e6295c65005b2cf7633dfafc9d6bc50da2ff7600463c10b43a1fba9c6aa4e3883cf8c06183c31ad92eaaf0f4e4cbb5d6eaae18cf9fcaaf0e43d2c24ac36632175d0af_long
      << 0xbe20d6120f95ad316ae5d9db12d21d14fae4d92df3b1836804d1f7fe3269ecaabfce91d2f43db71bb0f3fbe0e6c4e3954fc1b36bedb8525875c7cf96f9813f992227ff09388e9268_long
      << 0xd8acb7deb0efd5318434e243f86df909a7b57474f2c518adff6806cd97622bb74314baf674d7da1a6c8d13db7128d605fbc730292f0f68174b2918b40febfc40217870d1d6a8bc9babc49880ae3c6da5cad099ab224d036b85fb6e9f7370d96040b703727082d272bff154c384c6972d2d212eac03ef1c60c5dc92dd29a2e29945665b742d83a5687f49d81d1f29518_long;
  QTest::newRow("33014956382963640554850194959651207088725059408914745636979763987251147939369108177188370158180232732812768103591992890521456254183988350087660904477297982303098243612330361 * 4279668486913543772648711126631549273430345726559826255760194093427507592975196227782459586745548369622142611753308028204416409234954520753437756089806678994897694629180947703028674055332265713")
      << 0x222c1698383386e5656632bb4e771adcb0f80897fe8c6964db86ca250e6195c89565d87d43f379f518dfe4be75121907e7762b974a0b6b4cc1095273e4f144701bfa49fdc4c6c979_long
      << 0xf02231585ac670d4eabf98e9309a0e4fe8877f0f242893714a21b49e4cb3420e4039832484c108778b9090a82d30477d9957f762e199c426e8d750a2971d97ae4b47d8bd0a5789490d05b824b3d57ef1_long
      << 0x200de59ff080a97edb4852471f029af24a66e36080be483fc1250709eaa50905da3785af744fe5693726cccf19365774b885c60d776ee22bd647d6b719b5dd15dc6ff7c4d536baaab55231240507e232802da8067e043d88b8081268efc83b1a4b2740116dc68c7dd745fb5c9305a60c5e1d667659a4ae80b000e494620190e1f29a627b8c613362e5cdb054759bd60828e6940952fa38e9_long;
  QTest::newRow("3583158458506445274471764394419126032572293761645816429434683580542486940039034457690990820193269318422989871814318896587068398433518609993814529401266569036846241275724630555300527418011691663 * -14448637537923194548")
      << 0xc90d5ab5109c6fb3720294204343b1f5ad43b0fd6273bd092ecd9b70b3f33790644e5b3ca1c814a2547032e902951a45b2bb244e31928e9ba47362c6f39a957afeaf6247e4aac6576f51bb50bb662a8f_long << -0xc883df49e0495eb4_long
      << -0x9d7a000f86999cf8ecab6748bfc3d8d8baa9b64cc3a8f774a9eb50c2b3a7230ac33ef937ef982f412b81c52d0c06aa337bfd6cfbb17b1ca787ba279ae7c22cf8f37d57ab268f6f0a2d2bacd36a6f465a449fe2b98a3d6e8c_long;
  QTest::newRow("1179132971590094854677463985378052150077672941423074383482377289096801201208252171544608196671393668817665308673091868516362223139152539040573731222805514389680470412863976124019581778435994180 * -158230481349324595288628960891078344156")
      << 0x422959deff46c4014d4c82edf29f17d7a6ec6a45a2958de1f17875e9b16f959bb9c31b16f60c9b585262fa73ecf31721f575839f2085f8ee66aceec3b5b30623410ef847f7801a5dc6727cf4892f7244_long << -0x770a150c0336bd5dc2581d6024b67ddc_long
      << -0x1ec3d3d4aa8400fc5d01f2dd6147c688fb8b42c3556f3a3ad49d2672a17cdddf1b5de149e15e85ead7f85388da15af6e59c0430d99083c152f1ac76a10ed44c1572ece5ca92b6489d2090a5d41249a8989ff52d29896044c4ba78a6edbe96670_long;
  QTest::newRow("3891720650544694393406069827366371544056848715378347630420892756832712580731600736639965984642106986444647905040565706802828732762483609070525389574230083339100019839571951501138918232403099957 * -2704163782049262111407613914268490280816678637983387020771")
      << 0xda5d9dc255e0b9b1a6b83bfbfe12f935f6419b8d0d55c5b0d97af1534d528d32d62ac1ff4bfeff57f86cd6e89753abe6c9cabe0cdcecaf50d808dc571bf5478a3a8fe6430a2853b936257ca7454a4135_long
      << -0x6e48c986e78d7353c5f7534bbca680a1c2eab68b129eede3_long
      << -0x5e12500472f0016eb7a4452d2838bbae192adc23e35f715cbfbe98db7c3b43889b86f8b5795175411b00461e00b500d12ce7a4ee6ed3427dd4ca54362e631fe137611bfcd97d0e73e0960162f761027def00e3e08ab7cb9995e428d1b26f79f697df75a927ebe2ff_long;
  QTest::newRow("3413840239707008783609122606414647215815728146677793995535115548893397569177343997972547700676849146066898327835801357181479961697031471638402377142321512487064839611771344454368045339571535313 * -50233773958593953488393194977225978453144953732062314613766317017032673706528")
      << 0xbf8d39fbc3c04fe0f126aa3401867814348438ed2b6748b9bbddb50acbd40da1f887ae38f59cc8fc46c227617713382856841d3962a5afaf7b589359dbab2ce8914d3a9b776c658190220d78abbe3dd1_long
      << -0x6f0f4ef9650365960b3ed60e816897adf5d9bf5bd11ff28b32d4db6d609bc220_long
      << -0x5319b082333e38f8345aaeb5e28f2609aeff5a0a8382be8f7e58434a6de27c9f3a6d6dfbc1a588b2de6bd09cc76b607af85a5bace6854cb92407ea52ad08dd092c37653901901ff25a1db1ff5b406d9618d0466ae54c41c675b375460aba2d476b5e91988b81647d1ce49196702b1c20_long;
  QTest::newRow("4137222914602220587628241980270244681733262818116742174605675534474254050225594665349456805075339666335965473439702672909447725155837734623982524820642296190876309812877343658641418492857447227 * -338301645943360214296709670755201179481343053055453170851820439542412287216637465498623028274357")
      << 0xe82411f339dfdbeeffe8dd51a46a1f751aea958f6369e897dfe2c05ca13b96a7b73e731d7f74490b48e6c851162759eddcc4dfc3e8573f5348315cf0168ed1aaf494f0b31ea268c18ca40bb1bf8a733b_long
      << -0x288bb709fe86e8bdf74c96a1b7bb274d55b02843c79c15ef739e235f7fd162a14d1d8bc9bedca4b5_long
      << -0x24c4545e990306937dba3f6305de6e23e5354d0b89730f286a1eab6ad46f984e7272b525b0905436934f158a7cac4f50fbbfa8cbaaba0179eec66bc559bce208a73fa6b5264ef7b213d42bbba646113fa39f954145b2000813a26d53606e3a8f29026d607ac9b31c0f1fb23877e6c39bdd580234ef6944b7_long;
  QTest::newRow("953022907752379874215339668652687913570995744396072859347501927125267488593720401838130270143926263169696913401376242452033457146186861335574866797216183032954990582151183681098302955362465605 * -35631559595635299085040470303316775758510227020352569997377635301692083328515579512331225178311495950628022220014140")
      << 0x35797391910eafaceb3f4e508bbd56641e4e283462021e932a0d3e19bbe34545a1002fd466fdfb0e4a27ab719383c49ecc31db35ea8750c19bd1c6c751c810dcf19bfe2c5d954b0114656fa7b3243745_long
      << -0xe780befac0fc2558053c4c24d67b711e39c563ed0890f0058dd8ca2b044b7a86415dd0d6372a008ae72d593b02b0c23c_long
      << -0x305b7be6a75d6fb54e172ea0d78b787c7c72ed4391a429a1b69bc06a7da6e863628094da0898f10c69fcecc855947dd374edaa63da55f6ec95ec4948890344c81e7c8301380e6f14cf84ee15f9f7f3a14a1c2adf9aa1e83f44ac47bdebf9ff99fcbe4b72ad7c5e4e9f3bad789e7c210cad6a195c04e535ae93c56c4af7cf3e2c_long;
  QTest::newRow("1891883154575427358034372005292282167771814119851657696631586829710858839583014103607892591423355587983829623558899582494489851602181645985303089073848044265839627473439951954615657724332483213 * -136037352761118002715890503561827881270374865181251627968409454135152030020524043272024536906144170909532148196808972914053801369769406")
      << 0x6a27778cf27bb7fa34d23be13795e2d5bafad9dd5ded0136a9f2b3ee3861f2031d1f3a431b0218e9514f650683f470a29b0ba55d1927df7de817f3fe5427a98984f0458e8d8a8ec9ace179148818228d_long
      << -0x2fe9eaec5425041b37e8bdf098d49827d5fdf6816e837d8c90bc324a5016d47c4409424b22650e4f3313ac4c9963b1d38b0f70d184ed95be_long
      << -0x13de3e48c25ac19870cb6c656f9d294f259c4fc16f5aacf3f1d1b72bebce00dd08d84391981f822c243b708585a533533493991391a9e1f0c560476209b37f69d23f595409caa094f95ec8332c17ff59903eace2abf4365614f6ed4f0364a08d8880bf1809a74d698cb249cadad9606580113d834fe645bb34b7792e643f8b2a791425b8be8eb5a6_long;
  QTest::newRow("781897765999308842949247206079058516727436640460449061517364885907539157127865605699515171635198085145626891827251518027190237939547589717629351394309202079105246171283146307379427654360188359 * -1056893262720074985184633235097416735354457406221466666661076831570854104075747312387559900905346336295429666811823846222002105195213613254725270945419494")
      << 0x2bdf5e5844214d0ba68baf263b25d789ed891643ccb81e86ca89a9a8c2828ac58a8bd0751f173d0b7fc38908ab8cdfb936cf465871f69939e6b2fd2572300481e78408e052b72228304f283f234545c7_long
      << -0x142dfc958d81ee485dd819c42f41b176f0548c32974869e5eb0336756b00f02dda0673eb6e63592e8736ef94575d4f89354a234a6ad717b3c35cd1f8229850e6_long
      << -0x37554ebfcf7abab1be6f27fad33fdb3fe9c5b4b49e88a653b09892caa4e149906131a7b7c8226e0dfc01da3e91df113bb92d09dbd7991beff057a77a9a2285f1bacbf1141c6470f3b2fd6bd60ae4b08b4e403524020ce93b5b79c0521f283c9d173ea1d558a315737d24aa612285cd979162e4b51b9f4002d6963c3ffe9ffeeb9cb900c076b16b2cd7517ed3232e0ca_long;
  QTest::newRow("2995242509637890560196820384117173464483264363647893126009451101843043456957255347815744477763417757314054875976619210405799350058001486534982540691242397509474593950495938684690657503385529322 * -48023387921792427890119015868457913605909369562480774071314244442491992032633052314116543968129380204592567415916363478497337706138696556570254388080474927886644510652451583")
      << 0xa8106333adb26a02628fb2d0ebaa8dd0829a4f3fae04c79009679688be2a452679c59ba763ed32c497ede2af8cabee3574c1c9e0ae492f6da36fce25456ab4da91aad5fcfec9367dc4ea314d8330abea_long
      << -0x31b4ecbd6629044f94297a33b33f61ff1ad5e66772c6550f8cee728ab514b1c2831b5635bd15421495028ce4437c7fdaa778b40f2a5c19ec25971d39c2d1de4cadc64766e2d94aff_long
      << -0x20a1e9ee17339dffaf594c8fca382dc399e1871c1afd27c5c246b8f6c951ac9c897c0eca82d683d81d64c125fe43e45fa191f112bde61e6b1de7f96678e32997b06063440dd0c1de09cb8459335ce872c58b6d42ec54b653d1991a2c02b455e53cac0eff04c5be4b079915d9c71db366ef6c76d5322608b38a0e665e82a88f193c087e6597c312832959ac63eec9c1cbee1b15640c86e216_long;
  QTest::newRow("1507091017140130706225739568540294168700420241403232948665645596198944564503957879951679930295748072688114102097010489310866377307927855181457879291827378697683419808044668311728994016304908372 * -313910335041928582423409164625027738612692330996951504484545719881416685436656351816496050921594963909849859549287132111057926935430231811700598502789524497931764238387727192986553050984284693")
      << 0x5490383ed86945c2fba40bd7040889a86c23e9f46419fd2d4824d1a7acd8d49f6214daa31d1325649c08af52b1bc6688308476d81d8e0848458f9428641cba4b159207e47ea087313598c77bf9394854_long
      << -0x119d157d1bdd545f185d990ce3fd4b40e983ddba5e77c9ffcc1269ec0172c4d822bd3f2458bc79c81c901b6847a888df988f2cae51e21a1e759ba3ae0f930a5f5c9270e27ba423524c35e4cdb25f0215_long
      << -0x5d17747d326a6eff484230848d519d213772e287be922cf989f2ecae788dca2a24cc6198ea4a13e8c0d9b5c35ef70c419c434b09433f04d2f9209d03671d02cff403d0b122bbe4d2773d3de15f5868c81238ea47e816cec43e19e0334fac0305aedc65ffd2d980eaad6f9ef900ca944df9141286485289e6452b8cc1d769f8e07495fd07086f26dbecad02cfd7411409d6d35af79770155521060ee236f96e4_long;
  QTest::newRow("3934066297758363616737394135153023022929320558867563933353970754357238180914261664716464761570459103594433263834281282202877116995162309800701658810455332349292687726660655725239715560305595267 * 13053289556030929689")
      << 0xdcbde11dbff6be272bdf90162389dc6770c48bc9e10fc7bdaf44a00914b4b203f2d34ae4da2b14dc3337bd5d67f524f833ea6c1f2b6895268939b4c797278f47c86b96f939079f044f377f4ca0ba1383_long << 0xb52699b1218a3b19_long
      << 0x9c3388dfaae30bb39e49970827caaade26af04014f165bb77d9c8a131c8074e0e5bf0d2f3b2cd4aaa889418fbd66170154fa02dfa8f7c9fb4d66f2b1077d8b500db8053fdc59a19e83f46ca79d649c75e18b80ebfc4918cb_long;
  QTest::newRow("3970421604148701432512259102570683272667994747551882609217685943517674845091116390925773714395704033616266078461648013609102797190781593127313875408148081397775731615994237285110454723116138215 * 84918293383831895365201785302671154073")
      << 0xdec8188463295a29330ad348eb5cea7301ea986f89521535ce076bfe11c8d18b7f4f9ceb5afae7142ea87b53a6f404f711b2e87d35f7e7023787f1a1c41bd4b6805eb3288229a635609346a3f58dfee7_long << 0x3fe2ab1c9e13c8d23383ee48d88fdb99_long
      << 0x37987f96c91a8b27fad5339464900ee67f461d8fce71a61f97c71bc7ecc2a71ea1ddcd9bf031a2b3f266817a8ad7eb4cac5b95af9a60a375de07fac973edae32b72509009534c9b9b1ca30a1f4c3e4964e8dcac30d1004ba0a58e76a85f5f50f_long;
  QTest::newRow("1335849703560780345325026208232618090070386691685065786626612360012631517980564366304648746015246487234684131415148969117178749562862174825847917373952511889035755285671188403955199419649330560 * 3140740250697250543873613707955437698167332911454896344712")
      << 0x4af477d44c4ad77f520e3decba61b9194d51d62653235f730dda65b9b106779c2c01d4e03bad6d1c956cf4c7fa2399ebf92d3eb4254d96b21ad03e0585ad7748ef745fdf566f4b7624dad1dfb8c78d80_long
      << 0x8016dbb4a426575df3b76c3dcc2e18f366d42ab1923d4e88_long
      << 0x2580ed4078daaf5a3a39524fac2dcb503fa354eb9d2d3169cdbf89572396d673e6fe4d7589dd2f8271da4a523a2c8e177aa03e61f603a688422486afa795534195489ee0ad9125fc8fbef581b5ba3b386968173889ec5fd4d2f970e70a9751f5871254e6aea02c00_long;
  QTest::newRow("3689730045768550805915775421100857689726282654001256200295223674444931913576862416203362941117248550129746873551350647523704539165256122096131464076087458012492506863551674841449890949621365121 * 63244798610675111813204927116149173315444455301918842953085034678696884055746")
      << 0xcf082ca36875df652a3a79b7e267371e0ef153181efc9e62a48fbe65125de89e253b99e731b5ced4d47665cd48c7a2ba18e8b7f1de2944025e62b8983c7624f563d35ebf37a1bf7bb2dad756879c3981_long
      << 0x8bd349980e99c8fe7c44802fb51f8a2e315fed88f55e3039a2a9b1c660e02ec2_long
      << 0x71144f7dd1cb04227fdb3b425e7880c2270d67e7947d1689eb3e39532b8324ec7a5004fa2936fd7ad23d047bc5ee641039b6048a63bc64fefa96b37f3f64f6090e35550ef27f631562ee9959a32112280f8976085b753a1ed20a4f0f8fa1d3e13a7a20eec54ea70c39d9a4f98798c1c2_long;
  QTest::newRow("1764931200456676244177213776438802129079920370526523167057915935817540851755090288913096929935668245659150386254790757259655941660180190409167918425718313367148089146749506415938756693080183894 * 1387099486771939949973760301020022969660886834883107420508199190173365245356190837333134191073593")
      << 0x6307e5ffd40ade47884cf24e81bc03b958f1c89df218e9004852e2c1f8eb6eff7faf0426d4f1f191738997656d2086526df6271baec7b75064d69268f337ba6eff3e2994fd75e5f7d3edb93815ec9456_long
      << 0xa63ec1a45802bf07b6a3e944a0b48e5a48e55ef2fb9d9d9a69978a0c30be65c34ce998f785d79939_long
      << 0x404f65f61ef56489dd9aced035e62bdb7a84860c53da39f1ca4ff67ce3458ce0f55d23b6f6224bb7e5a90e38b5ae876bbcc34ce8c645db48a087757ff04805c99e95ee0449f98017186530c01eea5b1e47faef2689af420870e0d3fc84c199f06106ac1f9779730345f2123fe662edb81ebb4452888e6d26_long;
  QTest::newRow("3332854969412445248307608532926874068167328096218464424324656727322988910230487970690032130996523944500271031603672707960842837339615251147038290538056624346866693708502775729302849304455370430 * 22881381194129778075759170874720779178865873410847094004996422597838938446935987904891890524139113034365114796250008")
      << 0xbb01ef3b3564469dcc44e95647a181b2329efda8b089e6814bbef18b6b24f84566cd9bb1d3d4c904e72f0c644a764bce5f1dc15a1335e101f6810b019b156840bd4c1fd33c1fced695e7c071b4ad56be_long
      << 0x94a9d03889c5a1a5039ddcae694be41cbbcee7891431690b76f4f9b214705cdd8e2a249b7a6a2171538b92916c1c9398_long
      << 0x6c992ab008650ff38a0dddc556944385f83a9cac82785d33fa303eee073a9f977bf07c0725ab0bdba96ac53fcbf99208e7974ff382f72ff35760dee0c64e85e81fcdf6e398c51240e0f37e9d0cfcd2cb81ff7ef835fd6971ae256f1a7ac62fecb78ee722d12875eb4b3f78ed182849b315a583941c122093fe94ef6e74829ad0_long;
  QTest::newRow("4152594950072099483537554492481907924778326943240600799772882750346680293741253086778932609367208215662028072094781025557380953189732428990303302759114652481122331521992842871150394474495658860 * 716491644383846523593818489279920940474459260138511187260251292735038733087149264251302280136926421412026446784033954056477908315638804")
      << 0xe900e0b44e7799141058c7e4e309074d5da3012493dbaae3e0d1deb167c911ea3ee6c566221d8a4688742858cadee3afcbeb6570dcc6bb85a696c3db374c99ec1ed9e1a8eee458feb2a1a17fd3facb6c_long
      << 0xfc5b0c14bf65b3567a7e8670550ebab6a4981ad95d194b89960f956f9da73bf27ad8c7f28831231ea94a783dfe534e194f842e66fc178c14_long
      << 0xe5afbb804a23d93067536e60610a14a0fbbc07eb35962056fdd246299d43083dae23a95e442e79bee5fc94690d1b7a4b66a2e2c7d277436e2865a4374899fd8a6bf618a2a091abf62d52e4fa4eb24f946b5be5b99d751a189e7aed8735c06f622a0bd97d0e2539063c77f224f768846b2e6860e0b523bcace248d8ab6a772dbe6e43e6b84d8af470_long;
  QTest::newRow("941973577625392948799315250348320245966494334955008478591267964795980257504965696705976074747847391755263657202891541380546134397412965903412678090144372634923077313486318040092913798611510342 * 7056104848098394569090715793661202181394223468466109223593200449421263347736221729599213231575122979063716823944088658449014757291134512905491753952765674")
      << 0x34dabc7700259572478154e9f321ce23b2cfd08cad3a70474cd254439fda743b92ab6d27b40c7df9e14aab783e799d5970bca96fb57199f16476611cc86d3d7200f9bf78fcf0c0ee164d4232c958a446_long
      << 0x86b985a5798a958fae55f9a7d158423facdb9f012264da5cf5f52bf0a27c0761e36c8770d4db8e8440a0ff91059ac77e7d3d30b3206fe1d07a54d986c02666ea_long
      << 0x1bd0cc504a10130840f7de707f046c4cea8870ae5b7dc5bb66a54bd1ff24cf121aa183b727eb916fad722e7b31227bdef3f8872ab0efeb09e8cad4fef11b790cfb53d068f49bc3beb9b189e0d8f9a8b93f9618d1e7965ceea30338d3f2910e691e7bee2d1007279e652a2e29cdd75c5ce05cf3e1fb6460a6069aff5d6bbe3ad19c27115fe5ed7921e0286fa63ede0bfc_long;
  QTest::newRow("2500247122287542884847739040874599499642691038508068868785661167837747928441602159485188610775551435916751273967489501773864970462057749265963075995080317398806608763441885016724161928613566066 * 79865110333785801164996645968276210474441958309153926254062287580514339849424303374853166100703359667896614131233931002088009666309925683952235291632836935148829357485702997")
      << 0x8c4a2772feb4fb10c005b6552ae411799af7297813aa214c63b07a140ded629934a79014c8cf62605bc369b67bfc153bb0c0f0d5591737249eeba543b530f46ba0d547d0de3c9eeb9c3055cad93f9672_long
      << 0x52aa231a8a06e5170235522687c4e3631b2c238bcc19a873cb2721090a3d1e0e70b080ffd7cdcf28b7347970a2af1f0ee98cf682bb9c1fc18687b25d8567e13082dc872069d1bf55_long
      << 0x2d4cfd1db68397a68e7edf964465a7886fd61b01cc5e8a10f2354dc5ce32e00c44ea63137cfd9869b9778056e8a325e19cbc41f211ad959eadd724f19c1c5dd40b4782dad88d96226d2fcc394586a04f41d36a583a9c88459c32885931a00bd306e2274fe3ce10d9332595273cc897f85686016535936c703afa1dea5d5f2daffec86bb63cd73edb9c0498e3870efac00806324f286e01da_long;
  QTest::newRow("4224898947329457409172774018876636534506157804136124467686236017602764189890406365242965652572591442234163158501266229695400874408334122228233686585051331421910845736819923147111016439474235084 * 35970885247988640953306536459324729855385424749410781459809961530162058434259095105677823548453127648647896273028679950798463927412736822293606067822620388682489523719378124655483503508365950")
      << 0xed0f7847ea26fddbd96b075d0ef8285e6231568a454613f7c265ae65238775abb61547976211b116473170b2474181529a2e4f1df3e55af749cfb49d914d00e1ad8b532bcd3cc712444b8a562b6326cc_long
      << 0x204b1ca347247fda39112876d1667158ac4569745018133e36cff1ea446f102885739e06075d1f7fef41ad46d46e97debc3055d4c180b84996ab5df8fc131ed4d3cc42f0baf22c9469ce7233a6ea27e_long
      << 0x1de77d161e39037bd1ebef9bc9302cf9cac7d96d89abe71f32ed1d3331c5986a8fc3f114b94daa910a82d5e2a345bb681a812457dde31b982b12278dac54942a88c54ce8674bfa60d8bbb3eab32a0d385c1d9b91a23cff09b71e8642bafc38790cf54d24359c4ea5a3ced02638f59d997388378cd0af82efe4c6fd39a18c981f2e55581338ae12387ed13cb0147f30fb471dff40931c62434741b26fd023068_long;
}

void LongIntTest::test_times()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  // cout << left << " * " << right << endl;
  QCOMPARE(left * right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy *= right, result);
  QCOMPARE(copy, result);
}


void LongIntTest::test_pow_data()
{
  QTest::addColumn<LongInt>("left");
  QTest::addColumn<int>("right");
  QTest::addColumn<LongInt>("result");

  QTest::newRow("0 ** 0") << 0x0_long << 0 << 0x1_long;
  QTest::newRow("0 ** 1") << 0x0_long << 1 << 0x0_long;
  QTest::newRow("-1 ** 0") << -0x1_long << 0 << 0x1_long;
  QTest::newRow("1 ** 0") << 0x1_long << 0 << 0x1_long;
  QTest::newRow("-1 ** 1") << -0x1_long << 1 << -0x1_long;
  QTest::newRow("1 ** 1") << 0x1_long << 1 << 0x1_long;
  QTest::newRow("-22 ** 0") << -0x16_long << 0 << 0x1_long;
  QTest::newRow("-1069825435749090175213255482408 ** 0") << -0xd80cadbf8f88318db9c175c28_long << 0 << 0x1_long;
  QTest::newRow("74 ** 0") << 0x4a_long << 0 << 0x1_long;
  QTest::newRow("1089687422572306579751864261725 ** 0") << 0xdc0f84f4826b75309eb625c5d_long << 0 << 0x1_long;
  QTest::newRow("0 ** 21") << 0x0_long << 21 << 0x0_long;
  QTest::newRow("-68 ** 1") << -0x44_long << 1 << -0x44_long;
  QTest::newRow("-1169192405838021796308706008464 ** 1") << -0xec1dd4a5b2826b217e24e1d90_long << 1 << -0xec1dd4a5b2826b217e24e1d90_long;
  QTest::newRow("64 ** 1") << 0x40_long << 1 << 0x40_long;
  QTest::newRow("739467055557528137012575871226 ** 1") << 0x95558cfddd8b83185074620fa_long << 1 << 0x95558cfddd8b83185074620fa_long;
  QTest::newRow("-1 ** 50") << -0x1_long << 50 << 0x1_long;
  QTest::newRow("1 ** 14") << 0x1_long << 14 << 0x1_long;
  QTest::newRow("-5 ** 99") << -0x5_long << 99
      << -0x3a855d450f3e5c89bd4b4275c68ca4ef60ce939d218eef073ce88094fd_long;
  QTest::newRow("-1183928343468741237478660075811 ** 2") << -0xef17a9286cc76b2f644ed7123_long << 2
      << 0xdf4d300950264bf937de2ac5d8aef7b89ad07d1b9944cdeac9_long;
  QTest::newRow("108 ** 68") << 0x6c_long << 68
      << 0xa128f790fd5c6583b6a68a9bfa2f8422f31a7d0f3a9581fbfbdfa241e590e18df1a6ab8b418afe2f10000000000000000000000000000000000_long;
  QTest::newRow("825714437823231976542780914322 ** 39") << 0xa6c06f977079df6cea049fa92_long << 39
      << 0xebb0c2e665af10c87c1f798b669f65abdcda6535ef215d676e345d80fbb1a094d6d20e3b0d6c193ae86cbf945499d4937b79fcb70c24dea6e645af885142f1561ac438e0582a34e30eb7852735960b92de0055b7ca88bf6685063f9ecca8559887091823297fe2526cbab994a016f95dfc5c60c6915a2d2467b6baa346c969109d5c7f2705f0af9278e5e3e205c39cedf751e0500e2f6e3aa8130b91ccc41b654193dc21a4c51972b91bde8b8d60c7bb8a2219db6fd49dee9b15bcfb13e4e2ba85df8347f20c80459c2f2b5ead3d8d2234ccaa303c1387d77364efb1ccfb76eeacdf21f85cb00e8c4ad1082eeb5f18aebb84d8e18d0ddeb46c37dbc6556dbaccbe65c1929f5bab436d48140320faa76e7ef27135854a8324bb79603e09e4c32596af902fc9d8f3adee64979fa9f42660c1c5b70a0defba1b4cce541aeda1d7a068b4cbd2b8538cbca599cd2a8d46c87284a95fe463493a5a879c9769b0418009e01a111021b113fb3d2ba8ed308f31902f374e0ad1f78b88bca8dde70b4653a78e8e9b9fa8ad0453eaf37241b9351b2324f8f87e377a820e19c0b69c4d78e480b3167416e564d7170e92da7f45c7ddb0fe15724f391fcadde1f0788c08f56f20507608be4a9841893538f07782bb1301e391c5e3a167c58e7f998316e11d49c8000000000_long;
}

void LongIntTest::test_pow()
{
  QFETCH(LongInt, left);
  QFETCH(int, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left.pow(right), result);
  QCOMPARE(left, copy);
  QCOMPARE(copy.pow_eq(right), result);
  QCOMPARE(copy, result);
}



