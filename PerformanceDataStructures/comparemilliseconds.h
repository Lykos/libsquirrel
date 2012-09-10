#ifndef COMPAREMILLISECONDS_H
#define COMPAREMILLISECONDS_H

#include "performanceresult.h"

struct CompareMilliseconds
{
  bool operator()(const PerformanceResult& a, const PerformanceResult& b) const;
};

#endif // COMPAREMILLISECONDS_H
