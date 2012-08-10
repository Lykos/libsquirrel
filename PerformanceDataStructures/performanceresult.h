#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <ostream>

class PerformanceResult;

std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

class PerformanceResult {
  friend std::ostream& operator<<(std::ostream& out, const PerformanceResult& result);

public:

  PerformanceResult();

  PerformanceResult(const std::string& description, unsigned long milliseconds);

  const std::string& get_description() const;

  unsigned long get_milliseconds() const;

private:

  std::string m_description;

  unsigned long m_milliseconds;

  static const unsigned int DESCRIPTION_SIZE;

};

#endif // PERFORMANCERESULT_H
