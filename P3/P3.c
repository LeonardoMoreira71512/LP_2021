#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

const char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

const int max_players = 10000;

typedef struct 
{
    int internacionalizacoes;
    const char *name;
    const char *position;
    int goals;
    int birth;
    const char *club;
}Player;

Player player(int internacionalizacoes, const char *name, const char *position, int goals, int birth, const char *club)
{
    Player result = {internacionalizacoes, name, position, goals, birth, club};
    return result;
}

int player_read(FILE *f, Player* a)//ler o array de estrutura player
{
  int result = 0;
  int internacionalizacoes;
  char name[max_players];
  char position[max_players];
  int goals;
  int birth;
  char club[max_players];
  while (fscanf(f, "%d %s %s %d %d %s", &internacionalizacoes, name, position, &goals, &birth, club) != EOF)
    a[result++] = player(internacionalizacoes, str_dup(name), str_dup(position), goals, birth, str_dup(club));
  return result;
}

void player_write(FILE *f, Player *a, int n)
{
    for(int i = 0; i <n; i++)
    printf("[%d][%s][%s][%d][%d][%s]\n", a[i]. internacionalizacoes, a[i]. name, a[i].position, a[i].goals, a[i].birth, a[i].club);
}

void test_A(const char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    Player player[max_players];
    int n_player = player_read(f, player);
    player_write(stdout, player, n_player);
}


////////////////////////////////////////////////////// PROBLEMA B ///////////////////////////////////////////////////////////////



 int players_select_by_club(const Player *a, int n, const char *club, Player *b)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
    if (strcmp(a[i].club, club) == 0)
    b[result++] = player(a[i]. internacionalizacoes, a[i]. name, a[i].position, a[i].goals, a[i].birth, a[i].club);
    }
    return result;
} 

void player_writee(FILE *f, Player *a, int n)
{
    for(int i = 0; i <n; i++)
    printf("%s %d\n",  a[i]. name, a[i]. internacionalizacoes);
}

void test_B(const char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    Player a[max_players];
    int n = player_read(f, a);
    Player b[max_players];
    char club[max_players];
    while(scanf("%s", club) != EOF)
    {
      int result = players_select_by_club(a, n, club, b);//vai me dar o tamanho do array
      if(result > 0)
      player_writee(stdout, b, result);
      else
      printf("(void)\n");
    }
}   



////////////////////////////////////////////////////////////PROBLEMA C///////////////////////////////////////////////////////////////////



typedef struct{ //estrutura para poder agrupar as equipas com o nº jogos
    const char *club;
    int inter;
}Selecao;

Selecao ranking(const char *club, int inter) //construtor
{
    Selecao result = {club, inter};
    return result;
}


int sum_internacionalizacoes(Player *a, int n)//variacao da ints sum para somar as internacionalizacoes
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        result += a[i].internacionalizacoes;
    }
    return result;
}


int strings_count_club(Player *a, int n, const char *club)//usar para contar os clubes
{
    int result = 0;
    while(result < n && strcmp(a[result].club, club) == 0)
    result++;
    return result;
}

int contribuicao(Player *a, int n, Selecao *b)
{
    int result = 0;
    int i = 0;
    while (i < n)
    {
     int z = strings_count_club(a+i, n-i, a[i].club);//vai contar apenas os clubes
     b[result++] = ranking(a[i].club,sum_internacionalizacoes(a+i, z));
     i+= z;//vai ver de club em club e mete no array b para dar a lista com o club e a frente a soma das internacionalizacoes
    }
    return result;//no final da me o tamanho do array final
}

void exchange_inter(Selecao*a, int x, int y)//vai trocar os elementos
{
    Selecao m = a[x];
    a[x] = a[y];
    a[y] = m;
}

void ordenacao_inter(Selecao *a, int n)//para ordenar o numero de jogos por ordem decresecente
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && a[j-1].inter < a[j].inter)
        {
            exchange_inter(a, j-1, j);
            j--;
        }
    }
}

void string_exchange(Player *a, int x, int y)
{
    Player m = a[x];
    a[x] = a[y];
    a[y] = m;
}

