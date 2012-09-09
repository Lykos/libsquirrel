#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void move_part(int* A, size_t N, size_t target, size_t source, size_t size, int show_steps)
{
  assert(source + size <= N);
  assert(target + size <= N);
  if (show_steps) {
    printf("Moving size %d from %d to %d.\n", size, source, target);
  }
  memmove(A + target, A + source, size * sizeof(int));
}

void swap_parts(int* A, size_t N, size_t first_begin, size_t second_begin, size_t size, int show_steps)
{
  if (show_steps) {
    printf("Swapping size %d at %d and %d.\n", size, first_begin, second_begin);
  }
  assert(first_begin + size <= N);
  assert(second_begin + size <= N);
  size_t i;
  for (i = 0; i < size; ++i) {
    int x = A[first_begin + i];
    A[first_begin + i] = A[second_begin + i];
    A[second_begin + i] = x;
  }
}

void move_to_beginning(int* A, size_t N, size_t begin, size_t size, int show_steps)
{
  assert(begin <= N);
  assert(size <= N);
  // Denotes the start of our "working range". Increases during
  // the algorithm and becomes N
  size_t part_start = 0;
  // Note: Keeping the size is crucial since begin == end could
  // mean that the range is empty or full.
  size_t end = (begin + size) % N;
  while (part_start != N) {
    size_t i;
    if (show_steps) {
      for (i = 0; i < N; ++i) {
	printf("%d ", A[i]);
      }
      printf("\n");
      printf("part_start %d  begin %d  end %d  size %d\n", part_start, begin, end, size);
    }
    // loop invariants
    assert(part_start < N);
    // The two pointers are in our range
    assert(part_start <= begin && begin <= N);
    assert(part_start <= end && end <= N);
    // size is valid (wrapped case, non-empty, non-full case)
    assert(begin <= end || (N - begin) + (end - part_start) == size);
    // size is valid (non wrapped case, non-empty, non-full case)
    assert(begin >= end || end - begin == size);
    // size is valid (working range is full or empty case)
    assert(begin != end || size == 0 || part_start + size == N);
    if (size == 0 || begin == N || begin == part_start) {
      // ##|1234|# -> 1234### ||
      if (show_steps) {
	printf("Case 1:\nTerminating\n");
      }
      // #||# -> ## ||
      // 12|##| -> 12## ||
      // |12|## -> 12## ||
      break;
      /* Not necessary any more, but would be the correct transformation:
	 part_start = N;
	 begin = N;
	 end = N;
	 size = 0;*/
    } else if (end == part_start) {
      // |##|123 -> ##|123|
      if (show_steps) {
	printf("Case 2:\n");
	printf("Setting end to %d.\n", N);
      }
      end = N;
    } else if (begin < end) {
      // ##|1234|# -> 1234### ||
      if (show_steps) {
	printf("Case 3:\n");
      }
      move_part(A, N, part_start, begin, size, show_steps);
      break;
      /* Not necessary any more, but would be the correct transformation:
	 part_start = N;
	 begin = N;
	 end = N;
	 size = 0;*/
    } else {
      size_t end_size = end - part_start;
      size_t begin_size = N - begin;
      assert(begin_size + end_size == size);
      if (end_size >= begin_size) {
	// 345|#|12 -> 12 5|#|34
	if (show_steps) {
	  printf("Case 4:\n");
	}
	swap_parts(A, N, part_start, begin, begin_size, show_steps);
	assert(begin_size > 0); // Necessary for progress
	part_start += begin_size;
	size = end_size;
	// begin, end remain unchanged
      } else if (begin - part_start <= begin_size) {
	// 56|#|1234 -> 123 56|#|4
	size_t size_moved = begin - part_start;
	assert(size_moved >= end_size); // else the next step would be more efficient
	if (show_steps) {
	  printf("Case 5\n");
	}
	swap_parts(A, N, part_start, begin, end_size, show_steps);
	move_part(A, N, end, begin + end_size, begin - end, show_steps);
	assert(end_size + (begin - end) == size_moved);
	size -= size_moved;
	part_start = begin;
	begin += size_moved;
	end += size_moved;
      } else if (end_size <= begin_size) {
	// 45|##|123 -> 123 #|45|# 
	if (show_steps) {
	  printf("Case 6\n");
	}
	swap_parts(A, N, part_start, begin, end_size, show_steps);
	move_part(A, N, end, begin + end_size, begin_size - end_size, show_steps);
	part_start += begin_size;
	size = end_size;
	end = begin + end_size;
	// begin remains unchanged
      } else {
	// No case applies, this should never happen
	assert(0);
      }
    }
  }
}


int main()
{
  int N = 20;
  int A[20];
  size_t size = 17;
  size_t begin = 15;
  size_t i;
  for (i = 0; i < size; ++i) {
    A[(begin + i) % N] = i;
  }
  move_to_beginning(A, N, begin, size, 0);
  for (i = 0; i < size; ++i) {
    printf("%d ", A[i]);
  }
  printf("\n");
  return 0;
}
