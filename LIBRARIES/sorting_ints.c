//
//  main.c
//  qsort
//
//  Created by Pedro Guerreiro on 05/04/2021.
//

#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wextra"
#pragma GCC diagnostic error "-Wconversion"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#include "our_ints.h"

const char *author = "Pedro Guerreiro";

const int max_array_size = 2000000;
//const int max_large_array_size = 16000000;
const int max_large_array_size = 100000000;

// --------------------------------

int millisecs(clock_t x)
{
  return (int)(x * 1000 / CLOCKS_PER_SEC);
}

// --------------------------------

void ints_quicksort(int *a, int n)
{
  assert(n > 0);
  int i = 0;
  int j = n-1;
  int p = a[n/2];
  do
  {
    while (a[i] < p)
      i++;
    while (p < a[j])
      j--;
    if (i <= j)
      ints_exchange(a, i++, j--);
  }
  while (i <= j);
  if (j > 0)
    ints_quicksort(a, j+1);
  if (i < n-1)
    ints_quicksort(a+i, n-i);
}

void ints_quicksort_gen(int *a, int n, int cmp(int, int))
{
  assert(n > 0);
  int i = 0;
  int j = n-1;
  int p = a[n/2];
  do
  {
//  while (a[i] < p)
    while (cmp(a[i], p) < 0)
      i++;
//  while (p < a[j])
    while (cmp(p, a[j]) < 0)
      j--;
    if (i <= j)
      ints_exchange(a, i++, j--);
  }
  while (i <= j);
  if (j > 0)
    ints_quicksort_gen(a, j+1, cmp);
  if (i < n-1)
    ints_quicksort_gen(a+i, n-i, cmp);
}

int int_cmp1(int x, int y)  // obsolete
{
  return x < y ? -1 : x > y ? 1 : 0;
}

int int_cmp(int x, int y)
{
  return (x > y) - (x < y);
}

int int_weight(int x)
{
  int result = 0;
  if (x < 0)
    result = -int_weight(-x);  // For negative numbers...
  else
    while (x > 0)
    {
      result += x % 10;
      x /= 10;
    }
  return result;
}

void unit_test_int_weight(void)
{
  assert(int_weight(0) == 0);
  assert(int_weight(7) == 7);
  assert(int_weight(62) == 8);
  assert(int_weight(30) == 3);
  assert(int_weight(-35) == -8);
  assert(int_weight(-999) == -27);
  assert(int_weight(100000) == 1);
  assert(int_weight(-100000) == -1);
  assert(int_weight(2000000002) == 4);
  assert(int_weight(999999) == 54);
  assert(int_weight(123123123) == 18);
}

int int_cmp_by_weight(int x, int y)
{
  int result = int_weight(x) - int_weight(y);
  if (result == 0)
    result = int_cmp(x, y);
  return result;
}

int int_cmp_by_weight_only(int x, int y)
{
  return int_weight(x) - int_weight(y);
}

void qsort(void *a, size_t number, size_t width,
   int cmp (const void *, const void *));

int int_cmp_v(const void *p, const void *q)
{
  int x = *(int *) p;
  int y = *(int *) q;
  return int_cmp(x, y);
}

void ints_qsort(int *a, int n)
{
  qsort(a, (size_t)n, sizeof(int), int_cmp_v);
}

// -----------------

void test_timing_isort(void)
{
  int a[max_array_size];
  int n = ints_get(a);
  clock_t t1 = clock();
  ints_isort(a, n);
  clock_t t2 = clock();
  assert(ints_is_sorted(a, n));
  int w = millisecs(t2 - t1);
  printf("%d\n", w);
}

// Version with automatic array in test function.
// Will not work with large arrays.
void test_timing_msort_small_arrays(void)
{
  int a[max_array_size];
  int n = ints_get(a);
  clock_t t1 = clock();
  ints_msort(a, n);
  clock_t t2 = clock();
  assert(ints_is_sorted(a, n));
  int w = millisecs(t2 - t1);
  printf("%d\n", w);
}

// Version with dynamic array in test function.
// Will work with larger arrays.

 void test_timing_msort(void)
 {
   int *a = ints_new(max_large_array_size);
   int n = ints_get(a);
   clock_t t1 = clock();
   ints_msort(a, n);
   clock_t t2 = clock();
   assert(ints_is_sorted(a, n));
   int w = millisecs(t2 - t1);
   printf("%d\n", w);
   free(a);
}

void test_timing_quicksort(void)
{
  int *a = ints_new(max_large_array_size);
  int n = ints_get(a);
  clock_t t1 = clock();
  ints_quicksort(a, n);
  clock_t t2 = clock();
  assert(ints_is_sorted(a, n));
  int w = millisecs(t2 - t1);
  printf("%d\n", w);
  free(a);
}

void test_timing_qsort(void)
{
  int *a = ints_new(max_large_array_size);
  int n = ints_get(a);
  clock_t t1 = clock();
  ints_qsort(a, n);
  clock_t t2 = clock();
  assert(ints_is_sorted(a, n));
  int w = millisecs(t2 - t1);
  printf("%d\n", w);
  free(a);
}

void test_quicksort_gen(void)
{
  int a[max_array_size];
  int n = ints_get(a);
  ints_println_basic(a, n);
  ints_quicksort_gen(a, n, int_cmp_by_weight);
  ints_println_basic(a, n);
}

void demo_quicksort_is_not_stable(void)
{
  int a[max_array_size];
  int n = ints_get(a);
  ints_println_basic(a, n);
  ints_quicksort_gen(a, n, int_cmp);
  ints_println_basic(a, n);
  ints_quicksort_gen(a, n, int_cmp_by_weight_only);
  ints_println_basic(a, n);
}

void test_timing_quicksort_gen(void)
{
  int *a = ints_new(max_large_array_size);
  int n = ints_get(a);
  clock_t t1 = clock();
  ints_quicksort_gen(a, n, int_cmp);
  clock_t t2 = clock();
  assert(ints_is_sorted(a, n));
  int w = millisecs(t2 - t1);
  printf("%d\n", w);
  free(a);
}

void create_random_file(void)
{
  srand((unsigned int) time(0));
  rand(); rand();
  int x = int_get();
  int *a = ints_new(x);
  int n = ints_random(INT_MAX,x, a);
  ints_println(a, n, "\n");
  free(a);
}

void demo_difference_overflow(void)
{
  int x = 2000000000;
  int y = -2000000000;
  int z = x - y;
  printf("%d\n", z);
}

void unit_tests(void)
{
  unit_test_int_weight();
}

// --------------------------------

int main(int argc, char **argv)
{
  unit_tests();
  int x = 'U';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_timing_isort();
  else if (x == 'B')
    test_timing_msort();
  else if (x == 'C')
    test_timing_quicksort();
  else if (x == 'D')
    test_quicksort_gen();
  else if (x == 'E')
    demo_quicksort_is_not_stable();
  else if (x == 'F')
    test_timing_quicksort_gen();
  
  else if (x == 'G')
    test_timing_qsort();

  else if (x == 'S')
    demo_difference_overflow();
  else if (x == 'T')
    create_random_file();

  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);

  return 0;
}
