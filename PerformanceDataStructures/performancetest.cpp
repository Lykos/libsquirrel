#include "performancetest.h"
#include <string>

CompositePerformanceResult<PerformanceResult> PerformanceTest::accumulate_results() const
{
  CompositePerformanceResult<PerformanceResult> results (description());
  for (DataStructures::ArrayList<PerformanceResult>::const_iterator it = m_results.begin(); it < m_results.end(); ++it) {
    std::string description = (*it).get_description();
    unsigned long milliseconds = 0;
    for (; it < m_results.end() && (*it).get_description() == description; ++it) {
      milliseconds += (*it).get_milliseconds();
    }
    results.add_sub_result(PerformanceResult(description, milliseconds));
  }
  return results;
}
