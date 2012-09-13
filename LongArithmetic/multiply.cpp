#include "multiply.h"
#include "add.h"
#include "subtract.h"
#include "assembly.h"
#include "compare.h"
#include "shifts.h"
#include "thresholds.h"
#include "incdec.h"
#include "debug.h"
#include <cstring>

namespace LongArithmetic {

  namespace Operations {

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
        // Note that we want this to be modulo 1 << PART_SIZE, so * is fine.
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

    inline part_type* karatsuba_multiply(const part_type* const a_begin,
                                         const part_type* const a_end,
                                         const part_type* const b_begin,
                                         const part_type* const b_end,
                                         part_type* const space_begin,
                                         part_type* const space_end)

    {
      // Assume len(x) >= len(y) >= ceil(len(x) / 2)
      arithmetic_assert(a_end >= a_begin);
      arithmetic_assert(b_end >= b_begin);
      size_type a_size = a_end - a_begin;
      size_type b_size = b_end - b_begin;
      size_type part_size = a_size - a_size / 2;
      arithmetic_assert(a_size >= b_size);
      arithmetic_assert(b_size >= part_size);
      // Termination relies on this
      arithmetic_assert(part_size >= 1);
      // Don't allow aliasing with output pointer
      arithmetic_assert(a_end <= space_begin || space_end <= a_begin);
      arithmetic_assert(b_end <= space_begin || space_end <= b_begin);
      // Used space without recursion
      arithmetic_assert(space_begin + 6 * part_size + 2 < space_end);

      // Define aliases to make later code more clear
      const part_type* const a0_begin (a_begin);
      const part_type* const a0_end (a_begin + part_size);
      const part_type* const a1_begin (a0_end);
      const part_type* const a1_end (a_end);
      // printit("p0", true, a0_begin, a0_end);
      // printit("p1", true, a1_begin, a1_end);

      const part_type* const b0_begin (b_begin);
      const part_type* const b0_end (b_begin + part_size);
      const part_type* const b1_begin (b0_end);
      const part_type* const b1_end (b_end);
      // printit("p0", true, b0_begin, b0_end);
      // printit("p1", true, b1_begin, b1_end);

      // Pointwise multiply at 0
      part_type* const r0_begin (space_begin);
      part_type* const r0_end = multiply(a0_begin, a0_end, b0_begin, b0_end, r0_begin, space_end);
      // printit("r(0)", true, r0_begin, r0_end);

      // pointwise multiply at infty
      part_type* const rinf_begin (space_begin + 2 * part_size);
      part_type* const rinf_end = multiply(a1_begin, a1_end, b1_begin, b1_end, rinf_begin, space_end);
      // printit("r(inf)", true, rinf_begin, rinf_end);

      // Prepare the result range and set the gaps to 0.
      part_type* const c_end = space_begin + a_size + b_size;
      zero_out(r0_end, rinf_begin);
      if (c_end > rinf_end) {
        // If rinf is empty, this is not necessary and not valid, because rinf is outside the result range.
        zero_out(rinf_end, c_end);
      }

      // Aliases for the evaluatoin points
      part_type* const p_1_begin = c_end;
      part_type* const p_1_end = p_1_begin + part_size;

      part_type* const q_1_begin = p_1_end;
      part_type* const q_1_end = q_1_begin + part_size;

      // Evaluate the polynomials
      copy_pad_part(p_1_begin, p_1_end, a0_begin, a0_end);
      bool p_1_positive = signed_sub(true, p_1_begin, p_1_end, true, a1_begin, a1_end, false);
      // printit("p(-1)", p_1_positive, p_1_begin, p_1_end);

      copy_pad_part(q_1_begin, q_1_end, b0_begin, b0_end);
      bool q_1_positive = signed_sub(true, q_1_begin, q_1_end, true, b1_begin, b1_end, false);
      // printit("q(-1)", q_1_positive, q_1_begin, q_1_end);

      // Pointwise multiply
      part_type* const r_1_begin (q_1_end);
      part_type* r_1_end = multiply(p_1_begin, p_1_end, q_1_begin, q_1_end, r_1_begin, space_end);
      bool r_1_positive = p_1_positive ^ q_1_positive;
      zero_out(r_1_end, r_1_begin + 2 * part_size + 1);
      r_1_end = r_1_begin + 2 * part_size + 1;
      // printit("r(-1)", r_1_positive, r_1_begin, r_1_end);

      // Interpolate
      r_1_positive = signed_add(r_1_positive, r_1_begin, r_1_end, true, r0_begin, r0_end);
      r_1_positive = signed_add(r_1_positive, r_1_begin, r_1_end, true, rinf_begin, rinf_end);
      // printit("r1", r_1_positive, r_1_begin, r_1_end);

      // Recompose result
      signed_add(true, space_begin + part_size, c_end, r_1_positive, r_1_begin, r_1_end);
      // printit("c", true, space_begin, c_end);
      return c_end;
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
      // printit("a", true, a_begin, a_end);

      const part_type* const b0_begin (b_begin);
      const part_type* const b0_end (b_begin + part_size);
      const part_type* const b1_begin (b0_end);
      const part_type* const b1_end (std::min(b1_begin + part_size, b_end));
      const part_type* const b2_begin (b1_end);
      const part_type* const b2_end (b_end);
      // printit("b", true, b_begin, b_end);

      // Pointwise multiply at 0
      part_type* const r0_begin (space_begin);
      part_type* const r0_end = multiply(a0_begin, a0_end, b0_begin, b0_end, r0_begin, space_end);

      // pointwise multiply at infty
      part_type* const rinf_begin (space_begin + 4 * part_size);
      part_type* const rinf_end = multiply(a2_begin, a2_end, b2_begin, b2_end, rinf_begin, space_end);

      // Prepare the result range and set the gaps to 0.
      part_type* const c_end = space_begin + a_size + b_size;
      zero_out(r0_end, rinf_begin);
      if (c_end > rinf_end) {
        // If rinf is empty, this is not necessary and not valid, because rinf is outside the result range.
        zero_out(rinf_end, c_end);
      }

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
      // printit("p(1)", true, p1_begin, p1_end);
      // printit("p(-1)", p_1_positive, p_1_begin, p_1_end);
      // printit("p(-2)", p_2_positive, p_2_begin, p_2_end);

      copy_pad_part(q1_begin, q1_end, b0_begin, b0_end);
      add(q1_begin, q1_end, b2_begin, b2_end);
      copy_pad_part(q_1_begin, q_1_end, q1_begin, q1_end);
      add(q1_begin, q1_end, b1_begin, b1_end);
      bool q_1_positive = signed_sub(true, q_1_begin, q_1_end, true, b1_begin, b1_end, false);
      copy_pad_part(q_2_begin, q_2_end, q_1_begin, q_1_end);
      bool q_2_positive = signed_add(q_1_positive, q_2_begin, q_2_end, true, b2_begin, b2_end);
      shift_left(q_2_begin, q_2_end, 1);
      q_2_positive = signed_sub(q_2_positive, q_2_begin, q_2_end, true, b0_begin, b0_end, false);
      // printit("q(1)", true, q1_begin, q1_end);
      // printit("q(-1)", q_1_positive, q_1_begin, q_1_end);
      // printit("q(-2)", q_2_positive, q_2_begin, q_2_end);


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

      // printit("r(0)", true, r0_begin, r0_end);
      // printit("r(1)", true, r1_begin, r1_end);
      // printit("r(-1)", r_1_positive, r_1_begin, r_1_end);
      // printit("r(-2)", r_2_positive, r_2_begin, r_2_end);
      // printit("r(inf)", true, rinf_begin, rinf_end);

      // Interpolate
      part_type* const r3_begin (r_2_begin);
      part_type* const r3_end (r_2_begin + 2 * part_size + 2);
      zero_out(r_2_end, r3_end);
      bool r3_positive = signed_sub(r_2_positive, r3_begin, r3_end, true, r1_begin, r1_end, false);
      // printit("r3", r3_positive, r3_begin, r3_end);
      div_exact_3(r3_begin, r3_end);
      // printit("r3", r3_positive, r3_begin, r3_end);
      // We reuse the variable: r1 is now the coefficient r1, not r(1) any more.
      bool r1_positive = signed_sub(true, r1_begin, r1_end, r_1_positive, r_1_begin, r_1_end, false);
      // printit("r1", r1_positive, r1_begin, r1_end);
      arithmetic_assert(!(*r1_begin & 1));
      shift_right(r1_begin, r1_end, 1);
      // printit("r1", r1_positive, r1_begin, r1_end);
      part_type* const r2_begin (r_1_begin);
      part_type* const r2_end (r_1_begin + 2 * part_size + 2);
      zero_out(r_1_end, r2_end);
      bool r2_positive = signed_sub(r_1_positive, r2_begin, r2_end, true, r0_begin, r0_end, false);
      // printit("r2", r2_positive, r2_begin, r2_end);
      r3_positive = signed_sub(r3_positive, r3_begin, r3_end, r2_positive, r2_begin, r2_end, true);
      // printit("r3 = r2 - r3", r3_positive, r3_begin, r3_end);
      // Instead of shifting r_inf, we shift one mor than we want and shift back afterwards
      arithmetic_assert(!(*r3_begin & 1));
      part_type r3_bit = (*r3_begin >> 1) & 1;
      shift_right(r3_begin, r3_end, 2);
      // Two complement trick
      if (r3_bit && !r3_positive) {
        arithmetic_assert_nocarry(inc(r3_begin, r3_end));
      }
      // printit("r3 >>= 2", r3_positive, r3_begin, r3_end);
      r3_positive = signed_add(r3_positive, r3_begin, r3_end, true, rinf_begin, rinf_end);
      // printit("r3 += rinf", r3_positive, r3_begin, r3_end);
      shift_left(r3_begin, r3_end, 1);
      *r3_begin |= r3_bit;
      // printit("r3 <<= 1", r3_positive, r3_begin, r3_end);
      r2_positive = signed_add(r2_positive, r2_begin, r2_end, r1_positive, r1_begin, r1_end);
      // printit("r2", r2_positive, r2_begin, r2_end);
      r2_positive = signed_sub(r2_positive, r2_begin, r2_end, true, rinf_begin, rinf_end, false);
      // printit("r2", r2_positive, r2_begin, r2_end);
      r1_positive = signed_sub(r1_positive, r1_begin, r1_end, r3_positive, r3_begin, r3_end, false);
      // printit("r0", true, r0_begin, r0_end);
      // printit("r1", r1_positive, r1_begin, r1_end);
      // printit("r2", r2_positive, r2_begin, r2_end);
      // printit("r3", r3_positive, r3_begin, r3_end);
      // printit("r4", true, rinf_begin, rinf_end);

      // Recompose the result
      bool check = true;
      check = signed_add(true, r0_begin + part_size, c_end, r1_positive, r1_begin, r1_end);
      arithmetic_assert(check);
      check = signed_add(true, r0_begin + 2 * part_size, c_end, r2_positive, r2_begin, r2_end);
      arithmetic_assert(check);
      check = signed_add(true, r0_begin + 3 * part_size, c_end, r3_positive, r3_begin, r3_end);
      arithmetic_assert(check);
      // cout << a_size + b_size << " " << *c_end << endl;
      // printit("c", true, space_begin, c_end);
      return c_end;
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
#ifdef ARITHMETIC_DEBUG
      // Check that the part beyond the expected length is only padding
      for (const part_type* it = space_begin + a_size + b_size; it < c_end; ++it) {
        arithmetic_assert(*it == 0);
      }
      if (to_mpz(a_begin, a_end) * to_mpz(b_begin, b_end) != to_mpz(space_begin, c_end)) {
        // printit("a", true, a_begin, a_end);
        // printit("b", true, b_begin, b_end);
        // printit("a * b", true, space_begin, c_end);
        cout << "mpz(a * b) " << to_mpz(space_begin, c_end) << endl;
        cout << "mpz(a) * mpz(b) " << to_mpz(a_begin, a_end) * to_mpz(b_begin, b_end) << endl;
        assert(false);
      }
#endif
      return std::min(c_end, space_begin + a_size + b_size);
    }

  } // namespace LongArithmetic

} // namespace LongArithmetic
