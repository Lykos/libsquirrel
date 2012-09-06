#ifndef COMPAREMACROS_H
#define COMPAREMACROS_H

#include <QtTest/QtTest>

#define COMPARE_SIZE(list, expected_size) QCOMPARE((int) (list).size(), (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((int) (actual), (int) (expected))

#endif // COMPAREMACROS_H
