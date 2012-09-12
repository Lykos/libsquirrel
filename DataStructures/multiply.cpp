#include "multiply.h"
#include "add.h"
#include "subtract.h"
#include "assembly.h"
#include "compare.h"
#include "shifts.h"
#include "thresholds.h"
#include "incdec.h"
#include <cstring>

namespace DataStructures {

  namespace LongArithmetic {

    static const part_type INV_3 = 0xAAAAAAAAAAAAAAAB; // TODO make this depending on the size of part_type

    inline void zero_out(part_type* begin, part_type* end)
    {
      arithmetic_assert(end >= begin);
      memset(begin, 0, (end - begin) * sizeof(part_type));
    }

    inline void div_exact_3(part_type* begin, part_type* end)
    {
      part_type carry = 0;
      for (; begin < end; ++begin) {
        // Note that I want this to be modulo 1 << PART_SIZE, so * is fine.
        *begin = ((*begin) - carry) * INV_3;
        part_type dummy;
        ASM_MUL(dummy, carry, *begin, 3);
      }
      arithmetic_assert(carry == 0);
    }

    inline void copy_pad_part(part_type* const dst_begin,
                              part_type* const dst_end,
                              const part_type* const src_begin,
                              const part_type* const src_end)
    {
      arithmetic_assert(src_begin <= src_end);
      arithmetic_assert(dst_begin <= dst_end);
      size_type src_size = src_end - src_begin;
      size_type dst_size = dst_end - dst_begin;
      arithmetic_assert(src_size <= dst_size);
      memcpy(dst_begin, src_begin, src_size * sizeof(part_type));
      zero_out(dst_begin + src_size, dst_end);
    }

    // TODO Reuse the normal add/sub code
    inline bool signed_add(bool a_positive,
                           part_type* a_begin,
                           part_type* a_end,
                           bool b_positive,
                           const part_type* const b_begin,
                           const part_type* const b_end)
    {
      if (a_positive == b_positive) {
        add(a_begin, a_end, b_begin, b_end);
        return a_positive;
      } else {
        bool exchange = compare_to(a_begin, a_end, b_begin, b_end) == -1;
        subtract(a_begin, a_end, b_begin, b_end, exchange);
        return a_positive ^ exchange;
      }
    }

    inline bool signed_sub(bool a_positive,
                           part_type* a_begin,
                           part_type* a_end,
                           bool b_positive,
                           const part_type* const b_begin,
                           const part_type* const b_end,
                           bool exchange)
    {
      if (a_positive == b_positive) {
        bool ex = compare_to(a_begin, a_end, b_begin, b_end) == -1;
        subtract(a_begin, a_end, b_begin, b_end, ex);
        return a_positive ^ exchange ^ ex;
      } else {
        add(a_begin, a_end, b_begin, b_end);
        return a_positive ^ exchange;
      }
    }

