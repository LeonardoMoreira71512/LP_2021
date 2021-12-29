#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define max_line_length 10000

//Problema F//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Build the UTF-8 string corresponding to Unicode codepoint `x`
char *str_utf8(char *r, int x)
{
  // See table of powers of 2 at https://en.wikipedia.org/wiki/Power_of_two
  // See also https://en.wikipedia.org/wiki/Delete_character
  int n = 0;
  if (x <= 0)
    ; // these are not valid codepoints.
  else if (x < 127)
    r[n++] = (char)x;
  else if (x == 127)
    ; // this is the DEL character; it does not have a visual representation.
  else if (x < 128+64)
    ; // these are not valid codepoints.
  else if (x < 2048)  // 2048 = 2^11
  {
    r[n++] = (char)(128+64+x/64);
    r[n++] = (char)(128+x%64);
  }
  else if (x < 65536)  // 65536 = 2^16
  {
    r[n++] = (char)(128+64+32 + x/4096);  // 4096 = 2^12
    r[n++] = (char)(128+(x%4096)/64);
    r[n++] = (char)(128+x%64);
  }
  else if (x < 2097152)  // 2097152 = 2^21
  {
    r[n++] = (char)(128+64+32+16 + x/262144); // 262144 = 2^18
    r[n++] = (char)(128+(x%262144)/4096);
    r[n++] = (char)(128+(x%4096)/64);
    r[n++] = (char)(128+x%64);
  }
  else
    assert(1); // these are not valid codepoints. Ignore.
  r[n] = '\0';
  return r;
}


// Compute the codepoint of the first character of `s`.
// Note: `s` uses UTF-8; the first character may occupy up to 4 bytes.
int str_codepoint(const char* s)
{
  // see https://en.wikipedia.org/wiki/UTF-8
  assert(s);
  int result;
  int x = (unsigned char)s[0];
  if (x < 128)
    result = x;
  else if (x < 128+64)
    assert(0); // must not happen at the first byte.
  else if (x < 128+64+32)
    result = x % 32 * 64 + (unsigned char)s[1] % 64;
  else if (x < 128+64+32+16)
    result = (x % 16 * 64 + (unsigned char)s[1] % 64) * 64 +
                            (unsigned char)s[2] % 64;
  else
    result = ((x % 8 * 64 + (unsigned char)s[1] % 64) * 64 +
                            (unsigned char)s[2] % 64) * 64 +
                            (unsigned char)s[3] % 64;
  return result;
}


// Convert html string `s` to UTF-8
char *str_from_html(char *r, const char *s)
{
  int i = 0;
  int n = 0;
  while (s[i])
  {
    if (s[i] == '&' && s[i+1] == '#')
    {
      char *p;
      int x = (int)strtol(s+i+2, &p, 10);
      assert(*p == ';');
      i = (int)(p-s)+1;
      str_utf8(r+n, x);
      n += (int)strlen(r+n);
    }
    else
      r[n++] = s[i++];
  }
  r[n] = '\0';
  return r;
}


//ler o array
int str_len(const char *s)
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

const char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}



int str_ncpy_2(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = x; i < strlen(s) && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return n;
}

const char *str_ndup_partir_n(const char *s, int n)//eliminar os espacos antes dos caracteres
{
  char *result = (char *) malloc(strlen(s) + 1);
  int x = str_ncpy_2(result, s, n);
  result[x] = '\0';
  return result;
}
int str_count_while_is_space(const char *s)//conta o numero de espacos
{
  int result = 0;
  while (s[result] != '\0' && isspace(s[result]))
    result++;
  return result;
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[400000];
  char traduz[1000000];
  while (str_readline(f, line) != EOF)
  {
      if(strlen(line) < 1000){
        str_from_html(traduz, line);
        int espaco = str_count_while_is_space(traduz);
        a[result++] = str_ndup_partir_n(traduz, espaco);
        //a[result++] = str_dup(traduz);
    }
  }
  return result;
}

void str_print(FILE * f, const char** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(f,"%s\n", a[i]);
    }
}

typedef struct{
    const char *nome_a;//nome artistico;
    const char *nome_c;//nome completo;
    const char *posicao;
    const char *clube;//clube da ultima convocatoria;
    const char *inter;//primeira internalizacao;
    const char *nasce;//data de nascimento
    const char *naturalidade;
    int internalizacoes;
    int min_jogados;
    int golos;
    int cartao_a;
    int cartao_v;
}Jogador;


char *encontra_cenas(const char** a, int n, char* b, int g)
{
    const char *result;
    int i = 0;
    
    while(i<n)
    {
        if (strcmp(a[i],b)==0){
            result=a[i+g];
        }
        i++;
    }
    return (char*)result;
}

void dados_player(const char** a, int n, Jogador* c)
{
    c->nome_a = encontra_cenas(a, n, "</noscript>", 2);
}

void test_F()
{

    //Jogador player[max_line_length];

    const char *a[max_line_length];
    
    int n = strings_read(stdin, a);
    //dados_player(a, n, player);
    //printf("%s", player->nome_a);
    str_print(stdout, a, n);
}

int main (int argc, char **argv)
{
	
	//unit_tests();
	int x = 'A';
	if (argc > 1)
		x = *argv[1];
	if (x == 'A')
		test_F();
	//else if (x == 'U')
	//	printf("All unit tests PASSED.\n");
	else
		printf("%s: Invalid option.\n", argv[1]);
	return 0;
}