void ordenacao_club(Player *a, int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i;
        while( j > 0 && strcmp(a[j-1].club, a[j].club) > 0)//neste caso ja posso utilizar strcmp pq se trata de char
        {
            string_exchange(a, j-1, j);
            j--;
        }
    }
}

void ranks(FILE *f, Selecao a)//servira para organizar a resposta final
{
    fprintf(f, "%s %d", a.club, a.inter);
}

void selection(FILE *f, Selecao a)//construtor para a funcao de escrita
{
    ranks(f,a);
    fprintf(f, "\n");
}

void ranking_write (FILE *f, Selecao *a, int n)//funcao final de escrita
{
    for(int i = 0; i < n; i++)
    selection(f,a[i]);
}


void test_C(const char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    Player a[max_players];
    int n = player_read(f, a);
    ordenacao_club(a, n);
    Selecao b[max_players];
    int tamanho = contribuicao(a, n, b);
    ordenacao_inter(b,tamanho);  
    ranking_write(stdout, b, tamanho);//escrever a resposta final
}



///////////////////////////////////////////////////////////PROBLEMA D///////////////////////////////////////////////////////////////////////




typedef struct{
    int internacionalizacoes;
    const char *name;
    int position;
    int goals;
    int birth;
    const char *club;
}Position;

Position lista(int internacionalizacoes, const char *name,int position, int goals, int birth, const char *club)
{
   Position result = {internacionalizacoes, name, position, goals, birth, club};
   return result;
}

void exchange_position(Position *a, int x, int y)//para trocar as posicoes
{
    Position m = a[x];
    a[x] = a[y];
    a[y] = m;
}

int atribuicao_position(Player *a, int n, Position *b)//atribuir os numeros aos 4 caracteres
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
       if(strcmp("Guarda_Redes", a[i].position) == 0)
       b[result++] = lista(a[i].internacionalizacoes, a[i].name, 1, a[i].goals, a[i].birth, a[i].club);
       else if(strcmp("Defesa", a[i].position) == 0)
       b[result++] = lista(a[i].internacionalizacoes, a[i].name, 2, a[i].goals, a[i].birth, a[i].club);
       else if(strcmp("Medio", a[i].position) == 0)
       b[result++] = lista(a[i].internacionalizacoes, a[i].name, 3, a[i].goals, a[i].birth, a[i].club);
       else if(strcmp("Avancado", a[i].position) == 0)
       b[result++] = lista(a[i].internacionalizacoes, a[i].name, 4, a[i].goals, a[i].birth, a[i].club);
    }
    return result;
}

int comparacao_position(Position a, Position b)//para comparar as posicoes e os golos caso seja menor entao troca
{
    int result = a.position - b.position;
    if (result == 0 && b.goals > a.goals)
       result = 1;
    return result;
}


void ordenacao_position(Player *a, int n, Position *b)//funcao final de ordenacao
{
     for(int i = 1; i < n; i++)
    {
        int j = i;
        while( j > 0 && (comparacao_position(b[j-1], b[j]) > 0))//neste caso ja posso utilizar strcmp pq se trata de char
        {
            exchange_position(b, j-1, j);
            string_exchange(a, j-1, j);
            j--;
        }
    }
}

void ordenacao_name(Player *a, int n)//para desempatar por nome
{
    for(int i = 1; i < n; i++)
    {
        int j = i;
        while( j > 0 && strcmp(a[j-1].name, a[j].name) > 0)//neste caso ja posso utilizar strcmp pq se trata de char
        {
            string_exchange(a, j-1, j);
            j--;
        }
    }
}


void test_D(const char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f != NULL);
    Player a[max_players];
    int n = player_read(f, a);
    ordenacao_name(a,n);
    Position b[max_players];
    int n2 = atribuicao_position(a, n, b);
    ordenacao_position(a, n2, b);
    player_write(stdout, a, n);
}


int main(int argc, char **argv)
{
    int x = 'A';
    if (argc > 1)
        x = *argv[1];
    if (x == 'A')
        test_A(argv[2]);
    else if (x == 'B')
        test_B(argv[2]);
    else if (x == 'C')
        test_C(argv[2]);
    else if (x == 'D')
        test_D(argv[2]);
    else
       printf("%s: Invalid option.\n", argv[1]);
    return 0;
}