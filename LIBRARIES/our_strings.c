//
//  our_strings.c
//
//  Created by Pedro Guerreiro on 10/12/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#include "our_strings.h"

int max_line_length = 10000;

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

void unit_test_str_ncpy(void)
{
  char r[1000];
  assert(str_equal(str_ncpy(r, "abcde", 3), "abc"));
  assert(str_equal(str_ncpy(r, "abcde", 5), "abcde"));
  assert(str_equal(str_ncpy(r, "abcde", 10), "abcde"));
  assert(str_equal(str_ncpy(r, "abcde", 0), ""));
  assert(str_equal(str_ncpy(r, "abcde", -3), ""));
}

// Are the two strings equal?
int str_equal(const char *s, const char *t)
{
  int i = 0;
  while (s[i] && t[i] && s[i] == t[i])
    i++;
  return s[i] == '\0' && t[i] == '\0';
}

void unit_test_str_equal(void)
{
  assert(str_equal("abcd", "abcd"));
  assert(str_equal("", ""));
  assert(!str_equal("abcd", "abcde"));
  assert(!str_equal("abcdefgh", "abcdzfgh"));
  assert(!str_equal("while", "for"));
  assert(!str_equal(" ", ""));
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

// Find the first occurrence of `x` in `s`. Return -1 if it does not occur.
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

// Find the last occurrence of `x` in `s`. Return -1 if it does not occur.
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

// Convert `s` to lowercase. Result in `r`.
// Only for Basic Latin characters
char *str_tolower(char *r, const char *s)
{
  int x = 0;
  for (int i = 0; s[i]; i++)
    r[x++] = tolower(s[i]);
  r[x] = '\0';
  return r;
}

// Convert `s` to uppercase. Result in `r`.
// Only for Basic Latin characters
char *str_toupper(char *r, const char *s)
{
  int x = 0;
  for (int i = 0; s[i]; i++)
    r[x++] = toupper(s[i]);
  r[x] = '\0';
  return r;
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
  char *result = (char *) malloc(n + 1);
  strncpy(result, s, n);
  result[n] = '\0';
  return result;
}

// Number of initial chars in `s` equal to `x`
int str_count_while(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] == x)
    result++;
  return result;
}

// Number of initial chars in `s` NOT equal to `x`
int str_count_while_not(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] != x)
    result++;
  return result;
}

// Number of initial chars in `s` that satisfy `f`
int str_count_while_func(const char *s, int f(int))
{
  int result = 0;
  while (s[result] != '\0' && f(s[result]))
    result++;
  return result;
}

// Number of initial chars in `s` that do NOT satisfy `f`
int str_count_while_not_func(const char *s, int f(int))
{
  int result = 0;
  while (s[result] != '\0' && !f(s[result]))
    result++;
  return result;
}

// Read a file into a single string
char *str_from_file(char *r, FILE *f)
{
  int n = 0;
  char x;
  while (fscanf(f, "%c", &x) != EOF)
    r[n++] = x;
  r[n] = '\0';
  return r;
}

// Read a line from `f` to `s`. Does not control buffer overflow.
int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = (int) strlen(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
}

// Read a line from `stdin` to `s`. Does not control buffer overflow.
int str_getline(char *s)
{
  return str_readline(stdin, s);
}

// Read a file into a single string
//char *str_from_file(char *r, FILE *f)
//{
//  int n = 0;
//  char x;
//  while (fscanf(f, "%c", &x) != EOF)
//    r[n++] = x;
//  r[n] = '\0';
//  return r;
//}

// Create a dynamic array with `n` `const char *` strings.
const char **strings_new(int n)
{
  return (const char **) malloc (n * sizeof(char *));
}

// Copy all strings from `a` to `b`
// Note: only the addresses are copied, not the contents of the strings
int strings_copy(const char **a, int n, const char **b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(char *));  // Note: 3rd arg is unsigned.
  return n;
}



// Read `a` from `f`, line by line.
int strings_read(FILE *f, const char **a)
{
  int result = 0;
  char line[max_line_length];
  while (str_readline(f, line) != EOF)
    a[result++] = str_dup(line);
  return result;
}

// Read `a` from `stdin`, line by line.
int strings_get(const char **a)
{
  return strings_read(stdin, a);
}

