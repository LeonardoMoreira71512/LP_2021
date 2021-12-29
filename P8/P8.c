#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include "our_doubles.h"
#include "our_ints.h"
#include "our_strings.h"

typedef struct{
    int comprimento;
    int altura;
    int sobreiros;
}Coordenadas;

Coordenadas pista(int comprimento, int altura, int sobreiros)
{
    Coordenadas result = {comprimento, altura, sobreiros};
    return result;
}

void exchange_coordenadas(Coordenadas *a, int x, int y)
{
    Coordenadas m = a[x];
    a[x] = a[y];
    a[y] = m;
}

int sort_cmp(Coordenadas *a, int x, int y)
{
    int result = a[x].sobreiros - a[y].sobreiros;
    if (result == 0)
    result = a[x].altura -a[y].altura;
    if (result == 0)
    result = a[x].comprimento - a[y].comprimento;
    return result;
}

void ordenar(Coordenadas *a, int n)
{
  for(int i = 0; i < n; ++i)
  {
    int j = i;
    while (j > 0 && sort_cmp(a, j-1, j) > 0)
    {
      exchange_coordenadas(a, j-1, j);
      j--;
    }
  }
}

void matrix_println(FILE *f, Coordenadas a)
{
  fprintf(f, "%d %d %d\n", a.comprimento, a.altura, a.sobreiros);
}

void matrix_print(FILE *f, const Coordenadas *a, int n)
{
  for (int i = 0; i < n; i++)
    matrix_println(f, a[i]);
}

int m_sobreiros(int v, int h, const int m[v][h], int a, int c, int dv, int dh)
{
    int sobreiros = 0;
    for(int i = dv; i < a+dv; ++i)
    {
        for(int j = dh; j < c + dh; ++j)
        {
            sobreiros += m[i][j]; 
        }
    }
    return sobreiros;
}

int m_struct(int v, int h, const int t[v][h], int a, int c, Coordenadas *b)
{
    int result = 0;
    for(int i = 0; i < v-a+1; ++i)
    {
        for(int j = 0; j < h-c+1; ++j)
        {
            int sobreiros = m_sobreiros(v, h, t, a, c, i, j);
            b[result++] = pista(j, i, sobreiros);
        }
    }
    return result;
}

void matrix_get_clear(int h, int v, int t[h][v])
{
  for(int i = 0; i < h; ++i)
   for(int j = 0; j < v; ++j)
    t[i][j] = 0;
}

void test_A(void)
{
   int h = int_get();//tamanho horizontal da area
   int v = int_get();//tamanho vertical da area reservada
   int m1[v][h];//matriz da area
   int c; //comprimento da pista
   int a;//altura da pista
   scanf("%d%d", &c, &a);
   matrix_get_clear(h, v, m1);
   int x;
   int y;
   Coordenadas local[100000];
   while(scanf("%d %d", &x, &y) != EOF)
   {
       m1[y][x]++;
   }
   int n = m_struct(v, h, m1, a, c, local);
   ordenar(local, n);
   matrix_print(stdout, local, n);
}



///////////////////////////////////////////////////////// PROBLEMA B ///////////////////////////////////////////////////////


typedef struct{
 int coluna;
 int linha;
 int total;
}Alcochete;

Alcochete organize(int coluna, int linha, int total)
{
    Alcochete result;
    result.coluna = coluna;
    result.linha = linha;
    result.total = total;
    return result;
}

void put_zero(int col, int line, int **a)
{
  for(int i = 0; i < col; i++)
  {
      for(int i2 = 0; i2 < line; i2++)
      {
          a[i][i2] = 0;
      }
  } 
}

void sum_matrix(int col, int line, int **a)
{
    int x;
    int y;
    while(scanf("%d%d", &x, &y) != EOF)
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

int corner(int c, int l, int **n, int b, int d, Alcochete *m)
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

int troca(Alcochete a, Alcochete b)
{
    int result = a.total - b.total;
    if(result == 0)
    result = a.linha - b.linha;
    else if(result == 0)
    result = a.coluna - b.coluna;
    return result;
}

int matrix_cmp(const void *a, const void *b)        
{
    return troca(*(Alcochete *)a, *(Alcochete *)b);
}

void qsort_matrix(Alcochete *b, int n)
{
    qsort(b,(size_t)n, sizeof(Alcochete), matrix_cmp);
}

void print_matrix(int r, int c, int **m, const char *fmt)
{
    for(int i = 0; i < r+1; i++)
    ints_printfln(fmt, m[i], c+1);
}

void write_matrix(Alcochete *a, int n)
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
    Alcochete *b =(Alcochete *) malloc(10000000);
    put_zero(l, c, a);
    sum_matrix(l, c, a);
    accumulate(a, l, c, n);
    int n2 = corner(l, c, n, l2, c2, b);
    print_matrix(l, c, n, "%d");
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
   if (x == 'A')
   test_A();
   else if (x == 'B')
   test_B();
   else
   printf("%s: Invalid option.\n", argv[1]);
   return 0;
}