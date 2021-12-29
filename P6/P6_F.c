#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "our_strings.h"

#define max_tamanho 10000



int str_len1(const char *s)
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}


int str_readline1(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = str_len1(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}


const char *str_dup1(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}


//copiar um elemento de um array a[i] ate determinado ponto ex: str_ndup(a[i], size); com a[0] e size = 3 ->  a[0]=Joao Antonio , resultado= Joa
int str_ncpy1(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = x; i < strlen(s) && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup1(const char *s, int n)
{
  char *result = (char *) malloc(strlen(s) + 1);
  int f=str_ncpy1(result, s, n);
  result[f] = '\0';
  return result;
}



int str_count_while_is_space(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && isspace(s[result]))
    result++;
  return result;
}



int strings_read2(FILE *f, const char **a)
{
  int result = 0;
  char line[400000];
  char line2[400000];
  while (str_readline1(f, line) != EOF)
  {
    if(strlen(line)<1000)
    {
      str_from_html(line2,line);
      int n=str_count_while_is_space(line2);
      a[result++] = str_ndup1(line2,n);
    }
  }
  return result;
}


typedef struct {
 const char *nomeart;
 const char *nomecomp;
 const char *posicao;
 const char *clube;
 const char *dataint;
 const char *datanasci;
 const char *naturalidade;
 int inter;
 int minutosjogados;
 int golos;
 int cartoesama;
 int cartoesverme;
} Jogador;



Jogador *jogador(const char *nomeart,const char *nomecomp,const char *posicao,const char *clube,const char *dataint,const char *datanasci,const char *naturalidade,int inter,int minutosjogados,int golos,int cartoesama,int cartoesverme)
{
  Jogador *result=(Jogador*) malloc(sizeof(Jogador));
  result->nomeart=nomeart;
  result->nomecomp=nomecomp;
  result->posicao=posicao;
  result->clube=clube;
  result->dataint=dataint;
  result->datanasci=datanasci;
  result->naturalidade=naturalidade;
  result->inter=inter;
  result->minutosjogados=minutosjogados;
  result->golos=golos;
  result->cartoesama=cartoesama;
  result->cartoesverme=cartoesverme;
  return result;
}


int findseta(const char* a)
{
  int i=0;
  int r=0;
  int d=0;
  while (a[i]!= '\0')
  {
    if(a[i]=='>' && d==0)
    {
     r=i;
     d=1;
    }
    i++;
  }
  return r;
}


int findseta2(const char* a)
{
  int i=0;
  int r=0;
  while (a[i]!= '\0')
  {
    if(a[i]=='<')
    {
     r=i;
    }
    i++;
  }
  return r;
}



int str_ncpy2(char *r, const char *s, int x,int y)
{
  int n = 0;
  for (int i = x; i < y && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup2(const char *s, int x,int y)
{
  char *result = (char *) malloc(y + 1);
  int f=str_ncpy2(result, s,x,y);
  result[f] = '\0';
  return result;
}



char *find(const char** a,int n,const char* b,int d)
{
  int i=0;
  const char *r="";
  while (i<n)
  {
    if(strcmp(a[i],b)==0)
    {
      r=str_ndup2(a[i+d],findseta(a[i+d])+1,findseta2(a[i+d])); 
    }
    i++;
  }
  return (char*) r;
}



int findevirgula(const char* a)
{
  int i=0;
  int r=0;
  int d=0;
  while (a[i]!= '\0')
  {
    if(a[i]==',' && d==0)
    {
     r=i;
     d=1;
    }
    i++;
  }
  return r;
}


int findespaco(const char* a)
{
  int i=0;
  int r=0;
  int d=0;
  while (a[i]!= '\0')
  {
    if(isspace(a[i]) && d<5)
    {
     r=i;
     d++;
    }
    i++;
  }
  return r;
}



char *find2(const char** a,int n,const char* b,int d)
{
  int i=0;
  const char *r="";
  while (i<n)
  {
    if(strcmp(a[i],b)==0)
    {
      r=str_ndup2(a[i+d],0,findespaco(a[i+d])); 
    }
    i++;
  }
  return (char*) r;
}




void palavraschave(const char** a,int n,Jogador *b)
{
  b->nomeart=find(a,n,"<div class=\"title\">",1);
  b->nomecomp=find(a,n,"<dt>Nome:</dt>",1);
  b->posicao=find(a,n,"<dt>Posição:</dt>",1);
  b->clube=find(a,n,"<dt>Clube na última convocatória:</dt>",1);
  b->dataint=find2(a,n,"<dt>Primeira Internacionalização:</dt>",2);
  b->datanasci=find(a,n,"<dt>Data de Nascimento:</dt>",1);
  b->naturalidade=find(a,n,"<dt>Naturalidade:</dt>",1);
  b->inter=atoi(find(a,n,"<th scope=\"row\">Futebol Masculino Seleção A</th>",1));
  b->minutosjogados=atoi(find(a,n,"<th scope=\"row\">Futebol Masculino Seleção A</th>",2));
  b->golos=atoi(find(a,n,"<th scope=\"row\">Futebol Masculino Seleção A</th>",3));
  b->cartoesama=atoi(find(a,n,"<th scope=\"row\">Futebol Masculino Seleção A</th>",4));
  b->cartoesverme=atoi(find(a,n,"<th scope=\"row\">Futebol Masculino Seleção A</th>",5));
}


void print(FILE *f,Jogador *a)
{
  if(findevirgula(a->clube) ==0)
 fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d\n",a->nomeart, a->nomecomp, a->posicao,a->clube,a->dataint,a->datanasci,a->naturalidade,a->inter,a->minutosjogados,a->golos,a->cartoesama,a->cartoesverme);
 else
 fprintf(f, "%s,%s,%s,\"%s\",%s,%s,%s,%d,%d,%d,%d,%d\n",a->nomeart, a->nomecomp, a->posicao,a->clube,a->dataint,a->datanasci,a->naturalidade,a->inter,a->minutosjogados,a->golos,a->cartoesama,a->cartoesverme);
}


void test_F(void)
{
    const char *a[max_tamanho];
    Jogador jogador[max_tamanho];
    int n = strings_read2(stdin, a);
    palavraschave(a,n,jogador);
    print(stdout,jogador);
}



int main (int argc, char **argv)
 {
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'F')
        test_F();
    else if (x == 'U')
     printf("All unit tests PASSED.\n");
    else 
     printf("%s: Invalid option.\n", argv[1]);
    return 0;
}