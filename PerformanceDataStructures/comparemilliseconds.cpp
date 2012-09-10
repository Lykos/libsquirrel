#include "comparemilliseconds.h"

bool CompareMilliseconds::operator()(const PerformanceResult& a, const PerformanceResult& b) const
{
  return a.milliseconds() < b.milliseconds();
}
