//Problema B

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINES 10000
#define MAX_LINE_LENGTH 10000

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





/////////////////////////////////////////////////// INICIO DO PROBLEMA //////////////////////////////////////////////////////




int str_getline(char *s)
{
  return str_readline(stdin, s);
}

void strings_exchange(const char **c, int x, int y)
{
  const char *m = c[x];
    c[x] = c[y];
    c[y] = m;
}

void insertion_sort(const char **c, int y, const char **b)
{
    for (int i = 1; i < y; i++)
    {
        int j = i;
        while (j > 0 && strcmp(b[j-1], b[j]) >   0)
        {
            strings_exchange(c, j-1, j);
            strings_exchange(b, j-1, j);
            j--;
        }
    }
}

int str_count_while_is_not_space(const char *s)//retirado dos lusiadas
{
  int result = 0;
  while (s[result] != '\0' && s[result] != ' ')//vai contar o numero de letras antes do space
    result++;
  return result;
}

int str_words(const char *s, const char **a)//retorna o numero de linhas do array inicial
{
  int result = 0;
  int i = 0;
  while (s[i])
  if (s[i] == ' ')
    i++;
  else
  {
    int z = str_count_while_is_not_space(s+i);
    a[result++] = str_ndup(s+i, z);
    i += z;
  }
  return result;
}

const char *last_word (const char *s)
{
  const char *a[MAX_LINES];
  int n = str_words(s,a);
  return a[n-1];
}

int get_last_name(const char **s, int n, const char **b)
{
  int result = 0;
  for(int i = 0; i < n; i++)
  b[result++] = last_word(s[i]);
  return result;
}

void test_final_C()
{
  const char *s[MAX_LINES];
  int n = 0;
  char lines[MAX_LINES];
  while (str_getline(lines) != EOF)
  {
    s[n++] = str_dup(lines);
  }
  const char *b[MAX_LINES];
  int y = get_last_name(s, n, b);
  insertion_sort(s, y, b);
  for (int i = 0; i < y;i++)
  printf("%s\n", s[i]);
}

int main (void)
{
    test_final_C();
    return 0;
}