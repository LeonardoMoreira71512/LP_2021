//
//  main.c
//  sorting_strings
//
//  Created by Pedro Guerreiro on 14/03/2021.
//

#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wextra"
#pragma GCC diagnostic error "-Wconversion"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

char *author = "Pedro Guerreiro";

char *message[2] = {"NO", "YES"};
char *message_face[2] = {"☹️", "🙂"};

const int max_line_length = 10000;

// ----------


// Copy `s` to `r`, return `r`.
// `r` should not overlap `s` to the right.
char* str_cpy(char *r, const char *s)
{
  int n = 0;
  for (int i = 0; s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

// Copy at most `x` bytes from `s` to `r`, return `r`.
// `r` should not overlap `s` to the right.
char* str_ncpy(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

// Are the two strings equal?
int str_eq(const char *s, const char *t)
{
  int i = 0;
  while (s[i] && t[i] && s[i] == t[i])
    i++;
  return s[i] == '\0' && t[i] == '\0';
}

void unit_test_str_equal(void)
{
  assert(str_eq("abcd", "abcd"));
  assert(str_eq("", ""));
  assert(!str_eq("abcd", "abcde"));
  assert(!str_eq("abcdefgh", "abcdzfgh"));
  assert(!str_eq("while", "for"));
  assert(!str_eq(" ", ""));
}

// Length of the string, measured in memory bytes used
int str_len(const char *s)
{
  int result = 0;
  while (s[result] != '\0')
    result++;
  return result;
}

void unit_test_str_len(void)
{
  assert(str_len("abcd") == 4);
  assert(str_len("h") == 1);
  assert(str_len("") == 0);
  assert(str_len("abcdefghijklmnopqrstuvwxyz") == 26);
  assert(str_len("ÁÕÇÊÑãúçîè") == 20);  // each of these chars uses 2 bytes
  assert(str_len("☹️") == 6);  // this char uses 6 bytes
  assert(str_len("🙂") == 4);  // this char uses 4 bytes
  assert(str_len("😀") == 4);  // this char uses 4 bytes
  assert(str_len("😀🇵🇹") == 12);  // this string uses 4+8=12 bytes
}

int str_find(const char *s, char x)
{
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      return i;
  return -1;
}

void unit_test_str_find(void)
{
  assert(str_find("abcdedfghi", 'a') == 0);
  assert(str_find("abcdedfghi", 'd') == 3);
  assert(str_find("abcdedfghi", 'g') == 7);
  assert(str_find("abcdedfghi", 'i') == 9);
  assert(str_find("abcdedfghi", 'p') == -1);
  assert(str_find("", 'z') == -1);
}

int str_find_last(const char *s, char x)
{
  int result = -1;
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      result = i;
  return result;
}

void unit_test_str_find_last(void)
{
  assert(str_find_last("abcdeabcde", 'a') == 5);
  assert(str_find_last("abcdedfghi", 'a') == 0);
  assert(str_find_last("abcdedfghi", 'g') == 7);
  assert(str_find_last("abcdedfghi", 'i') == 9);
  assert(str_find_last("aaaaaaaaaa", 'a') == 9);
  assert(str_find_last("", 'z') == -1);
}

char *str_prefix(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; s[i] && i < x; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

void unit_test_str_prefix(void)
{
  char r[1000];
  assert(str_eq(str_prefix(r, "abcde", 3), "abc"));
  assert(str_eq(str_prefix(r, "abcde", 5), "abcde"));
  assert(str_eq(str_prefix(r, "abcde", 10), "abcde"));
  assert(str_eq(str_prefix(r, "abcde", 0), ""));
  assert(str_eq(str_prefix(r, "abcde", -3), ""));
}

// Read a line from `f` to `s`. Does not control buffer overflow.
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

// Create a dynamic copy of at most the first `n` bytes of `s`
// and return its address
const char *str_ndup(const char *s, int n)
{
  char *result = (char *) malloc((unsigned)(n + 1));
  str_ncpy(result, s, n);
  result[n] = '\0';
  return result;
}

int str_count_while(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] == x)
    result++;
  return result;
}

int str_count_while_not(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != x)
    result++;
  return result;
}

int str_count_while_not_func(const char *s, int f(int))
{
  int result = 0;
  while (s[result] != '\0' && !f(s[result]))
    result++;
  return result;
}

int str_count_while_is_not_space(const char *s)
{
  int result = 0;
  while (s[result] != '\0' && !isspace(s[result]))
    result++;
  return result;
}

// --------

void strings_fprint_basic(FILE *f, const char **a, int n)
{
  for (int i = 0; i < n; i++)
    fprintf(f, "%s\n", a[i]);
}

void strings_fprint(FILE *f, const char **s, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%s", s[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%s", separator, s[i]);
  }
}

