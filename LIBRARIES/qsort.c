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
#include "our_doubles.h"
#include "our_strings.h"

const char *author = "Pedro Guerreiro";

const int max_array_size = 200000;

// --------------------------------

// For reference:
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

int int_cmp_not_used_see_below(int x, int y)
{
  return x < y ? -1 : x > y ? 1 : 0;
}

int int_cmp(int x, int y)
{
  return (x > y) - (x < y);
}

int int_cmp_v1(const void *p, const void *q)
{
  int x = *(int *) p;
  int y = *(int *) q;
  return int_cmp(x, y);
}

int int_cmp_v(const void *p, const void *q)
{
  return int_cmp(*(int *)p, *(int *)q);
}

void ints_qsort(int *a, int n)
{
  qsort(a, (size_t)n, sizeof(int), int_cmp_v);
}

int int_cmp_down(int x, int y)
{
  return -((x > y) - (x < y));
}

int int_cmp_down_v_not_used_see_below(const void *p, const void *q)
{
  return int_cmp_down(*(int *)p, *(int *)q);
}

int int_cmp_down_v(const void *p, const void *q)
{
  return -int_cmp_v(p, q);
}

int weight(int x)
{
  int result = 0;
  if (x < 0)
    result = -weight(-x);  // For negative numbers...
  else
    while (x > 0)
    {
      result += x % 10;
      x /= 10;
    }
  return result;
}

void unit_test_weight(void)
{
  assert(weight(0) == 0);
  assert(weight(7) == 7);
  assert(weight(62) == 8);
  assert(weight(30) == 3);
  assert(weight(-35) == -8);
  assert(weight(-999) == -27);
  assert(weight(100000) == 1);
  assert(weight(-100000) == -1);
  assert(weight(2000000002) == 4);
  assert(weight(999999) == 54);
  assert(weight(123123123) == 18);
}

int int_cmp_by_weight(int x, int y)
{
  int result = weight(x) - weight(y);
  if (result == 0)
    result = int_cmp(x, y);
  return result;
}

int int_cmp_by_weight_v(const void *p, const void *q)
{
  return int_cmp_by_weight(*(int *)p, *(int *)q);
}

int int_cmp_by_date(int x, int y) // date is in DDMMYYYY format
{
  int result = x % 10000 - y % 10000;
  if (result == 0)
  {
    result = x / 10000 % 100 - y / 10000 % 100;
    if (result == 0)
      result = x / 1000000 - y / 1000000;
  }
  return result;
}

int int_cmp_by_date_v(const void *p, const void *q)
{
  return int_cmp_by_date(*(int *) p, *(int *) q);
}

void dma_show(int *a, int n)
{
  int i;
  printf("%d", n);
  for (i = 0; i < n; i++)
    printf(" %08d", a[i]);
  printf("\n");
}

// compare by parity:
int int_cmp_by_parity(int x, int y)
{
  int result = x%2 - y%2;
  if (result == 0)
    result = int_cmp(x, y);
  return result;
}

int int_cmp_by_parity_v(const void *p, const void *q)
{
  return int_cmp_by_parity(*(int *) p, *(int *) q);
}

void test_qsort_ints(void)
{
  int a[1000];
  int n = ints_get(a);
  ints_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(int), int_cmp_v);
  ints_println(a, n, " ");
}

void test_qsort_ints_down(void)
{
  int a[1000];
  int n = ints_get(a);
  ints_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(int), int_cmp_down_v);
  ints_println(a, n, " ");
}

void test_qsort_ints_by_weight(void)
{
  int a[1000];
  int n = ints_get(a);
  ints_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(int), int_cmp_by_weight_v);
  ints_println(a, n, " ");
}

void test_qsort_ints_by_parity(void)
{
  int a[1000];
  int n = ints_get(a);
  ints_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(int), int_cmp_by_parity_v);
  ints_println(a, n, " ");
}

void test_qsort_ints_by_date(void)
{
  int a[1000];
  int n = ints_get(a);
  qsort(a, (size_t)n, sizeof(int), int_cmp_by_date_v);
  ints_printf("%08d\n", a, n);
}

// --------------------------------

int str_cmp_v0(const void *p, const void *q)
{
  const char **px = (const char **) p;
  const char **py = (const char **) q;
  return strcmp(*px, *py);
}

int str_cmp_v1(const void *p, const void *q)
{
  const char *px = *(const char **) p;
  const char *py = *(const char **) q;
  return strcmp(px, py);
}

