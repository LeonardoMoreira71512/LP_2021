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
  int linhas;
  int colunas;
  int pessoas;
}Mesa;

Mesa esplanada(int linhas, int colunas, int pessoas)
{
    Mesa result;
    result.linhas = linhas;
    result.colunas = colunas; 
    result.pessoas = pessoas;
    return result;
}

int Mesa_read(Mesa* a)
{
  int result = 0;
  int linhas;
  int colunas;
  int pessoas;
  while(scanf("%d %d %d", &linhas,  &colunas, &pessoas) != EOF)
    a[result++] = esplanada(linhas, colunas, pessoas);
  return result;
}

/* int distance_manhattan(Mesa a, Mesa b)
{
 return fabs(a.linhas-b.linhas) + fabs(a.colunas-b.colunas);
} */

void occupy (int r, int c, int m[r][c], Mesa *a, int n)
{
  for(int i = 0; i < n; i++)
  m[a[i].linhas][a[i].colunas] = a[i].pessoas;
}

typedef struct{
  int linhas;
  int colunas;
  int distancia;
}Manhattan;

Manhattan distance1(int linhas, int colunas, int distancia)
{
  Manhattan result = {linhas, colunas, distancia};
  return result;
}

int sum_distance(int r, int c, int m[r][c], Mesa *a, int n)
{
    int operation;
    int result = 0;
    for(int i = 0; i < n; i++)
    {
      operation = a[i].pessoas*(abs(r-a[i].linhas) + abs(c - a[i].colunas));
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
  printf("%d %d %d\n", a[n].linhas, a[n].colunas, a[n].distancia);
}

void test_A(void)
{
  int r, c;
  scanf("%d %d" , &r, &c);
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







///////////////////////////////////////////////////// PROBLEMA B /////////////////////////////////////////////////////////////////////







typedef struct{  //estrutura
    const char*nome;
    int idade;
    int doenca;
    int doenca_aj;
}Vacina;

Vacina stats(const char *nome, int idade, int doenca, int doenca_aj)//construtor
{
    Vacina result;
    result.nome = nome;
    result.idade = idade; 
    result.doenca = doenca;
    result.doenca_aj = doenca_aj;
    return result;
}

int read(const char**a)
{
  int result = 0;
  char line[1000];
  while(scanf("%[^\n]%'c", line) != EOF)
  {
    a[result++] = str_dup(line);
  }
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

int find_virgula2(const char*a)
{
  int i = 0; 
  int r = 0;
  while(a[i]!= '\0')
  {
    if(a[i] == ',')
    {
      r += 1;
    }
    i++;
  }
  return r -1;
}

int str_ncpy1(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup1(const char *s, int n)
{
  char *result = (char *) malloc(strlen(s)+ 1);//o strlen le ate ao fim do array 
  int f = str_ncpy1(result, s, n);
  result[f] = '\0';//vai ser um terminador de string
  return result;
} 

int str_ncpy2(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = x; i < strlen(s) && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup2(const char *s, int n)
{
  char *result = (char *) malloc(strlen(s)+ 1);
  int x = str_ncpy2(result, s, n);
  result[x] = '\0';//vai ser um terminador de string
  return result;
} 


/* int str_len2(const char *s)//da me o tamanho do array
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
} */

int organize (const char **a, int n, Vacina *b)//vai ser a funcao que me vai organizar a resposta final
{
    int i = 0;
    while(i < n)
    {
      int pos_virgula = find_virgula(a[i]);//encontra o indice da virgula
      b[i].nome = str_ndup2(a[i], pos_virgula);//a parte do nome vai ser ate a virgula por isso utilizo o ndup2
      b[i].idade = atoi(str_ndup2_modificado(a[i], pos_virgula+1));//converte a string em numeros inteiros com o atoi, utilizo o ndup2 para organizar o array com as datas
      b[i].doenca = atoi(str_ndup2_modificado(a[i], pos_virgula+4));
      i++;
    }    
}
void idade_ajustada(Vacina *a, int n)
{
    for(int i = 0; i < n;i++)
    {
        if(a[i].idade < 80 && a[i].idade > 65)
        {
            a[i].idade += 5;
            i++;
        }
        else
        {
        a[i].idade = a[i].idade;
        }
    }
}
int compare(const void * a, const void * b)
{
  Vacina data_1 = *(Vacina *)a;
  Vacina data_2 = *(Vacina *)b;
  return ( data_1.idade - data_2.idade);
}
 
int troca(Vacina a, Vacina b)
{
    int result = a.idade - b.idade;
    return result;
}

int matrix_cmp(const void *a, const void *b)        
{
    return troca(*(Vacina *)a, *(Vacina *)b);
}

void qsort_matrix(Vacina *b, int n)
{
    qsort(b,(size_t)n, sizeof(Vacina), matrix_cmp);
}

void Vacina_write(Vacina *a, int n)//funcao de escrita
{
    for(int i = 0; i <n; i++)
    printf("%s %d %d\n", a[i].nome, a[i].idade, a[i].doenca);
}

void test_B(void)
{
  const char *a[10000];
  int n = read(a);
  Vacina b[10000];
  while(fread(b, sizeof(b), 1, f))
  printf("%s %d %d\n", b->nome, b->idade, b->doenca);
  int n = strings_read2(f, a);
  answer(a, n, b);
  idade_ajustada(b, n);
  qsort_matrix(b, n);
  qsort(b, n, sizeof(b), compare);
  Vacina_write(b, n);
}


int main(int argc, char **argv)
{
   int x = 'A';
   if (argc > 1)
   x = *argv[1];
   if (x == 'A')
   test_A();
   else if (x == 'B')
   test_B(argv[2]);
   //else if(x == 'C')
   //test_C();
   //else if (x == 'D')
   //test_D();
   else
   printf("%s: Invalid option.\n", argv[1]);
   return 0;
}