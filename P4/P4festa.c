/* Eu, Leonardo Moreira aluno 71512, de­cla­ro por mi­nha hon­ra que este pro­gra­ma foi es­cri­to por mim, du­ran­te a
fes­ta de 26 de mar­ço de 2021, e que não re­ce­bi aju­da de nin­guém, a não ser da pro­fesso­ra Gra­ça,
do pro­fes­sor Ami­ne, do pro­fes­sor Pe­ter Stal­lin­ga, do meu co­le­ga Pe­dro Cava­lhei­ro e do pro­fes­sor Pe­dro. */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "our_strings.h"



/////////////////////////////////////////////////////////////////////////////////// INICIO DO B /////////////////////////////////77

const int max_value = 10000;

//contar o numero de letras ate haver um espaco
int str_count_while_is_not_space(const char *a)
{
  int result = 0;
  while (a[result] != '\0' && a[result]!=' ')         //!isspace(a[result]) faz o mesmo que a[result]!=' '
    result++;
  return result;
}

typedef struct{
    const char*nome;
    int data;
}birthday;  

birthday stats(const char *nome, int data)
{
    birthday result;
    result.nome = nome;
    result.data = data; 
    return result;
}


int find_virgula(const char *a)
{
    int i = 0;
    while (i < str_len(a))
    {
        if(a[i] == ',')
        {
            return i;
        }
        i++;
    }
    return 0;
}

int str_ncpyy(char *r, const char *s, int x)
{
    int n = 0;
    for(int i = x; i < str_len(s); i++)
    r[n++] = s[i];
    r[n] = '\0';
    return n;
}

const char *str_ndupp(const char *s, int n)
{
  char *result = (char *) malloc(str_len(s) + 1);
  int m = str_ncpyy(result, s, n);
  result[m] = '\0';
  return result;
}

void answer(const char **a, int n, birthday *b)//vai ser a funcao que me vai organizar a resposta final
{
    int i = 0;
    while(i < n)
    {
      int pos_virgula = find_virgula(a[i]);
      b[i].nome = str_ndup(a[i], pos_virgula);
      b[i].data = atoi(ndupp(a[i], pos_virgula+1));
    }    
}

/* char *find(const char **a, int n)
{
    int i = 0;
    const char *r;
    while (i < n)
    {
        r = str_ndupp(a[i], 0, find_virgula(a[i]));
        i++;
    }
    return (char*)r;
} */


void birthday_write(birthday *a, int n)
{
    for(int i = 0; i <n; i++)
    printf("%s %d\n", a[i].nome, a[i].data);
}

void string_exchange_birthday(birthday *a, int x, int y)
{
  birthday m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void ordenar_alfabeticamente(birthday *a, int n)
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

void ordenar_birthday(birthday *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1].data > a[j].data)
    {
      string_exchange_birthday(a, j-1, j);
      j--;
    }
  }
}

 int select_by_next_data(birthday *a, int n, int data)
{
    for(int i = 0; i < n; i++)
    {
      while(a[i].data  < data)
      {
        a[i].data += 10000; 
      }
      i++;
    }
  
} 



void test_festa(const char *filename)
{
  FILE *f = fopen(filename, "r");
  assert(f != NULL);
  const char *a[max_value];
  int n = strings_read(f, a);
  birthday b[max_value];
  ordenar_alfabeticamente(b,n);
  int data;
  while(scanf("%d", data) != EOF)
  {
    answer(a,n,b);
    select_by_next_data(b,n,data);
    ordenar_birthday(b,n);
    birthday_write(b,n);
  }
}


int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_festa(argv[2]);
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}

