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
  QTest::newRow("LongInt(-1)") << qlonglong(-0x1) << -0x1_long;
  QTest::newRow("LongInt(4)") << qlonglong(0x4) << 0x4_long;
  QTest::newRow("LongInt(-76)") << qlonglong(-0x4c) << -0x4c_long;
  QTest::newRow("LongInt(9)") << qlonglong(0x9) << 0x9_long;
}

void LongIntTest::test_char_constructor()
{
  QFETCH(qlonglong, input);
  QFETCH(LongInt, result);

  LongInt constructed ((char)input);

  cout << constructed << " " << result << endl;
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
  QTest::newRow("LongInt(-83)") << qlonglong(-0x53) << -0x53_long;
  QTest::newRow("LongInt(12)") << qlonglong(0xc) << 0xc_long;
  QTest::newRow("LongInt(-25440)") << qlonglong(-0x6360) << -0x6360_long;
  QTest::newRow("LongInt(8287)") << qlonglong(0x205f) << 0x205f_long;
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
  QTest::newRow("LongInt(-28538)") << qlonglong(-0x6f7a) << -0x6f7a_long;
  QTest::newRow("LongInt(3851)") << qlonglong(0xf0b) << 0xf0b_long;
  QTest::newRow("LongInt(-2054196169)") << qlonglong(-0x7a708bc9) << -0x7a708bc9_long;
  QTest::newRow("LongInt(738371102)") << qlonglong(0x2c02a61e) << 0x2c02a61e_long;
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
  QTest::newRow("LongInt(-2027013258)") << qlonglong(-0x78d1c48a) << -0x78d1c48a_long;
  QTest::newRow("LongInt(1599674317)") << qlonglong(0x5f5917cd) << 0x5f5917cd_long;
  QTest::newRow("LongInt(-7159526349296722255)") << qlonglong(-0x635bbf4829e1614f) << -0x635bbf4829e1614f_long;
  QTest::newRow("LongInt(3239767569338773125)") << qlonglong(0x2cf5f7707544ae85) << 0x2cf5f7707544ae85_long;
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
  QTest::newRow("LongInt(-310255572)") << qlonglong(-0x127e1fd4) << -0x127e1fd4_long;
  QTest::newRow("LongInt(106326774)") << qlonglong(0x6566af6) << 0x6566af6_long;
  QTest::newRow("LongInt(-336598702414646312)") << qlonglong(-0x4abd6bc89484c28) << -0x4abd6bc89484c28_long;
  QTest::newRow("LongInt(4200957977456741014)") << qlonglong(0x3a4ccd05daa70a96) << 0x3a4ccd05daa70a96_long;
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
  QTest::newRow("(char)-5") << -0x5_long << qlonglong(-0x5);
  QTest::newRow("(char)5") << 0x5_long << qlonglong(0x5);
  QTest::newRow("(char)-19") << -0x13_long << qlonglong(-0x13);
  QTest::newRow("(char)45") << 0x2d_long << qlonglong(0x2d);
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
  QTest::newRow("(short)-101") << -0x65_long << qlonglong(-0x65);
  QTest::newRow("(short)18") << 0x12_long << qlonglong(0x12);
  QTest::newRow("(short)-18731") << -0x492b_long << qlonglong(-0x492b);
  QTest::newRow("(short)20440") << 0x4fd8_long << qlonglong(0x4fd8);
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
  QTest::newRow("(int)-32681") << -0x7fa9_long << qlonglong(-0x7fa9);
  QTest::newRow("(int)22352") << 0x5750_long << qlonglong(0x5750);
  QTest::newRow("(int)-1528347717") << -0x5b18bc45_long << qlonglong(-0x5b18bc45);
  QTest::newRow("(int)1833119475") << 0x6d432ef3_long << qlonglong(0x6d432ef3);
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
  QTest::newRow("(long int)-1179082510") << -0x46475f0e_long << qlonglong(-0x46475f0e);
  QTest::newRow("(long int)901043614") << 0x35b4d59e_long << qlonglong(0x35b4d59e);
  QTest::newRow("(long int)-8602749287559239263") << -0x77631ae5d0b6965f_long << qlonglong(-0x77631ae5d0b6965f);
  QTest::newRow("(long int)9025511959078373338") << 0x7d410f4ebce807da_long << qlonglong(0x7d410f4ebce807da);
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
  QTest::newRow("(long long int)-1776475815") << -0x69e2dea7_long << qlonglong(-0x69e2dea7);
  QTest::newRow("(long long int)1115027583") << 0x4275f87f_long << qlonglong(0x4275f87f);
  QTest::newRow("(long long int)-4095979998773615833") << -0x38d7d81b82019cd9_long << qlonglong(-0x38d7d81b82019cd9);
  QTest::newRow("(long long int)4076675590295651596") << 0x389342d9a814050c_long << qlonglong(0x389342d9a814050c);
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
  QTest::newRow("LongInt(10)") << qlonglong(0xa) << 0xa_long;
  QTest::newRow("LongInt(33)") << qlonglong(0x21) << 0x21_long;
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
  QTest::newRow("LongInt(34)") << qlonglong(0x22) << 0x22_long;
  QTest::newRow("LongInt(64210)") << qlonglong(0xfad2) << 0xfad2_long;
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
  QTest::newRow("LongInt(21662)") << qlonglong(0x549e) << 0x549e_long;
  QTest::newRow("LongInt(2502943344)") << qlonglong(0x952fe270) << 0x952fe270_long;
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
  QTest::newRow("LongInt(487147283)") << qlonglong(0x1d094713) << 0x1d094713_long;
  QTest::newRow("LongInt(17883189047554278098)") << qlonglong(0xf82dd9b086a102d2) << 0xf82dd9b086a102d2_long;
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
  QTest::newRow("LongInt(1142198843)") << qlonglong(0x4414923b) << 0x4414923b_long;
  QTest::newRow("LongInt(17022769517321542262)") << qlonglong(0xec3d06af7d4c5a76) << 0xec3d06af7d4c5a76_long;
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
  QTest::newRow("(unsigned char)5") << 0x5_long << qlonglong(0x5);
  QTest::newRow("(unsigned char)173") << 0xad_long << qlonglong(0xad);
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
  QTest::newRow("(unsigned short)220") << 0xdc_long << qlonglong(0xdc);
  QTest::newRow("(unsigned short)127") << 0x7f_long << qlonglong(0x7f);
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
  QTest::newRow("(unsigned int)58499") << 0xe483_long << qlonglong(0xe483);
  QTest::newRow("(unsigned int)2865226374") << 0xaac7e286_long << qlonglong(0xaac7e286);
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
  QTest::newRow("(unsigned long int)3470806564") << 0xcee04e24_long << qlonglong(0xcee04e24);
  QTest::newRow("(unsigned long int)3872507692789713375") << 0x35bde93aaab2c9df_long << qlonglong(0x35bde93aaab2c9df);
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
  QTest::newRow("(unsigned long long int)3151525430") << 0xbbd87636_long << qlonglong(0xbbd87636);
  QTest::newRow("(unsigned long long int)11283321453620173460") << 0x9c96691499931a94_long << qlonglong(0x9c96691499931a94);
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
  QTest::newRow("LongInt(-0x62_long)") << -0x62_long << -0x62_long;
  QTest::newRow("LongInt(0x91_long)") << 0x91_long << 0x91_long;
  QTest::newRow("LongInt(-0x8329ce7b_long)") << -0x8329ce7b_long << -0x8329ce7b_long;
  QTest::newRow("LongInt(0x7eb7282e_long)") << 0x7eb7282e_long << 0x7eb7282e_long;
  QTest::newRow("LongInt(-0x47adc034a50f2ced822228ad15db8c8116dc415fb7b3d0b33d_long)")
      << -0x47adc034a50f2ced822228ad15db8c8116dc415fb7b3d0b33d_long
      << -0x47adc034a50f2ced822228ad15db8c8116dc415fb7b3d0b33d_long;
  QTest::newRow("LongInt(0xdca7a1ed3f0a811ea4ea470ac49ce360aaee6d1f33e0a2a4c1_long)")
      << 0xdca7a1ed3f0a811ea4ea470ac49ce360aaee6d1f33e0a2a4c1_long
      << 0xdca7a1ed3f0a811ea4ea470ac49ce360aaee6d1f33e0a2a4c1_long;
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
  QTest::newRow("LongInt(\"-54\")") << string("-54") << -0x36_long;
  QTest::newRow("LongInt(\"46\")") << string("46") << 0x2e_long;
  QTest::newRow("LongInt(\"-6942991069\")") << string("-6942991069") << -0x19dd5a2dd_long;
  QTest::newRow("LongInt(\"5538573368\")") << string("5538573368") << 0x14a1fec38_long;
  QTest::newRow("LongInt(\"-854549475551897090565791514835386477148189283066202354767144\")")
      << string("-854549475551897090565791514835386477148189283066202354767144")
      << -0x882338d1486c667e30b751c26b2ad07940199b2aeaed9a5528_long;
  QTest::newRow("LongInt(\"13880220117759036740251767186383759804847728009206407073947\")")
      << string("13880220117759036740251767186383759804847728009206407073947")
      << 0x23614427fc2456e94beb392a6b26177e0bdc723da0e77909b_long;
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
  QTest::newRow("LongInt(\"-0xb7\")") << string("-0xb7") << -0xb7_long;
  QTest::newRow("LongInt(\"0x5\")") << string("0x5") << 0x5_long;
  QTest::newRow("LongInt(\"-0x1f41095ec\")") << string("-0x1f41095ec") << -0x1f41095ec_long;
  QTest::newRow("LongInt(\"0x17bdb6e55\")") << string("0x17bdb6e55") << 0x17bdb6e55_long;
  QTest::newRow("LongInt(\"-0x275482c4378ebdaebff59451053e37919b0571fb5ee05a090\")")
      << string("-0x275482c4378ebdaebff59451053e37919b0571fb5ee05a090")
      << -0x275482c4378ebdaebff59451053e37919b0571fb5ee05a090_long;
  QTest::newRow("LongInt(\"0xcd43ecb3e26d2330533f720db42c4ac37c2e313bb0a4caa530\")")
      << string("0xcd43ecb3e26d2330533f720db42c4ac37c2e313bb0a4caa530")
      << 0xcd43ecb3e26d2330533f720db42c4ac37c2e313bb0a4caa530_long;
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
  QTest::newRow("istream(\"-84\") >> constructed") << string("-84") << -0x54_long;
  QTest::newRow("istream(\"96\") >> constructed") << string("96") << 0x60_long;
  QTest::newRow("istream(\"-721118366\") >> constructed") << string("-721118366") << -0x2afb649e_long;
  QTest::newRow("istream(\"5771456346\") >> constructed") << string("5771456346") << 0x158016f5a_long;
  QTest::newRow("istream(\"-1395344073509369128983432847213788867561309227497582223631676\") >> constructed")
      << string("-1395344073509369128983432847213788867561309227497582223631676")
      << -0xde4a87de1cb4b3ff85872ee518dbdddc070386b00e0b07253c_long;
  QTest::newRow("istream(\"174671506391396085830272957721615102711397050100713877661452\") >> constructed")
      << string("174671506391396085830272957721615102711397050100713877661452")
      << 0x1bd3a79e243db9c24f516fc4ae567b1d3c3c22b99d181fe70c_long;
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
  QTest::newRow("istream(\"-105\") >> hex >> constructed") << string("-69") << -0x69_long;
  QTest::newRow("istream(\"87\") >> hex >> constructed") << string("57") << 0x57_long;
  QTest::newRow("istream(\"-3472684895\") >> hex >> constructed") << string("-cefcf75f") << -0xcefcf75f_long;
  QTest::newRow("istream(\"3635734639\") >> hex >> constructed") << string("d8b4e86f") << 0xd8b4e86f_long;
  QTest::newRow("istream(\"-1505100677246704167389241133610782688172085557702021650518610\") >> hex >> constructed")
      << string("-efc6c04747e61626f0e49e2a414e88a58eb4235d3cb2b31252")
      << -0xefc6c04747e61626f0e49e2a414e88a58eb4235d3cb2b31252_long;
  QTest::newRow("istream(\"1343240779264647844287275735000833077769576903816336251561028\") >> hex >> constructed")
      << string("d5fd9817f9acb37e4b355f3788d64713e7487846d405182444")
      << 0xd5fd9817f9acb37e4b355f3788d64713e7487846d405182444_long;
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
  QTest::newRow("out << -0x27_long") << -0x27_long << string("-39");
  QTest::newRow("out << 0xa7_long") << 0xa7_long << string("167");
  QTest::newRow("out << -0x1ef88650a_long") << -0x1ef88650a_long << string("-8313660682");
  QTest::newRow("out << 0xd2b16080_long") << 0xd2b16080_long << string("3534839936");
  QTest::newRow("out << -0x4e50ff55569a56c1888c31ce391828d9073d340a278895a875_long")
      << -0x4e50ff55569a56c1888c31ce391828d9073d340a278895a875_long
      << string("-491599985728997875854405378614347566908405435743347917826165");
  QTest::newRow("out << 0x9fbd7bb9540c8626ae871661006f54d37d10ef55d04cb22ea7_long")
      << 0x9fbd7bb9540c8626ae871661006f54d37d10ef55d04cb22ea7_long
      << string("1002705292841086276964284889154830383599682990686192652136103");
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
  QTest::newRow("out << hex << -0x57_long") << -0x57_long << string("-57");
  QTest::newRow("out << hex << 0xc7_long") << 0xc7_long << string("c7");
  QTest::newRow("out << hex << -0x98618f1c_long") << -0x98618f1c_long << string("-98618f1c");
  QTest::newRow("out << hex << 0x398986a1_long") << 0x398986a1_long << string("398986a1");
  QTest::newRow("out << hex << -0xbed6cd29a2d1c17fbce1868073748607c023714759bf03b69c_long")
      << -0xbed6cd29a2d1c17fbce1868073748607c023714759bf03b69c_long
      << string("-bed6cd29a2d1c17fbce1868073748607c023714759bf03b69c");
  QTest::newRow("out << hex << 0x24aee0a2555b817393876632c06d4226a04dbb5d793e7f536f_long")
      << 0x24aee0a2555b817393876632c06d4226a04dbb5d793e7f536f_long
      << string("24aee0a2555b817393876632c06d4226a04dbb5d793e7f536f");
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
  QTest::newRow("i = -0xb7_long") << -0xb7_long << -0xb7_long;
  QTest::newRow("i = 0x33_long") << 0x33_long << 0x33_long;
  QTest::newRow("i = -0x3dd17837_long") << -0x3dd17837_long << -0x3dd17837_long;
  QTest::newRow("i = 0x19662588f_long") << 0x19662588f_long << 0x19662588f_long;
  QTest::newRow("i = -0x279206a39bf1b8cd4e2b6bdaa6fd6e3aa30d93dabf8a759a95_long")
      << -0x279206a39bf1b8cd4e2b6bdaa6fd6e3aa30d93dabf8a759a95_long
      << -0x279206a39bf1b8cd4e2b6bdaa6fd6e3aa30d93dabf8a759a95_long;
  QTest::newRow("i = 0x331ab1d96e0d71f839a28aa060a4ee03aefa7de962c44e7a69_long")
      << 0x331ab1d96e0d71f839a28aa060a4ee03aefa7de962c44e7a69_long
      << 0x331ab1d96e0d71f839a28aa060a4ee03aefa7de962c44e7a69_long;
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
  QTest::newRow("-94++") << -0x5e_long << -0x5d_long;
  QTest::newRow("194++") << 0xc2_long << 0xc3_long;
  QTest::newRow("-2267416054++") << -0x872605f6_long << -0x872605f5_long;
  QTest::newRow("5319781014++") << 0x13d156a96_long << 0x13d156a97_long;
  QTest::newRow("-1146737636037287361563162892922221139810396703010780495106848++")
      << -0xb6af938d55c3392b576a5ac3935be9dc262f6ee04b0c9e5320_long
      << -0xb6af938d55c3392b576a5ac3935be9dc262f6ee04b0c9e531f_long;
  QTest::newRow("1359523898440166295623304254340312276912118572591303371685644++")
      << 0xd895abca4720b3168ed3205558c8dcd118f872f26f4d0a7f0c_long
      << 0xd895abca4720b3168ed3205558c8dcd118f872f26f4d0a7f0d_long;
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
  QTest::newRow("-132--") << -0x84_long << -0x85_long;
  QTest::newRow("78--") << 0x4e_long << 0x4d_long;
  QTest::newRow("-3137668270--") << -0xbb0504ae_long << -0xbb0504af_long;
  QTest::newRow("4848503248--") << 0x120fe49d0_long << 0x120fe49cf_long;
  QTest::newRow("-713634624433862182280560435426723753335633994495182454878770--")
      << -0x71b04520163394eddc7c9565742543f52c0c524406f3b37232_long
      << -0x71b04520163394eddc7c9565742543f52c0c524406f3b37233_long;
  QTest::newRow("1326123825456110408911578042140933072662523995151908246993159--")
      << 0xd34382c1e43ce8b4f40e572089ffa7755ca7d43c45cfa93907_long
      << 0xd34382c1e43ce8b4f40e572089ffa7755ca7d43c45cfa93906_long;
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
  QTest::newRow("+-103") << -0x67_long << -0x67_long;
  QTest::newRow("+30") << 0x1e_long << 0x1e_long;
  QTest::newRow("+-8527040677") << -0x1fc4050a5_long << -0x1fc4050a5_long;
  QTest::newRow("+3098395006") << 0xb8adc17e_long << 0xb8adc17e_long;
  QTest::newRow("+-534473916955034260310900786483336930804396290961623427682798")
      << -0x5525880fb3c0ea2ef3d81de5b93868ff7dcc8f03824edd91ee_long
      << -0x5525880fb3c0ea2ef3d81de5b93868ff7dcc8f03824edd91ee_long;
  QTest::newRow("+1240579842415251863709755965524621566829542891343076980356250")
      << 0xc5a2c1e6dbf5ffeb1c2f0c2d962b76b298bcc4b3ea6442f49a_long
      << 0xc5a2c1e6dbf5ffeb1c2f0c2d962b76b298bcc4b3ea6442f49a_long;
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
  QTest::newRow("--48") << -0x30_long << 0x30_long;
  QTest::newRow("-80") << 0x50_long << -0x50_long;
  QTest::newRow("--3213571918") << -0xbf8b374e_long << 0xbf8b374e_long;
  QTest::newRow("-7652996849") << 0x1c82776f1_long << -0x1c82776f1_long;
  QTest::newRow("--518957810463758444246596549819800567834516539297893803452049")
      << -0x52acbc59d5914620e98cdb43c326ec63448685fb11be156691_long
      << 0x52acbc59d5914620e98cdb43c326ec63448685fb11be156691_long;
  QTest::newRow("-260833468671794269619611638424844294847833289463166954125285")
      << 0x298d9c7a46e392fd6b00dd9b39ce708def078a80c07fa037e5_long
      << -0x298d9c7a46e392fd6b00dd9b39ce708def078a80c07fa037e5_long;
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
  QTest::newRow("~-176") << -0xb0_long << 0xaf_long;
  QTest::newRow("~48") << 0x30_long << -0x31_long;
  QTest::newRow("~-2839795034") << -0xa943d55a_long << 0xa943d559_long;
  QTest::newRow("~64645909") << 0x3da6b15_long << -0x3da6b16_long;
  QTest::newRow("~-1327531877277439062390805830148896433592178721474669587207999")
      << -0xd37cef811c0d9c078308c379da35eb190dc9dbc92339b8173f_long
      << 0xd37cef811c0d9c078308c379da35eb190dc9dbc92339b8173e_long;
  QTest::newRow("~940825098161432191208760549394529531084832459994461504986392")
      << 0x95e1d058bc228699550f2badfdcb0530ea2112188c7926dd18_long
      << -0x95e1d058bc228699550f2badfdcb0530ea2112188c7926dd19_long;
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
  QTest::newRow("-14954859241784808148 >> 0") << -0xcf8a553f048d12d4_long << 0 << -0xcf8a553f048d12d4_long;
  QTest::newRow("-6324455110536099746 >> 0") << -0x57c4fa6a256877a2_long << 0 << -0x57c4fa6a256877a2_long;
  QTest::newRow("12096677112688000872 >> 0") << 0xa7e007be385dbf68_long << 0 << 0xa7e007be385dbf68_long;
  QTest::newRow("11954584173643919527 >> 0") << 0xa5e736f7c38d70a7_long << 0 << 0xa5e736f7c38d70a7_long;
  QTest::newRow("0 >> 14") << 0x0_long << 14 << 0x0_long;
  QTest::newRow("-2016771763004737719 >> 1") << -0x1bfd033baeef88b7_long << 1 << -0xdfe819dd777c45c_long;
  QTest::newRow("-3913336509819168027 >> 2") << -0x364ef6d26a56a51b_long << 2 << -0xd93bdb49a95a947_long;
  QTest::newRow("-1785042176744187278 >> 32") << -0x18c5be66f5ed658e_long << 32 << -0x18c5be67_long;
  QTest::newRow("-7829373426812896108 >> 1") << -0x6ca785a65f10c36c_long << 1 << -0x3653c2d32f8861b6_long;
  QTest::newRow("-15581844306986631704 >> 2") << -0xd83dd4d74f618218_long << 2 << -0x360f7535d3d86086_long;
  QTest::newRow("-2547071350095817484 >> 32") << -0x235903e5e0092b0c_long << 32 << -0x235903e6_long;
  QTest::newRow("10965910566139279388 >> 1") << 0x982ebd8f5d6f381c_long << 1 << 0x4c175ec7aeb79c0e_long;
  QTest::newRow("4010961876979884055 >> 2") << 0x37a9cc937d052017_long << 2 << 0xdea7324df414805_long;
  QTest::newRow("807698571462923042 >> 32") << 0xb35859245a35322_long << 32 << 0xb358592_long;
  QTest::newRow("7882152216903580116 >> 1") << 0x6d6307ae0a1879d4_long << 1 << 0x36b183d7050c3cea_long;
  QTest::newRow("14353032487278954222 >> 2") << 0xc730370065e746ee_long << 2 << 0x31cc0dc01979d1bb_long;
  QTest::newRow("2970183817118705260 >> 32") << 0x29383671e8f9666c_long << 32 << 0x29383671_long;
  QTest::newRow("-1 >> 9") << -0x1_long << 9 << -0x1_long;
  QTest::newRow("1 >> 25") << 0x1_long << 25 << 0x0_long;
  QTest::newRow("-9778917554932861664 >> 19") << -0x87b5b1b48d9acae0_long << 19 << -0x10f6b63691b4_long;
  QTest::newRow("-16786004978440198677 >> 13") << -0xe8f3de9781ddda15_long << 13 << -0x7479ef4bc0eef_long;
  QTest::newRow("17848410784483350480 >> 28") << 0xf7b24b0b266197d0_long << 28 << 0xf7b24b0b2_long;
  QTest::newRow("8871062176347733560 >> 2") << 0x7b1c580c699c3e38_long << 2 << 0x1ec716031a670f8e_long;
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
  QTest::newRow("-1430066524306707573 << 0") << -0x13d89ded527a9475_long << 0 << -0x13d89ded527a9475_long;
  QTest::newRow("-12443253607547787152 << 0") << -0xacaf513a97fbd790_long << 0 << -0xacaf513a97fbd790_long;
  QTest::newRow("3706995789994014621 << 0") << 0x3371e507ce76379d_long << 0 << 0x3371e507ce76379d_long;
  QTest::newRow("6760531934355368034 << 0") << 0x5dd23bf9b7efa862_long << 0 << 0x5dd23bf9b7efa862_long;
  QTest::newRow("0 << 7") << 0x0_long << 7 << 0x0_long;
  QTest::newRow("-3833212534429495638 << 1") << -0x35324e7da73eb156_long << 1 << -0x6a649cfb4e7d62ac_long;
  QTest::newRow("-2611067901799056817 << 2") << -0x243c606c332845b1_long << 2 << -0x90f181b0cca116c4_long;
  QTest::newRow("-14249688096170733824 << 32") << -0xc5c10fd34c5e7100_long << 32 << -0xc5c10fd34c5e710000000000_long;
  QTest::newRow("-12869107473460633721 << 1") << -0xb29841104bf22079_long << 1 << -0x16530822097e440f2_long;
  QTest::newRow("-10471206506987806095 << 2") << -0x915132d6dac45d8f_long << 2 << -0x24544cb5b6b11763c_long;
  QTest::newRow("-14138015989414454688 << 32") << -0xc43452a2cdd765a0_long << 32 << -0xc43452a2cdd765a000000000_long;
  QTest::newRow("2054004573899429025 << 1") << 0x1c814a47024d94a1_long << 1 << 0x3902948e049b2942_long;
  QTest::newRow("11265641424729575215 << 2") << 0x9c57993017ee8f2f_long << 2 << 0x2715e64c05fba3cbc_long;
  QTest::newRow("13763826270345144768 << 32") << 0xbf02ef11aa1ca9c0_long << 32 << 0xbf02ef11aa1ca9c000000000_long;
  QTest::newRow("3140532015682298005 << 1") << 0x2b95693aa07c2095_long << 1 << 0x572ad27540f8412a_long;
  QTest::newRow("6988168794059349720 << 2") << 0x60faf67e48609ed8_long << 2 << 0x183ebd9f921827b60_long;
  QTest::newRow("4557424834347026902 << 32") << 0x3f3f39bd95cc49d6_long << 32 << 0x3f3f39bd95cc49d600000000_long;
  QTest::newRow("-1 << 29") << -0x1_long << 29 << -0x20000000_long;
  QTest::newRow("1 << 18") << 0x1_long << 18 << 0x40000_long;
  QTest::newRow("-8239858348428642042 << 1") << -0x7259db82e1a046fa_long << 1 << -0xe4b3b705c3408df4_long;
  QTest::newRow("-382695484511594654 << 1") << -0x54f9b83fb75a89e_long << 1 << -0xa9f3707f6eb513c_long;
  QTest::newRow("8024341221389259722 << 17") << 0x6f5c2fd3796e53ca_long << 17 << 0xdeb85fa6f2dca7940000_long;
  QTest::newRow("10130917090570626400 << 10") << 0x8c983f6b00656560_long << 10 << 0x23260fdac0195958000_long;
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
  QTest::newRow("-12127572150765830133 + 0") << -0xa84dca9dd2513ff5_long << 0x0_long << -0xa84dca9dd2513ff5_long;
  QTest::newRow("-28879155583995902593901088742726684331876325369468886463 + 0")
      << -0x12d83301a5b3ac4ffcca252fa657d1da7feb0771aa71dbf_long << 0x0_long
      << -0x12d83301a5b3ac4ffcca252fa657d1da7feb0771aa71dbf_long;
  QTest::newRow("13015092979405565377 + 0") << 0xb49ee61b9c262dc1_long << 0x0_long << 0xb49ee61b9c262dc1_long;
  QTest::newRow("2805950292921743989511044419447861168393261517588808764911 + 0")
      << 0x726f7cebd36055da2b2c82373371dfa937e3d7a0edfa8def_long << 0x0_long
      << 0x726f7cebd36055da2b2c82373371dfa937e3d7a0edfa8def_long;
  QTest::newRow("0 + -16700686754370262131") << 0x0_long << -0xe7c4c21e7b4f9473_long << -0xe7c4c21e7b4f9473_long;
  QTest::newRow("0 + -7648308602154035186") << 0x0_long << -0x6a244026b3f4a7f2_long << -0x6a244026b3f4a7f2_long;
  QTest::newRow("0 + 6598092457976801623") << 0x0_long << 0x5b912221e0e42957_long << 0x5b912221e0e42957_long;
  QTest::newRow("0 + 4170975246014496233") << 0x0_long << 0x39e247e331a43de9_long << 0x39e247e331a43de9_long;
  QTest::newRow("-1540718057435913347 + 1") << -0x1561bae9007f5c83_long << 0x1_long << -0x1561bae9007f5c82_long;
  QTest::newRow("-11290129747628480749 + 1") << -0x9cae9930137758ed_long << 0x1_long << -0x9cae9930137758ec_long;
  QTest::newRow("-2757026712244379407056644800580866114575261235156208520185 + 1")
      << -0x7070b3b386518ad42a4ec2e2fd76bf8081c27ba7ef830bf9_long << 0x1_long
      << -0x7070b3b386518ad42a4ec2e2fd76bf8081c27ba7ef830bf8_long;
  QTest::newRow("-45812752436358380864907170825242809223698026701145449804 + 1")
      << -0x1de4eb53e71fc134a31b0dbb77eac771d464b47cf3f254c_long << 0x1_long
      << -0x1de4eb53e71fc134a31b0dbb77eac771d464b47cf3f254b_long;
  QTest::newRow("13291181864198454487 + 1") << 0xb873c37c5ca9bcd7_long << 0x1_long << 0xb873c37c5ca9bcd8_long;
  QTest::newRow("9015087872020872880 + 1") << 0x7d1c06a7d6bc7eb0_long << 0x1_long << 0x7d1c06a7d6bc7eb1_long;
  QTest::newRow("6004426422105434262456152049492990760849275581108101833325 + 1")
      << 0xf4e1230b9bf66d9e1222f475abd0d86f2da76c1292dbe26d_long << 0x1_long
      << 0xf4e1230b9bf66d9e1222f475abd0d86f2da76c1292dbe26e_long;
  QTest::newRow("1958970562383800285419361699360429044843347152099338862003 + 1")
      << 0x4fe49b6322be29c469f181599f20667e04b417dd02ebbdb3_long << 0x1_long
      << 0x4fe49b6322be29c469f181599f20667e04b417dd02ebbdb4_long;
  QTest::newRow("-1 + -1043911552067142468") << -0x1_long << -0xe7cb80695e38344_long << -0xe7cb80695e38345_long;
  QTest::newRow("-1 + -3314283777055564031") << -0x1_long << -0x2dfeb389103ca0ff_long << -0x2dfeb389103ca100_long;
  QTest::newRow("-1 + 9537990992934452284") << -0x1_long << 0x845dc0460cbbbc3c_long << 0x845dc0460cbbbc3b_long;
  QTest::newRow("-1 + 9690592956471184537") << -0x1_long << 0x867be6f3715e0c99_long << 0x867be6f3715e0c98_long;
  QTest::newRow("1 + -16530038225630045699") << 0x1_long << -0xe5667e2fb24ea603_long << -0xe5667e2fb24ea602_long;
  QTest::newRow("1 + -4160934555013190513") << 0x1_long << -0x39be9beea5359371_long << -0x39be9beea5359370_long;
  QTest::newRow("1 + 8310998035552658784") << 0x1_long << 0x735698ae0615e560_long << 0x735698ae0615e561_long;
  QTest::newRow("1 + 8942279077500349370") << 0x1_long << 0x7c195b7158d0ebba_long << 0x7c195b7158d0ebbb_long;
  QTest::newRow("-8067428304908247162 + -15280816432318904229") << -0x6ff5434cdcfce07a_long << -0xd4105d957e51f7a5_long << -0x14405a0e25b4ed81f_long;
  QTest::newRow("-6751915742980275311 + -14422825565134648387") << -0x5db39f9855b4fc6f_long << -0xc8282b6fa345f443_long << -0x125dbcb07f8faf0b2_long;
  QTest::newRow("-12487933819603254840 + 15166466654544357166") << -0xad4e0da52009fe38_long << 0xd27a1d1121ec672e_long << 0x252c0f6c01e268f6_long;
  QTest::newRow("-9252570232223261427 + 4460660369348036815") << -0x8067bb9a9f0562f3_long << 0x3de772f8eaa708cf_long << -0x428048a1b45e5a24_long;
  QTest::newRow("-2835909986487739205393563574069267047109766332316499834387 + -16459128454236947201")
      << -0x73a848220495d04f90d1b246057936e8069d378b98d3f613_long << -0xe46a921ffb514301_long
      << -0x73a848220495d04f90d1b246057936e8eb07c9ab94253914_long;
  QTest::newRow("-3275512662361699806211657987362232110013323814772106554319 + -15991042991162365669")
      << -0x8595f2a6c37e2ce3a0dbf5b8a31a100a65d8f36fb1436bcf_long << -0xddeb98e0543b96e5_long
      << -0x8595f2a6c37e2ce3a0dbf5b8a31a100b43c48c50057f02b4_long;
  QTest::newRow("-3496667075272272420369541115973555715415775163431504399957 + 8087751200189199871")
      << -0x8e9ae85c9a45ea8d51667676ebf798b88455d70068ad4e55_long << 0x703d76dda70435ff_long
      << -0x8e9ae85c9a45ea8d51667676ebf798b814186022c1a91856_long;
  QTest::newRow("-2335672094603077960778883911860040749111903328755826660238 + 10788239127369140989")
      << -0x5f418df2e4b3e776055d946bfd0aac49795c9cfddced938e_long << 0x95b78653eacecafd_long
      << -0x5f418df2e4b3e776055d946bfd0aac48e3a516a9f21ec891_long;
  QTest::newRow("6582897991237676394 + -8535125171874222273") << 0x5b5b26d8685aad6a_long << -0x7672db1f6f0ed0c1_long << -0x1b17b44706b42357_long;
  QTest::newRow("9548791057537101515 + -5960150554793931683") << 0x84841ee00aeceecb_long << -0x52b6b559f256f3a3_long << 0x31cd69861895fb28_long;
  QTest::newRow("1495196196131600605 + 18222879323370582203") << 0x14c00104bbf078dd_long << 0xfce4ac32165070bb_long << 0x111a4ad36d240e998_long;
  QTest::newRow("10775138704843934631 + 6686819522419674210") << 0x9588fb901bc90ba7_long << 0x5ccc5aed66f8cc62_long << 0xf255567d82c1d809_long;
  QTest::newRow("5276421391541764954070076598881078925028526183165315359870 + -17348788101034259850")
      << 0xd73068e41142ddb3f3f7131f6dd36f1f584231f3bc79a47e_long << -0xf0c346dc2dabb58a_long
      << 0xd73068e41142ddb3f3f7131f6dd36f1e677eeb178ecdeef4_long;
  QTest::newRow("6146903581997911540522541739256998073317285556790880034150 + -854131046902245593")
      << 0xfab0aaf865cc80b19f7e071e11f7da059323e588940edd66_long << -0xbda7ba96a3da8d9_long
      << 0xfab0aaf865cc80b19f7e071e11f7da05874969df29d1348d_long;
  QTest::newRow("2988618073960570890640880594316351471459173315955380908550 + 16375305321452037755")
      << 0x79e2a0eb86cae5d29351ac6c533e7bf57b335301ca0ef206_long << 0xe340c56e05b6667b_long
      << 0x79e2a0eb86cae5d29351ac6c533e7bf65e74186fcfc55881_long;
  QTest::newRow("3725775932352751130826969636433617728441527357654836191915 + 2307750569463438155")
      << 0x97f2ea6e0108c213c4c5255231b762cfaee8f059195c22ab_long << 0x2006c6ea7b12db4b_long
      << 0x97f2ea6e0108c213c4c5255231b762cfceefb743946efdf6_long;
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
  QTest::newRow("-8955108468944518405 - 0") << -0x7c46efb4d087bd05_long << 0x0_long << -0x7c46efb4d087bd05_long;
  QTest::newRow("-5505109828352565797788527180807499819332698961660633292491 - 0")
      << -0xe08407463f3d0c4ee27cc292bd24f4752afe9a2cd03a1ecb_long << 0x0_long
      << -0xe08407463f3d0c4ee27cc292bd24f4752afe9a2cd03a1ecb_long;
  QTest::newRow("599293316213735265 - 0") << 0x8511e188d2f7f61_long << 0x0_long << 0x8511e188d2f7f61_long;
  QTest::newRow("4925103835667096833922100878477251946674916798497876635202 - 0")
      << 0xc8dc7bb9bb123555bd9ea10ffee4c1dd4c10677860146e42_long << 0x0_long
      << 0xc8dc7bb9bb123555bd9ea10ffee4c1dd4c10677860146e42_long;
  QTest::newRow("0 - -15135456895666348990") << 0x0_long << -0xd20bf1db036de3be_long << 0xd20bf1db036de3be_long;
  QTest::newRow("0 - -17983977288428460211") << 0x0_long << -0xf993ec0f857898b3_long << 0xf993ec0f857898b3_long;
  QTest::newRow("0 - 18011346341400951172") << 0x0_long << 0xf9f52811bdbc3984_long << -0xf9f52811bdbc3984_long;
  QTest::newRow("0 - 1992688828177807752") << 0x0_long << 0x1ba773ee776d7988_long << -0x1ba773ee776d7988_long;
  QTest::newRow("-13702830462482185406 - 1") << -0xbe2a3bb475a6fcbe_long << 0x1_long << -0xbe2a3bb475a6fcbf_long;
  QTest::newRow("-11060363894165891108 - 1") << -0x997e4e5c86506824_long << 0x1_long << -0x997e4e5c86506825_long;
  QTest::newRow("-1920934774100597390078001841792156703106471630062189707463 - 1")
      << -0x4e577eacb2e9cef01158ef8cf3be85a37d696a7eb6fe80c7_long << 0x1_long
      << -0x4e577eacb2e9cef01158ef8cf3be85a37d696a7eb6fe80c8_long;
  QTest::newRow("-1820104649079259118377368446514438089988678727461224647092 - 1")
      << -0x4a3ac77988273a63ee41495e18c4cccf8f247912db2909b4_long << 0x1_long
      << -0x4a3ac77988273a63ee41495e18c4cccf8f247912db2909b5_long;
  QTest::newRow("13962659997977262590 - 1") << 0xc1c5554a72fdb9fe_long << 0x1_long << 0xc1c5554a72fdb9fd_long;
  QTest::newRow("17389646833149294319 - 1") << 0xf1546fa9135c36ef_long << 0x1_long << 0xf1546fa9135c36ee_long;
  QTest::newRow("233624965781654207732128284846005188361559628479247399948 - 1")
      << 0x98728905e38a3a8630578cac059bce8e2700dd3663fbc0c_long << 0x1_long
      << 0x98728905e38a3a8630578cac059bce8e2700dd3663fbc0b_long;
  QTest::newRow("5001448994469664809190897135046085244057680273104525699079 - 1")
      << 0xcbf9905f2aa7bcdcbb79e57c443497f7be94922b2445a807_long << 0x1_long
      << 0xcbf9905f2aa7bcdcbb79e57c443497f7be94922b2445a806_long;
  QTest::newRow("-1 - -10863187719186415839") << -0x1_long << -0x96c1cbacca7e00df_long << 0x96c1cbacca7e00de_long;
  QTest::newRow("-1 - -17590006969780479947") << -0x1_long << -0xf41c4224a66927cb_long << 0xf41c4224a66927ca_long;
  QTest::newRow("-1 - 13934563343548272555") << -0x1_long << 0xc1618388505fcfab_long << -0xc1618388505fcfac_long;
  QTest::newRow("-1 - 4703201335019359857") << -0x1_long << 0x414520b210f8ce71_long << -0x414520b210f8ce72_long;
  QTest::newRow("1 - -4685343902280158763") << 0x1_long << -0x4105af7481f38e2b_long << 0x4105af7481f38e2c_long;
  QTest::newRow("1 - -11897996973883491061") << 0x1_long << -0xa51e2d359eff82f5_long << 0xa51e2d359eff82f6_long;
  QTest::newRow("1 - 2301496068768292588") << 0x1_long << 0x1ff08e7b0ee45eec_long << -0x1ff08e7b0ee45eeb_long;
  QTest::newRow("1 - 13705953506430654716") << 0x1_long << 0xbe355418cad198fc_long << -0xbe355418cad198fb_long;
  QTest::newRow("-16769442333204355180 - -6256636466883224467") << -0xe8b906f4280b186c_long << -0x56d409b7b1546393_long << -0x91e4fd3c76b6b4d9_long;
  QTest::newRow("-12469657024679866022 - -10309955467655636729") << -0xad0d1eff32ff6ea6_long << -0x8f1451df93b5e6f9_long << -0x1df8cd1f9f4987ad_long;
  QTest::newRow("-397634346776173968 - 1226821154954359594") << -0x584ae54e6169d90_long << 0x11068b5727fd332a_long << -0x168b39ac0e13d0ba_long;
  QTest::newRow("-16599559794315635553 - 9704013105674506112") << -0xe65d7baf480a2b61_long << 0x86ab94816b76cf80_long << -0x16d091030b380fae1_long;
  QTest::newRow("-2824930175236236069459621976192854538464723962462530855460 - -11929419573493861562")
      << -0x7335a5ae4bebf7b23de0b3049f07774e8a324466795e6224_long << -0xa58dcfe5b6b18cba_long
      << -0x7335a5ae4bebf7b23de0b3049f07774de4a47480c2acd56a_long;
  QTest::newRow("-3885906296199604062906276904623017583136567421619200541439 - -13979240194796166929")
      << -0x9e7ac13717d492bbb6a2c5f8c207f368a9b1db9e06d342ff_long << -0xc2003ce458b01f11_long
      << -0x9e7ac13717d492bbb6a2c5f8c207f367e7b19eb9ae2323ee_long;
  QTest::newRow("-1746025777740670181896644796130155665768296283034805653278 - 14267611981617060150")
      << -0x47355c14e77174b226bd11990bb4d6e90f5632a47730cf1e_long << 0xc600bd8115645936_long
      << -0x47355c14e77174b226bd11990bb4d6e9d556f0258c952854_long;
  QTest::newRow("-5595022582536972591563364747652634814521443201013978491082 - 5650800696876083325")
      << -0xe42ec2e928776a99c6dd20c020ecbb8b0192edd33f8be8ca_long << 0x4e6bad4b69d4287d_long
      << -0xe42ec2e928776a99c6dd20c020ecbb8b4ffe9b1ea9601147_long;
  QTest::newRow("8787921815631882120 - -7921076793490140622") << 0x79f4f854b6a4e788_long << -0x6ded51604291edce_long << 0xe7e249b4f936d556_long;
  QTest::newRow("15349388121133816118 - -9255633089945909614") << 0xd503fb2befc81936_long << -0x80729d41c193b96e_long << 0x15576986db15bd2a4_long;
  QTest::newRow("3778998079200892438 - 6340121865751863098") << 0x3471b2bb25a71616_long << 0x57fca33ed8d39f3a_long << -0x238af083b32c8924_long;
  QTest::newRow("13976193215210637541 - 15530602118961877130") << 0xc1f569ae20dac8e5_long << 0xd787c857b0a6d08a_long << -0x15925ea98fcc07a5_long;
  QTest::newRow("408025903542634033899597869440136043698713763338093446740 - -7013243487807713125")
      << 0x10a3fd3c5ce13f8ff19178092b1722b147047725c049c654_long << -0x61540bcb5e19af65_long
      << 0x10a3fd3c5ce13f8ff19178092b1722b1a85882f11e6375b9_long;
  QTest::newRow("278638184787799419323850345777589032936171171788186956027 - -15651962223679227232")
      << 0xb5d1e4ea3acbbda5b3cd578d95e3bd1c59839994d13b0fb_long << -0xd936f0b6fc3bc560_long
      << 0xb5d1e4ea3acbbda5b3cd578d95e3bd29ecf2a50494f765b_long;
  QTest::newRow("4856249420002631298871217996067974792748920578237069676530 - 15828592483274104960")
      << 0xc60d9c12bc7f1104831ceb14be9e23ed2666297395ae4ff2_long << 0xdbaa750003f8a080_long
      << 0xc60d9c12bc7f1104831ceb14be9e23ec4abbb47391b5af72_long;
  QTest::newRow("352263554346367756818744548266062767382642144516233831246 - 12288235230482379512")
      << 0xe5dcd98c1e5570f8925afe450d9e19b01842d69df2d234e_long << 0xaa8894d61557b2f8_long
      << 0xe5dcd98c1e5570f8925afe450d9e19a56fb9893c9d57056_long;
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


void LongIntTest::test_times_data()
{
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
  QTest::newRow("-2543802170724703847 * 0") << -0x234d6698bce9de67_long << 0x0_long << 0x0_long;
  QTest::newRow("-5633760454446651162886258159498123586118389167253558534359 * 0")
      << -0xe5c33420b4bf39dd6f06e5e89505c9e57f9ed2e64fea20d7_long << 0x0_long << 0x0_long;
  QTest::newRow("110037120020169975 * 0") << 0x186ee2d7ae8c4f7_long << 0x0_long << 0x0_long;
  QTest::newRow("50222094639377385680570861903695065507643914816017858291 * 0")
      << 0x20c57d79baab99d94028f618442b872d2fbe83acb06fef3_long << 0x0_long << 0x0_long;
  QTest::newRow("0 * -6014709401359278602") << 0x0_long << -0x53788a554f38e20a_long << 0x0_long;
  QTest::newRow("0 * -6501944072122180926") << 0x0_long << -0x5a3b8baf504ca53e_long << 0x0_long;
  QTest::newRow("0 * 1051875222576535660") << 0x0_long << 0xe9902f11db5986c_long << 0x0_long;
  QTest::newRow("0 * 5362840973922527660") << 0x0_long << 0x4a6ca373c58fe9ac_long << 0x0_long;
  QTest::newRow("-5080504975842685186 * 1") << -0x4681945b9cb53102_long << 0x1_long << -0x4681945b9cb53102_long;
  QTest::newRow("-11505827132390702064 * 1") << -0x9face8d10132fbf0_long << 0x1_long << -0x9face8d10132fbf0_long;
  QTest::newRow("-1192427536602050433508626283840342912186619438331300164755 * 1")
      << -0x30a1863d3a627dec468dc536fcbc56c83b58674930103493_long << 0x1_long
      << -0x30a1863d3a627dec468dc536fcbc56c83b58674930103493_long;
  QTest::newRow("-209857010434583638204516571329321345051522148158232393026 * 1")
      << -0x88f02696238eee9a133697ab8f818316ec85e10eb1cf542_long << 0x1_long
      << -0x88f02696238eee9a133697ab8f818316ec85e10eb1cf542_long;
  QTest::newRow("2367954850658290015 * 1") << 0x20dcaa6405a6895f_long << 0x1_long << 0x20dcaa6405a6895f_long;
  QTest::newRow("7463420412629123670 * 1") << 0x6793655288288256_long << 0x1_long << 0x6793655288288256_long;
  QTest::newRow("3050483440567389404440835631864550678417575486734005954970 * 1")
      << 0x7c68887d196bbfc00909f465372b657bd2a58a6a9d03e99a_long << 0x1_long
      << 0x7c68887d196bbfc00909f465372b657bd2a58a6a9d03e99a_long;
  QTest::newRow("3211973935732522681493873061776974782532764684013379991158 * 1")
      << 0x82fe9295cd2a53ac8ad581ecb33fc95e322996c9fd7f3676_long << 0x1_long
      << 0x82fe9295cd2a53ac8ad581ecb33fc95e322996c9fd7f3676_long;
  QTest::newRow("-1 * -11437872370440392147") << -0x1_long << -0x9ebb7c520a5acdd3_long << 0x9ebb7c520a5acdd3_long;
  QTest::newRow("-1 * -9054582864573114579") << -0x1_long << -0x7da85724603828d3_long << 0x7da85724603828d3_long;
  QTest::newRow("-1 * 3462251772116181751") << -0x1_long << 0x300c63a497f3a2f7_long << -0x300c63a497f3a2f7_long;
  QTest::newRow("-1 * 5144129565849801081") << -0x1_long << 0x47639e95db0fd179_long << -0x47639e95db0fd179_long;
  QTest::newRow("1 * -1891448634895629098") << 0x1_long << -0x1a3fc68319d9fb2a_long << -0x1a3fc68319d9fb2a_long;
  QTest::newRow("1 * -4589892160287121432") << 0x1_long << -0x3fb29299fb43a018_long << -0x3fb29299fb43a018_long;
  QTest::newRow("1 * 769812862491893846") << 0x1_long << 0xaaeecb8445b2056_long << 0xaaeecb8445b2056_long;
  QTest::newRow("1 * 15587224985067327137") << 0x1_long << 0xd850f28a0d080ea1_long << 0xd850f28a0d080ea1_long;
  QTest::newRow("-13775052535859468444 * -6570924724286489450") << -0xbf2ad14c4a3f589c_long << -0x5b309d38f4ed836a_long << 0x441885d527522edbb3acdecee0fe8498_long;
  QTest::newRow("-6289186664144491004 * -14381322481118085572") << -0x5747adf31274d1fc_long << -0xc794b899df6201c4_long << 0x440b6c987ee600dfb71e946b7cbac0f0_long;
  QTest::newRow("-12229316419047590569 * 1437292239375064248") << -0xa9b7427d4b2f0aa9_long << 0x13f249ad36605cb8_long << -0xd393a043ddfc3960c0b542b97046578_long;
  QTest::newRow("-6319794205031536807 * 10144110114824480785") << -0x57b46b58847a18a7_long << 0x8cc71e67548f6811_long << -0x303ae25e6565a5303a55a42df7687b17_long;
  QTest::newRow("-3465512273801754045230493070226321731856436223686339779489 * -2576678405587618610")
      << -0x8d55a2e866267e674b4419f23c2ba71bdb73b4c74524dba1_long << -0x23c2335ba9784b32_long
      << 0x13bdec85e489d39d5e420eacc5d43c4c421821bd900572e16b7a93ac8a031072_long;
  QTest::newRow("-4155431822853473330373754463291979138961769145258495614530 * -13945156847534666994")
      << -0xa978bb88046184dbb20c0f3fabdc9747f9999e0324f29e42_long << -0xc1872644aa68f4f2_long
      << 0x801d7d61d0bf7d1a1dbf573d14e9c435b71bb65fc47adad9b06053604b008264_long;
  QTest::newRow("-4126053010874491596093950138816103612627146409246216067897 * 7117501578594544185")
      << -0xa84600e122a6cf73f97a33216e7f3687ed7f116bfff69b39_long << 0x62c671f9c068ea39_long
      << -0x40ed3d65ee585ac3d8dce02b6392d968ee409d03e4502a39cc87ad0e36f2a9b1_long;
  QTest::newRow("-3248765253736006261118776369887991269973170925485440506902 * 13625896325893390452")
      << -0x847eb11f1e82e351f309bc9c3d12bda0c7589f5146f21c16_long << 0xbd18e883eb2d0074_long
      << -0x61de6cfbab81ebc4c7fc56213b7655096aa04305dc79e5ff88fa386d4792b9f8_long;
  QTest::newRow("9529926408247157865 * -11313475924829822116") << 0x844119939b2fa469_long << -0x9d018a698a6a5ca4_long << -0x511cb8723dbeecd0a63f67c037150f44_long;
  QTest::newRow("1624535536627537208 * -11371171240833446485") << 0x168b8276a1aed538_long << -0x9dce83ff1a03f255_long << -0xde5bee597a2809460c827b72443bb98_long;
  QTest::newRow("4195724297397532566 * 3740706236689862118") << 0x3a3a3504c1daf796_long << 0x33e9a880cefccde6_long << 0xbcebdddb2ed0801cae9b348eea58ec4_long;
  QTest::newRow("3883559548998812709 * 3580016882063457769") << 0x35e52cd576268425_long << 0x31aec662f14b3de9_long << 0xa75a91d69e886f3ab21bf49426216ad_long;
  QTest::newRow("3516292428891046983049709434421925603933182455296084778821 * -6136575099916539210")
      << 0x8f67ce5076402a56010bb5359cc4a2f06cf6a81f3dd99f45_long << -0x55297e8a5808554a_long
      << -0x2fb4b60358f769d9b0384fff85ca51847eff3143c8294a32421c874fd4f1f2f2_long;
  QTest::newRow("5931292412717130265281000344609959445312084425124449372709 * -12002305214248266499")
      << 0xf1e5950bc33e850058def78dd6a886757ef4290415ec4a25_long << -0xa690c1005d162b03_long
      << -0x9d63a627e48b951fa6c20b90a9ff35d72b25b5b1db368d1a58c6c8f8c267156f_long;
  QTest::newRow("1272476407439720160961303186635554849658599822230148515578 * 16906591606902933389")
      << 0x33e54609465ae20c08c7fb8d9587481c6065df89de0a86fa_long << 0xeaa0477dd40cc78d_long
      << 0x2f900fce587745a99c09577d59311636df0f18dd73977150260aa8e0d670adb2_long;
  QTest::newRow("4278604973647646030213857786077036167654248425788621773585 * 16436711192414808902")
      << 0xae7eb861ca1f10bfb2ff5df0433c75a9263d85b90bb0db11_long << 0xe41aedbe7b926b46_long
      << 0x9b7b3722f8ec42c0060d0192b29b4f812a751a19c1377fcd23a8e038389e01a6_long;
}

void LongIntTest::test_times()
{
  QFETCH(LongInt, left);
  QFETCH(LongInt, right);
  QFETCH(LongInt, result);

  LongInt copy (left);

  QCOMPARE(left * right, result);
  QCOMPARE(left, copy);
  QCOMPARE(copy *= right, result);
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
  QTest::newRow("-7433446392787700936 <=> 0") << -0x6728e81c33050cc8_long << 0x0_long << -1;
  QTest::newRow("-3916848034795325709840999923583121578727890156272934502472 <=> 0")
      << -0x9fbdcd33c30bc331e13b9885086df7cc3fa070fb2e14c048_long << 0x0_long << -1;
  QTest::newRow("18381321359165629095 <=> 0") << 0xff179263435e22a7_long << 0x0_long << 1;
  QTest::newRow("4102156783122958300111092963839145782922880262490028731483 <=> 0")
      << 0xa74c83e29c3aa914e4bfc09b888586014885ff74572b6c5b_long << 0x0_long << 1;
  QTest::newRow("0 <=> -6205233386071991282") << 0x0_long << -0x561d6ae34d3723f2_long << 1;
  QTest::newRow("0 <=> -838999021001489072") << 0x0_long << -0xba4b92a15b1bab0_long << 1;
  QTest::newRow("0 <=> 8495727018856303358") << 0x0_long << 0x75e6e2b61b9e4afe_long << -1;
  QTest::newRow("0 <=> 9340173117149649385") << 0x0_long << 0x819ef5f6b45b99e9_long << -1;
  QTest::newRow("-2791384401818674918 <=> 1") << -0x26bcfd52f5f7e6e6_long << 0x1_long << -1;
  QTest::newRow("-8452061619199920671 <=> 1") << -0x754bc143001fca1f_long << 0x1_long << -1;
  QTest::newRow("-5349486038845554312100679837750988491862167235488580920705 <=> 1")
      << -0xda2b3d80732a5e04b88a57a70c9b5ecc4419a36c5e4c6581_long << 0x1_long << -1;
  QTest::newRow("-4631047458329595967058022473656264794594666406679832066859 <=> 1")
      << -0xbcde6437a69385fb22be433741d4cdc5bfdc1ed3dd9e7b2b_long << 0x1_long << -1;
  QTest::newRow("6202773856519698840 <=> 1") << 0x5614adf573efb998_long << 0x1_long << 1;
  QTest::newRow("7689598229459758310 <=> 1") << 0x6ab6f0d9346bece6_long << 0x1_long << 1;
  QTest::newRow("5592289887625628907850591697807740782839373041492852967645 <=> 1")
      << 0xe4123b0f6c9fec79c612110c7a5bf9dc8fc900dd857788dd_long << 0x1_long << 1;
  QTest::newRow("453693145132494177123179355233921320751912442921703390425 <=> 1")
      << 0x1280c7070b9b88c4c6343049bf26ea8e14e717bb394f3cd9_long << 0x1_long << 1;
  QTest::newRow("-1 <=> -9504292448183843725") << -0x1_long << -0x83e607a02f6cfb8d_long << 1;
  QTest::newRow("-1 <=> -13379729311104168206") << -0x1_long << -0xb9ae58eb6b3ef10e_long << 1;
  QTest::newRow("-1 <=> 10203181070447795269") << -0x1_long << 0x8d98fb1ff307dc45_long << -1;
  QTest::newRow("-1 <=> 6283492326303137658") << -0x1_long << 0x573372faba30ff7a_long << -1;
  QTest::newRow("1 <=> -7574744902174977365") << 0x1_long << -0x691ee65b16572d55_long << 1;
  QTest::newRow("1 <=> -8413301001608944828") << 0x1_long << -0x74c20caf7556dcbc_long << 1;
  QTest::newRow("1 <=> 15879812796213000336") << 0x1_long << 0xdc606d9a71fa7890_long << -1;
  QTest::newRow("1 <=> 3053603033557869885") << 0x1_long << 0x2a6093c7c445a53d_long << -1;
  QTest::newRow("-14215424446584752629 <=> -4888452397126475260") << -0xc5475537b61689f5_long << -0x43d7458e18215dfc_long << -1;
  QTest::newRow("-16201253119979455558 <=> -17439796660660243319") << -0xe0d669dfec908446_long << -0xf2069aa9b1b28b77_long << 1;
  QTest::newRow("-15838355666950832065 <=> 9639551980453871806") << -0xdbcd24905ae63fc1_long << 0x85c6917424ddc0be_long << -1;
  QTest::newRow("-13972570822937564577 <=> 10643579022224847087") << -0xc1e88b22342e55a1_long << 0x93b596ba8682f0ef_long << -1;
  QTest::newRow("-3656767263285094901784180031662625085814993006782482534489 <=> -3630495202591134049")
      << -0x95226e7e8c555c41060ee572f73b2c460a1ba9e53d84d059_long << -0x32621c26cd345161_long << -1;
  QTest::newRow("-3126336463486749724328169504703953066163168213741248192386 <=> -11552823677635733587")
      << -0x7f8079c57fd52e7f1c3ec515576b53a612f2880e105c1f82_long << -0xa053dfece2332853_long << -1;
  QTest::newRow("-6019001339121169921205223887987488290969339233855195758627 <=> 13800264173346138503")
      << -0xf5794e5e83f069b86ecc1b6cb52be04a9a7a0606c57ec023_long << 0xbf84632612d8a987_long << -1;
  QTest::newRow("-679457187550368499944156650356993860465081874353073964722 <=> 2059695194980974843")
      << -0x1bb5dd3162194c8e0fb99dc405a458370405f123e25446b2_long << 0x1c9581ddfa6b80fb_long << -1;
  QTest::newRow("133237498738819773 <=> -4748057805735052907") << 0x1d95acc9716c2bd_long << -0x41e47d6b03dbc66b_long << 1;
  QTest::newRow("6181798449629911337 <=> -5967096057664972213") << 0x55ca28eff7405929_long << -0x52cf623fd9c125b5_long << 1;
  QTest::newRow("2987570399646366455 <=> 8248259393916480147") << 0x2975fb731c64baf7_long << 0x7277b437b5abaa93_long << -1;
  QTest::newRow("4441342556138598598 <=> 14451192731839400043") << 0x3da2d186087770c6_long << 0xc88cf33951fe886b_long << -1;
  QTest::newRow("2631391609743715951949132661204826119221698616159783682594 <=> -1266089614834848176")
      << 0x6b5102a209627afaf7bb0f73525ef7a5830449d5bdf50222_long << -0x11920dcbf20ad1b0_long << 1;
  QTest::newRow("587193959202627892044750648674388905092532897779199163783 <=> -12865100597982774188")
      << 0x17f2974ac96e74c02525236bdf2ea861902cc645ee52bd87_long << -0xb28a04d4e66dc3ac_long << 1;
  QTest::newRow("3123349096065238771297083233389411637155559605320348606378 <=> 7452854165980720978")
      << 0x7f61493dc350c9d7738e10c2708abc567b4eb3c47e781faa_long << 0x676ddb6086122f52_long << 1;
  QTest::newRow("4627472306504126647231937783633447998457192136913471305149 <=> 1753171055171550592")
      << 0xbcb910ad813b429b89bb4cccbfff739fbb00612277f675bd_long << 0x185483c935ff3d80_long << 1;
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
  QTest::newRow("-3413580080205386740 | 0") << -0x2f5f78ff3cfdd3f4_long << 0x0_long << -0x2f5f78ff3cfdd3f4_long;
  QTest::newRow("-1850532422557665143830392715736146867842843507638239538388 | 0")
      << -0x4b7875c0ff2ade51cfe84f19d0f0565380c50c516f60acd4_long << 0x0_long
      << -0x4b7875c0ff2ade51cfe84f19d0f0565380c50c516f60acd4_long;
  QTest::newRow("5908694171349120797 | 0") << 0x51ffe60b11af771d_long << 0x0_long << 0x51ffe60b11af771d_long;
  QTest::newRow("1182269633529041472878130131007662347128275911410638791033 | 0")
      << 0x3037788de74385bb76cd25daf7950a3a04b3b3fb377a2179_long << 0x0_long
      << 0x3037788de74385bb76cd25daf7950a3a04b3b3fb377a2179_long;
  QTest::newRow("0 | -17874648760334258987") << 0x0_long << -0xf80f8257f499932b_long << -0xf80f8257f499932b_long;
  QTest::newRow("0 | -14100265078241457069") << 0x0_long << -0xc3ae3461db6d73ad_long << -0xc3ae3461db6d73ad_long;
  QTest::newRow("0 | 8792093857517917320") << 0x0_long << 0x7a03cac7e93fd488_long << 0x7a03cac7e93fd488_long;
  QTest::newRow("0 | 15890941379105367485") << 0x0_long << 0xdc87f6fd9021a5bd_long << 0xdc87f6fd9021a5bd_long;
  QTest::newRow("-10067326559318901964 | 1") << -0x8bb6542aae0f04cc_long << 0x1_long << -0x8bb6542aae0f04cb_long;
  QTest::newRow("-4854292665184893692 | 1") << -0x435de975b8213afc_long << 0x1_long << -0x435de975b8213afb_long;
  QTest::newRow("-2377689177728122187623542828047324703624598416353965054841 | 1")
      << -0x60f83bb9ce04f304d9385906bdacb2b2cf67a0f896ff1b79_long << 0x1_long
      << -0x60f83bb9ce04f304d9385906bdacb2b2cf67a0f896ff1b79_long;
  QTest::newRow("-996234076469584450160573195707870794783299713129518712242 | 1")
      << -0x28a12b48571c31b44367be067c97001f98b5e048f097c5b2_long << 0x1_long
      << -0x28a12b48571c31b44367be067c97001f98b5e048f097c5b1_long;
  QTest::newRow("3158982255352469975 | 1") << 0x2bd6f59fce0bd9d7_long << 0x1_long << 0x2bd6f59fce0bd9d7_long;
  QTest::newRow("8637860018842691149 | 1") << 0x77dfd7ebfaaae64d_long << 0x1_long << 0x77dfd7ebfaaae64d_long;
  QTest::newRow("4422582466430514884188498894247817782382923622778310040318 | 1")
      << 0xb45dea57ffde27c0a7975a3b09ff7cceea3288e9f4991afe_long << 0x1_long
      << 0xb45dea57ffde27c0a7975a3b09ff7cceea3288e9f4991aff_long;
  QTest::newRow("2089825053762803909098224647318977188875477139063668377255 | 1")
      << 0x553acaa76a2b0d71215bec210e4b14d92a6603c34fb686a7_long << 0x1_long
      << 0x553acaa76a2b0d71215bec210e4b14d92a6603c34fb686a7_long;
  QTest::newRow("-1 | -9630133732990578166") << -0x1_long << -0x85a51b9b8668edf6_long << -0x1_long;
  QTest::newRow("-1 | -11515900197220590744") << -0x1_long << -0x9fd0b2372c2f2498_long << -0x1_long;
  QTest::newRow("-1 | 11925931833240146631") << -0x1_long << 0xa5816bd0e7cd52c7_long << -0x1_long;
  QTest::newRow("-1 | 6041232387994121125") << -0x1_long << 0x53d6c4d95bf973a5_long << -0x1_long;
  QTest::newRow("1 | -15590878226916049194") << 0x1_long << -0xd85ded24b3b4012a_long << -0xd85ded24b3b40129_long;
  QTest::newRow("1 | -864186666425382282") << 0x1_long << -0xbfe3531c7e9f58a_long << -0xbfe3531c7e9f589_long;
  QTest::newRow("1 | 2773588679681251187") << 0x1_long << 0x267dc43585721773_long << 0x267dc43585721773_long;
  QTest::newRow("1 | 3295733957622276076") << 0x1_long << 0x2dbccc92aa449fec_long << 0x2dbccc92aa449fed_long;
  QTest::newRow("-963067768195993058 | -6216772060789273272") << -0xd5d810859f34de2_long << -0x564669405ceaf2b8_long << -0x444010058e240a2_long;
  QTest::newRow("-12752087151499630862 | -17792135994457981404") << -0xb0f883b369f5590e_long << -0xf6ea5d6b911c01dc_long << -0xb0e801230114010a_long;
  QTest::newRow("-13610323907785838258 | 16768353377418387276") << -0xbce1957bc994ceb2_long << 0xe8b5288de13e9f4c_long << -0x14409572088040b2_long;
  QTest::newRow("-4689400015085202689 | 3936477952874555161") << -0x41141877dcdd6d01_long << 0x36a12dd77f3ea719_long << -0x4114102080c14801_long;
  QTest::newRow("-4863497098517400817916754327958899710660734379231331680672 | -6706891065053622595")
      << -0xc65947699d1464f83fbad0f1f44f1101c79d2bcc6e8301a0_long << -0x5d13a9e397c33143_long << -0x451129c006830103_long;
  QTest::newRow("-3972143474679983094822474896716424235775484662263675316883 | -18203522732462538186")
      << -0xa1ff1ce70d5ce71adedb88c72735011d958c30f573036a93_long << -0xfc9fe77a912d7dca_long << -0x948c207011016881_long;
  QTest::newRow("-2202704301565638424040543177806051885577709000846640418128 | 581539553288714212")
      << -0x59d54e52f13321d1528d5dbd607c19dfd92e0b4023f80d50_long << 0x8120b24809cf7e4_long
      << -0x59d54e52f13321d1528d5dbd607c19dfd12c00402360080c_long;
  QTest::newRow("-2183933031729417768399159329492405566874114494322589616711 | 10225738196302264590")
      << -0x59115322ebd59a866f7eb6852bc01898db781cfe58e8ca47_long << 0x8de91eb614bd790e_long
      << -0x59115322ebd59a866f7eb6852bc018985210004848408241_long;
  QTest::newRow("13688517526137475214 | -1625260528414510837") << 0xbdf7622a4722108e_long << -0x168e15d6ef9c4ef5_long << -0x20815d4a89c4e71_long;
  QTest::newRow("391210968486948455 | -790635938858137367") << 0x56ddc4d98e6ae67_long << -0xaf8e7328a4bf717_long << -0xa90233202095111_long;
  QTest::newRow("2355358481423931824 | 1656494888759190581") << 0x20afea0f43fa19b0_long << 0x16fd0d5328bde435_long << 0x36ffef5f6bfffdb5_long;
  QTest::newRow("673217870888599286 | 9167761074293317878") << 0x957c01632c27ef6_long << 0x7f3a6e1fcae820f6_long << 0x7f7fee1ffaea7ef6_long;
  QTest::newRow("1244463704184361125510031337809473885918836917062295338334 | -2731911013190900234")
      << 0x32c0ceabe9b098f8ab827d4505a15474e096f6630d4bbd5e_long << -0x25e9b2979b389a0a_long << -0x569009492300202_long;
  QTest::newRow("3626619622527996759681139088947741253460402946850168181194 | -10509410390426363315")
      << 0x93e7acf1ab57590af4d58560a1106ce7acc66089847311ca_long << -0x91d8ed11a029a5b3_long << -0x11188d102008a431_long;
  QTest::newRow("1075253076569458798359688393393544351699834890981405439216 | 6550964198339535995")
      << 0x2bda2a7a3baa296ffe7a1c4f5fc1f9321067b825684534f0_long << 0x5ae9b33ada54647b_long
      << 0x2bda2a7a3baa296ffe7a1c4f5fc1f9325aefbb3ffa5574fb_long;
  QTest::newRow("5611755396960068288452703984000953412134095333430509783606 | 2436425156316585212")
      << 0xe4dd75c962d4bbb377813862db831991268d13743d994a36_long << 0x21cfebc55c135cfc_long
      << 0xe4dd75c962d4bbb377813862db83199127cffbf57d9b5efe_long;
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
  QTest::newRow("-8603997551557835686 ^ 0") << -0x77678a2fecef7ba6_long << 0x0_long << -0x77678a2fecef7ba6_long;
  QTest::newRow("-4674273654170370112803118216910672016347978769379645600635 ^ 0")
      << -0xbea1b1ab0ddc80b326c8f70eefa09a85ecfbd72bc55a337b_long << 0x0_long
      << -0xbea1b1ab0ddc80b326c8f70eefa09a85ecfbd72bc55a337b_long;
  QTest::newRow("15202854896217482912 ^ 0") << 0xd2fb63fadcd9e6a0_long << 0x0_long << 0xd2fb63fadcd9e6a0_long;
  QTest::newRow("4421345550858898090179902447196469773096303957836777884059 ^ 0")
      << 0xb451005c057df60dcaae754cdab90e4481d4924e1b77899b_long << 0x0_long
      << 0xb451005c057df60dcaae754cdab90e4481d4924e1b77899b_long;
  QTest::newRow("0 ^ -2618472949812591319") << 0x0_long << -0x2456af464b8c7ad7_long << -0x2456af464b8c7ad7_long;
  QTest::newRow("0 ^ -7225648127167358173") << 0x0_long << -0x6446a8b043c6e4dd_long << -0x6446a8b043c6e4dd_long;
  QTest::newRow("0 ^ 3693174994017565593") << 0x0_long << 0x3340cb16fbc5bb99_long << 0x3340cb16fbc5bb99_long;
  QTest::newRow("0 ^ 4481004516778459876") << 0x0_long << 0x3e2fb9dddb8042e4_long << 0x3e2fb9dddb8042e4_long;
  QTest::newRow("-2989577315881378545 ^ 1") << -0x297d1cbab5ace2f1_long << 0x1_long << -0x297d1cbab5ace2f2_long;
  QTest::newRow("-8153756679985235263 ^ 1") << -0x7127f67fff7d053f_long << 0x1_long << -0x7127f67fff7d0540_long;
  QTest::newRow("-3981250164611775988396686488157789253122623160730553274294 ^ 1")
      << -0xa25e30f1286d050bb636dfbcedf968b0421e6f5e4561cfb6_long << 0x1_long
      << -0xa25e30f1286d050bb636dfbcedf968b0421e6f5e4561cfb5_long;
  QTest::newRow("-2283086033940848134790387494524834861901026857820070106445 ^ 1")
      << -0x5d1c87c81857ecf6f436eaee771f50f91b5d9b2c4dcc554d_long << 0x1_long
      << -0x5d1c87c81857ecf6f436eaee771f50f91b5d9b2c4dcc554e_long;
  QTest::newRow("15168340561063924960 ^ 1") << 0xd280c55ffe5d54e0_long << 0x1_long << 0xd280c55ffe5d54e1_long;
  QTest::newRow("3393278092021045401 ^ 1") << 0x2f17587243079899_long << 0x1_long << 0x2f17587243079898_long;
  QTest::newRow("1455950412125603839258230302396733728046101687745778631326 ^ 1")
      << 0x3b60d4e194962e8ebf78ef29577c16957164d300d51d429e_long << 0x1_long
      << 0x3b60d4e194962e8ebf78ef29577c16957164d300d51d429f_long;
  QTest::newRow("4940911167693025008376896941689491458182294453618589530700 ^ 1")
      << 0xc981850134b2639f551553fc9d278390cd3ff3f849337a4c_long << 0x1_long
      << 0xc981850134b2639f551553fc9d278390cd3ff3f849337a4d_long;
  QTest::newRow("-1 ^ -12258162606541045113") << -0x1_long << -0xaa1dbdf1b1dafd79_long << 0xaa1dbdf1b1dafd78_long;
  QTest::newRow("-1 ^ -11751144626779066379") << -0x1_long << -0xa31473c71f68100b_long << 0xa31473c71f68100a_long;
  QTest::newRow("-1 ^ 10336185798654827023") << -0x1_long << 0x8f7182386d421a0f_long << -0x8f7182386d421a10_long;
  QTest::newRow("-1 ^ 13583975286663114334") << -0x1_long << 0xbc83f98d5f3d6e5e_long << -0xbc83f98d5f3d6e5f_long;
  QTest::newRow("1 ^ -15952528839557447333") << 0x1_long << -0xdd62c4759efefea5_long << -0xdd62c4759efefea6_long;
  QTest::newRow("1 ^ -1299999126015839418") << 0x1_long << -0x120a8651427e0cba_long << -0x120a8651427e0cb9_long;
  QTest::newRow("1 ^ 5268419008616762250") << 0x1_long << 0x491d2f2cd0848b8a_long << 0x491d2f2cd0848b8b_long;
  QTest::newRow("1 ^ 10212376431432782395") << 0x1_long << 0x8db9a641c41f523b_long << 0x8db9a641c41f523a_long;
  QTest::newRow("-84317474259260727 ^ -2456892631577022651") << -0x12b8e4bcd94d537_long << -0x2218a2d4cc6c50bb_long << 0x23332c9f01f8858c_long;
  QTest::newRow("-8902320158592718913 ^ -6854186661139988491") << -0x7b8b650489b7d841_long << -0x5f1ef6740978400b_long << 0x2495937080cf984a_long;
  QTest::newRow("-12320937636392750223 ^ 4207751434545052451") << -0xaafcc3804cee4c8f_long << 0x3a64efa2d732bb23_long << -0x90982c229bdcf7ae_long;
  QTest::newRow("-7396707225681623918 ^ 16785048439456626087") << -0x66a6620846517b6e_long << 0xe8f0789feb8975a7_long << -0x8e561a97add80ecb_long;
  QTest::newRow("-2576437546688356775959885131042723452452921128574280168241 ^ -17242870445462992043")
      << -0x6913435a4066316e923fe5259153684e36f3f81bf87e7331_long << -0xef4afb5041e734ab_long
      << 0x6913435a4066316e923fe5259153684ed9b9034bb999479a_long;
  QTest::newRow("-1248494136808268490815898601189319076131879577399957434696 ^ -1664383837058270450")
      << -0x32eae311d27edee1c4547a8b6de228e42bc889b01398b148_long << -0x1719144811c284f2_long
      << 0x32eae311d27edee1c4547a8b6de228e43cd19df8025a35b6_long;
  QTest::newRow("-1683485113523749722965898267362488499250703721571903109428 ^ 1963732587696480538")
      << -0x44a86799f4d0aa8a27edb4a6fbf1a46c33a83afcab987934_long << 0x1b4094625b81e11a_long
      << -0x44a86799f4d0aa8a27edb4a6fbf1a46c28e8ae9ef019982a_long;
  QTest::newRow("-6018403841259318471570106728497742217541626705781335539706 ^ 1104682734274614113")
      << -0xf5731165e3686b5fe654ca01d6f28c83c2108261f5243ffa_long << 0xf549f180df21361_long
      << -0xf5731165e3686b5fe654ca01d6f28c83cd441d79f8d62c99_long;
  QTest::newRow("11822858139164284203 ^ -16631018651280244987") << 0xa4133ad65eb9152b_long << -0xe6cd3f59327480fb_long << -0x42de058f6ccd95d2_long;
  QTest::newRow("12913471991235940523 ^ -11601952053627350178") << 0xb335de5b869310ab_long << -0xa10269ec49926ca2_long << -0x1237b7b7cf017c0b_long;
  QTest::newRow("12697166898646719677 ^ 10263321585392213783") << 0xb035660597af9cbd_long << 0x8e6ea49ac0e6df17_long << 0x3e5bc29f574943aa_long;
  QTest::newRow("11689206232059433682 ^ 16827582591267690316") << 0xa2386722d02f52d2_long << 0xe9879535dd0ed74c_long << 0x4bbff2170d21859e_long;
  QTest::newRow("2701832243124887603456211931721562234402332442960494012595 ^ -755331494797938890")
      << 0x6e3071df3c45c910fdccdeb1696780385bbab1706b9b28b3_long << -0xa7b79fe1b1890ca_long
      << -0x6e3071df3c45c910fdccdeb16967803851c1c88e7083b87b_long;
  QTest::newRow("5162874404709242209089514490689646182695336438234624366318 ^ -10447700602074846136")
      << 0xd28eec82f49ee30c6cea43b55d3e81fa982fd4459be116ee_long << -0x90fdb057e24e53b8_long
      << -0xd28eec82f49ee30c6cea43b55d3e81fa08d2641279af455a_long;
  QTest::newRow("5786329409342291147573611741761292686236098292393201619798 ^ 12751980473750017115")
      << 0xebfc190bd79c1be5ce21b080c1bbe9ed4879cc9499d7d356_long << 0xb0f822ad9096545b_long
      << 0xebfc190bd79c1be5ce21b080c1bbe9edf881ee390941870d_long;
  QTest::newRow("1303298692865913653154771862620537576688121729027537855036 ^ 14900263971564101836")
      << 0x352712c0c4b17aaaead3d39059907c30edc74be8b2ff623c_long << 0xcec85f231ca120cc_long
      << 0x352712c0c4b17aaaead3d39059907c30230f14cbae5e42f0_long;
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
  QTest::newRow("-15670298588721883065 & 0") << -0xd978158aa912a7b9_long << 0x0_long << 0x0_long;
  QTest::newRow("-600647477663539967992302883309826891145538758903723652605 & 0")
      << -0x187f0d61aa4fca195fde010cbf187f7de0bde6523c8af5fd_long << 0x0_long << 0x0_long;
  QTest::newRow("3924578402730899935 & 0") << 0x3676e74393f1f9df_long << 0x0_long << 0x0_long;
  QTest::newRow("1888378446203240364261727702095736395263385481654202210977 & 0")
      << 0x4d0397453315eac847a446e0f31b4f1c6cc7d13f9ac31aa1_long << 0x0_long << 0x0_long;
  QTest::newRow("0 & -5256479517783279828") << 0x0_long << -0x48f2c4457a96c8d4_long << 0x0_long;
  QTest::newRow("0 & -13267926864176258729") << 0x0_long << -0xb821252fbd169ea9_long << 0x0_long;
  QTest::newRow("0 & 10452790358559442248") << 0x0_long << 0x910fc57329904548_long << 0x0_long;
  QTest::newRow("0 & 10899755335229737795") << 0x0_long << 0x9743b5ba5f098b43_long << 0x0_long;
  QTest::newRow("-9067180308788237253 & 1") << -0x7dd518736bbd53c5_long << 0x1_long << 0x1_long;
  QTest::newRow("-7129410802511583209 & 1") << -0x62f0c15a058917e9_long << 0x1_long << 0x1_long;
  QTest::newRow("-5968731982736993286074950396753098454803218788362782061327 & 1")
      << -0xf36c78351bf89dacf7c45720d0449f166206127f3d09330f_long << 0x1_long << 0x1_long;
  QTest::newRow("-3954014250554644426268362079914822251392526425680703799121 & 1")
      << -0xa141d5c088954d7ebf4bf998027973e0f799ab1cb0fe3f51_long << 0x1_long << 0x1_long;
  QTest::newRow("7716554223818071891 & 1") << 0x6b16b52eb8b75f53_long << 0x1_long << 0x1_long;
  QTest::newRow("8611551060690981159 & 1") << 0x77826010519fd127_long << 0x1_long << 0x1_long;
  QTest::newRow("4234825756392355705636956740746779056514444736450361900231 & 1")
      << 0xacb5a4d5c779471aae348c38ee8ebaf43ca266bec3453cc7_long << 0x1_long << 0x1_long;
  QTest::newRow("2187985784486867500231338262138827857637882159146325767622 & 1")
      << 0x593ba330e2bf486acb10a73c284c588a3e42a25d4c8ff5c6_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 & -4364419405525965517") << -0x1_long << -0x3c9188535d325acd_long << -0x3c9188535d325acd_long;
  QTest::newRow("-1 & -10566216424585889850") << -0x1_long << -0x92a2bddb1f57083a_long << -0x92a2bddb1f57083a_long;
  QTest::newRow("-1 & 3173592943220019252") << -0x1_long << 0x2c0addf7aa50d034_long << 0x2c0addf7aa50d034_long;
  QTest::newRow("-1 & 7967709903571677446") << -0x1_long << 0x6e92fdf14bc07106_long << 0x6e92fdf14bc07106_long;
  QTest::newRow("1 & -6950698307778908095") << 0x1_long << -0x6075d748d8120fbf_long << 0x1_long;
  QTest::newRow("1 & -3593234100751441729") << 0x1_long << -0x31ddbb607a1c1f41_long << 0x1_long;
  QTest::newRow("1 & 6704321077637820124") << 0x1_long << 0x5d0a887fc4c42edc_long << 0x0_long;
  QTest::newRow("1 & 17137741926475561888") << 0x1_long << 0xedd57d7b83e4fba0_long << 0x0_long;
  QTest::newRow("-9720686377928885429 & -3196221224352612023") << -0x86e6d0c2216e04b5_long << -0x2c5b4244ed19feb7_long << -0xaeffd2c6ed7ffeb7_long;
  QTest::newRow("-1617798658134702826 & -17642239367037562409") << -0x1673934ee038faea_long << -0xf4d5d33b52afae29_long << -0xf6f7d37ff2bffeea_long;
  QTest::newRow("-1832803740342586923 & 18410750799723288925") << -0x196f6d4a8e208e2b_long << 0xff80204ed9bed95d_long << 0xe6800004519e5155_long;
  QTest::newRow("-9341379514574999781 & 7216120880801757696") << -0x81a33f2cfe5a90e5_long << 0x6424cfb55c77ba00_long << 0x6404c09100252a00_long;
  QTest::newRow("-4345035386382511928849829680475486584364359459754792866118 & -12791422160902709745")
      << -0xb134493eacd9ab35b004b8267312a745f17ef36210aa5146_long << -0xb18442aef8aa61f1_long
      << -0xb134493eacd9ab35b004b8267312a745f1fef3eef8aa71f6_long;
  QTest::newRow("-839932721666697618983372617189914527586727153432193143603 & -16960447814253643265")
      << -0x22414e898df6a2db15d54f655d4124fa637bf4b0775c1333_long << -0xeb5f9d6d40238601_long
      << -0x22414e898df6a2db15d54f655d4124faeb7ffdfd777f9733_long;
  QTest::newRow("-4916163747593679598364507038717983872069851782766206198109 & 10584922083244333180")
      << -0xc87f24f93e0b8be2e830f2b8f65a750721738eb2a379215d_long << 0x92e5328daaf7587c_long << 0x9284300d08865820_long;
  QTest::newRow("-6047612182861790519146272603012869166966840548834990019222 & 10239293045635768778")
      << -0xf6a4046c348904f2ddf4344981f3a9d89a05e6716a0ad296_long << 0x8e1946c6603f61ca_long << 0x41800860035214a_long;
  QTest::newRow("3569538934626204248 & -6513553279232716040") << 0x31898cbfb2523a58_long << -0x5a64ca327a3f2d08_long << 0x2189048d80401258_long;
  QTest::newRow("1658070927207093440 & -17959852872712425516") << 0x1702a6b93494d4c0_long << -0xf93e3708484d902c_long << 0x60080b1349044c0_long;
  QTest::newRow("11869153245365929620 & 8391306601435437352") << 0xa4b7b3fdbeb60694_long << 0x7473e8e51bf31928_long << 0x2433a0e51ab20000_long;
  QTest::newRow("503908362806965414 & 9826741678793903648") << 0x6fe3dfc747534a6_long << 0x885f997e18094e20_long << 0x5e197c10010420_long;
  QTest::newRow("1840386830318219459596287370489100402089938186934305671423 & -5533369387046478309")
      << 0x4b0e88f916113c5f0a751aa167dcdeef2e60a3e91d37c8ff_long << -0x4cca7a23f5ed21e5_long
      << 0x4b0e88f916113c5f0a751aa167dcdeef222081c80812c81b_long;
  QTest::newRow("1268449317006545698433059583536418003240298266569874505271 & -13687764257802232056")
      << 0x33bb3a922f64567b7a2090809c5b6e440c85e7f85d5e7e37_long << -0xbdf4b512539720f8_long
      << 0x33bb3a922f64567b7a2090809c5b6e44000142e80c485e00_long;
  QTest::newRow("2160462107795462154838756818586356543814155628395266103757 & 11287713722845038638")
      << 0x581c46e113b7a1ef5459d22a0213aee3be0d126c5a24d9cd_long << 0x9ca603d3787b082e_long << 0x9c0402405820080c_long;
  QTest::newRow("3931019910041251249145498631126280774870663906526535311523 & 16121720161611140101")
      << 0xa051c34a4c62bfe5c2bdc85849e69046746a248be3cb60a3_long << 0xdfbbdb120915cc05_long << 0x542a000201014001_long;
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
  QTest::newRow("0 % -405823407613130678") << 0x0_long << -0x5a1c63d3451b7b6_long << 0x0_long;
  QTest::newRow("0 % -16517468880886533346") << 0x0_long << -0xe539d66f11cf8ce2_long << 0x0_long;
  QTest::newRow("0 % 4291256771409825955") << 0x0_long << 0x3b8d9b4c2bdf50a3_long << 0x0_long;
  QTest::newRow("0 % 13268409325174376791") << 0x0_long << 0xb822dbfb717fc957_long << 0x0_long;
  QTest::newRow("-16284865777935084524 % 1") << -0xe1ff7724e4bc6bec_long << 0x1_long << 0x0_long;
  QTest::newRow("-2211006656604634387 % 1") << -0x1eaf12d6faf17d13_long << 0x1_long << 0x0_long;
  QTest::newRow("-12298161994519397524 % 1") << -0xaaabd92cf189c494_long << 0x1_long << 0x0_long;
  QTest::newRow("-5003965936858457464 % 1") << -0x4571a881e69a6578_long << 0x1_long << 0x0_long;
  QTest::newRow("9879375206665013487 % 1") << 0x891a97684411c8ef_long << 0x1_long << 0x0_long;
  QTest::newRow("5327887887742050175 % 1") << 0x49f075ce37f89f7f_long << 0x1_long << 0x0_long;
  QTest::newRow("5150239974996999499 % 1") << 0x477953f859b67d4b_long << 0x1_long << 0x0_long;
  QTest::newRow("17795184224699223844 % 1") << 0xf6f531c4f9d50f24_long << 0x1_long << 0x0_long;
  QTest::newRow("-1 % -17584270566299300226") << -0x1_long << -0xf407e0ea22a07182_long << -0x1_long;
  QTest::newRow("-1 % -357971599346565769") << -0x1_long << -0x4f7c545e2bb0289_long << -0x1_long;
  QTest::newRow("-1 % 12625782440719264078") << -0x1_long << 0xaf37ca3c4e6fa94e_long << -0x1_long;
  QTest::newRow("-1 % 2187213378224405549") << -0x1_long << 0x1e5a8afaa90c3c2d_long << -0x1_long;
  QTest::newRow("1 % -9937664935463557097") << 0x1_long << -0x89e9ad9b572917e9_long << 0x1_long;
  QTest::newRow("1 % -9271758423305023897") << 0x1_long << -0x80abe7298054f199_long << 0x1_long;
  QTest::newRow("1 % 15558839454098147228") << 0x1_long << 0xd7ec1a0c9ada479c_long << 0x1_long;
  QTest::newRow("1 % 11929620833032358244") << 0x1_long << 0xa58e86f119fe4964_long << 0x1_long;
  QTest::newRow("-13392848531999358540 % -1368058643655929158") << -0xb9dcf4c8106efe4c_long << -0x12fc52168f03ad46_long << -0xefe11fd094de6d6_long;
  QTest::newRow("-4210904419323458287 % -9781595684031370587") << -0x3a70234250e5b2ef_long << -0x87bf3573132f155b_long << -0x3a70234250e5b2ef_long;
  QTest::newRow("-598151325763723419 % 1020373737320456671") << -0x84d0f762e13609b_long << 0xe291882071fa1df_long << -0x84d0f762e13609b_long;
  QTest::newRow("-15309920522540043654 % 5758715275687250990") << -0xd477c3998d764d86_long << 0x4feb110841f44c2e_long << -0x34a1a189098db52a_long;
  QTest::newRow("-11393012636487303073 % -14923073107302883559") << -0x9e1c1ca14f5cbfa1_long << -0xcf1967ecddf920e7_long << -0x9e1c1ca14f5cbfa1_long;
  QTest::newRow("-12610259012224677057 % -15566072070042517718") << -0xaf00a3c27551f4c1_long << -0xd805cc133b0380d6_long << -0xaf00a3c27551f4c1_long;
  QTest::newRow("-15784215627504601925 % 4436144436216594703") << -0xdb0ccc7c1f94cb45_long << 0x3d9059dc6d04010f_long << -0x225bbee6d888c818_long;
  QTest::newRow("-7980642972880512833 % 15675367153726470642") << -0x6ec0f08025c2a741_long << 0xd98a175fe9b139f2_long << -0x6ec0f08025c2a741_long;
  QTest::newRow("17772212140751683744 % -9992318743029002202") << 0xf6a394c7e26380a0_long << -0x8aabd8f488b8afda_long << 0x6bf7bbd359aad0c6_long;
  QTest::newRow("1158230010263216923 % -9209675406940811449") << 0x1012dc0ec9efa31b_long << -0x7fcf56fcd75bb0b9_long << 0x1012dc0ec9efa31b_long;
  QTest::newRow("4821482381955149626 % 13895792881459755779") << 0x42e958ae5b3daf3a_long << 0xc0d7c600abcf7b03_long << 0x42e958ae5b3daf3a_long;
  QTest::newRow("13484598135120654428 % 96450108530615094") << 0xbb22ea8f36c2f05c_long << 0x156a8dcd983e336_long << 0x1153aa51c26920a_long;
  QTest::newRow("4052206970209628979 % -2882384402263082749") << 0x383c54c517b4f333_long << -0x28004957a30486fd_long << 0x103c0b6d74b06c36_long;
  QTest::newRow("1510107612471131316 % -14788488308185870091") << 0x14f4fadf65f47cb4_long << -0xcd3b43c3766faf0b_long << 0x14f4fadf65f47cb4_long;
  QTest::newRow("14460411415281715798 % 7832655952581095953") << 0xc8adb39151deca56_long << 0x6cb32f16f571f211_long << 0x5bfa847a5c6cd845_long;
  QTest::newRow("11812320892050978022 % 17192227681638012394") << 0xa3edcb44579fb4e6_long << 0xee970ffcf5abd5ea_long << 0xa3edcb44579fb4e6_long;
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
  QTest::newRow("0 / -12910855890363583806") << 0x0_long << -0xb32c930713618d3e_long << 0x0_long;
  QTest::newRow("0 / -15016963187891617614") << 0x0_long << -0xd066f874c365bf4e_long << 0x0_long;
  QTest::newRow("0 / 12262188285032303930") << 0x0_long << 0xaa2c0b47024e8d3a_long << 0x0_long;
  QTest::newRow("0 / 4651839658395281951") << 0x0_long << 0x408ea785d6b9aa1f_long << 0x0_long;
  QTest::newRow("-3198960543863746244 / 1") << -0x2c64fdaa737d2ec4_long << 0x1_long << -0x2c64fdaa737d2ec4_long;
  QTest::newRow("-15702475939876952729 / 1") << -0xd9ea66ac0a7bda99_long << 0x1_long << -0xd9ea66ac0a7bda99_long;
  QTest::newRow("-15914783881276261049 / 1") << -0xdcdcab9eb09582b9_long << 0x1_long << -0xdcdcab9eb09582b9_long;
  QTest::newRow("-7113253130881649089 / 1") << -0x62b75a08efa2c9c1_long << 0x1_long << -0x62b75a08efa2c9c1_long;
  QTest::newRow("1421717351730791209 / 1") << 0x13baf46618ec4329_long << 0x1_long << 0x13baf46618ec4329_long;
  QTest::newRow("2128320921615985881 / 1") << 0x1d89509a14f3ecd9_long << 0x1_long << 0x1d89509a14f3ecd9_long;
  QTest::newRow("8298776798951182793 / 1") << 0x732b2d87a3bd11c9_long << 0x1_long << 0x732b2d87a3bd11c9_long;
  QTest::newRow("8562511912117968124 / 1") << 0x76d42737cad79cfc_long << 0x1_long << 0x76d42737cad79cfc_long;
  QTest::newRow("-1 / -524967367272892474") << -0x1_long << -0x7490f0a04f9083a_long << 0x0_long;
  QTest::newRow("-1 / -11108355326318322760") << -0x1_long << -0x9a28ce509005a448_long << 0x0_long;
  QTest::newRow("-1 / 12306623034076662601") << -0x1_long << 0xaac9e8723ac78b49_long << 0x0_long;
  QTest::newRow("-1 / 126152579662257185") << -0x1_long << 0x1c02f1a52449c21_long << 0x0_long;
  QTest::newRow("1 / -7982870147896260314") << 0x1_long << -0x6ec8da1abd6d36da_long << 0x0_long;
  QTest::newRow("1 / -15299942815137547456") << 0x1_long << -0xd45450ed841044c0_long << 0x0_long;
  QTest::newRow("1 / 13345648434604498816") << 0x1_long << 0xb935448b01d95f80_long << 0x0_long;
  QTest::newRow("1 / 16079152945798644744") << 0x1_long << 0xdf24a069c7810408_long << 0x0_long;
  QTest::newRow("-12702562784938264306 / -11385979311966573909") << -0xb048918d455786f2_long << -0x9e031fdbd5b6d555_long << 0x1_long;
  QTest::newRow("-10001021099654845390 / -7808519871451711281") << -0x8acac3b3d41d13ce_long << -0x6c5d6f73a7754731_long << 0x1_long;
  QTest::newRow("-1963249494747022985 / 7705587292315681978") << -0x1b3edd0383dc8689_long << 0x6aefbed1003d84ba_long << 0x0_long;
  QTest::newRow("-7704688411427306024 / 974370719769230980") << -0x6aec8d49fc317a28_long << 0xd85a901d762fe84_long << -0x7_long;
  QTest::newRow("-4571492659268899830 / -12877461864463094259") << -0x3f71345a510753f6_long << -0xb2b5ef5687f651f3_long << 0x0_long;
  QTest::newRow("-3435255966931740915 / -12545849951663695941") << -0x2fac7b19e581e8f3_long << -0xae1bd00f6e442845_long << 0x0_long;
  QTest::newRow("-7805254629024726743 / 2451837788340678406") << -0x6c51d5bb287dfed7_long << 0x2206ad7a64ecef06_long << -0x3_long;
  QTest::newRow("-14876727849657663450 / 13134549412462809764") << -0xce74c128b3017fda_long << 0xb6474b19cea952a4_long << -0x1_long;
  QTest::newRow("2002488143380922210 / -10346924407351082675") << 0x1bca445b5526bf62_long << -0x8f97a8ed99fafeb3_long << 0x0_long;
  QTest::newRow("1523375667916929695 / -10088102664611421725") << 0x15241e1949a97a9f_long << -0x8c0023eca5d5de1d_long << 0x0_long;
  QTest::newRow("15957811649217316141 / 2437947907448299228") << 0xdd7589259830452d_long << 0x21d554b47c5cdedc_long << 0x6_long;
  QTest::newRow("11480178150533023850 / 9667800295894020008") << 0x9f51c9340cb8c86a_long << 0x862aed259c2defa8_long << 0x1_long;
  QTest::newRow("3185111713880116658 / -3997686893284266977") << 0x2c33ca3a73c28db2_long << -0x377aa30c7d7193e1_long << 0x0_long;
  QTest::newRow("17395203522380943254 / -12533604503561021351") << 0xf1682d709b23cf96_long << -0xadf04ee3ddfda7a7_long << -0x1_long;
  QTest::newRow("8787255858883410374 / 3376298580491944405") << 0x79f29aa5933739c6_long << 0x2edb05aba9e0c1d5_long << 0x2_long;
  QTest::newRow("9210450322176786449 / 14669604239589476158") << 0x7fd217c4dabac011_long << 0xcb94e755404b873e_long << 0x0_long;
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
  QTest::newRow("-8 ** 0") << -0x8_long << 0 << 0x1_long;
  QTest::newRow("-254230657505071512165390826838 ** 0") << -0x33576abc6f888cb11e2213d56_long << 0 << 0x1_long;
  QTest::newRow("136 ** 0") << 0x88_long << 0 << 0x1_long;
  QTest::newRow("1100623872752245241473013021812 ** 0") << 0xde44ebab05ea39b8bb8e27c74_long << 0 << 0x1_long;
  QTest::newRow("0 ** 47") << 0x0_long << 47 << 0x0_long;
  QTest::newRow("-132 ** 1") << -0x84_long << 1 << -0x84_long;
  QTest::newRow("-764840257146768848493089153439 ** 1") << -0x9a755084c251a47382254619f_long << 1 << -0x9a755084c251a47382254619f_long;
  QTest::newRow("40 ** 1") << 0x28_long << 1 << 0x28_long;
  QTest::newRow("771582464404784157532897109693 ** 1") << 0x9bd1e0e37f82548f1861766bd_long << 1 << 0x9bd1e0e37f82548f1861766bd_long;
  QTest::newRow("-1 ** 74") << -0x1_long << 74 << 0x1_long;
  QTest::newRow("1 ** 65") << 0x1_long << 65 << 0x1_long;
  QTest::newRow("-183 ** 28") << -0xb7_long << 28
      << 0x56cc5fb74ae691b0372d8111ddf7f6de160203d64035826e5ba61_long;
  QTest::newRow("-456489328980026504574150954405 ** 94") << -0x5c2ff1f6dd46a156ce000cda5_long << 94
      << 0x2cf61afc0c46ee4548b03876cc2587f40048d0981f79dfc7d67196f7b29bd72cac14eb55c8ffc54c96f5c71c6cb9de01c015e8f5a1a2098574463a71b4d2baba3ccb9c7bbe897953dd2c539b45beb7e7235fddadc34c567cbd4b36d8e4967cf6d2e0c72787cf04af04f8a2d5a8f11ffa9e7d357540911e8df9b47c5926a2c7c9c817b88c48f8ef061d5d7d9e42213c09510da04bfef19b14990230bd36dae7dd5025a06777c547de9b3930dcec0bbe210cbae6b951918a597869088382875ab8312d991f416eb6d6d68866d3592a1c1cb7bf7d84cd91016ff987241f1581c5cb054ab6c09f7c83fc1d0789d1c8fe7fbfe159424016f2c8db2ca79052327cb344aa8dd52f878b137c8858c90cedb908fb01f54a6f60d2848414ba4cc734ed11a58d022f2298d997ec5fca5881998fc2a7b09b9af2c16d3e217eab49a181be9287b11e4f2f3cb63b2e3cec9e75876a434f0bdee841237be037b72ba75a40125f5238d2f9b440e365b23614773c45b8948bea9d13a9f6dd73cbdd12cd6ed3e8d9f3bc1005be80ddebe75977831f6817fd77b239571d2339feb77d50c29b0738d9146b5602d13f55a48806fb8f355365902c0aea367eaa1f688d5e7e43e1098f8ca862e416053cbbd4e47e75e279ee78a7be7126a9d39c9f5bc18eb6857aa539e2c63366f4d6cf8ad1d1fde055a3992cb5112170c6b0f678bf817c801d2ea6917ded6fbdba5f67c10a68e4ae52db563546bc39e611d3d5737fbf52bb62fdf567017f13ea065c53898e72f54ae84f480556777acb91463270d0a3423c3559dfe9b90ad069677fc6691ba9fb67ab5c5bda534aa104ba198ea3043e901f0c2be3ba424e101a630fd89cf9a69d951362449630576f9f0e9e2bc303056b22b6c5b51016723668375898d3f6c8f783f591d1aa0496b8e8bf3cbad0c0a8f2b000455d1485b09347666e6acf91a881db37e0cf37f902af1a009a75522de230e60e74feff4f12039cc1d1b3607b34432390adfd1d6dc9b15437b9ed88d15e3f81051faf6c12ec58a1d47a97cebc72485ca90a45ebe972ad73705f454bc774c0c8bfb04c445235d73dbf149208556ed115dda7a4ca7cd734bc25f16d48f92b255157b39dd54002e920fedaccd519871f10243fa82044f32c2d11a3fe18ef72eca77c45fb5a8fed0effe4921ccaee4e97fbdf790c1fd438fb14e24d9dea8f89f6f1ec4c70cd3f16e78c9a1305e8be55033e2ae70639fefc2ce2ee7b95ddbaa34f263dbf78471139f69ffd29507ce290d2969df7d090bb9fe7a34b306f6b3a29810d150bc7c1a92cae3dd12111789fac56b75efc691f6e060e7943dbf8d3398085b8ed4a1d954360e888be11eff613b6d91d4fd1e00bca4eb535b18df14dc3c97f78951db6126a5df24b1100219446ad4e5c21d294d4f53542798554eaf279c746bc3ef39dfbec8720f0945b24edb4458d989598c5e9fce82cafc0b60058913cb99a9844dde13c5b8043641ff1cfe71af0ef0e6f5e0670557f038fc13438af5b1b7279240fb6ec4adaa01f7c61a1ea86cd83671fc856c13f71b41c20da129cc66f3bb30d0f44a66d33ee764345485fbb998e9faf63a2bcb4c4de92163ca559579045640eb15d2ecbb01e0dcb9a69_long;
  QTest::newRow("154 ** 84") << 0x9a_long << 84
      << 0x550a3c6247a2a57965c3d27484b96b39d745329c7146c574314d1a98fa6edc2d6d9a71c8cb039863ea40458b5acc0ed2f0626c5778ed7e2b9ec1e2fcb52274cad1d1000000000000000000000_long;
  QTest::newRow("653606520778706972257405867201 ** 47") << 0x83feaa468f2c4194b8da394c1_long << 47
      << 0x87a8cd67f785b6d4db0e5dca71ddb1c3bf5181ec4373e0411320a12ba58603adc653b6c3b7c02cb67f003d0751e2d36640506e9a8391c0556d7276eb14ff97267e8fb02cda37f92ab4b94ea05fc261b6c7c533881fe2cab46bc82db42c4d4dc45ccd1f97c8f7a2199ea8e95fc48df3a79f88de2b3a38cebfce46588dc2273c5c2cbfb3898c661a2090eb75dd87ec49c0e43b273602d1b95cc8aa5c9885de0e9670b829fece066141993d8e2b763a62ee27e18c688a204a02e7e1dcaff3b0d4051e988f1d0135edee0d22712587c44c4a615fc8c8a6db696a62ee245914969968437c10ce3ca0179c68f58766a441ab38a28b9c1f2dff5c24c86fd7fd91fce9fe70a4048ecf9b11e4b79d3c2e05ef89017701664e28c8302e46b33b83972f8a7f0078714453bd430d346367d9fa0144791d06368a5ac2222ff65e1acfb557f7e8b6d2a22a8fd9a74fe0a00a4f43898fc788e1303ec44901ecff014bce5102b2207695e44d6b0e311bb9eb4e490026eb470556ee403b4d4bb65f5f39814c82c6f8dc0bdd8bd001b91b626937e3e32bb29008bf2a8fae9d473ad95d2206a0795496873fcfb8e1253cbb44d2a8cbb50e424255c20a644604d192d1c580ed559c19e737df49dcdbb74352ed706ae5d3fd248c20f4c7d00e0e4e3b205905b8b9582d567b5e902df96acb1208deb9cf2833e93dcbc9b9a5f6f32dd5be8850b433af797691b84439cda007dc7f801d74e8e5da6e707f6ee55a084a7bfcb0440e367ba9b63a050082d07fa821656a2fbbc404fb260ffbf42b2e8101a5169fd5892bcebbf89448545a5f41_long;
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



