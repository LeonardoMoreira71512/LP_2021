

#include<math.h>
#include<stdio.h>
#include<assert.h>
#include"our_ints.h"
#include"our_doubles.h"


///////////////////////////////// PROBLEMA A - MAIOR DIVISOR IMPAR ////////////////////////////////////////


int recursiva(int x)
{
	return x % 2 == 1 ? x : recursiva(x/2);
}

void test_recursiva(void)
{
	int x;
	while(scanf("%d", &x) != EOF)
	{
		int z = recursiva(x);
		printf("%d\n", z);
	}
}

int par(int x)//fazer a divisao de numeros pares
{
	while(x % 2 == 0)
	{
		x /= 2;
	}
	return x;
}

int desenferrujando_final(const int *a, int n, int *b)
{
   int result = 0;
   int i = 0;
   while(i < n)
   {
   	if (a[i] % 2 == 1)//se for impar
   		b[result++] = a[i++];
   	else
   		b[result++] = par(a[i++]); 
   }
   return result;//retorna o tamanho do array
}

void test_desenferrujando(void)
{
	int a[1000];
	int b[1000];
	int n = ints_get(a);
	int y = desenferrujando_final(a, n, b);
	ints_println_special(b,y);
}


 void unit_test_par(void)//para testar os valores da funcao
 {
 	assert(par(5) == 5);
 	assert(par(9) == 9);
 	assert(par(20) == 5);
 	assert(par(40) == 5);
 	assert(par(55) == 55);
 	assert(par(87) == 87);
 	assert(par(112) == 7);
 	assert(par(1) == 1);
 }






////////////////////////// PROBLEMA B - VARIAÇÕES RELATIVAS ///////////////////////////////////////






double variacao(double x, double y)
{
  double z = (y-x) / x;
  return z;
}

int variacoes(const double *a, int n, double *b)
{
	int result = 0;
	for (int i = 0; i < n-1; i++)
	{
		b[result++] = variacao(a[i], a[i+1]);
	}
	return result;
}

void test_variacoes()
{
	double a[1000];
	double n = doubles_get(a);
	double b[1000];
	int y = variacoes(a,n,b);
	printf("%f\n", doubles_max(b,y));
}

void unit_test_variacoes(void)
{
	double a[10] = {1, 5, 3, 9, 4, 6, 6, 2, 1, 3};
	double b[10];
	assert(doubles_max(b, variacoes(a, 3,b)) == 4);
	assert(doubles_max(b, variacoes(a + 1, 3, b)) == 2);//a[1] + a[2] + a[3] + a[4]
	assert(doubles_max(b,variacoes(a + 2, 3, b)) == 2);
	assert(doubles_max(b, variacoes(a + 3, 3, b)) == 0.5);
}






//////////////////////////////////////////////// PROBLEMA C - PINGAO /////////////////////////////////////////////






int bilhete(int *a, int n, int vi)//retorna o tamanho do primeiro grupo
{
	int i = 0;
	int result = 0;
	while( i < n && result < vi)
	{
		result += a[i];
		i++;
	}
	return i;//retorna a posicao quando atinge o vi e depois faz o mesmo processo a partir dessa posicao
}


int pingao(int *a, int n, int vi)
{
	int result = 0;
	int i = 0;
	int y = 0;
    while(i < n)
	{
		result = bilhete(a + i, n - i, vi);//da me o numero de elementos que sao maiores do que valor inicial, ou seja o numero de bilhetes , mas nao a sua soma
		i += result;//vou somando o primeiro grupo com o segundo e assim sucessivamente 
	    y += ints_sum(a+i, result) / vi;//o ints sum vai somar todos os elementos de cada grupo que seja maior que vi e dividir pelo vi
	}	
	return y;
}

void test_pingao(void)
{
	int a[1000];
	int vi;
	while(scanf("%d", &vi) != EOF)
	{
		int n = ints_get(a);
		int y = pingao(a,n,vi);
		printf("%d\n", y);
	}
}






/////////////////////////////////////////////// PROBLEMA D - OCEANO /////////////////////////////////////////////////////////






int oceano(int *a, int n, int *b, int vi)
{
 int lista = ints_sum(a, n);//da me a soma da minha lista de produtos
 int v;
 int cont = 0;
 int final = 0;
 for(int i = 0; i < n; i++)
 {
     v = lista + a[i];//valor da lista + qualquer produto que esteja na mesma
     if(v >= vi)//quando o total dos produtos + um qualquer que eu adiciona para ser superior ao valor inicial
     {
       b[cont++] =a[i];//meto todos no array b
     }
   }
   if(cont != 0)
   {
      final = ints_min(b, cont);
   }
 return final;
}


void test_oceano()
{
	int a[1000];
	int b[1000];
	int vi;
	while(scanf("%d", &vi) != EOF)
	{
		int n = ints_get(a);
		int vf = oceano(a, n, b, vi);
		printf("%d\n", vf);
	}
}






//////////////////////////////PROBLEMA E - BOLSA///////////////////////////////////////////////////////



	

