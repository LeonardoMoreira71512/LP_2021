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


void matrix_get_clear(int h, int v, int t[h][v])
{
  for(int i = 0; i < h; ++i)
  {
    for(int j = 0; j < v; ++j)
    {
      t[i][j] = 0;
    }
  }
}

typedef struct{
  int linha;
  int coluna;
  int pessoas;
}Mesa;

Mesa esplanada(int linha, int coluna, int pessoas)
{
    Mesa result;
    result.linha = linha;
    result.coluna = coluna; 
    result.pessoas = pessoas;
    return result;
}

int Mesa_read(Mesa* a)
{
  int result = 0;
  int linha;
  int coluna;
  int pessoas;
  while(scanf("%d %d %d", &linha,  &coluna, &pessoas) != EOF)
    a[result++] = esplanada(linha, coluna, pessoas);
  return result;
}

void occupy (int r, int c, int m[r][c], Mesa *a, int n)
{
  for(int i = 0; i < n; i++)
  m[a[i].linha][a[i].coluna] = a[i].pessoas;
}

typedef struct{
  int linha;
  int coluna;
  int distancia;
}Manhattan;

Manhattan distance1(int linha, int coluna, int distancia)
{
  Manhattan result = {linha, coluna, distancia};
  return result;
}

int sum_distance(int r, int c, int m[r][c], Mesa *a, int n)
{
    int operation;
    int result = 0;
    for(int i = 0; i < n; i++)
    {
      operation = a[i].pessoas*(abs(r-a[i].linha) + abs(c - a[i].coluna));
      result += operation; 
    }
    return result;
}

int possibilities_table(int r, int c, int m[r][c], Mesa *a, int n, Manhattan *b)
{
  int distance = 0;
  int result = 0;
  for(int i = 0; i < r; i++)
  {
    for(int i2 = 0; i2 < c; i2++)
    {
      if(m[i][i2] == 0)
      {
        distance = sum_distance(i, i2, m, a, n);
        b[result++] = distance1(i, i2, distance);
      }
    }
  }
  return result;
}

int distance_max(Manhattan *a, int n)
{
  int result = a[0].distancia;
  int position = 0; 
  for(int  i = 1; i < n; i++)
  {
    if(result < a[i].distancia)
    {
      result = a[i].distancia;
      position = i;
    }
  }
  return position;
}

void mesa_write(Manhattan *a, int n)
{
  printf("%d %d %d", a[n].linha, a[n].coluna, a[n].distancia);
}

void test_A(void)
{
  int r;
  scanf("%d", &r);
  int c;
  scanf("%d", &c);
  int m[r][c];
  matrix_get_clear(r, c, m);
  Mesa table[1000];
  int n = Mesa_read(table);
  occupy(r, c, m, table, n);
  Manhattan table2[1000];
  int unoccupied = possibilities_table(r, c, m, table, n, table2);
  int max_distance = distance_max(table2, unoccupied);
  mesa_write(table2, max_distance);
}

int main(int argc, char **argv)
{
  int x = 'A';
   if (argc > 1)
   x = *argv[1];
   if (x == 'A')
   test_A();
   else
   printf("%s: Invalid option.\n", argv[1]);
   return 0;
}