// Read `a` from `f`, word by words, using white space as separators.
int strings_readwords(FILE *f, const char **a)
{
  int result = 0;
  char word[max_line_length];
  while (fscanf(f, "%s", word) != EOF)
    a[result++] = str_dup(word);
  return result;
}

// Read `a` from `stdin`, word by words, using white space as separators.
int strings_getwords(const char **a)
{
  return strings_readwords(stdin, a);
}

// Write strings in `a` to `f`, one per line
void strings_fprint_basic(FILE *f, const char **a, int n)
{
  for (int i = 0; i < n; i++)
    fprintf(f, "%s\n", a[i]);
}

// Write strings in `a` to `stdout`, one per line
void strings_print_basic(const char **a, int n)
{
  strings_fprint_basic(stdout, a, n);
}

// Write strings in `a` to `f`, separated by `separator`
void strings_fprint(FILE *f, const char **a, int n, const char *separator)
{
  if (n > 0)
  {
    fprintf(f, "%s", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      fprintf(f, "%s%s", separator, a[i]);
  }
}

// Write strings in `a` to `stdout`, separated by `separator`
void strings_print(const char **a, int n, const char *separator)
{
  strings_fprint(stdout, a, n, separator);
}

// Write strings in `a` to `f`, separated by `separator`
// and add a newline after writing all strings
void strings_fprintln(FILE *f, const char **a, int n, const char *separator)
{
  strings_fprint(f, a, n, separator);
  fprintf(f, "\n");
}

// Write strings in `a` to `stdout`, separated by `separator`
// and add a newline after writing all strings
void strings_println(const char **a, int n, const char *separator)
{
  strings_fprintln(stdout, a, n, separator);
}

// Write strings in `a` to `f`, each using `fmt` as format string
void strings_fprintf(FILE *f, const char **a, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, a[i]);
}

// Write strings in `a` to `f`, each using `fmt` as format string
// and add a newline after writing all strings
void strings_fprintfln(FILE *f, const char **a, int n, const char *fmt)
{
  strings_fprintf(f, a, n, fmt);
  fprintf(f, "\n");
}

// Write strings in `a` to `stdout`, each using `fmt` as format string
void strings_printf(const char **a, int n, const char *fmt)
{
  strings_fprintf(stdout, a, n, fmt);
}

// Write strings in `a` to `stdout`, each using `fmt` as format string
// and add a newline after writing all strings
void strings_printfln(const char **a, int n, const char *fmt)
{
  strings_fprintfln(stdout, a, n, fmt);
}

// Linear search for arrays of strings
int strings_find(const char **a, int n, const char *x)
{
  for (int i = 0; i < n; i++)
    if (strcmp(a[i], x) == 0)
      return i;
  return -1;
}

// Count the occurrences of `x` in `a`.
int strings_count(const char **a, int n, const char *x)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (strcmp(a[i], x) == 0)
      result++;
  return result;
}

// Are the string arrays `a` and `b` equal?
int strings_equal(const char **a, const int n, const char **b, int m)
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

// Compute the rank of `x` in `a`
// Pre: a is sorted.
int strings_rank(const char **a, int n, const char *x)
{
  int result = 0;
  while (n > 0)
  {
    int m = n / 2;
    if (strcmp(x, a[m]) <= 0)
      n = m;
    else
    {
      result += m+1;
      a += m+1;
      n -= m+1;
    }
  }
  return result;
}

// Binary search for arrays of strings
// Pre: `a` is sorted
int strings_bfind(const char **a, int n, const char *x)
{
  int r = strings_rank(a, n, x);
  return r < n && strcmp(a[r], x) == 0 ? r : -1;
}

// Exchange values at position `x` in `y` of `a`
void strings_exchange(const char **a, int x, int y)
{
  const char *m = a[x];
  a[x] = a[y];
  a[y] = m;
}

// Insertion sort for arrays of strings
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

// Insertion sort for arrays of strings with parametric comparison
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

