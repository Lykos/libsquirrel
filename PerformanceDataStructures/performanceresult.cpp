#include "performanceresult.h"
#include <cstring>

PerformanceResult::PerformanceResult(const PerformanceResult& other):
  m_description (other.m_description),
  m_milliseconds (other.m_milliseconds)
{}

PerformanceResult::PerformanceResult(PerformanceResult&& other):
  m_description (std::move(other.m_description)),
  m_milliseconds (other.m_milliseconds)
{}

PerformanceResult& PerformanceResult::operator=(const PerformanceResult& other)
{
  m_description = other.m_description;
  m_milliseconds = other.m_milliseconds;
  return *this;
}

PerformanceResult& PerformanceResult::operator=(PerformanceResult&& other)
{
  m_description = std::move(other.m_description);
  m_milliseconds = other.m_milliseconds;
  return *this;
}

PerformanceResult::~PerformanceResult()
{}

PerformanceResult::PerformanceResult(const char* description, unsigned long milliseconds):
  m_description (description),
  m_milliseconds (milliseconds)
{
}

const char* PerformanceResult::description() const
{
  return m_description;
}

unsigned long PerformanceResult::milliseconds() const
{
  return m_milliseconds;
}

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result)
{
  out << result.m_description;
  for (unsigned int i = strlen(result.m_description); i < PerformanceResult::DESCRIPTION_SIZE; ++i) {
    out << " ";
  }
  return out << " " << result.m_milliseconds << " ms";
}

const unsigned int PerformanceResult::DESCRIPTION_SIZE (20);
