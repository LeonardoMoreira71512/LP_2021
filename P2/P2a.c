//Problema A

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

 int str_len(const char *s)//tamanho da string em bits de memoria ex: assert(str_len("abcd") == 4);
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}

int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = str_len(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

// Create a dynamic copy of `s` and return its address
const char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

char* str_ncpy(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[1000];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}



void str_print(const char** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", a[i]);
    }
    
}

int str_find(const char *s, char x)
{
    for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
    return i;
    return -1;
}

const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc(n + 1);
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_search(const char* s, const char **a, int n)//retirado dos lusiadas
{
  for (int i = 0; i < n; i++)
  {
    if (strcmp(s, a[i]) == 0)//(s == a[i])
    {
      return 1;

    }
    
  }
  return 0;
  
}

int str_count_while_is_not_space(const char *s)//retirado dos lusiadas
{
  int result = 0;
  while (s[result] != '\0' && !isspace(s[result]))//vai contar o numero de letras antes do space
    result++;
  return result;
}

int nomes_proprios(const char **a, int n, const char **b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
  {
    int t = str_count_while_is_not_space(a[i]);// o t vai ser o tamanho das letras do array "a" até chegar ao space
    b[result++] = str_ndup(a[i], t);//o array b vai ser apenas os nomes iniciais de cada linha de nomes
  }
    return result;
}

int unique_first_names(const char **a, int n, const char**b)
{
  int result = 0;
  for(int i = 0; i < n; i++)
  {
    if(str_search(a[i], b, result) != 1)//o b é um subarray de a e utilizo o tamanho do array b, verifica se cada nome esta no array inicial
    {
      b[result++] = a[i];//se o a for diferente de b entao copio as letras de a para b
    }
  }
  return result;
}

void test_Final_A()
{
 const char *a[1000];
 const char *b[1000];
 const char *c[1000];
 int n = strings_read(stdin,a);
 int m = nomes_proprios(a, n, b);//chamo a variavel m para dar o tamanho do array b
 int z = unique_first_names(b, m, c);//com o z acho o tamanho do novo array c que ira ver se os nomes sao repetidos ou nao
 str_print(c,z);//dou print no array c de tamanho z
}

int main(void)
{
  test_Final_A();
  return 0;
}
