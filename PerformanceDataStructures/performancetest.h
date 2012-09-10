#ifndef PERFORMANCETEST_H
#define PERFORMANCETEST_H

#include <QObject>
#include <QElapsedTimer>
#include <QtTest/QtTest>
#include <string>
#include "DataStructures/arraylist.h"
#include "performanceresult.h"
#include "compositeperformanceresult.h"

class PerformanceTest : public QObject
{
  Q_OBJECT

public:
  CompositePerformanceResult<PerformanceResult> accumulate_results() const;

  virtual std::string description() const = 0;

protected:
  QElapsedTimer m_timer;
  DataStructures::ArrayList<PerformanceResult> m_results;
};

#endif // PERFORMANCETEST_H