void strings_fprintln(FILE *f, const char **s, int n, const char *separator)
{
  strings_fprint(f, s, n, separator);
  fprintf(f, "\n");
}

void strings_print(const char **s, int n, const char *separator)
{
  strings_fprint(stdout, s, n, separator);
}

void strings_println(const char **s, int n, const char *separator)
{
  strings_fprintln(stdout, s, n, separator);
}

void strings_fprintf(FILE *f, const char **s, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, s[i]);
}

void strings_fprintfln(FILE *f, const char **s, int n, const char *fmt)
{
  strings_fprintf(f, s, n, fmt);
  fprintf(f, "\n");
}

void strings_printf(const char **s, int n, const char *fmt)
{
  strings_fprintf(stdout, s, n, fmt);
}

void strings_printfln(const char **s, int n, const char *fmt)
{
  strings_fprintfln(stdout, s, n, fmt);
}

int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

int strings_read_words(FILE *f, const char **a)
{
  int result = 0;
  char word[max_line_length];
  while (fscanf(f, "%s", word) != EOF)
    a[result++] = str_dup(word);
  return result;
}


void test_read_write(void)
{
  const char *a[1000];
  int n = strings_read(stdin, a);
  strings_fprint_basic(stdout, a, n);
}

int strings_eq(const char **a, const int n, const char **b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (strcmp(a[i], b[i]) != 0)
      result = 0;
    else
      i++;
  return result;
}

int strings_copy(const char **a, int n, const char **b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, (size_t)n * sizeof(char *));  // Note: 3rd arg is unsigned.
  return n;
}

void strings_exchange(const char **a, int x, int y)
{
  const char *m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void strings_isort(const char **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strcmp(a[j-1], a[j]) > 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

void strings_isort_gen(const char **a, int n, int cmp(const char *, const char *))
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a[j-1], a[j]) > 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

int strings_count_while(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) == 0)
    result++;
  return result;
}

int strings_count_while_not(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) != 0)
    result++;
  return result;
}

int strings_groups(const char **a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = strings_count_while(a+i, n-i, a[i]);
    b[result++] = z;
    i += z;
  }
  return result;
}

int strings_unique(const char **a, int n, const char **b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = strings_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}

// Splitting a string into words
int str_words(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_not_func(s+i, isspace);
      a[result++] = str_ndup(s+i, z);
      i += z;
    }
  return result;
}

int str_count(const char *s, char x)
{
  int result = 0;
  for (int i = 0; s[i]; i++)
    if (s[i] == x)
      result++;
  return result;
}
                            
int str_count_words(const char *s)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_is_not_space(s+i);
      result++;
      i += z;
    }
  return result;
}

void unit_test_count_words(void)
{
  assert(str_count_words("aaa bbb ccc") == 3);
  assert(str_count_words("") == 0);
  assert(str_count_words("     ") == 0);
  assert(str_count_words("aaa") == 1);
  assert(str_count_words("      aaa  ") == 1);
  assert(str_count_words("  a      aaa  a    aaaa  aa  ") == 5);
  assert(str_count_words(" a b c d e f g h i j ") == 10);
  assert(str_count_words("aaa\naaa\naaa\naaa") == 4);
  assert(str_count_words("água café limão Évora São João") == 6);
}

