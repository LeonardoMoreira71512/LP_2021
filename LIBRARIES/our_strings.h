//
//  our_strings.h
//
//  Created by Pedro Guerreiro on 10/12/2018.
//  Copyright © 2018 Pedro Guerreiro. All rights reserved.
//

#ifndef our_strings_h
#define our_strings_h

extern int max_line_length;
extern char csv_separator;

char* str_cpy(char *r, const char *s);
char* str_ncpy(char *r, const char *s, int x);
int str_equal(const char *s, const char *t);
int str_len(const char *s);
int str_find(const char *s, char x);
int str_find_last(const char *s, char x);

char *str_tolower(char *r, const char *s);
char *str_toupper(char *r, const char *s);

const char *str_dup(const char *s);
const char *str_ndup(const char *s, int n);

int str_count_while(const char *s, char x);
int str_count_while_not(const char *s, char x);
int str_count_while_func(const char *s, int f(int));
int str_count_while_not_func(const char *s, int f(int));

int str_readline(FILE *f, char *s);
int str_getline(char *s);
char *str_from_file(char *r, FILE *f);

const char **strings_new(int n);
int strings_copy(const char **a, int n, const char **b);

int strings_read(FILE *f, const char **a);
int strings_get(const char **a);
int strings_readwords(FILE *f, const char **a);
int strings_getwords(const char **a);

void strings_fprint_basic(FILE *f, const char **a, int n);
void strings_print_basic(const char **a, int n);
void strings_fprint(FILE *f, const char **a, int n, const char *separator);
void strings_fprintln(FILE *f, const char **a, int n, const char *separator);
void strings_print(const char **a, int n, const char *separator);
void strings_println(const char **a, int n, const char *separator);
void strings_fprintf(FILE *f, const char **a, int n, const char *fmt);
void strings_fprintfln(FILE *f, const char **a, int n, const char *fmt);
void strings_printf(const char **a, int n, const char *fmt);
void strings_printfln(const char **a, int n, const char *fmt);

int strings_find(const char **a, int n, const char *x);
int strings_count(const char **a, int n, const char *x);
int strings_equal(const char **a, const int n, const char **b, int m);
int strings_rank(const char **a, int n, const char *x);
int strings_bfind(const char **a, int n, const char *x);

void strings_exchange(const char **a, int x, int y);
void strings_sort_last(const char **a, int n);
void strings_isort(const char **a, int n);
void strings_isort_gen(const char **a, int n, int cmp(const char *, const char *));

int strings_merge(const char **a, int n, const char **b, int m, const char **c);
void strings_msort(const char **a, int n);

int strings_count_while(const char **a, int n, const char *x);
int strings_count_while_not(const char **a, int n, const char *x);
int strings_groups(const char **a, int n, int *b);
int strings_unique(const char **a, int n, const char **b);

int str_lines(const char *s, const char **a);
int str_words(const char *s, const char **a);
int str_count_words(const char *s);

int str_count_while_csv(const char *s);
int str_split_csv(const char *s, const char **a);
int strings_from_csv(const char *s, const char **a);
const char* str_dup_unquoting(const char *s);

char *str_utf8(char *r, int x);
int str_codepoint(const char* s);
char *str_from_html(char *r, const char *s);

void unit_test_str_ncpy(void);
void unit_test_str_equal(void);
void unit_test_str_len(void);
void unit_test_str_find(void);
void unit_test_str_find_last(void);
void unit_test_count_words(void);

void unit_test_str_count_while_csv(void);
void unit_test_str_split(void);

void unit_test_str_utf8(void);
void unit_test_str_codepoint(void);
void unit_test_str_from_html(void);

void our_strings_unit_tests(void);

#endif
