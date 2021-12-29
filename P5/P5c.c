#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define max_value 1000

typedef struct{
    int dias;
    double incidencia;
    double transmissibilidade;
}Covid;

Covid stats(int dias, double incidencia, double transmissibilidade)
{
    Covid result;
    result.dias = dias;
    result.incidencia = incidencia;
    result.transmissibilidade = transmissibilidade;
    return result;
}

int Covid_read(FILE *f, Covid* a)
{
  int result = 0;
  int dias;
  double incidencia;
  double transmissibilidade;
  while(fscanf(f, "%d%lf%lf", &dias, &incidencia, &transmissibilidade) != EOF)
    a[result++] = stats(dias, incidencia, transmissibilidade);
  return result;
}

int max_dias(const int *a, int n)
{
  assert(n > 0);
  int result = a[0];
  for (int i = 1; i < n; i++) 
    if (result < a[i])
      result = a[i];
  return result;
}

int Covid_count_while_sobe(Covid *a, int n)
{
  int i = 0;
  while (i + 1 < n && (a[i].incidencia < a[i+1].incidencia || a[i].transmissibilidade < a[i+1].transmissibilidade))//conta enqunanto a inc e a trans. estiver a aumentar
    i++;
  return i;
}

int Covid_count_while_desce(Covid *a, int n)
{
  int i = 0;
  while (i + 1 < n && !(a[i].incidencia < a[i+1].incidencia || a[i].transmissibilidade < a[i+1].transmissibilidade))//conta enqunanto a inc e a trans. estiver a descer
    i++;
  return i;
}

int count_maior_numero_de_dias_seguidos_COM_subidas(Covid *a, int n, int *b)
{
   int result = 0;
   int i = 0;
   while(i < n)
   {
    int z = Covid_count_while_sobe(a+i, n-i);//enquanto os dados sobem
    b[result++] = a[i+z].dias - a[i].dias;//mete no array b a diferenca entre esses valores
    i+= z;//vai aumentando de z em z
    i++;
   } 
  return result;
}

int count_maior_numero_de_dias_seguidos_SEM_subidas(Covid *a, int n, int *b)
{
   int result = 0;
   int i = 0;
   while(i < n)
   {
    int z = Covid_count_while_desce(a+i, n-i);
    b[result++] = a[i+z].dias - a[i].dias;
    i+= z;
    i++;    
   }
  return result;
}

void test_festa_C()
{
  Covid a[max_value];
  int n = Covid_read(stdin,a);
  int b[max_value];
  int tamanho = count_maior_numero_de_dias_seguidos_COM_subidas(a, n, b);
  int num_days = max_dias(b, tamanho); 
  int c[max_value];
  int tamanho2 = count_maior_numero_de_dias_seguidos_SEM_subidas(a, n, c);
  int num_days2 = max_dias(c, tamanho2);
  const char *vamos[2] = {"NO", "YES"};
  int desconfinar = (num_days2 > num_days);
  printf("%s\n", vamos[desconfinar]);
}

int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'C')
        test_festa_C();
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}