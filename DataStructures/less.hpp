#include "less.h"

namespace DataStructures {

  template <typename T>
  bool Less<T>::operator()(const T& a, const T& b) const
  {
    return a < b;
  }
  
} // namespace DataStructures
