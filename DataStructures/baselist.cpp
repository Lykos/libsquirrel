#include "arraylist.h"

namespace DataStructures {
  // TODO Make more efficient!

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

  index_type log2(index_type k)
  {
    if (k == 0) {
      return 0;
    }
    index_type result;
    for (result = 0; k > 1; k >>= 1, ++result);
    return result;
  }
}
