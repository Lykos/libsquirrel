#include "queuetest.h"
#include "DataStructures/preconditionviolation.h"
#include "comparemacros.h"
#include <QtTest/QtTest>
#include <iostream>
#include <deque>
#include <vector>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace DataStructures;
using namespace std;
using namespace boost;

void QueueTest::test_random_queueing()
{
  typedef size_t size_type;
  random::uniform_int_distribution<int> elem_dist (0, 100);
  random::uniform_int_distribution<int> op_dist (0, 6);
  random::mt19937_64 rng;
  deque<int> expected (100, 34);
  Queue<int> actual (size_type(100), 34);
  for (int i = 0; i < 1000; ++i) {
    int operation = op_dist(rng);
    if (operation == 0) {
      for (int i = 0; i < 20; ++i) {
        int elem = elem_dist(rng);
        expected.push_back(elem);
        actual.push_back(elem);
      }
    } else if (operation == 1 && expected.size() >= 15) {
      for (int i = 0; i < 15; ++i) {
        QCOMPARE(actual.back(), expected.back());
        expected.pop_back();
        actual.pop_back();
      }
    } else if (operation == 2) {
      for (int i = 0; i < 20; ++i) {
        int elem = elem_dist(rng);
        expected.push_front(elem);
        actual.push_front(elem);
      }
    } else if (operation == 3 && expected.size() >= 15) {
      for (int i = 0; i < 15; ++i) {
        QCOMPARE(actual.front(), expected.front());
        expected.pop_front();
        actual.pop_front();
      }
    } else if (operation == 4) {
      random::uniform_int_distribution<size_type> start_dist (0, expected.size() - 1);
      size_type start = start_dist(rng);
      random::uniform_int_distribution<size_type> end_dist (start, expected.size() - 1);
      size_type end = end_dist(rng);
      expected.erase(expected.begin() + start, expected.begin() + end);
      actual.erase(start, end);
    } else if (operation == 5) {
      random::uniform_int_distribution<size_type> start_dist (0, expected.size() - 1);
      size_type start = start_dist(rng);
      random::uniform_int_distribution<size_type> length_dist (5, 20);
      size_type length = length_dist(rng);
      int elem = elem_dist(rng);
      expected.insert(expected.begin() + start, length, elem);
      actual.insert(start, length, elem);
    } else {
      random::uniform_int_distribution<size_type> start_dist (0, expected.size() - 1);
      size_type start = start_dist(rng);
      random::uniform_int_distribution<size_type> length_dist (5, 20);
      size_type length = length_dist(rng);
      vector<int> elems (length);
      for (size_type i = 0; i < length; ++i) {
        elems[i] = elem_dist(rng);
      }
      expected.insert(expected.begin() + start, elems.begin(), elems.end());
      actual.insert(start, elems.begin(), elems.end());
    }
    QCOMPARE(actual.size(), expected.size());
    for (size_type i = 0; i < expected.size(); ++i) {
      QCOMPARE(expected[i], actual[i]);
    }
  }
}

void QueueTest::test_push_front() {
  for (int n = 0; n < 100; ++n) {
    list.push_front(n);
    COMPARE_SIZE(list, 21 + n);
    for (int i = 0; i < n; ++i) {
      QCOMPARE(list[n - i], i);
    }
    for (int i = 0; i < 20; ++i) {
      QCOMPARE(list[i + n + 1], i);
    }
  }
}

void QueueTest::test_pop_front() {
  for (int n = 0; n < 20; ++n) {
    QCOMPARE(list.pop_front(), n);
    COMPARE_SIZE(list, 19 - n);
    for (int i = 0; i < 19 - n; ++i) {
      QCOMPARE(list[i], i + n + 1);
    }
  }
  try {
    list.pop_front();
    QFAIL("Popping from an empty list didn't cause an exception.");
  } catch (PreconditionViolation e) {
    QCOMPARE(e.type(), EmptyList);
  }
}

