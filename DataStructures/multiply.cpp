#include "multiply.h"
#include "add.h"
#include "subtract.h"
#include "longint.h"
#include "assembly.h"
#include <gmpxx.h>

namespace DataStructures {

  namespace LongArithmetic {

    typedef LongInt::part_type part_type;
    typedef LongInt::size_type size_type;

    mpz_class to_mpz(const part_type* begin, const part_type* end)
    {
      mpz_class r = 0;
      for (const part_type* p = end; p > begin;) {
        --p;
        r = (r << 64) + *p;
      }
      return r;
    }

    inline part_type* simple_multiply(const part_type a,
                                      const part_type b,
                                      part_type* const c_begin,
                                      part_type* const c_end)
    {
      assert(c_begin + 2 <= c_end);
      // Not necessary for the algorithm, but for the postcondition.
      assert(a != 0 && b != 0);
      part_type c0, c1;
      ASM_MUL(c0, c1, a, b);
      if (c1 != 0) {
        c_begin[0] = c0;
        c_begin[1] = c1;
        return c_begin + 2;
      } else {
        c_begin[0] = c0;
        return c_begin + 1;
      }
    }

    part_type* scalar_multiply(const part_type* const a_begin,
                               const part_type* const a_end,
                               register const part_type b,
                               part_type* const space_begin,
                               part_type* const space_end)
    {
      // Valid ranges
      assert(a_end >= a_begin);
      assert(space_end >= space_begin);
      size_type a_size = a_end - a_begin;
      assert(size_type(space_end - space_begin) >= a_size + 1);
      part_type* const c_begin = space_begin;
      part_type* const c_end = c_begin + a_size + 1;
      for (size_type i = 0; i < a_size + 1; ++i) {
        c_begin[i] = 0;
      }
      mpz_class gb = b;
      for (size_type i = 0; i < a_size; ++i) {
        part_type c0, c1;
        // With b, a, it is easier to figure out for the compiler how to keep b in a register
        ASM_MUL(c0, c1, b, a_begin[i]);
        // Note that no overflow can happen for mathematical reasons.
        ASM_TWO_ADD(c_begin[i], c_begin[i + 1], c0, c1);
      }
      if (c_end[-1] != 0) {
        return c_end;
      } else {
        return c_end - 1;
      }
    }

