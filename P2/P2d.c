//Problema B

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

int strings_read(FILE *f, const char **a)//vai ler o ficherio que escrevo no bloco de notas
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

const char *str_ndup(const char *s, int n)//copiar um elemento de um array a[i] ate determinado ponto
{//exemplo: str_ndup(a[i], size); com a[0] e size = 3 ->  a[0]=Joao Antonio , resultado= Joa
  char *result = (char *) malloc(n + 1);
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_search(const char* s, const char **a, int n)//verificar se uma determinada palavra existe num array de palavras
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



/////////////////////////////////////////////////////INICIO DO PROBLEMA //////////////////////////////////////////////////////////



int str_count_while_is_not_space(const char *a)//retirado dos lusiadas
{
  int result = 0;
  while (a[result] != '\0' && a[result] != ' ')//vai contar o numero de letras antes do space
    result++;
  return result;
}

const char * string_names(const char *s, const char **a)
{
    int result = 0;
    int i = 0;
    while(s[i])
    if (isspace(s[i]))
        i++;
    else
    {
        int z = str_count_while_is_not_space(s+i);
        a[result++] = str_ndup(s+i, z);
        i += z;
    }
    return a[result - 1];//da me todos os nomes menos o apelido
}

void apelidos(const char **a, int n, const char **b, const char **c)
{
    int i = 0;
    while (i < n)
    {
        b[i] = string_names(a[i], c);
        i++;
    }
}

typedef struct{
    const char *_1;
    const char *_2;
}StringString;

StringString construction (const char *_1, const char *_2)
{
    StringString result = {_1, _2};
    return result;
}

void exchange_1_and_2(StringString *a, int _1, int _2)
{
    StringString n[1000];
    n[1] = a[_1];
    a[_1] = a[_2];
    a[_2] = n[1];
}

void insertion_sort(StringString *a, int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && ((strcmp(a[j-1]._2, a[j]._2) > 0) || (strcmp(a[j-1]._2, a[j]._2) == 0 && strcmp(a[j-1]._1, a[j]._1) > 0)))
        {
            exchange_1_and_2(a, j-1, j);
            j--;
        }
    }
}

void string_ints_print(StringString *a, int n)//tenho que criar esta funcao de modo a dar print na funcao de teste de um array de StringInt
{
  for(int i = 0; i < n; i++)
  {
    printf("%s\n", a[i]._1);
  }
}

void test_final_D()
{
    const char *a[1000];
    const char *b[1000];
    const char *c[1000];
    int i = 0;
    StringString d[1000];
    int n = strings_read(stdin, a);
    apelidos(a, n, b, c);
    while (i < n)
    {
        d[i] = construction(a[i],b[i]);
        i++;
    }
    insertion_sort(d,n);
    string_ints_print(d,n);
}

int main (void)
{
    test_final_D();
    return 0;
}