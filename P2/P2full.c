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

/////////////////////////////////////////////PROBLEMA A //////////////////////////////////////////////////////////////////



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


//////////////////////////////////////////////////////PROBLEMA B ///////////////////////////////////////////////////////////////





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



////////////////////////////////////////////////////////PROBLEMA C///////////////////////////////////////////////////////////////




#define MAX_LINES 10000
#define MAX_LINE_LENGTH 10000

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



///////////////////////////////////////////////////PROBLEMA D///////////////////////////////////////////////////////////////////////




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

void insertion_sortt(StringString *a, int n)
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

void string_ints_print2(StringString *a, int n)//tenho que criar esta funcao de modo a dar print na funcao de teste de um array de StringInt
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
    insertion_sortt(d,n);
    string_ints_print2(d,n);
}


////////////////////////////////////////////////////////// FUNCAO MAIN////////////////////////////////////////////////////////////7



int main (int argc, char **argv) 
{
    int x = 'A';
    if (argc >= 2)
        x = *argv[1];
    if (x == 'A')
        test_Final_A();
    else if (x == 'B')
        test_Final_B();
    else if (x == 'C')
        test_final_C();
    else if (x == 'D')
        test_final_D();
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}