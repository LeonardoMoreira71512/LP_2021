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
int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[1000];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

//dar print do array
void str_print(const char** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", a[i]);
    }
}

//copiar um elemento de um array a[i] ate determinado ponto ex: str_ndup(a[i], size); com a[0] e size = 3 ->  a[0]=Joao Antonio , resultado= Joa
char* str_ncpy(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}
const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc(n + 1);
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

//contar o numero de letras ate haver um espaco
int str_count_while_is_not_space(const char *a)
{
  int result = 0;
  while (a[result] != '\0' && a[result]!=' ')         //!isspace(a[result]) faz o mesmo que a[result]!=' '
    result++;
  return result;
}

//verificar se uma determinada palavra existe num array de palavras
int str_search(const char* s, const char **a, int n)
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

//organizar arrays por ordem crescente
void ints_exchange (int *a, int x, int y)
{
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}
void ints_crescente(int *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1] > a[j])
    {
      ints_exchange(a, j-1, j);
      j--;
    }
  }
}

//organizar arrays por ordem decrescente
void ints_exchange (int *a, int x, int y)
{
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}
void ints_decrescente(int *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1] < a[j])
    {
      ints_exchange(a, j-1, j);
      j--;
    }
  }
}

//organizar arrays por ordem decrescente com desempate por ordem alfabetica 
void ints_exchange1(ClubCont *a, int x, int y)
{
  ClubCont m = a[x];
  a[x] = a[y];
  a[y] = m;
}
void ints_decrescente(ClubCont *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while ((j > 0 && a[j-1].inter < a[j].inter) || (a[j-1].inter==a[j].inter && strcmp(a[j-1].club,a[j].club)>0))
    {
      ints_exchange1(a, j-1, j);
      j--;
    }
  }
}