// double group(double *a, int n, double *b)//retorna o tamanho do primeiro grupo
// {
// 	int i = 0;
// 	int result = 0;
// 	while(i < n && a[i] < a[i+1])
// 	{
// 		result += a[i+1] - a[i];
// 		i++;
// 	}
// 	return i;//retorna a posicao quando atinge o vi e depois faz o mesmo processo a partir dessa posicao
// }

// double bolsa(double *a, int n, double *b)
// {
//     double result = 0;
//     int i = 0;
//     double y = 0;
//     while(i < n)
//     {
//     	result = group(a+i, n-i, b)
//     }
// }

// int bilhete(int *a, int n, int vi)//retorna o tamanho do primeiro grupo
// {
// 	int i = 0;
// 	int result = 0;
// 	while( i < n && result < vi)
// 	{
// 		result += a[i];
// 		i++;
// 	}
// 	return i;//retorna a posicao quando atinge o vi e depois faz o mesmo processo a partir dessa posicao
// }

// int pingao(int *a, int n, int vi)
// {
// 	int result = 0;
// 	int i = 0;
// 	int y = 0;
//     while(i < n)
// 	{
// 		result = bilhete(a + i, n - i, vi);//da me o numero de elementos que sao maiores do que valor inicial, ou seja o numero de bilhetes , mas nao a sua soma
// 		i += result;//vou somando o primeiro grupo com o segundo e assim sucessivamente 
// 	    y += ints_sum(a+i, result) / vi;//o ints sum vai somar todos os elementos de cada grupo que seja maior que vi e dividir pelo vi
// 	}	
// 	return y;
// }

// double diferenca(double*a, int n, double *b)
// {
// 	int i = 0;
// 	int result = 0;
// 	while (i < n-1)
// 	{
// 		b[result++] = a[i+1] - a[i];//o array b calcula a diferenca de cada elemento do array a
// 		i++;
// 	}
// 	return result;
// }

// double count_up(double *a, int n)//para saber quando a cotação aumentou
// {
//  int result=0;
//  while((a[result]>=0) && (result<n))
//  {
//   result++;
//  }
//   return result;
// }

// double count_down(double *a,int n)//para saber quando a cotação desceu
// {
//   int result=0;
//  while((a[result]<0) && (result<n))
//  {
//   result++;
//  }
//   return result; 
// }

// double ups_and_down(double *a, int n, double *b) 
// {
//   int result = 0;
//   int i= 0;
//   while (i< n)
//   { 
//     double y = count_up(a+i,n-i);//o y representa a subida das cotacoes
//     double z = count_down(a+i,n-i);//z representa a descida das cotacoes
//     if(y>0)//se y é positivo entao 
//     {
//       b[result++] = y;
//       i+= y;
//     }
//     else if(z>0)//quer dizer que o pib aumentou de trimestre para trimestre pois o array b significa a diferenca do pib de um trimestre para o outro
//     {
//       i += z;
//     }
//   }
//   return result;
// }
//   double count_groups(double *a, int n, double *b)
//  {
//  	int result = 0;
//  	int i = 0;
//  	while(i<n)
//  	{
//  		c[result++] = a[b[i]];
//  		i++;
//  	}
//  	return result;
//  }


int count_while(double *a, int n)
{
	int i = 1;
	while(i < n && a[i-1] < a[i])
		i++;
	return i;
}


int bolsa(double *a, int n, int *b)
{
 int result = 0;
 int i = 0;
 while(i<n)
 	{
         int p = count_while(a+i, n-i);
         b[result++] = p;
         i += p; 
 	}
 	return result;
}


void test_bolsa(void)
{
	char *message[2] = {"NO", "YES"};
	double a[1000];
	int b[1000];
	int n = doubles_get(a);
	int w = bolsa(a, n, b);
	int y = (ints_max(b,w) == b[w-1]);
	printf("%s\n", message[y]);
}

// void unit_test_count_while(void)
// {
//   double a[25] = {3.1, 4.2, 5.5, 2.0, 2.0, 4.0, 3.4, 5.5, 2.9, 3.0, 5.4, 6.5, 7.1, 5.0, 4.5,5.2, 5.1, 4.1, 3.4, 5.8, 5.1, 6.1, 8.1, 9.6, 12.5};

//   assert(count_while(a, 4, 2.0) == 0);
//   assert(count_while(a, 8, 5.5) == 7);
//   assert(count_while(a, 5, 2.0) == 1);
//   assert(count_while(a, 10, 3.0) == 3);
// }

void unit_tests()
{
	unit_test_par();
	unit_test_variacoes();
    //unit_test_count_while();
}


int main(int argc, char **argv)
{
	int x = 'A';
	unit_tests();
	if (argc > 1);
    x = *argv[1];
    if (x == 'A')
    {
    test_desenferrujando();
    test_recursiva();
    }
    else if (x == 'B')
    test_variacoes();
    else if (x == 'C')
    test_pingao();
    else if (x == 'D')
    test_oceano();
    else if (x == 'E')
    test_bolsa();
    else
    printf("%s: INVALID OPTION.\n", argv[1]); 
    return 0;
}