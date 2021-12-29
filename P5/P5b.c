#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "our_strings.h"


typedef struct{//estrutura
    const char*nome;
    int data;
}birthday;  

birthday stats(const char *nome, int data)//construtor
{
    birthday result;
    result.nome = nome;
    result.data = data; 
    return result;
}

int str_len2(const char *s)//da me o tamanho do array
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}

int str_readline2(FILE *f, char *s)//vai ler linha a linha
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = str_len2(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

const char *str_dup2(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

int strings_read2(FILE *f, const char **a)
{
  int result = 0;
  char line[1000];
  while (str_readline2(f, line) != EOF)
    a[result++] = str_dup2(line);
  return result;
}

int find_virgula(const char *a)//funcao que me encontra a posicao da virgula
{
    int i = 0;
    while (i < strlen(a))//neste caso o i tem que ser menor que o tamanho do array
    {
        if(a[i] == ',')//quando encontra a posicao da virgula retorna a posicao da mesma
        {
            return i;
        }
        i++;
    }
    return 0;
}

char* str_ncpy2(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

const char *str_ndup2(const char *s, int n)
{
  char *result = (char *) malloc(n+ 1);//o strlen le ate ao fim do array 
  str_ncpy2(result, s, n);
  result[n] = '\0';//vai ser um terminador de string
  return result;
} 

int str_ncpy2_modificado(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = x; i < strlen(s); i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup2_modificado(const char *s, int n)
{
  char *result = (char *) malloc(strlen(s)+ 1);
  int x = str_ncpy2_modificado(result, s, n);
  result[x] = '\0';//vai ser um terminador de string
  return result;
} 

void answer(const char **a, int n, birthday *b)//vai ser a funcao que me vai organizar a resposta final
{
    int i = 0;
    while(i < n)
    {
      int pos_virgula = find_virgula(a[i]);//encontra o indice da virgula
      b[i].nome = str_ndup2(a[i], pos_virgula);//a parte do nome vai ser ate a virgula por isso utilizo o ndup2
      b[i].data = atoi(str_ndup2_modificado(a[i], pos_virgula+1));//converte a string em numeros inteiros com o atoi, utilizo o ndup2 para organizar o array com as datas
      i++;
    }    
}

void string_exchange_birthday(birthday *a, int x, int y)//para trocar os elementos simplesmente
{
  birthday m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void ordenar_alfabeticamente(birthday *a, int n)//oredenar alfabeticamete os nomes
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while ((j > 0 && strcmp(a[j-1].nome, a[j].nome)>0))
    {
      string_exchange_birthday(a, j-1, j);
      j--;
    }
  }
}

void select_by_next_data(birthday *a, int n, int data)
{
    int i = 0;
    while (i < n)
    {
      while(a[i].data < data)
      {
        a[i].data += 10000;//vai avancando 10000 por causa dos anos (substitui os 365)
      }
      i++;
    }
}

void ordenar_birthday(birthday *a, int n)//para ordenar as datas pela mais recente
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1].data > a[j].data)//se o numero da data anterior for maior entao troca
    {
      string_exchange_birthday(a, j-1, j);
      j--;
    }
  }
}

void birthday_write(birthday *a, int n)//funcao de escrita
{
    for(int i = 0; i <n; i++)
    printf("%s %d\n", a[i].nome, a[i].data);
}


void test_festa_b(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  const char *a[10000]; 
  birthday b[10000];
  int data;
  scanf("%d", &data);//o que me permite escrever o input
  int n = strings_read2(f, a);
  answer(a,n,b);//vai organizar o array
  ordenar_alfabeticamente(b,n);//ordena
  select_by_next_data(b,n,data);//da me o proximo aniversario
  ordenar_birthday(b,n);//ordena me o aniversario
  birthday_write(b,n);//escreve a resposta final
}


int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'B')
        test_festa_b(argv[2]);
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}