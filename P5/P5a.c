#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "our_strings.h"

int read(const char **a)// le o array dos nomes
{
    int result = 0;
    char line[1000];
    while (scanf("%[^\n]%*c", line) != EOF)
    {
        a[result++] = str_dup(line);
    }
    return result;
}


int split_names(const char **a, int n, const char **b)
{
  int result = 0;
  int i2 = 0;
  const char **c = (const char**) malloc(100);
  for(int i = 0; i < n; i++)
  {
    int x = str_words(a[i], c);
    while(i2 < x)
    {
      b[result++] = c[i2];
      i2++;
    }
    i2 = 0;
  }
  return result;
}

int select_names(const char* s, const char **a, int n)
{
  int g=0;
  for (int i = 0; i < n; i++)
  {
    if (strcmp(s, a[i]) == 0)//(s == a[i])
    {
      g++;
    } 
  }
  return g; 
}

int choose_names(const char **a, int n, const char **b, int m, const char **final)
{
  int result = 0;
  int i2 = 0;
  const char **c = (const char**) malloc(100);
  for(int i = 0; i < n; i++)
  {
    int x = str_words(a[i], c);
    while(i2 < x)
    {
      if (select_names(c[i2], b, m) == 1)
      {
        if(select_names(a[i], final, result) < 1)
        {
          final[result++] = a[i];
        }
        final[result++] = c[i2];
      }
      i2++;
    }
    i2 = 0;
  }
  return result;
}


void test_festa_A(void)
{
  const char *a[10000];
  int n = read(a);
  const char *b[10000];
  int tamanho = split_names(a,n,b);
  const char *c[10000];
  int e = choose_names(a,n,b,tamanho, c);
  if(e > 0)
  strings_print_basic(c, e);
  else
  printf("***\n");
} 

int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_festa_A();
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}
