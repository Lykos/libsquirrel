#include "multiply.h"
#include "add.h"
#include "subtract.h"

namespace DataStructures {
  namespace LongArithmetic {
    

    LongInt::part_list::iterator multiply(const LongInt::part_list::const_iterator& a_begin,
                                          const LongInt::part_list::const_iterator& a_end,
                                          const LongInt::part_list::const_iterator& b_begin,
                                          const LongInt::part_list::const_iterator& b_end,
                                          const LongInt::part_list::iterator& c_begin,
                                          const LongInt::part_list::iterator& c_end)
    {
      typedef LongInt::part_list::const_iterator c_it;
      typedef LongInt::part_list::iterator it;
      LongInt::part_list::difference_type a_size = a_end - a_begin;
      LongInt::part_list::difference_type b_size = b_end - b_begin;
      if (a_size <= 0 || b_size <= 0) {
        return c_begin;
      } else if (a_size == 1 && b_size == 1) {
        assert(c_end - c_begin >= 2);
        LongInt::part_type c0, c1;
        asm("mulq %3"
        : "=a" (c0), "=d" (c1) : "a" (*a_begin), "b" (*b_begin));
        it res_begin (c_begin), res_end (c_begin);
        *res_begin = c0;
        ++res_end;
        if (c1 > 0) {
          *res_end = c1;
          ++res_end;
        } else if (*res_begin == 0) {
          return res_begin;
        }
        return res_end;
      }
      LongInt::part_list::size_type max_size = std::max(a_size, b_size);
      LongInt::part_list::size_type part_size = max_size - max_size / 2;
      const c_it& x0_begin (a_begin);
      c_it x0_end (std::min(a_begin + part_size, a_end));
      c_it& x1_begin (x0_end);
      const c_it& x1_end (a_end);
      const c_it& y0_begin (b_begin);
      c_it y0_end (std::min(b_begin + part_size, b_end));
      c_it& y1_begin (y0_end);
      const c_it& y1_end (b_end);
      const it& res_begin (c_begin);

      // z0 = x0 * y0
      const it& z0_begin (res_begin); // Is the first part of the actual result
      it z0_end = multiply(x0_begin, x0_end, y0_begin, y0_end, z0_begin, c_end); // z0 = x0 * y0
      // This has to be padded to size at least 2 * part_size because the final result is constructed here
      for (it z0_it = z0_end; z0_it < z0_begin + 2 * part_size; ++z0_it) {
        *z0_it = 0l;
      }

      // z2 = x1 * y1
      it z2_begin (std::max(z0_end, z0_begin + 2 * part_size)); // Is the second part of the actual result
      it z2_end = multiply(x1_begin, x1_end, y1_begin, y1_end, z2_begin, c_end);
      it res_end (z2_begin + part_size);
      if (z2_begin < z2_end) {
        res_end += part_size;
      }
      assert(z2_end <= res_end); // z2 is part of the result.
      assert(res_end < c_end); // We need enough space for the result
      // This has to be padded to size at least part_size
      for (it z2_it = z2_end; z2_it < res_end; ++z2_it) {
        *z2_it = 0l;
      }
      it z1_begin (res_end);

      // x2 = x0 + x1
      std::pair<c_it, c_it> x2 = calc_xy2(x0_begin, x0_end, x1_begin, x1_end, z1_begin, c_end);
      c_it x2_begin (x2.first), x2_end (x2.second);

      // y2 = y0 + y1
      std::pair<c_it, c_it> y2 = calc_xy2(y0_begin, y0_end, y1_begin, y1_end, z1_begin, c_end);
      c_it y2_begin (y2.first), y2_end (y2.second);

      // z1 = x2 * y2 - z0 - z2
      it z1_end = multiply(x2_begin, x2_end, y2_begin, y2_end, z1_begin, c_end);
      subtract(z1_begin, z1_end, z0_begin, z0_end, false);
      subtract(z1_begin, z1_end, z2_begin, z2_end, false);
      while (z1_end > z1_begin && *(z1_end - 1) == 0) {
        --z1_end;
      }

      // Put result together
      add(z0_begin + part_size, res_end, z1_begin, z1_end);
      while (res_end > res_begin && *(res_end - 1) == 0) {
        --res_end;
      }
      return res_end;
    }

    std::pair<LongInt::part_list::const_iterator, LongInt::part_list::const_iterator> inline calc_xy2(const LongInt::part_list::const_iterator& xy0_begin,
                                                                                                      const LongInt::part_list::const_iterator& xy0_end,
                                                                                                      const LongInt::part_list::const_iterator& xy1_begin,
                                                                                                      const LongInt::part_list::const_iterator& xy1_end,
                                                                                                      LongInt::part_list::iterator& c_begin,
                                                                                                      const LongInt::part_list::iterator& c_end)
    {
      if (xy1_begin < xy1_end) {
        LongInt::part_list::difference_type part_size = xy0_end - xy0_begin;
        assert(c_begin + part_size + 1 < c_end); // We need enough space for xy2
        LongInt::part_list::iterator xy2_begin (c_begin);
        LongInt::part_list::iterator xy2_end (c_begin + part_size);
        copy(xy2_begin, xy2_end, xy0_begin, xy0_end);
        *(xy2_end++) = 0l;
        add(xy2_begin, xy2_end, xy1_begin, xy1_end);
        // Take out leading zeroes. Is necessary because else size 3 would result in endless recursion.
        while (xy2_end > xy2_begin && *(xy2_end - 1) == 0) {
          --xy2_end;
        }
        c_begin = xy2_end;
        return make_pair(xy2_begin, xy2_end);
      } else {
        return make_pair(xy0_begin, xy0_end);
      }
    }

    static const LongInt::part_list::size_type INITIAL_SPACE_USAGE[][4] = {{0, 0, 0, 0}, {0, 2, 11, 28}, {0, 11, 16, 33}, {0, 28, 33, 42}};

    LongInt::part_list::size_type space_usage(LongInt::part_list::size_type size_a, LongInt::part_list::size_type size_b)
    {
      if (size_a < size_b) {
        return space_usage(size_b, size_a);
      }
      if (size_a < 4) {
        return INITIAL_SPACE_USAGE[size_a][size_b];
      }
      LongInt::part_list::size_type part_size = size_a - size_a / 2;
      if (size_b <= part_size) {
        return space_usage(part_size + 1, size_b) + 4 * part_size + 1;
      } else {
        return space_usage(part_size + 1, part_size + 1) + 6 * part_size + 2;
      }
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