    inline part_type* heterogen_multiply(const part_type* const a_begin,
                                         const part_type* const a_end,
                                         const part_type* const b_begin,
                                         const part_type* const b_end,
                                         part_type* const space_begin,
                                         part_type* const space_end)
    {
      // Valid ranges
      assert(a_end >= a_begin);
      assert(b_end >= b_begin);
      assert(space_end >= space_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type space = space_end - space_begin;
      // Used space without recursion
      assert(space >= a_size + b_size);
      // For 1, take scalar_multiply
      assert(b_size > 1);
      size_type chunks = 1 + (a_size - 1) / b_size;
      // Termination relies on this
      assert(chunks >= 2);
      for (size_type i = 0; i < a_size + b_size; ++i) {
        space_begin[i] = 0;
      }
      // The range for the result
      part_type* const c_begin = space_begin;
      part_type* const c_end = c_begin + a_size + b_size;
      // This makes the indices in the loop valid
      assert(a_begin + (chunks - 1) * b_size < a_end);
      assert(a_begin + chunks * b_size >= a_end);
      assert(c_begin + chunks * b_size < c_end);
      assert(c_begin + (chunks + 1) * b_size >= c_end);
      part_type* const intermediate_begin = c_end;
      for (size_type i = 0; i < chunks; ++i) {
        part_type* const intermediate_end = multiply(a_begin + i * b_size,
                                                     i < chunks - 1 ? a_begin + (i + 1) * b_size : a_end,
                                                     b_begin,
                                                     b_end,
                                                     intermediate_begin,
                                                     space_end);
        add(c_begin + i * b_size,
            i < chunks - 1 ? c_begin + (i + 2) * b_size : c_end,
            intermediate_begin,
            intermediate_end);
      }
      if (c_end[-1] != 0) {
        return c_end;
      } else {
        return c_end - 1;
      }
    }

    void inline karatsuba_xy2(const part_type* const xy0_begin,
                              const part_type* const xy0_end,
                              const part_type* const xy1_begin,
                              const part_type* const xy1_end,
                              part_type* const xy2_begin,
                              part_type* const xy2_end)
    {
      size_type part_size = xy0_end - xy0_begin;
      // Valid ranges
      assert(xy0_begin <= xy0_end);
      assert(xy1_begin <= xy1_end);
      assert(xy2_begin <= xy2_end);
      // len(xy1) <= len(xy0)
      assert(size_type(xy1_end - xy1_begin) <= part_size);
      size_type space = xy2_end - xy2_begin;
      // space for len(xy0) + 1
      assert(space >= part_size + 1);
      for (size_type i = 0; i < part_size; ++i) {
        xy2_begin[i] = xy0_begin[i];
      }
      xy2_begin[part_size] = 0;
      assert(xy2_end - xy2_begin >= xy1_end - xy1_begin);
      add(xy2_begin, xy2_end, xy1_begin, xy1_end);
    }

    inline part_type* karatsuba_multiply(const part_type* const x_begin,
                                         const part_type* const x_end,
                                         const part_type* const y_begin,
                                         const part_type* const y_end,
                                         part_type* const space_begin,
                                         part_type* const space_end)

    {
      // Assume len(x) >= len(y) >= ceil(len(x) / 2)
      assert(x_end >= x_begin);
      assert(y_end >= y_begin);
      size_type x_size = x_end - x_begin;
      size_type y_size = y_end - y_begin;
      size_type part_size = x_size - x_size / 2;
      assert(x_size >= y_size);
      assert(y_size >= part_size);
      // Termination relies on this
      assert(part_size >= 1);
      // Valid ranges
      assert(x_end >= x_begin);
      assert(y_end >= y_begin);
      assert(space_end >= space_begin);
      // Don't allow aliasing with output pointer
      assert(x_end <= space_begin || space_end <= x_begin);
      assert(y_end <= space_begin || space_end <= y_begin);
      // Used space without recursion
      assert(space_begin + 6 * part_size + 2 < space_end);

      // Define aliases to make later code more clear
      const part_type* const x0_begin (x_begin);
      const part_type* const x0_end (x_begin + part_size);
      const part_type* const x1_begin (x0_end);
      const part_type* const x1_end (x_end);
      const part_type* const y0_begin (y_begin);
      const part_type* const y0_end (y_begin + part_size);
      const part_type* const y1_begin (y0_end);
      const part_type* const y1_end (y_end);

      // z0 = x0 * y0
      part_type* const z0_begin (space_begin); // Is the first part of the actual result
      part_type* const z0_end = multiply(x0_begin, x0_end, y0_begin, y0_end, z0_begin, space_end); // z0 = x0 * y0


      // z0 has to be padded with 0s because it is part of the result and the additions won't work otherwise.
      for (part_type *it = z0_end; it < z0_begin + 2 * part_size; ++it) {
        *it = 0;
      }

      // z2 = x1 * y1
      part_type* const z2_begin (space_begin + 2 * part_size); // Is the second part of the actual result
      part_type* const z2_end = multiply(x1_begin, x1_end, y1_begin, y1_end, z2_begin, space_end);

      // x2 = x0 + x1
      part_type* const x2_begin = z2_end;
      part_type* const x2_end = x2_begin + part_size + 1;
      karatsuba_xy2(x0_begin, x0_end, x1_begin, x1_end, x2_begin, x2_end);

      // y2 = y0 + y1
      part_type* const y2_begin = x2_end;
      part_type* const y2_end = y2_begin + part_size + 1;
      karatsuba_xy2(y0_begin, y0_end, y1_begin, y1_end, y2_begin, y2_end);

      // z1 = x2 * y2 - z0 - z2
      //   z1 = x2 * y2
      part_type* const z1_begin = y2_end;
      part_type* const z1_end = multiply(x2_begin, x2_end, y2_begin, y2_end, z1_begin, space_end);

      //   z1 -= z0
      subtract(z1_begin, z1_end, z0_begin, z0_end, false);

      //   z1 -= z2
      subtract(z1_begin, z1_end, z2_begin, z2_end, false);

      // Put result together. Note that for mathematical reasons, there can be no carry, so the space for z2 suffices.
      add(z0_begin + part_size, z2_end + 1, z1_begin, z1_end);
      return z2_end;
    }

    size_type space_usage(size_type size_a, size_type size_b)
    {
      if (size_a < size_b) {
        return space_usage(size_b, size_a);
      }
      if (size_b == 0) {
        return 0;
      }
      size_type part_size = size_a - size_a / 2;
      if (size_b == 1) {
        return size_a + 1;
      } else if (size_b <= size_a - size_a / 2) {
        return size_a + size_b + space_usage(size_b, size_b);
      } else if (part_size + 1 == size_a) {
        // In this case, the lower recursion would not terminate, but the worst case can only appear once and
        // The second time, it gets smaller.
        return 12 * part_size + 4 + space_usage(part_size, part_size);
      } else {
        return space_usage(part_size + 1, part_size + 1) + 6 * part_size + 2;
      }
    }

    part_type* multiply(const part_type* a_begin,
                        const part_type* a_end,
                        const part_type* b_begin,
                        const part_type* b_end,
                        part_type* const space_begin,
                        part_type* const space_end)
    {
      // Valid ranges
      assert(a_end >= a_begin);
      assert(b_end >= b_begin);
      assert(space_end >= space_begin);
      // No aliases with output range. Note that a and b may overlap if a number is multiplied with itself.
      assert(a_end <= space_begin || space_end <= a_begin);
      assert(b_end <= space_begin || space_end <= b_begin);
      // This doesn't cost much and saves a lot of recursions for sparse numbers, e.g. powers of 2.
      while (a_end > a_begin && a_end[-1] == 0) {
        --a_end;
      }
      while (b_end > b_begin && b_end[-1] == 0) {
        --b_end;
      }
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      // Space required for result
      assert(size_type(space_end - space_begin) >= a_size + b_size);
      if (a_size < b_size) {
        std::swap(a_size, b_size);
        std::swap(a_begin, b_begin);
        std::swap(a_end, b_end);
      }
      if (b_size == 0) {
        return space_begin;
      }
      part_type *c_begin = space_begin;
      part_type *c_end;
      if (a_size == 1) {
        c_end = simple_multiply(a_begin[0], b_begin[0], space_begin, space_end);
      } else if (b_size == 1) {
        c_end = scalar_multiply(a_begin, a_end, b_begin[0], space_begin, space_end);
      } else if (b_size <= a_size - a_size / 2) {
        c_end = heterogen_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      } else {
        c_end = karatsuba_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      }
      size_type c_size = c_end - c_begin;
      assert(c_size <= a_size + b_size);
      assert(c_size >= a_size + b_size - 1);
      assert(c_end[-1] != 0);
      return c_end;
    }

  } // namespace LongArithmetic

} // namespace DataStructures