// Merge two arrays of strings, lexicographically.
int strings_merge(const char **a, int n, const char **b, int m, const char **c)
{
  int result = 0;
  int i = 0;
  int j = 0;
  while (i < n && j < m)
    if (strcmp(a[i], b[j]) <= 0)
      c[result++] = a[i++];
    else
      c[result++] = b[j++];
  result += strings_copy(a + i, n - i, c+result);
  result += strings_copy(b + j, m - j, c+result);
  return result;
}

// This is a private function
void strings_msort_i(const char **a, int n, const char **b)
{
  if (n > 1)
  {
    int m = n / 2;
    strings_msort_i(a, m, b);
    strings_msort_i(a+m, n-m, b);
    strings_merge(a, m, a+m, n-m, b);
    strings_copy(b, n, a);
  }
}

// Merge two arrays of strings, lexicographically.
void strings_msort(const char **a, int n)
{
  const char **b = (const char **) strings_new(n);
  strings_msort_i(a, n, b);
}

// Number of initial strings in `a` equal to `x`
int strings_count_while(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) == 0)
    result++;
  return result;
}

// Number of initial strings in `a` NOT equal to `x`
int strings_count_while_not(const char **a, int n, const char *x)
{
  int result = 0;
  while (result < n && strcmp(a[result], x) != 0)
    result++;
  return result;
}

// Compute the length of each maximal subarray of equal elements is `a`.
// Store those values in `b`.
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

// Keep in `b` the first element of each maximal subarray
// of equal elements is `a`.
// Informally: remove consecutive duplicades from `a`, result in `b`.
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

// Splitting a string into lines
int str_lines(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    int z = str_count_while_not(s+i, '\n');
    a[result++] = str_ndup(s+i, z);
    i += z;
    if (s[i]) // if not at the end of strings, skip the current character
      i++;
  }
  return result;
}

// Splitting a string into words. Words are separated by white space.
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

