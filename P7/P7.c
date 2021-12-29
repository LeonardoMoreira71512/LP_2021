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

void get_system(int x, double a[x][x+1])
{
   doubles_get_some((double*)a, x*(x+1));
}

void help_print(int r, int c, const double a[r][c], const char *fmt)
{
    for (int i = 0; i < r; i++)
   doubles_printfln(fmt, a[i], c);
}

void print_system(int x, const double a[x][x+1])
{
   help_print(x, x+1, a, "%12f");
}

void test_A(void)
{
  int x = int_get();
  double m[x][x+1];
  get_system(x, m);
  print_system(x, m);
}


////////////////////////////////////////////////////// PROBLEMA B ////////////////////////////////////////////////////////////////////////
 
int is_solution(int x, const double m[x][x+1], int *a, int tamanho, int *b, int size)
{
    int i2 = 0;
    int y  = x;
    int c = 0;
    for(int i = 0; i < x; i++)
    {
        while(i2 < y)
        {
            c += m[i][i2] * a[tamanho];
            i2++;
            tamanho++;
        }
        b[size++] = c;
        c = 0;
        i2 = 0;
        tamanho -= x;
    }
    return size; 
}

int size_b(int x, const double m[x][x+1], int *a, int tamanho, int *b)
{
  int result = 0;
  int i = 0;
  while(i < tamanho)
  {
      result = is_solution(x, m, a, i, b, result); 
      i += x;
  }  
  return result;
}

void compare(int x, const double m[x][x+1], int *a, int c)
{
    int i = 0;
    int count = 0;
    while (i < x)
    {
      if(m[i][x] == a[c])
      {
          count++;
      }
      c++;
      i++;
    }
    if(count == x)
    printf("1\n");
    else
    printf("0\n");
}

 void test_B(void)
 { 
     int x;
     scanf("%d\n", &x);
     double m1[x][x+1];
     get_system(x, m1);
     int a[1000];
     int n = ints_get(a);
     int b[1000];
     int tamanho = size_b(x, m1, a, n, b);
     int i = 0;
     while(i < tamanho)
     {
     compare(x, m1, b, i);
     i += x;
     }
 } 





///////////////////////////////////////////////////// PROBLEMA C ///////////////////////////////////////////////////////////////////////

int produto_interno (const double *m, int x, const double *a)
{
    double y = 0;
    int i = 0;
    while (i < x)
    {
        y += a[i] * m[i];
        i++;
    }
    return y == m[x];
}

int solution(int x, const double m[x][x+1], const double *a, int n)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        result += produto_interno((double *) m[i], x, a);
    }
    return result == x;
}


void convert(double *a, int ind, int x, int y, int w)
{
  for(int i = x-1; i >= 0; i--)
  {
      int sub = (ind%y) - w;
      a[i] = sub;
      ind /= y;
  }
}

int brute_force(int x, const double m[x][x+1], int y, double *a)
{
 int base = (y*2) + 1;
 int i = 0;
 int z = 0;
 while (i < pow(base, x) && z == 0)
 {
     convert(a, i, x, base, y);
     z = solution(x, m, a, x);
     i++;
 }   
 return z;
}

void test_C(void)
{
  int x = int_get();
  double m[x][x+1];
  get_system(x, m);
  int y;
  double a[x];
  while (scanf("%d", &y) != EOF)
  {
      int tamanho = brute_force(x, m, y, a);
      if(tamanho == 1)
      doubles_println_basic(a, x);
      else
      printf("***\n");
  }
}

///////////////////////////////////////////////////// PROBLEMA D ///////////////////////////////////////////////////////////////////////


void columnize(int n, double a[n][n+1], int x)
{
  int j = 0;
  for(int i = 0; i < n; i++)// j < linha
  {
      double div = a[i][x];
      
      while(j < n+1)//j < coluna
      {
          if(div != 0 && a[i][j] != 0)
          {
             a[i][j] = a[i][j]/div; 
          }
          j++;
      }
      j = 0;
  }
}

void subtract_row(int n, double a[n][n+1], int x)
{
    int j = 0;
    for(int  i = 0; i < n; i++)
    {
    double sub = a[i][x];
       while( j < n+1)
       {
        if(sub != 0)
        {
          if(i != x)
          {
              a[i][j] = a[i][j] - a[x][j];
          }
          j++;
        }
        else
        j = n+1;
       }
       j = 0;
    }
}

void repeat(int n, double a[n][n+1])
{
    for(int i = 0; i < n; i++)
    {
        columnize(n, a, i);
        subtract_row(n, a, i);
    }
}

void repeat2(int n, double a[n][n+1])//vai ter de repetir o processo columnize
{
    for(int i = 0; i < n; i++)
    {
        columnize(n, a, i);
    }
}

int array(double *m, int tamanho, int n, double a[n][n+1])//mete num array a ultima coluna
{
  int result = 0;
  for(int i = 0; i < n; i++)
  {
      m[result++] = a[i][tamanho]; 
  }
  return result;
}

void test_D(void)
{
  int x = int_get();
  double m1[x][x+1];
  get_system(x, m1);
  repeat(x, m1);
  repeat2(x, m1);
  double b[1000];
  int c = array(b,x,x,m1);
  doubles_println(b, c, " ");
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
    else if (x == 'C')
        test_C();
    else if (x == 'D')
        test_D();
    //else if (x == 'E')
        //test_E(argv[2]);
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}