    inline part_type* simple_multiply(const part_type a,
                                      const part_type b,
                                      part_type* const c_begin,
                                      part_type* const c_end)
    {
      arithmetic_assert(c_begin + 2 <= c_end);
      // Not necessary for the algorithm, but for the postcondition.
      arithmetic_assert(a != 0 && b != 0);
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

    inline part_type* scalar_multiply(const part_type* const a_begin,
                                      const part_type* const a_end,
                                      register const part_type b,
                                      part_type* const space_begin,
                                      part_type* const space_end)
    {
      // Valid ranges
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(space_end >= space_begin);
      size_type a_size = a_end - a_begin;
      arithmetic_assert(size_type(space_end - space_begin) >= a_size + 1);
      part_type* const c_begin = space_begin;
      part_type* const c_end = c_begin + a_size + 1;
      for (size_type i = 0; i < a_size + 1; ++i) {
        c_begin[i] = 0;
      }
      for (size_type i = 0; i < a_size; ++i) {
        part_type c0, c1;
        // With b, a, it is easier to figure out for the compiler how to keep b in a register
        ASM_MUL(c0, c1, b, a_begin[i]);
        // Note that no overflow can happen for mathematical reasons.
        ASM_TWO_ADD(c_begin[i], c_begin[i + 1], c0, c1);
      }
      return c_end[-1] ? c_end : c_end - 1;
    }

    inline part_type* unbalanced_multiply(const part_type* const a_begin,
                                         const part_type* const a_end,
                                         const part_type* const b_begin,
                                         const part_type* const b_end,
                                         part_type* const space_begin,
                                         part_type* const space_end)
    {
      // Valid ranges
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(b_end >= b_begin);
      arithmetic_assert(space_end >= space_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type space = space_end - space_begin;
      // Used space without recursion
      arithmetic_assert(space >= a_size + b_size);
      // For 1, take scalar_multiply
      arithmetic_assert(b_size > 1);
      size_type chunks = 1 + (a_size - 1) / b_size;
      // Termination relies on this
      arithmetic_assert(chunks >= 2);
      zero_out(space_begin, space_begin + a_size + b_size);
      // The range for the result
      part_type* const c_begin = space_begin;
      part_type* const c_end = c_begin + a_size + b_size;
      // This makes the indices in the loop valid
      arithmetic_assert(a_begin + (chunks - 1) * b_size < a_end);
      arithmetic_assert(a_begin + chunks * b_size >= a_end);
      arithmetic_assert(c_begin + chunks * b_size < c_end);
      arithmetic_assert(c_begin + (chunks + 1) * b_size >= c_end);
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
      return c_end[-1] ? c_end : c_end - 1;
    }

    inline part_type* school_multiply(const part_type* const a_begin,
                                      const part_type* const a_end,
                                      const part_type* const b_begin,
                                      const part_type* const b_end,
                                      part_type* space_begin,
                                      part_type* space_end)
    {
      // Valid ranges
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(b_end >= b_begin);
      arithmetic_assert(space_end >= space_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type space = space_end - space_begin;
      // Used space without recursion
      arithmetic_assert(space >= a_size + b_size);
      // For 1, take scalar_multiply
      arithmetic_assert(b_size > 1);
      space_end = space_begin + a_size + b_size;
      memset(space_begin, 0, (a_size + b_size) * sizeof(part_type));
      for (size_type i = 0; i < a_size; ++i) {
        for (size_type j = 0; j < b_size; ++j) {
          part_type c[2];
          ASM_MUL(c[0], c[1], a_begin[i], b_begin[j]);
          add(space_begin + i + j, space_end, c, c + 2);
        }
      }
      return space_end[-1] ? space_end : space_end - 1;
    }

    inline void karatsuba_xy2(const part_type* const xy0_begin,
                              const part_type* const xy0_end,
                              const part_type* const xy1_begin,
                              const part_type* const xy1_end,
                              part_type* const xy2_begin,
                              part_type* const xy2_end)
    {
      size_type part_size = xy0_end - xy0_begin;
      // Valid ranges
      arithmetic_assert(xy0_begin <= xy0_end);
      arithmetic_assert(xy1_begin <= xy1_end);
      arithmetic_assert(xy2_begin <= xy2_end);
      // len(xy1) <= len(xy0)
      arithmetic_assert(size_type(xy1_end - xy1_begin) <= part_size);
      size_type space = xy2_end - xy2_begin;
      // space for len(xy0) + 1
      arithmetic_assert(space >= part_size + 1);
      for (size_type i = 0; i < part_size; ++i) {
        xy2_begin[i] = xy0_begin[i];
      }
      xy2_begin[part_size] = 0;
      arithmetic_assert(xy2_end - xy2_begin >= xy1_end - xy1_begin);
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
      arithmetic_assert(x_end >= x_begin);
      arithmetic_assert(y_end >= y_begin);
      size_type x_size = x_end - x_begin;
      size_type y_size = y_end - y_begin;
      size_type part_size = x_size - x_size / 2;
      arithmetic_assert(x_size >= y_size);
      arithmetic_assert(y_size >= part_size);
      // Termination relies on this
      arithmetic_assert(part_size >= 1);
      // Don't allow aliasing with output pointer
      arithmetic_assert(x_end <= space_begin || space_end <= x_begin);
      arithmetic_assert(y_end <= space_begin || space_end <= y_begin);
      // Used space without recursion
      arithmetic_assert(space_begin + 6 * part_size + 2 < space_end);

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

    part_type* toom3_multiply(const part_type* a_begin,
                              const part_type* a_end,
                              const part_type* b_begin,
                              const part_type* b_end,
                              part_type* const space_begin,
                              part_type* const space_end)
    {
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(b_end >= b_begin);
      arithmetic_assert(space_end >= space_begin);
      // No unwanted aliasing
      arithmetic_assert(a_end <= space_begin || space_end <= a_begin);
      arithmetic_assert(b_end <= space_begin || space_end <= b_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type part_size = a_size - 2 * a_size / 3;
      // Otherwise dividing into 3 pieces is not useful
      arithmetic_assert(a_size >= 3);
      arithmetic_assert(a_size >= b_size);
      // Use unbalanced multiply for the other part
      arithmetic_assert(b_size >= part_size);

      // Define aliases to make later code more clear
      const part_type* const a0_begin (a_begin);
      const part_type* const a0_end (a_begin + part_size);
      const part_type* const a1_begin (a0_end);
      const part_type* const a1_end (a1_begin + part_size);
      const part_type* const a2_begin (a1_end);
      const part_type* const a2_end (a_end);
      // cout.flags(ios::hex);
      // cout << "a " << *a0_begin << " " << *a1_begin << " " << *a2_begin << endl;

      const part_type* const b0_begin (b_begin);
      const part_type* const b0_end (b_begin + part_size);
      const part_type* const b1_begin (b0_end);
      const part_type* const b1_end (std::min(b1_begin + part_size, b_end));
      const part_type* const b2_begin (b1_end);
      const part_type* const b2_end (b_end);
      // cout << "b " <<  *b0_begin << " " << *b1_begin << " " << *b2_begin << endl;

      // Pointwise multiply at 0 and infty
      part_type* const r0_begin (space_begin);
      part_type* const r0_end = multiply(a0_begin, a0_end, b0_begin, b0_end, r0_begin, space_end);

      part_type* const rinf_begin (space_begin + 4 * part_size);
      // Pad Set the gap in the result to 0.
      zero_out(r0_end, rinf_begin);
      part_type* const rinf_end = multiply(a2_begin, a2_end, b2_begin, b2_end, rinf_begin, space_end);

      // Aliases for the evaluation points
      part_type* const p1_begin (space_begin + 6 * part_size);
      part_type* const p1_end (p1_begin + part_size + 1);
      part_type* const p_1_begin (p1_end);
      part_type* const p_1_end (p_1_begin + part_size + 1);
      part_type* const p_2_begin (p_1_end);
      part_type* const p_2_end (p_2_begin + part_size + 1);

      part_type* const q1_begin (p_2_end);
      part_type* const q1_end (q1_begin + part_size + 1);
      part_type* const q_1_begin (q1_end);
      part_type* const q_1_end (q_1_begin + part_size + 1);
      part_type* const q_2_begin (q_1_end);
      part_type* const q_2_end (q_2_begin + part_size + 1);

      // Evaluate the polynomials
      copy_pad_part(p1_begin, p1_end, a0_begin, a0_end);
      add(p1_begin, p1_end, a2_begin, a2_end);
      copy_pad_part(p_1_begin, p_1_end, p1_begin, p1_end);
      add(p1_begin, p1_end, a1_begin, a1_end);
      bool p_1_positive = signed_sub(true, p_1_begin, p_1_end, true, a1_begin, a1_end, false);
      copy_pad_part(p_2_begin, p_2_end, p_1_begin, p_1_end);
      bool p_2_positive = signed_add(p_1_positive, p_2_begin, p_2_end, true, a2_begin, a2_end);
      shift_left(p_2_begin, p_2_end, 1);
      p_2_positive = signed_sub(p_2_positive, p_2_begin, p_2_end, true, a0_begin, a0_end, false);
      // cout << "p(1) " << p1_begin[1] << " " << p1_begin[0] << endl;
      // cout << "p(-1) " << (p_1_positive ? "" : "-") << p_1_begin[1] << " " << p_1_begin[0] << endl;
      // cout << "p(-2) " << (p_2_positive ? "" : "-") << p_2_begin[1] << " " << p_2_begin[0] << endl;

      copy_pad_part(q1_begin, q1_end, b0_begin, b0_end);
      add(q1_begin, q1_end, b2_begin, b2_end);
      copy_pad_part(q_1_begin, q_1_end, q1_begin, q1_end);
      add(q1_begin, q1_end, b1_begin, b1_end);
      bool q_1_positive = signed_sub(true, q_1_begin, q_1_end, true, b1_begin, b1_end, false);
      copy_pad_part(q_2_begin, q_2_end, q_1_begin, q_1_end);
      bool q_2_positive = signed_add(q_1_positive, q_2_begin, q_2_end, true, b2_begin, b2_end);
      shift_left(q_2_begin, q_2_end, 1);
      q_2_positive = signed_sub(q_2_positive, q_2_begin, q_2_end, true, b0_begin, b0_end, false);
      // cout << "q(1) " << q1_begin[1] << " " << q1_begin[0] << endl;
      // cout << "q(-1) " << (q_1_positive ? "" : "-") << q_1_begin[1] << " " << q_1_begin[0] << endl;
      // cout << "q(-2) " << (q_2_positive ? "" : "-") << q_2_begin[1] << " " << q_2_begin[0] << endl;


      // Pointwise multiply the rest
      part_type* const r1_begin (q_2_end);
      part_type* r1_end = multiply(p1_begin, p1_end, q1_begin, q1_end, r1_begin, space_end);
      zero_out(r1_end, r1_begin + 2 * part_size + 2);
      r1_end = r1_begin + 2 * part_size + 2;

      part_type* const r_1_begin (q_2_end + 2 * part_size + 2);
      part_type* r_1_end = multiply(p_1_begin, p_1_end, q_1_begin, q_1_end, r_1_begin, space_end);
      bool r_1_positive = q_1_positive == p_1_positive;
      zero_out(r_1_end, r_1_begin + 2 * part_size + 2);
      r_1_end = r_1_begin + 2 * part_size + 2;

      part_type* const r_2_begin (q_2_end + 4 * part_size + 4);
      part_type* r_2_end = multiply(p_2_begin, p_2_end, q_2_begin, q_2_end, r_2_begin, space_end);
      bool r_2_positive = q_2_positive == p_2_positive;
      zero_out(r_2_end, r_2_begin + 2 * part_size + 2);
      r_2_end = r_2_begin + 2 * part_size + 2;

      // cout << "r(0) " << r0_begin[1] << " " << r0_begin[0] << endl;
      // cout << "r(1) " << r1_begin[2] << " " << r1_begin[1] << " " << r1_begin[0] << endl;
      // cout << "r(-1) " << (r_1_positive ? "" : "-") << r_1_begin[2] << " " << r_1_begin[1] << " " << r_1_begin[0] << endl;
      // cout << "r(-2) " << (r_2_positive ? "" : "-") << r_2_begin[2] << " " << r_2_begin[1] << " " << r_2_begin[0] << endl;
      // cout << "r(inf) " << rinf_begin[1] << " " << rinf_begin[0] << endl;

      // Interpolate
      part_type* const r3_begin (r_2_begin);
      part_type* const r3_end (r_2_begin + 2 * part_size + 2);
      zero_out(r_2_end, r3_end);
      bool r3_positive = signed_sub(r_2_positive, r3_begin, r3_end, true, r1_begin, r1_end, false);
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      div_exact_3(r3_begin, r3_end);
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      // We reuse the variable: r1 is now the coefficient r1, not r(1) any more.
      bool r1_positive = signed_sub(true, r1_begin, r1_end, r_1_positive, r_1_begin, r_1_end, false);
      arithmetic_assert(!(*r1_begin & 1));
      shift_right(r1_begin, r1_end, 1);
      part_type* const r2_begin (r_1_begin);
      part_type* const r2_end (r_1_begin + 2 * part_size + 2);
      zero_out(r_1_end, r2_end);
      bool r2_positive = signed_sub(r_1_positive, r2_begin, r2_end, true, r0_begin, r0_end, false);
      r3_positive = signed_sub(r3_positive, r3_begin, r3_end, r2_positive, r2_begin, r2_end, true);
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      // Instead of shifting r_inf, we shift one mor than we want and shift back afterwards
      arithmetic_assert(!(*r3_begin & 1));
      part_type r3_bit = (*r3_begin >> 1) & 1;
      shift_right(r3_begin, r3_end, 2);
      // Two complement trick
      if (r3_bit && !r3_positive) {
        bool carry = inc(r3_begin, r3_end);
        arithmetic_assert(!carry);
      }
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      r3_positive = signed_add(r3_positive, r3_begin, r3_end, true, rinf_begin, rinf_end);
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      shift_left(r3_begin, r3_end, 1);
      *r3_begin |= r3_bit;
      r2_positive = signed_add(r2_positive, r2_begin, r2_end, r1_positive, r1_begin, r1_end);
      r2_positive = signed_sub(r2_positive, r2_begin, r2_end, true, rinf_begin, rinf_end, false);
      r1_positive = signed_sub(r1_positive, r1_begin, r1_end, r3_positive, r3_begin, r3_end, false);
      // cout << "r0 " << r0_begin[1] << " " << r0_begin[0] << endl;
      // cout << "r1 " << (r1_positive ? "" : "-") << r1_begin[2] << " " << r1_begin[1] << " " << r1_begin[0] << endl;
      // cout << "r2 " << (r2_positive ? "" : "-") << r2_begin[2] << " " << r2_begin[1] << " " << r2_begin[0] << endl;
      // cout << "r3 " << (r3_positive ? "" : "-") << r3_begin[2] << " " << r3_begin[1] << " " << r3_begin[0] << endl;
      // cout << "r4 " << rinf_begin[1] << " " << rinf_begin[0] << endl;

      // Recompose the result
      // Note: We use wrong end of target to trick the space assertions
      // in the arithmetic operation, but really our result fits into r,
      // so this is a valid trick.
      bool check = true;
      check = signed_add(true, r0_begin + part_size, r1_begin, r1_positive, r1_begin, r1_end);
      arithmetic_assert(check);
      check = signed_add(true, r0_begin + 2 * part_size, r2_begin, r2_positive, r2_begin, r2_end);
      arithmetic_assert(check);
      check = signed_add(true, r0_begin + 3 * part_size, r3_begin, r3_positive, r3_begin, r3_end);
      arithmetic_assert(check);
      return rinf_end;
    }

    inline size_type unbalanced_space_usage(size_type size_a, size_type size_b)
    {
      return size_a + size_b + space_usage(size_b, size_b);
    }

    inline size_type school_space_usage(size_type size_a, size_type size_b)
    {
      return size_a + size_b;
    }

    size_type karatsuba_space_usage(size_type size_a)
    {
      size_type part_size = size_a - size_a / 2;
      if (part_size + 1 == size_a) {
        // In this case, the lower recursion would not terminate, but the worst case can only appear once and
        // The second time, it gets smaller.
        return 12 * part_size + 4 + space_usage(part_size, part_size);
      } else {
        return space_usage(part_size + 1, part_size + 1) + 6 * part_size + 2;
      }
    }

    size_type toom3_space_usage(size_type size_a)
    {
      arithmetic_assert(size_a >= 3);
      size_type part_size = size_a - 2 * size_a / 3;
      return space_usage(part_size + 1, part_size + 1) + 18 * part_size + 12;
    }

    size_type space_usage(size_type size_a, size_type size_b)
    {
      if (size_a < size_b) {
        return space_usage(size_b, size_a);
      }
      if (size_b == 0) {
        return 0;
      }
      if (size_b == 1) {
        return size_a + 1;
      } else if (size_b <= size_a - size_a / 2) {
        return unbalanced_space_usage(size_a, size_b);
      } else if (size_a < KARATSUBA_THRESHOLD) {
        return school_space_usage(size_a, size_b);
      } else if (size_a < TOOM3_THRESHOLD) {
        return karatsuba_space_usage(size_a);
      } else {
        return toom3_space_usage(size_a);
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
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(b_end >= b_begin);
      arithmetic_assert(space_end >= space_begin);
      // No aliases with output range. Note that a and b may overlap if a number is multiplied with itself.
      arithmetic_assert(a_end <= space_begin || space_end <= a_begin);
      arithmetic_assert(b_end <= space_begin || space_end <= b_begin);
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
      arithmetic_assert(size_type(space_end - space_begin) >= a_size + b_size);
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
        c_end = unbalanced_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      } else if (a_size < KARATSUBA_THRESHOLD) {
        c_end = school_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      } else if (a_size < TOOM3_THRESHOLD) {
        c_end = karatsuba_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      } else {
        c_end = toom3_multiply(a_begin, a_end, b_begin, b_end, space_begin, space_end);
      }
      size_type c_size = c_end - c_begin;
      arithmetic_assert(c_size <= a_size + b_size);
      arithmetic_assert(c_size >= a_size + b_size - 1);
      return c_end;
    }

  } // namespace LongArithmetic

} // namespace DataStructures
