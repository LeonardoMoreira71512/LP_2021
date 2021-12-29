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





//////////////////////////////////////////////////////////////////// INICIO DO PROBLEMA //////////////////////////////////////////////////////





typedef struct
{
    const char *string;
    int number;
} StringInt;

StringInt string_int(const char *string, int number){
    StringInt result = {string, number};
    return result;
}

void strings_tally(const char *a, int n, StringInt *c, int tamanho)
 {
        c[tamanho] = string_int(a,n);//por exemplo c[0] == Leonardo 4 (em que a = Leonardo e n = nº de vezes que o nome aparece)
 }

int strings_count_while(const char **a, int n, const char *b)
{
  int result = 0;
  while (result < n && strcmp(a[result], b) == 0)
    result++;
  return result;
}

int str_search2(const char *s, const char **a, int n)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    if (strcmp(s, a[i]) == 0)
    {
      result++;
    }
    i++;
  }
  return result;
}

int str_count_while_is_not_space(const char *a)//retirado dos lusiadas
{
  int result = 0;
  while (a[result] != '\0' && !isspace(a[result]))//vai contar o numero de letras antes do space
    result++;
  return result;
}

void nomes_proprios1(const char **a, int n, const char **b)
{
    int i = 0;
    int result = 0;
    while(i < n)
    {
    int t = str_count_while_is_not_space(a[i]);// o t vai ser o tamanho das letras do array "a" até chegar ao space
    b[result++] = str_ndup(a[i], t);//o array b vai ser apenas os nomes iniciais de cada linha de nomes
    i++;
    }
}

int unique_first_names2(const char **a, int n, const char**b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    if(str_search(a[i], b, result) == 0)//meto todas as letras do array a estiver no array b entao meto tudo no b
    {
      b[result++] = a[i];
    }
    i++;
  }
  return result;
}

void string_ints_print(StringInt *a, int n)//tenho que criar esta funcao de modo a dar print na funcao de teste de um array de StringInt
{
  for(int i = 0; i < n; i++)
  printf("%s %d\n", a[i].string, a[i].number);
}



void string_int_exchange(StringInt*a, int x, int y)//troca os valores no array a 
{
 StringInt m = a[x];
 a[x] = a[y];
 a[y] = m;
}

void string_ints_isort(StringInt *a, int n)
{
 for (int i = 1; i < n; i++)
 {
 int j = i;
 while ((j > 0 && a[j-1].number <  a[j].number) || (a[j-1].number == a[j].number && strcmp(a[j-1].string, a[j].string) > 0)) //a condicao em sentido lexicografico, ou seja z > a
   {
      string_int_exchange(a, j-1, j);
      j--;
   }
 }
}

void test_Final_B(void)
{
  
  const char *a[5000];
  const char *b[5000];// o array b vai ser apenas os nomes iniciais
  const char *c[5000];
  StringInt d[5000];
  int n = strings_read(stdin, a);
  nomes_proprios1(a,n,b);//da me o tamanho do array b que contem a lista apenas dos nomes proprios
  int i = 0;
  int w = unique_first_names2(b,n,c);//dá me o tamanho do array c que vai ter os nomes e o numero a frente
  while (i < w)
  {
    int r = str_search2(c[i], b, n);//esta funcao precisa de me dar o nº vezes que um numero aparece
    strings_tally(c[i],r, d, i);//vai me retornar a StringInt d ex: d[0] = Leonardo 4( onde c[0] = Leonardo 1 e r = nºvezes que o nome aparece(1) )
    i++;//utilizo c[i] pq so conta ate ao tamanho do array c ou seja o i tem que ser menor que o w para percorrer o array
  } 
  string_ints_isort(d, i);
  string_ints_print(d, i);
}

int main (void)
{
    test_Final_B();
    return 0;
}

