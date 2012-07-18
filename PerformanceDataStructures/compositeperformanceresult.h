#ifndef PERFORMANCERESULT_H
#define PERFORMANCERESULT_H

#include <string>
#include <ostream>
#include "arraylist.h"

template <typename T>
class CompositePerformanceResult;

template <typename T>
std::ostream& operator<<(std::ostream& out, CompositePerformanceResult<T> result);

template <typename T>
class CompositePerformanceResult
{
  friend std::ostream& operator<< <> (std::ostream& out, CompositePerformanceResult<T> result);

public:
  explicit CompositePerformanceResult(const std::string& name);

  const std::string& get_name() const;

  const DataStructures::ArrayList<T> get_sub_results() const;

  void add_sub_result(const T& sub_result);

private:
  std::string m_description;
  DataStructures::ArrayList<ClassPerformanceResult> m_sub_results;

};

template <typename T>
explicit CompositePerformanceResult<T>::CompositePerformanceResult(const std::string& description):
  m_description (description)
{
}

template <typename T>
const std::string& CompositePerformanceResult<T>::get_description() const
{
  return m_description;
}

template <typename T>
const DataStructures::ArrayList<T>& CompositePerformanceResult<T>::get_sub_results() const
{
  return m_sub_results;
}

template <typename T>
void CompositePerformanceResult<T>::add_sub_result(const T& sub_result)
{
  m_sub_results.push(sub_result);
}

template <typename T>
std::ostream& operator<<(std::ostream out, const CompositePerformanceResult<T>& result)
{
  out << result.m_description << std::endl;
  for (DataStructures::ArrayList<T>::const_iterator it = m_sub_results.begin(); it < m_sub_results.end(); ++it) {
    out << "\t" << *it << std::endl;
  }
  return out << std::endl;
}

#endif // PERFORMANCERESULT_H
