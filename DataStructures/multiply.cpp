#include "multiply.h"
#include "add.h"
#include "subtract.h"
#include "longint.h"
#include <cstdio>
#include <iostream>
using namespace std;

namespace DataStructures {

  namespace LongArithmetic {

    typedef LongInt::part_type part_type;
    typedef LongInt::size_type size_type;

    int inline uCompareTo(const part_type* a_begin,
                          const part_type* a_end,
                          const part_type* b_begin,
                          const part_type* b_end)
    {
      assert(a_begin <= a_end);
      assert(b_begin <= b_end);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type max_index = std::max(a_size, b_size);
      for (size_type i = max_index + 1; i > 0;) {
        --i;
        part_type a = i < a_size ? a_begin[i] : 0;
        part_type b = i < b_size ? b_begin[i] : 0;
        if (a > b) {
          return 1;
        } else if (a < b) {
          return -1;
        }
      }
      return 0;
    }

    std::pair<const part_type*, const part_type*> inline calc_xy2(const part_type* xy0_begin,
                                                                  const part_type* xy0_end,
                                                                  const part_type* xy1_begin,
                                                                  const part_type* xy1_end,
                                                                  part_type* c_begin,
                                                                  part_type* c_end)
    {
      assert(xy1_begin <= xy1_end);
      if (xy1_begin < xy1_end) {
        size_type part_size = xy0_end - xy0_begin;
        assert(c_begin + part_size + 1 < c_end); // We need enough space for xy2
        part_type* xy2_begin (c_begin);
        part_type* xy2_end (c_begin + part_size);
        copy(xy2_begin, xy2_end, xy0_begin, xy0_end);
        *(xy2_end++) = 0l;
        add(xy2_begin, xy2_end, xy1_begin, xy1_end);
        // Take out leading zeroes. Is necessary because else size 3 would result in endless recursion.
        while (xy2_end > xy2_begin && *(xy2_end - 1) == 0) {
          --xy2_end;
        }
        c_begin = xy2_end;
        return std::make_pair(xy2_begin, xy2_end);
      } else {
        return std::make_pair(xy0_begin, xy0_end);
      }
    }

    part_type* simple_multiply(const part_type a,
                               const part_type b,
                               part_type* c)
    {
      // TODO: This sucks. CMOV may be fun, but if it takes so many steps, it might not be faster.
      asm("\tmulq %2;\n"             // rax:rdx = a * b; (rax is lower part, rdx upper part)
          "\tmov %%rax, (%0);\n"     // *c = rax;
          "\taddq $0x8, %0;\n"       // ++c;
          "\tmov %%rdx, (%0);\n"     // *c = rdx;
          "\txorq %2, %2;\n"         // b = 0;
          "\tmov $0x8, %%rax;\n"     // rax = 1;
          "\ttestq %%rdx, %%rdx;\n"  // if (rdx != 0)
          "\tcmovnz %%rax, %2;\n"    //   b = rax;
          "\taddq %2, %0;\n"         // c += b;
      : "=r" (c) : "a" (a), "r" (b), "0" (c) : "%rdx", "cc");
      return c;
    }

    inline part_type* karatsuba_multiply(const part_type* a_begin,
                                         const part_type* a_end,
                                         const part_type* b_begin,
                                         const part_type* b_end,
                                         part_type* c_begin,
                                         part_type* c_end)

