#ifndef COMPOSITEPERFORMANCERESULT_H
#define COMPOSITEPERFORMANCERESULT_H

#include "DataStructures/arraylist.h"
#include <string>
#include <ostream>
#include <sstream>

template <typename T>
class CompositePerformanceResult;

template <typename T>
std::ostream& operator<<(std::ostream& out, const CompositePerformanceResult<T>& result);

template <typename T>
class CompositePerformanceResult
{
  friend std::ostream& operator<< <> (std::ostream& out, const CompositePerformanceResult<T>& result);

public:
  CompositePerformanceResult();

  explicit CompositePerformanceResult(const std::string& description);

  const std::string& get_description() const;

  const DataStructures::ArrayList<T>& get_sub_results() const;

  void add_sub_result(const T& sub_result);

private:
  std::string m_description;
  DataStructures::ArrayList<T> m_sub_results;

};

template <typename T>
CompositePerformanceResult<T>::CompositePerformanceResult():
  m_description ("")
{
}

template <typename T>
CompositePerformanceResult<T>::CompositePerformanceResult(const std::string& description):
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
  m_sub_results.push_back(sub_result);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const CompositePerformanceResult<T>& result)
{
  out << result.m_description << std::endl;
  typedef typename DataStructures::ArrayList<T>::const_iterator const_iterator;
  for (const_iterator it = result.m_sub_results.begin(); it < result.m_sub_results.end(); ++it) {
    std::stringstream ss;
    ss << *it;
    std::string line;
    while (std::getline(ss, line)) {
      out << "\t" << line << std::endl;
    }
  }
  return out << std::endl;
}

#endif // COMPOSITEPERFORMANCERESULT_H
