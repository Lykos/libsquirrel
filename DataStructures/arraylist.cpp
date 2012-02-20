#include "arraylist.h"

namespace DataStructures {
  index_type next_higher(index_type k)
  {
    if (k == 0) {
      return 0;
    }
    index_type result;
    // TODO Overflow!
    for (result = 1; result < k; result <<= 1);
    return result;
  }

  index_type next_lower(index_type k)
  {
    if (k == 0) {
      return 0;
    }
    index_type result;
    // TODO Overflow!
    for (result = 1; (result << 1) <= k; result <<= 1);
    return result;
  }
}
