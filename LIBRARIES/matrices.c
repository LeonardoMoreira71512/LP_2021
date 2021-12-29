//
//  main.c
//  matrices
//
//  Created by Pedro Guerreiro on 31/03/2021.
//

#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wextra"
#pragma GCC diagnostic error "-Wconversion"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "our_ints.h"
#include "our_doubles.h"

char *author = "Pedro Guerreiro";


// --------------------

void show_multiplication_table(int r, int c)
{
  double m[r][c];
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      m[i][j] = i * j;
  for (int i = 0; i < r; i++)
    doubles_printfln("%4g", m[i], c);
}

void test_show_multiplication_table(void)
{
  int r = int_get();
  int c = int_get();
  show_multiplication_table(r, c);
}

void matrix_printf(int r, int c, const double m[r][c], const char *fmt)
{
  for (int i = 0; i < r; i++)
    doubles_printfln(fmt, m[i], c);
}

void test_matrix_printf(void)
{
  double m[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
  matrix_printf(3, 4, m, "%4g");
  printf("\n");
  matrix_printf(3, 4, m, "%10.2f");
}

void test_matrix_printf_2(void)
{
  double m[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
//  double m[4][3] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
  matrix_printf(2, 6, m, "%4g");
  printf("\n");
  matrix_printf(5, 2, m, "%4g");
}

void multiplication_table(int r, int c, double m[r][c])
{
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      m[i][j] = i * j;
}

void test_multiplication_table(void)
{
  int r = int_get();
  int c = int_get();
  double m[r][c];
  multiplication_table(r, c, m);
  matrix_printf(r, c, m, "%4g");
}

// Add two matrices
void matrix_add(int r, int c, const double m1[r][c], const double m2[r][c], double m3[r][c])
{
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      m3[i][j] = m1[i][j] + m2[i][j];
}

void matrix_zip_original(int r, int c, const double m1[r][c], const double m2[r][c], double op(double, double), double m3[r][c])
{
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      m3[i][j] = op(m1[i][j], m2[i][j]);
}

void matrix_zip(int r, int c, const double m1[r][c], const double m2[r][c], double op(double, double), double m3[r][c])
{
  doubles_zip((const double *)m1, (const double *)m2, r*c, op, (double *)m3);
}

void matrix_add_1(int r, int c, const double m1[r][c], const double m2[r][c], double z[r][c])
{
  matrix_zip(r, c, m1, m2, dbl_sum, z);
}

void matrix_subtract(int r, int c, const double x[r][c], const double y[r][c], double z[r][c])
{
  matrix_zip(r, c, x, y, dbl_difference, z);
}

void matrix_multiply(int r, int c, const double x[r][c], const double y[r][c], double z[r][c])
{
  matrix_zip(r, c, x, y, dbl_product, z);
}

void matrix_divide(int r, int c, const double x[r][c], const double y[r][c], double z[r][c])
{
  matrix_zip(r, c, x, y, dbl_quotient, z);
}

// Set all elements to zero
void doubles_clear(double *a, int n)
{
  memset(a, 0, (size_t)n * sizeof(double));
}

// Set all elements to zero
void matrix_clear(int r, int c, double m[r][c])
{
  doubles_clear((double *)m, r*c);
}

// Are the two matrices equal?
int matrix_equal(int r1, int c1, const double m1[r1][c1], int r2, int c2, const double m2[r2][c2])
{
  return r1 == r2 && c1 == c2 &&
         doubles_equal((const double *)m1, r1*c1, (const double *)m2, r2*c2);
}

void unit_test_matrix_add(void)
{
  {
    double m1[2][3] = {{2,3,5},{7,11,13}};
    double m2[2][3] = {{1,2,4},{8,16,32}};
    double m3[2][3];
    matrix_add(2, 3, m1, m2, m3);
    double z[2][3] = {{3,5,9},{15,27,45}};
    assert(matrix_equal(2, 3, m3, 2, 3, z));
  }
  {
    double m1[1][4] = {{2,4,6,8}};
    double m2[1][4] = {{10,20,30,40}};
    double m3[1][4];
    matrix_add(1, 4, m1, m2, m3);
    double z[1][4] = {{12,24,36,48}};
    assert(matrix_equal(1, 4, m3, 1, 4, z));
  }
  {
    double m1[5][1] = {{2},{1},{9},{3},{7}};
    double m2[5][1] = {{1},{5},{3},{6},{2}};
    double m3[5][1];
    matrix_add(5, 1, m1, m2, m3);
    double z[5][1] = {{3},{6},{12},{9},{9}};
    assert(matrix_equal(5, 1, m3, 5, 1, z));
  }
}

// Addl `x` to each element in the matrix
void matrix_plus(int r, int c, double m[r][c], double x)
{
  for (int i = 0; i < r*c; i++)
    ((double *)m)[i] += x;
}

void matrix_plus2(int r, int c, double m[r][c], double x)
{
  double *p = (double *)m;
  for (int i = 0; i < r*c; i++)
    p[i] += x;
}

void unit_test_matrix_plus(void)
{
  double m1[2][3] = {{1,3,5},{2,4,8}};
  matrix_plus(2, 3, m1, 5);
  double r1[2][3] = {{6,8,10},{7,9,13}};
  assert(matrix_equal(2, 3, m1, 2, 3, r1));

  double m2[2][2] = {{1,3},{2,4}};
  matrix_plus(2, 2, m2, -1);
  double r2[2][2] = {{0,2},{1,3}};
  assert(matrix_equal(2, 2, m2, 2, 2, r2));
}

void unit_test_matrix_plus2(void)
{
  double m1[2][3] = {{1,3,5},{2,4,8}};
  matrix_plus2(2, 3, m1, 5);
  double r1[2][3] = {{6,8,10},{7,9,13}};
  assert(matrix_equal(2, 3, m1, 2, 3, r1));

  double m2[2][2] = {{1,3},{2,4}};
  matrix_plus2(2, 2, m2, -1);
  double r2[2][2] = {{0,2},{1,3}};
  assert(matrix_equal(2, 2, m2, 2, 2, r2));
}

// Transpose `m` to `t`
void matrix_transpose(int r, int c, const double m[r][c], double t[c][r])
{
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      t[j][i] = m[i][j];
}

void unit_test_matrix_transpose(void)
{
  {
    double m[2][3] = {{1,3,5},{2,4,8}};
    double t[3][2];
    matrix_transpose(2, 3, m, t);
    double r[3][2] = {{1,2},{3,4},{5,8}};
    assert(matrix_equal(3, 2, t, 3, 2, r));
  }
  {
    double m[2][2] = {{1,3},{2,4}};
    double t[2][2];
    matrix_transpose(2, 2, m, t);
    double r[2][2] = {{1,2},{3,4}};
    assert(matrix_equal(2, 2, t, 2, 2, r));
  }
  {
    double m[5][1] = {{1},{3},{5},{4},{8}};
    double t[1][5];
    matrix_transpose(5, 1, m, t);
    double r[1][5] = {{1,3,5,4,8}};
    assert(matrix_equal(1, 5, t, 1, 5, r));
  }
  {
    double m[1][4] = {{6,3,8,2}};
    double t[4][15];
    matrix_transpose(1, 4, m, t);
    double r[4][1] = {{6},{3},{8},{2}};
    assert(matrix_equal(4, 1, t, 4, 1, r));
  }
}

// Transpose square matrix `m` onto itself
void matrix_square_transpose(int c, double m[c][c])
{
  for (int i = 0; i < c; i++)
    for (int j = 0; j < i; j++)
      doubles_exchange((double *)m, i*c+j, j*c+i);
}

void unit_test_matrix_square_transpose(void)
{
  {
    double m[2][2] = {{1,3},{2,4}};
    matrix_square_transpose(2, m);
    double r[2][2] = {{1,2},{3,4}};
    assert(matrix_equal(2, 2, m, 2, 2, r));
  }
  {
    double m[3][3] = {{1,3,8},{2,4,7},{5,6,9}};
    matrix_square_transpose(3, m);
    double r[3][3] = {{1,2,5},{3,4,6},{8,7,9}};
    assert(matrix_equal(3, 3, m, 3, 3, r));
  }
  {
    double m[1][1] = {{7}};
    matrix_square_transpose(1, m);
    double r[2][2] = {{7}};
    assert(matrix_equal(1, 1, m, 1, 1, r));
  }
}

// Compute the product of matrices `m1` and `m2`
void matrix_product(int r1, int c1, const double m1[r1][c1], int r2, int c2, const double m2[r2][c2], double m3[r1][c2])
{
  assert(c1 >= r2); // We do not require c1 == r2. See `doubles_inner_product`.
  double t[c2][r2];
  matrix_transpose(r2, c2, m2, t);
  for (int i = 0; i < r1; i++)
    for (int j = 0; j < c2; j++)
      m3[i][j] = doubles_inner_product(m1[i], t[j], r2);
}

void unit_test_matrix_product(void)
{
  // test cases from https://www.mathsisfun.com/algebra/matrix-multiplying.html
  {
    double m1[2][3] = {{1,2,3},{4,5,6}};
    double m2[3][2] = {{7,8},{9,10},{11,12}};
    double r[2][2];
    matrix_product(2, 3, m1, 3, 2, m2, r);
    double p[2][2] = {{58,64},{139,154}};
    assert(matrix_equal(2, 2, r, 2, 2, p));
  }
  {
    double m1[1][3] = {{3,4,2}};
    double m2[3][4] = {{13,9,7,15},{8,7,4,6},{6,4,0,3}};
    double r[1][4];
    matrix_product(1, 3, m1, 3, 4, m2, r);
    double p[1][4] = {{83,63,37,75}};
    assert(matrix_equal(1, 4, r, 1, 4, p));
  }
  {
    double m1[1][3] = {{1,2,3}};
    double m2[3][1] = {{4},{5},{6}};
    double r[1][1];
    matrix_product(1, 3, m1, 3, 1, m2, r);
    double p[1][1] = {{32}};
    assert(matrix_equal(1, 1, r, 1, 1, p));
  }
  {
    double m1[2][2] = {{1,2},{3,4}};
    double m2[2][2] = {{2,0},{1,2}};
    double r[2][2];
    matrix_product(2, 2, m1, 2, 2, m2, r);
    double p1[2][2] = {{4,4},{10,8}};
    assert(matrix_equal(2, 2, r, 2, 2, p1));
    matrix_product(2, 2, m2, 2, 2, m1, r);
    double p2[2][2] = {{2,4},{7,10}};
    assert(matrix_equal(2, 2, r, 2, 2, p2));
  }
}

// Compute the product of matrices `m1` and `m2`
void matrix_product_by_column(int r1, int c1, const double m1[r1][c1], int r2, const double m2[r2][1], double m3[r1][1])
{
  assert(c1 >= r2); // We do not require c1 == r2. See `doubles_inner_product`.
  for (int i = 0; i < r1; i++)
    m3[i][0] = doubles_inner_product(m1[i], (double *)m2, r2);
}

void unit_test_matrix_product_by_column(void)
{
  {
    double m1[2][3] = {{1,2,3},{4,5,6}};
    double m2[3][1] = {{7},{9},{5}};
    double r[2][1];
    matrix_product_by_column(2, 3, m1, 3, m2, r);
    double p[2][1] = {{40},{103}};
    assert(matrix_equal(2, 1, r, 2, 1, p));
  }
  {
    double m1[4][4] = {{1,2,-3,4},{0,1,1,1},{2,-1,0,1},{1,-1,2,0}};
    double m2[4][1] = {{2},{1},{0},{-1}};
    double r[4][1];
    matrix_product_by_column(4, 4, m1, 4, m2, r);
    double p[4][1] = {{0},{0},{2},{1}};
    assert(matrix_equal(4, 1, r, 4, 1, p));
  }
  {
    double m1[1][5] = {{1,2,3,4,5}};
    double m2[5][1] = {{2},{1},{0},{-1},{-2}};
    double r[1][1];
    matrix_product_by_column(1, 5, m1, 5, m2, r);
    double p[5][1] = {{-10}};
    assert(matrix_equal(1, 1, r, 1, 1, p));
  }
}

void test_matrix_product_by_column(void)
{
  double m[3][3] = {{1,2,0},{2,-1,3},{3,0,1}};
  double a[3];
  int n;
  while ((n = doubles_get_some(a, 3)) != 0)
  {
    assert(3 == n);
    double b[3];
    matrix_product_by_column(3, 3, m, 3,
                             (const double (*)[1])a, (double (*)[1])b);
    doubles_println_basic(b, 3);
  }
}

// Read a matrix from the standard input
void matrix_get(int r, int c, double m[r][c])
{
  doubles_get_some((double*)m, r*c);
}

void test_matrix_get(void)
{
  int r = int_get();
  int c = int_get();
  double m[r][c];
  matrix_get(r, c, m);
  matrix_printf(r, c, m, "%9.1f");
}

// Write a sparse matrix to the standard input
int matrix_print_sparse(int r, int c, double m[r][c])
{
  int result = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      if (m[i][j] != 0.0)
      {
        printf("%d %d %g\n", i, j, m[i][j]);
        result++;
      }
  return result;
}

// Read a sparse matrix from the standard input
int matrix_get_sparse(int r, int c, double m[r][c])
{
  int result = 0;
  int i, j;
  double x;
  while (scanf("%d%d%lf", &i, &j, &x) != EOF)
  {
    m[i][j] = x;
    result++;
  }
  return result;
}

void test_matrix_print_sparse(void)
{
  int r = int_get();
  int c = int_get();
  double m[r][c];
  matrix_get(r, c, m);
  matrix_printf(r, c, m, "%6.1f");
  printf("\n");
  int n = matrix_print_sparse(r, c, m);
  printf("%d\n", n);
}

void test_matrix_get_sparse(void)
{
  int r = int_get();
  int c = int_get();
  double m[r][c];
  matrix_clear(r, c, m);
  int n = matrix_get_sparse(r, c, m);
  printf("%d\n", n);
  matrix_printf(r, c, m, "%6.1f");
}

// Compute the array `a` with column x of matrix `m`
void matrix_column(int r, int c, const double m[r][c], int x, double a[r])
{
  assert(0 <= x && x < c);
  for (int i = 0; i < r; i++)
    a[i] = m[i][x];
}

void test_clear_plus(void)
{
  int r = int_get();
  int c = int_get();
  double m[r][c];
  multiplication_table(r, c, m);
  matrix_printf(r, c, m, "%4g");
  printf("----\n");
  matrix_plus(r, c, m, 2.0);
  matrix_printf(r, c, m, "%4g");
  printf("----\n");
  matrix_clear(r, c, m);
  matrix_printf(r, c, m, "%4g");
  printf("----\n");
}

void test_matrix_operations(void)
{
  int r = int_get();
  int c = int_get();
  double m1[r][c];
  matrix_get(r, c, m1);
  double m2[r][c];
  matrix_get(r, c, m2);
  matrix_printf(r, c, m1, "%12f");
  printf("\n");
  matrix_printf(r, c, m2, "%12f");
  printf("\n");
  double m_add[r][c];
  matrix_add(r, c, m1, m2, m_add);
  matrix_printf(r, c, m_add, "%12f");
  printf("\n");
  double m_sub[r][c];
  matrix_subtract(r, c, m1, m2, m_sub);
  matrix_printf(r, c, m_sub, "%12f");
  printf("\n");
  double m_mult[r][c];
  matrix_multiply(r, c, m1, m2, m_mult);
  matrix_printf(r, c, m_mult, "%12f");
  printf("\n");
  double m_div[r][c];
  matrix_divide(r, c, m1, m2, m_div);
  matrix_printf(r, c, m_div, "%12f");
}

// --------------------

void unit_tests(void)
{
  unit_test_matrix_add();
  unit_test_matrix_plus();
  unit_test_matrix_transpose();
  unit_test_matrix_square_transpose();
  unit_test_matrix_product();
  unit_test_matrix_product_by_column();
}

void test(void)
{
  assert(0);
}

int main(int argc, const char **argv)
{
  unit_tests();
  int x = 'U';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_matrix_printf();
  else if (x == 'B')
    test_matrix_printf_2();
  else if (x == 'C')
    test_multiplication_table();
  else if (x == 'D')
    test_matrix_product_by_column();
  else if (x == 'E')
    test_matrix_get();
  else if (x == 'F')
    test_matrix_print_sparse();
  else if (x == 'G')
    test_matrix_get_sparse();
  else if (x == 'H')
    test_matrix_operations();

  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);
  return 0;
}