    {
      size_type max_size = std::max(a_end - a_begin, b_end - b_begin);
      size_type part_size = max_size - max_size / 2;
      const part_type* x0_begin (a_begin);
      const part_type* x0_end (std::min(a_begin + part_size, a_end));
      const part_type* x1_begin (x0_end);
      const part_type* x1_end (a_end);
      const part_type* y0_begin (b_begin);
      const part_type* y0_end (std::min(b_begin + part_size, b_end));
      const part_type* y1_begin (y0_end);
      const part_type* y1_end (b_end);
      part_type* res_begin (c_begin);

      // z0 = x0 * y0
      part_type* z0_begin (res_begin); // Is the first part of the actual result
      assert(y0_begin != z0_begin);
      assert(x0_begin != z0_begin);
      part_type* z0_end = multiply(x0_begin, x0_end, y0_begin, y0_end, z0_begin, c_end); // z0 = x0 * y0
      // This has to be padded to size at least 2 * part_size because the final result is constructed here
      for (part_type* z0_it = z0_end; z0_it < z0_begin + 2 * part_size; ++z0_it) {
        *z0_it = 0l;
      }

      // z2 = x1 * y1
      part_type* z2_begin (std::max(z0_end, z0_begin + 2 * part_size)); // Is the second part of the actual result
      assert(y1_begin != z2_begin);
      assert(x1_begin != z2_begin);      part_type* z2_end = multiply(x1_begin, x1_end, y1_begin, y1_end, z2_begin, c_end);
      part_type* res_end (z2_begin + part_size);
      if (z2_begin < z2_end) {
        res_end += part_size;
      }
      assert(z2_end <= res_end); // z2 is part of the result.
      assert(res_end < c_end); // We need enough space for the result
      // This has to be padded to size at least part_size
      for (part_type* z2_it = z2_end; z2_it < res_end; ++z2_it) {
        *z2_it = 0l;
      }
      part_type* z1_begin (res_end);

      // x2 = x0 + x1
      std::pair<const part_type*, const part_type*> x2 = calc_xy2(x0_begin, x0_end, x1_begin, x1_end, z1_begin, c_end);
      const part_type *x2_begin (x2.first), *x2_end (x2.second);

      // y2 = y0 + y1
      std::pair<const part_type*, const part_type*> y2 = calc_xy2(y0_begin, y0_end, y1_begin, y1_end, z1_begin, c_end);
      const part_type *y2_begin (y2.first), *y2_end (y2.second);

      // z1 = x2 * y2 - z0 - z2
      assert(y2_begin != z1_begin);
      assert(x2_begin != z1_begin);
      part_type *z1_end = multiply(x2_begin, x2_end, y2_begin, y2_end, z1_begin, c_end);
      if (uCompareTo(z1_begin, z1_end, z0_begin, z0_end) != 1) {
        cout << "x0 length " << x0_end - x0_begin << endl;
        cout << "x0 " << x0_begin[1] << " " << x0_begin[0] << endl;
        cout << "x1 length " << x1_end - x1_begin << endl;
        cout << "x1 " << x1_begin[1] << " " << x1_begin[0] << endl;
        cout << "y0 length " << y0_end - y0_begin << endl;
        cout << "y0 " << y0_begin[1] << " " << y0_begin[0] << endl;
        cout << "y1 length " << y1_end - y1_begin << endl;
        cout << "y1 " << y1_begin[1] << " " << y1_begin[0] << endl;
        cout << "z0 length " << z0_end - z0_begin << endl;
        cout << "z0 " << z0_begin[1] << " " << z0_begin[0] << endl;
        cout << "z1 length " << z1_end - z1_begin << endl;
        cout << "z1 " << z1_begin[1] << " " << z1_begin[0] << endl;
        assert(false);
      }
      subtract(z1_begin, z1_end, z0_begin, z0_end, false);
      if (uCompareTo(z1_begin, z1_end, z2_begin, z2_end) != 1) {
        cout << "x0 length " << x0_end - x0_begin << endl;
        cout << "x0 " << x0_begin[1] << " " << x0_begin[0] << endl;
        cout << "x1 length " << x1_end - x1_begin << endl;
        cout << "x1 " << x1_begin[1] << " " << x1_begin[0] << endl;
        cout << "y0 length " << y0_end - y0_begin << endl;
        cout << "y0 " << y0_begin[1] << " " << y0_begin[0] << endl;
        cout << "y1 length " << y1_end - y1_begin << endl;
        cout << "y1 " << y1_begin[1] << " " << y1_begin[0] << endl;
        cout << "z0 length " << z0_end - z0_begin << endl;
        cout << "z0 " << z0_begin[1] << " " << z0_begin[0] << endl;
        cout << "z2 length " << z2_end - z2_begin << endl;
        cout << "z2 " << z2_begin[1] << " " << z2_begin[0] << endl;
        assert(false);
      }
      subtract(z1_begin, z1_end, z2_begin, z2_end, false);
      while (z1_end > z1_begin && *(z1_end - 1) == 0) {
        --z1_end;
      }

      // Put result together
      assert(res_end - (z0_begin + part_size) >= z1_end - z1_begin);
      add(z0_begin + part_size, res_end, z1_begin, z1_end);
      while (res_end > res_begin && *(res_end - 1) == 0) {
        --res_end;
      }
      return res_end;
    }

    static const size_type INITIAL_SPACE_USAGE[][4] = {{0, 0, 0, 0}, {0, 2, 11, 28}, {0, 11, 16, 33}, {0, 28, 33, 42}};

    size_type space_usage(size_type size_a, size_type size_b)
    {
      if (size_a < size_b) {
        return space_usage(size_b, size_a);
      }
      if (size_a < 4) {
        return INITIAL_SPACE_USAGE[size_a][size_b];
      }
      size_type part_size = size_a - size_a / 2;
      if (size_b <= part_size) {
        return space_usage(part_size + 1, size_b) + 4 * part_size + 1;
      } else {
        return space_usage(part_size + 1, part_size + 1) + 6 * part_size + 2;
      }
    }

    part_type* multiply(const part_type* a_begin,
                        const part_type* a_end,
                        const part_type* b_begin,
                        const part_type* b_end,
                        part_type* c_begin,
                        part_type* c_end)
    {
      assert(a_end >= a_begin);
      assert(b_end >= b_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      if (a_size == 0 || b_size == 0) {
        return c_begin;
      }
      // Forbidden aliasing
      assert(a_begin != c_begin);
      assert(b_begin != c_begin);
      if (a_size == 1 && b_size == 1) {
        assert(c_begin + 2 <= c_end);
        part_type *r = simple_multiply(a_begin[0], b_begin[0], c_begin);
        assert(r >= c_begin);
        assert(r <= c_begin + 2);
        if (c_begin[0] != a_begin[0] * b_begin[0]) {
          printf("%ld * %ld = %ld (%ld)\n", a_begin[0], b_begin[0], c_begin[0], a_begin[0] * b_begin[0]);
          printf("0x%lx * 0x%lx = 0x%lx  (0x%lx)\n", a_begin[0], b_begin[0], c_begin[0], a_begin[0] * b_begin[0]);
          assert(c_begin[0] == a_begin[0] * b_begin[0]);
        }
        return r;
      } else {
        return karatsuba_multiply(a_begin, a_end, b_begin, b_end, c_begin, c_end);
      }
    }
    
  } // namespace LongArithmetic

} // namespace DataStructures
