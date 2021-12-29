#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "our_doubles.h"
#include "our_ints.h"


typedef struct{
    int coluna;
    int linha;
    int total;
}Matrix;

Matrix organize(int coluna, int linha, int total)
{
    Matrix result = {coluna, linha, total};
    return result;
}

void put_zero(int col, int line, int **a)
{
  for(int i = 0; i < col; i++)
   for(int j = 0; j < line; j++)
    a[i][j] = 0;
}

void sum_matrix(int col, int line, int **a)
{
    int x;
    int y;
    while(scanf("%d %d", &x, &y) != EOF)
    {
        a[y][x] += 1;
    }
}

void accumulate(int **a, int line, int col, int **b)
{
  for (int i = 0; i < line+1; i++)  // array b has line+1 rows.
  b[i][0] = 0;
  for (int j = 1; j < col+1; j++)  // array b has col+1 columns.
  b[0][j] = 0;
  for (int i = 0; i < line; i++)
  for (int j = 0; j < col; j++)
  b[i+1][j+1] = a[i][j] + b[i][j+1] + b[i+1][j] - b[i][j];
}

int corner(int c, int l, int **n, int b, int d, Matrix *m)
{
    int total = 0;
    int result = 0;
    for(int i = 0; i < c-b+1; i++)
    {
        for(int j = 0; j < l-d+1; j++)
        {
            total = n[i][j] + n[i+b][j+d] - n[i+b][j] - n[i][j+d];
            m[result++] = organize(j, i, total);
        }
    }
    return result;
}

int troca(Matrix a, Matrix b)
{
    int result = a.total - b.total;
    if(result == 0)
    result = a.linha - b.linha;
    else if(result == 0)
    result = a.coluna - b.coluna;
    return result;
}

int matrix_cmp(const void *p, const void *q)
{
    return troca(*(Matrix *)p, *(Matrix *)q);
}

void qsort_matrix(Matrix *b, int n)
{
    qsort(b,(size_t)n, sizeof(Matrix), matrix_cmp);
}

void print_matrix(int r, int c, int **m, const char *fmt)
{
    for(int i = 0; i < r+1; i++)
    ints_printfln(fmt, m[i], c+1);
}

void write_matrix(Matrix *a, int n)
{
    for(int i = 0; i< n; i++)
    printf("%d %d %d\n", a[i].coluna, a[i].linha, a[i].total);
}

void test_B(void)
{
    int c = int_get();
    int l = int_get();
    int c2 = int_get();
    int l2 = int_get();
    if(c > 1000)
    c = 1000;
    if(l > 1000)
    l = 1000;
    int **a;

    a = malloc( (l) * sizeof(int *));//put in dynamic memory
    for(int i = 0; i < l; i++)
    {
        a[i] = malloc ( (c) * sizeof(int));
    }
    int **n;

    n = malloc( (l+1) * sizeof(int *));
    for(int i2 = 0; i2 < l+1; i2++)
    {
        n[i2] = malloc( (c+1) * sizeof(int));
    }
    Matrix *b =(Matrix *) malloc(10000000);
    put_zero(l, c, a);
    sum_matrix(l, c, a);
    accumulate(a, l, c, n);
    int n2 = corner(l, c, n, l2, c2, b);
    //print_matrix(l, c, n, "%d ");
    qsort_matrix(b, n2);
    if(n2 > 10000)
    n2 = 10000;
    write_matrix(b, n2);
}

int main(int argc, char **argv)
{
   int x = 'A';
   if (argc > 1)
   x = *argv[1];
   //if (x == 'A')
   //test_A();
   if (x == 'B')
   test_B();
   else
   printf("%s: Invalid option.\n", argv[1]);
   return 0;
}