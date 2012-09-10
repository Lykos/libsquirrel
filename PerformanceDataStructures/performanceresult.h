#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <ostream>

class PerformanceResult;

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

class PerformanceResult {
  friend std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

public:
  PerformanceResult(const PerformanceResult& other);

  PerformanceResult(PerformanceResult&& other);

  PerformanceResult& operator=(const PerformanceResult& other);

  PerformanceResult& operator=(PerformanceResult&& other);

  ~PerformanceResult();

  PerformanceResult(const char* description, unsigned long milliseconds);

  const char* description() const;

  unsigned long milliseconds() const;

private:
  const char* m_description;

  unsigned long m_milliseconds;

  static const unsigned int DESCRIPTION_SIZE;

};

#endif // PERFORMANCERESULT_H
