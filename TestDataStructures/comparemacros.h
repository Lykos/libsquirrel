#ifndef COMPAREMACROS_H
#define COMPAREMACROS_H

#include <QtTest/QtTest>

#define COMPARE_SIZE(list, expected_size) QCOMPARE((unsigned long int) (list).size(), (unsigned long int) (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((unsigned long int) (actual), (unsigned long int) (expected))

#endif // COMPAREMACROS_H