// --------------------

void strings_isort_by_length_only(const char **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strlen(a[j-1]) > strlen(a[j]))
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_strings_isort_by_length_only(void)
{
  const char *a1[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
  strings_isort_by_length_only(a1, 8);
  const char *b1[8] = {"", "zz", "xx", "aa", "ppp", "aaaa", "pppp", "ccccc"};
  assert(strings_eq(a1, 8, b1, 8));
  const char *a2[6] = {"ppp", "zzz", "aaa", "bbb", "ccc", "xxx"};
  strings_isort_by_length_only(a2, 6);
  const char *b2[6] = {"ppp", "zzz", "aaa", "bbb", "ccc", "xxx"};
  assert(strings_eq(a2, 6, b2, 6));
}

// For demonstration only:
void strings_isort_by_length1(const char **a, int n)
{
  strings_isort(a, n);
  strings_isort_by_length_only(a, n);
}

int str_cmp_by_length(const char *s, const char *t)
{
  int result = (int)strlen(s) - (int)strlen(t);
  if (result == 0)
    result = strcmp(s, t);
  return result;
}

void strings_isort_by_length(const char **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && str_cmp_by_length(a[j-1], a[j]) > 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_strings_isort_by_length(void)
{
  const char *a1[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
  strings_isort_by_length(a1, 8);
  const char *b1[8] = {"", "aa", "xx", "zz", "ppp", "aaaa", "pppp", "ccccc"};
  assert(strings_eq(a1, 8, b1, 8));
  
  const char *a2[6] = {"ppp", "zzz", "aaa", "bbb", "ccc", "xxx"};
  strings_isort_by_length(a2, 6);
  const char *b2[6] = {"aaa", "bbb", "ccc", "ppp", "xxx", "zzz"};
  assert(strings_eq(a2, 6, b2, 6));
}

int str_cmp_by_length_down(const char *s, const char *t)
{
  int result = -((int)strlen(s) - (int)strlen(t));
  if (result == 0)
    result = strcmp(s, t);
  return result;
}

void strings_isort_by_length_down(const char **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && str_cmp_by_length_down(a[j-1], a[j]) > 0)
    {
      strings_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_strings_isort_by_length_down(void)
{
  const char *a1[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
  strings_isort_by_length_down(a1, 8);
  const char *b1[8] = {"ccccc", "aaaa", "pppp", "ppp", "aa", "xx", "zz", ""};
  assert(strings_eq(a1, 8, b1, 8));
  
  const char *a2[6] = {"ppp", "zzz", "aaa", "bbb", "ccc", "xxx"};
  strings_isort_by_length_down(a2, 6);
  const char *b2[6] = {"aaa", "bbb", "ccc", "ppp", "xxx", "zzz"};
  assert(strings_eq(a2, 6, b2, 6));
}

void unit_test_strings_isort_gen(void)
{
  const char *a1[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
//  strings_isort(a1, 8);
  strings_isort_gen(a1, 8, strcmp);
  const char *b1[8] = {"", "aa", "aaaa", "ccccc", "ppp", "pppp", "xx", "zz"};
  assert(strings_eq(a1, 8, b1, 8));
  
  const char *a2[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
//  strings_isort_by_length(a2, 8);
  strings_isort_gen(a2, 8, str_cmp_by_length);
  const char *b2[8] = {"", "aa", "xx", "zz", "ppp", "aaaa", "pppp", "ccccc"};
  assert(strings_eq(a2, 8, b2, 8));

  
  const char *a3[8] = {"ppp", "zz", "aaaa", "pppp", "", "ccccc", "xx", "aa"};
//  strings_isort_by_length_down(a3, 8);
  strings_isort_gen(a3, 8, str_cmp_by_length_down);
  const char *b3[8] = {"ccccc", "aaaa", "pppp", "ppp", "aa", "xx", "zz", ""};
  assert(strings_eq(a3, 8, b3, 8));
}

int str_cmp_down(const char *s, const char *t)
{
  return -strcmp(s, t);
}

int str_weight(const char *s)
{
  int result = 0;
  int i = 0;
  while (s[i])
    result += s[i++];
  return result;
}

void unit_test_str_weight(void)
{
  assert(str_weight("") == 0);
  assert(str_weight("A") == 65);
  assert(str_weight("abc") == 294);  // 97+98+99
}

int str_cmp_by_weight(const char *s, const char *t)
{
  int result = str_weight(s) - str_weight(t);
  if (result == 0)
    result = strcmp(s, t);
  return result;
}

int str_cmp_by_weight_down_length_up(const char *s, const char *t)
{
  int result = -(str_weight(s) - str_weight(t));
  if (result == 0)
  {
    result = (int)strlen(s) - (int)strlen(t);
    if (result == 0)
      result = strcmp(s, t);
  }
  return result;
}

int str_cmp_by_letter_a_count(const char *s, const char *t)
{
  int result = str_count(s, 'a') - str_count(t, 'a');
  if (result == 0)
    result = strcmp(s, t);
  return result;
}

int str_cmp_by_letter_a_count_down_length_up(const char *s, const char *t)
{
  int result = -(str_count(s, 'a') - str_count(t, 'a'));
  if (result == 0)
  {
    result = (int)strlen(s) - (int)strlen(t);
    if (result == 0)
      result = strcmp(s, t);
  }
  return result;
}

void test_strings_isort_gen(void)
{
  const char *a[1000];
  int n = strings_read_words(stdin, a);
  strings_fprintfln(stdout, a, n, "<%s>");
  const char *b[1000];
  int m = strings_copy(a, n, b);
  strings_isort_gen(b, m, strcmp);
  strings_fprintfln(stdout, b, m, "[%s]");
  
  m = strings_copy(a, n, b);
  strings_isort_gen(b, m, str_cmp_down);
  strings_fprintfln(stdout, b, m, "[%s]");
  
  m = strings_copy(a, n, b);
  strings_isort_gen(b, m, str_cmp_by_length);
  strings_fprintfln(stdout, b, m, "[%s]");
  
  m = strings_copy(a, n, b);
  strings_isort_gen(b, m, str_cmp_by_length_down);
  strings_fprintfln(stdout, b, m, "[%s]");
  
  m = strings_copy(a, n, b);
  strings_isort_gen(b, m, str_cmp_by_letter_a_count);
  strings_fprintfln(stdout, b, m, "[%s]");
  
  m = strings_copy(a, n, b);
  strings_isort_gen(b, m, str_cmp_by_letter_a_count_down_length_up);
  strings_fprintfln(stdout, b, m, "[%s]");

//  m = strings_copy(a, n, b);
//  strings_isort_gen(b, m, str_cmp_by_weight);
//  strings_fprintfln(stdout, b, m, "[%s]");
  
//  m = strings_copy(a, n, b);
//  strings_isort_gen(b, m, str_cmp_by_weight_down_length_up);
//  strings_fprintfln(stdout, b, m, "[%s]");
}

void test_strings_isort(void)
{
  const char *a[1000];
  int n = strings_read_words(stdin, a);
  strings_fprintfln(stdout, a, n, "<%s>");
  strings_isort(a, n);
  strings_fprintfln(stdout, a, n, "[%s]");
}

// --------------------

void unit_tests(void)
{
  unit_test_str_equal();
  unit_test_str_len();
  unit_test_str_find();
  unit_test_str_find_last();
  unit_test_str_prefix();
  unit_test_count_words();
  unit_test_str_weight();
  unit_test_strings_isort_by_length_only();
  unit_test_strings_isort_by_length();
  unit_test_strings_isort_by_length_down();
  unit_test_strings_isort_gen();
}

void test(void)
{
  assert(0);
}

int main(int argc, const char **argv)
{
  unit_tests();
  int x = 'U';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_strings_isort();
  else if (x == 'B')
    test_strings_isort_gen();
  else if (x == 'C')
    test();
  else if (x == 'D')
    test();
  else if (x == 'E')
    test();
  
  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);
  return 0;
}