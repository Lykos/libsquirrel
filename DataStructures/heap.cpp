#include "heap.h"

namespace DataStructures {

  inline index_type level_base(index_type index)
  {
    if (index == 0) {
      return 0;
    }
    index_type base;
    // TODO Overflow!
    for (base = 1; (base << 1) + 1 <= index; base = (base << 1) + 1);
    return base;
    assert(base <= index && index < (base << 1) + 1);
  }

  index_type parent(index_type index)
  {
    index_type child_base = level_base(index);
    index_type child_offset = index - child_base;
    index_type parent_base = child_base >> 1;
    index_type parent_offset = child_offset / 2;
    return parent_base + parent_offset;
  }

  index_type left_child(index_type index)
  {
    index_type parent_base = level_base(index);
    index_type parent_offset = index - parent_base;
    index_type child_base = (parent_base << 1) + 1;
    index_type child_offset = parent_offset * 2;
    return child_base + child_offset;
  }

  index_type right_child(index_type index)
  {
    return left_child(index) + 1;
  }

}