// Count the words in `s`. Words are separated by white space.
// Note: it merely counts. It does not create the list of words.
int str_count_words(const char *s)
{
  int result = 0;
  int i = 0;
  while (s[i])
    if (isspace(s[i]))
      i++;
    else
    {
      int z = str_count_while_not_func(s+i, isspace);
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

// Handling CSV files

char csv_separator = ',';

// Number of bytes in the first field in csv string `s`
int str_count_while_csv(const char *s)
{
  int result = 0;
  if (*s == '"')
  {
    result = 1 + str_count_while_not(s+1, '"');
    if (s[result] == '"')
      result++;
  }
  else
    result = str_count_while_not(s, csv_separator);
  return result;
}

void unit_test_str_count_while_csv(void)
{
  const char *s1 = "01234,abcdefghi,xxx";
  assert(str_count_while_csv(s1) == 5);
  assert(str_count_while_csv(s1+6) == 9);
  assert(str_count_while_csv(s1+6+10) == 3);
  const char *s2 = ",,,,";
  assert(str_count_while_csv(s2) == 0);
  assert(str_count_while_csv(s2+1) == 0);
  assert(str_count_while_csv(s2+2) == 0);
  assert(str_count_while_csv(s2+3) == 0);
  const char *s3 = "\"abcde\",1234567890,";
  assert(str_count_while_csv(s3) == 7);
  assert(str_count_while_csv(s3+8) == 10);
  assert(str_count_while_csv(s3+8+11) == 0);
}

// Split csv string `s` into dynamic array `a`
// Same as strings_from_csv
int str_split_csv(const char *s, const char **a)
{
  int result = 0;
  int i = 0;
  while (s[i])
  {
    int x = str_count_while_csv(s+i);
    a[result++] = str_ndup(s+i, x);
    i += x;
    if (s[i] == csv_separator)
    {
      i++;
      if (s[i] == '\0')
        a[result++] = strdup("");
    }
  }
  return result;
}

void unit_test_str_split(void)
{
  const char *s1 = "01234,abcdefghi,xxx";
  const char *a1[10];
  int n1 = str_split_csv(s1, a1);
  const char *b1[3] = {"01234", "abcdefghi", "xxx"};
  assert(strings_equal(a1, n1, b1, 3));
  const char *s2 = ",,,,";
  const char *a2[10];
  int n2 = str_split_csv(s2, a2);
  const char *b2[5] = {"", "", "", "", ""};
  assert(strings_equal(a2, n2, b2, 5));
  const char *s3 = "\"abcde\",1234567890,";
  const char *a3[10];
  int n3 = str_split_csv(s3, a3);
  const char *b3[3] = {"\"abcde\"","1234567890",""};
  assert(strings_equal(a3, n3, b3, 3));
}

// Split csv string `s` into dynamic array `a`
// Same as str_split_csv
int strings_from_csv(const char *s, const char **a)
{
  return str_split_csv(s, a);
}

// Return a dynamic copy of `s` without the initial quote,
// which must exist, and the final quote, if it exists
const char* str_dup_unquoting(const char *s)
{
  assert(*s == '"');
  int x = (int)strlen(s);
  if (s[x] == '"') x--;
  return str_ndup(s+1, x-2); // two quote chars will be removed.
}

// UTF-8 stuff

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

void unit_test_str_utf8(void)
{
  // See https://unicode-table.com
  char s[8];
  assert(str_equal(str_utf8(s, 65), "A"));
  assert(str_equal(str_utf8(s, 90), "Z"));
  assert(str_equal(str_utf8(s, 97), "a"));
  assert(str_equal(str_utf8(s, 122), "z"));
  
  assert(str_equal(str_utf8(s, 192), "À"));
  assert(str_equal(str_utf8(s, 201), "É"));
  assert(str_equal(str_utf8(s, 223), "ß"));
  assert(str_equal(str_utf8(s, 215), "×"));
  assert(str_equal(str_utf8(s, 247), "÷"));
  assert(str_equal(str_utf8(s, 213), "Õ"));
  
  assert(str_equal(str_utf8(s, 951), "η"));
  assert(str_equal(str_utf8(s, 8364), "€"));
  
  assert(str_equal(str_utf8(s, 128169), "💩"));
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

void unit_test_str_codepoint(void)
{
  // See https://unicode-table.com
  assert(str_codepoint("A") == 65);
  assert(str_codepoint("Z") == 90);
  assert(str_codepoint("a") == 97);
  assert(str_codepoint("z") == 122);
  assert(str_codepoint("À") == 192);
  assert(str_codepoint("ß") == 223);
  
  assert(str_codepoint("×") == 215);
  assert(str_codepoint("÷") == 247);
  
  assert(str_codepoint("Õ") == 213);
  assert(str_codepoint("η") == 951);
  assert(str_codepoint("€") == 8364);
  assert(str_codepoint("💩") == 128169);
  
  assert(str_codepoint("À") == 192);
  assert(str_codepoint("Å") == 197);
  assert(str_codepoint("È") == 200);
  assert(str_codepoint("Ë") == 203);
  assert(str_codepoint("Ì") == 204);
  assert(str_codepoint("Ï") == 207);
  assert(str_codepoint("Ò") == 210);
  assert(str_codepoint("Ø") == 216);
  assert(str_codepoint("Ù") == 217);
  assert(str_codepoint("Ü") == 220);
  
  assert(str_codepoint("Ç") == 199);
  assert(str_codepoint("Ñ") == 209);
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

void unit_test_str_from_html(void)
{
  // See https://unicode-table.com
  char s[32];
  assert(str_equal(str_from_html(s, "A"), "A"));
  assert(str_equal(str_from_html(s, "&#201;"), "É"));
  assert(str_equal(str_from_html(s, "GUIN&#201;"), "GUINÉ"));
  assert(str_equal(str_from_html(s, "&#951;&#8364;&#128169;"), "η€💩"));
  assert(str_equal(str_from_html(s, "Hist&#243;rico"), "Histórico"));
  assert(str_equal(str_from_html(s, "Internacionaliza&#231;&#245;es"),
                                    "Internacionalizações"));
  assert(str_equal(str_from_html(s,
                "Clube na &#250;ltima convocat&#243;ria"),
                "Clube na última convocatória"));
}

void our_strings_unit_tests(void)
{
  unit_test_str_ncpy();
  unit_test_str_equal();
  unit_test_str_len();
  unit_test_str_find();
  unit_test_str_find_last();
  unit_test_count_words();
  unit_test_str_count_while_csv();
  unit_test_str_split();
  unit_test_str_utf8();
  unit_test_str_codepoint();
  unit_test_str_from_html();
}