int str_cmp_v(const void *p, const void *q)
{
  return strcmp(*(char **)p, *(char **)q);
}

int str_cmp_v_wrong(const void *p, const void *q)  // This is WRONG
{
  return strcmp((const char *) p, (const char *) q);
}

int str_cmp_by_length(const char *x, const char *y)
{
  int result = (int) (strlen(x) - strlen(y));
  if (result == 0)
    result = strcmp(x, y);
  return result;
}

int str_cmp_by_length_v(const void *p, const void *q)
{
  return str_cmp_by_length(*(char **)p, *(char **)q);
}

int str_cmp_by_length_only(const char *x, const char *y)
{
  return (int)(strlen(x) - strlen(y));
}

int str_cmp_by_length_only_v(const void *p, const void *q)
{
  return str_cmp_by_length_only(*(char **)p, *(char **)q);
}

void test_qsort_strings()
{
  const char *a[1000];
  int n = strings_getwords(a);
  strings_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(char *), str_cmp_v);
  strings_println(a, n, " ");
}

void test_qsort_strings_by_length()
{
  const char *a[1000];
  int n = strings_getwords(a);
  strings_println(a, n, " ");
  qsort(a, (size_t)n, sizeof(char*), str_cmp_by_length_v);
  strings_println(a, n, " ");
}

void test_isort_strings_by_length_composed()
{
  const char *a[1000];
  int n = strings_getwords(a);
  strings_println(a, n, ",");
  strings_isort(a, n);
  strings_println(a, n, ",");
  strings_isort_gen(a, n, str_cmp_by_length_only);
  strings_println(a, n, ",");
}

void demo_qsort_strings_by_length_composed_does_not_work()
{
  const char *a[1000];
  int n = strings_getwords(a);
  strings_println(a, n, ",");
  qsort(a, (size_t)n, sizeof(char*), str_cmp_v);
  strings_println(a, n, ",");
  qsort(a, (size_t)n, sizeof(char*), str_cmp_by_length_only_v);
  strings_println(a, n, ",");
}

// --------------------------------

int chr_cmp_v0(const void *p, const void *q)
{
  char *x = (char *) p;
  char *y = (char *) q;
  return *x - *y;
}

int chr_cmp_v(const void *p, const void *q)
{
  return *(char *) p - *(char *) q;
}

void test_qsort_chars()
{
  char line[max_line_length];
  while (str_getline(line) != EOF)
  {
    qsort(line, strlen(line), sizeof(char), chr_cmp_v);
    printf("%s\n", line);
  }
}

// --------------------------------

typedef struct {
  const char *string;
  int number;
} StringInt;

StringInt string_int(const char *string, int number)
{
  StringInt result = {string, number};
  return result;
}

StringInt string_int_from_csv(const char *s)
{
  int z = str_count_while_not(s, ',');
  return string_int(str_ndup(s, z), atoi(s+z+1));
}

int string_ints_read(FILE *f, StringInt *a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = string_int_from_csv(line);
  return result;
}

const StringInt *string_int_ref(const char *string, int number)
{
  StringInt *result = malloc(sizeof(StringInt));
  result -> number = number;
  result -> string = string;
  return result;
}

const StringInt *string_int_from_csv_ref(const char *s)
{
  int z = str_count_while_not(s, ',');
  return string_int_ref(str_ndup(s, z), atoi(s+z+1));
}

int string_ints_read_ref(FILE *f, const StringInt **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = string_int_from_csv_ref(line);
  return result;
}

int string_int_cmp(StringInt x, StringInt y)
{
  int result = strcmp(x.string, y.string);
  if (result == 0)
    result = int_cmp(x.number, y.number);
  return result;
}

int string_int_cmp_v(const void *p, const void *q)
{
  return string_int_cmp(*(StringInt *)p, *(StringInt *)q);
}

int string_int_cmp_by_number(StringInt x, StringInt y)
{
  int result = int_cmp(x.number, y.number);
  if (result == 0)
    result = strcmp(x.string, y.string);
  return result;
}

int string_int_cmp_by_number_v(const void *p, const void *q)
{
  return string_int_cmp_by_number(*(StringInt *)p, *(StringInt *)q);
}

int string_int_cmp_by_number_down(StringInt x, StringInt y)
{
  int result = -int_cmp(x.number, y.number);
  if (result == 0)
    result = strcmp(x.string, y.string);
  return result;
}

int string_int_cmp_by_number_down_v(const void *p, const void *q)
{
  return string_int_cmp_by_number_down(*(StringInt *)p, *(StringInt *)q);
}

