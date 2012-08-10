#include "performanceresult.h"

PerformanceResult::PerformanceResult():
  m_description (""),
  m_milliseconds (0)
{
}

PerformanceResult::PerformanceResult(const std::string& description, unsigned long milliseconds):
  m_description (description),
  m_milliseconds (milliseconds)
{
}

const std::string& PerformanceResult::get_description() const
{
  return m_description;
}

unsigned long PerformanceResult::get_milliseconds() const
{
  return m_milliseconds;
}

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result)
{
  out << result.m_description;
  for (unsigned int i = result.m_description.size(); i < PerformanceResult::DESCRIPTION_SIZE; ++i) {
    out << " ";
  }
  return out << " " << result.m_milliseconds << " ms";
}

const unsigned int PerformanceResult::DESCRIPTION_SIZE (20);
