#ifndef DATASTRUCTURES_LESS_H
#define DATASTRUCTURES_LESS_H

namespace DataStructures {

  template <typename T>
  struct Less
  {
    bool operator()(const T& a, const T& b) const;
  };
  
} // namespace DataStructures

#include "less.hpp"

#endif // DATASTRUCTURES_LESS_H