void string_ints_print(const StringInt *a, int n)
{
  for (int i = 0; i < n; i++)
    printf("%s %d\n", a[i].string, a[i].number);
}

void test_qsort_string_ints()
{
  StringInt a[1000];
  int n = string_ints_read(stdin, a);
//  string_ints_print(a, n);
//  printf("\n");
  qsort(a, (size_t)n, sizeof(StringInt), string_int_cmp_v);
  string_ints_print(a, n);
}

void test_qsort_string_ints_by_number()
{
  StringInt a[1000];
  int n = string_ints_read(stdin, a);
//  string_ints_print(a, n);
//  printf("\n");
  qsort(a, (size_t)n, sizeof(StringInt), string_int_cmp_by_number_v);
  string_ints_print(a, n);
}

void test_qsort_string_ints_by_number_down()
{
  StringInt a[1000];
  int n = string_ints_read(stdin, a);
//  string_ints_print(a, n);
//  printf("\n");
  qsort(a, (size_t)n, sizeof(StringInt), string_int_cmp_by_number_down_v);
  string_ints_print(a, n);
}

int string_int_ref_cmp(StringInt *x, StringInt *y)
{
  return string_int_cmp(*x, *y);
}

int string_int_ref_cmp_v(const void *p, const void *q)
{
  return string_int_ref_cmp(*(StringInt **)p, *(StringInt **)q);
}

int string_int_ref_cmp_by_number(StringInt *x, StringInt *y)
{
  return string_int_cmp_by_number(*x, *y);
}

int string_int_ref_cmp_by_number_v(const void *p, const void *q)
{
  return string_int_ref_cmp_by_number(*(StringInt **)p, *(StringInt **)q);
}

int ptrs_copy(const void **a, int n, const void **b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, (size_t)n * sizeof(void *));
  return n;
}

int string_int_copy_ref(const StringInt *a, int n, const StringInt **b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    b[result++] = a+i;
  assert(result == n);
  return result;
}

void string_ints_print_ref(const StringInt **a, int n)
{
  for (int i = 0; i < n; i++)
    printf("%s %d\n", a[i]->string, a[i]->number);
}

void test_qsort_string_ints_twice()
{
  StringInt a[1000];
  int n = string_ints_read(stdin, a);
  qsort(a, (size_t)n, sizeof(StringInt), string_int_cmp_v);
  const StringInt *b[n];
  int m = string_int_copy_ref(a, n, b);
  qsort(b, (size_t)m, sizeof(StringInt *), string_int_ref_cmp_by_number_v);
  string_ints_print(a, n);
  printf("\n");
  string_ints_print_ref(b, m);
}

void test_qsort_string_ints_twice_better()
{
  const StringInt *a[1000];
  int n = string_ints_read_ref(stdin, a);
  qsort(a, (size_t)n, sizeof(StringInt *), string_int_ref_cmp_v);
  const StringInt *b[n];
  int m = ptrs_copy((const void **)a, n, (const void **)b);
  qsort(b, (size_t)m, sizeof(StringInt *), string_int_ref_cmp_by_number_v);
  string_ints_print_ref(a, n);
  printf("\n");
  string_ints_print_ref(b, m);
}

// --------------------------------

void unit_tests(void)
{
  unit_test_weight();
}

// --------------------------------

int main(int argc, char **argv)
{
  unit_tests();
  int x = 'Z';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_qsort_ints();
  else if (x == 'B')
    test_qsort_ints_down();
  else if (x == 'C')
    test_qsort_ints_by_weight();
  else if (x == 'D')
    test_qsort_ints_by_parity();
  
  else if (x == 'E')
    test_qsort_strings();
  else if (x == 'F')
    test_qsort_strings_by_length();
  
  else if (x == 'G')
     test_qsort_chars();

  else if (x == 'H')
    test_qsort_string_ints();
  else if (x == 'I')
    test_qsort_string_ints_by_number();
  else if (x == 'J')
    test_qsort_string_ints_by_number_down();
  else if (x == 'K')
    test_qsort_string_ints_twice();
  else if (x == 'L')
    test_qsort_string_ints_twice_better();

// Not used in sebenta
  else if (x == 'E')
    test_qsort_ints_by_date();
  else if (x == 'H')
    test_isort_strings_by_length_composed();
  else if (x == 'I')
    demo_qsort_strings_by_length_composed_does_not_work();
  else if (x == 'M')
    test_qsort_string_ints_by_number_down();
  
  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);

  return 0;
}
