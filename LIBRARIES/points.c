//
//  main.c
//  points
//
//  Created by Pedro Guerreiro on 13/03/2021.
//

#pragma GCC diagnostic error "-Wall"
#pragma GCC diagnostic error "-Wextra"
#pragma GCC diagnostic error "-Wconversion"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#include "our_ints.h"
#include "our_doubles.h"

char *author = "Pedro Guerreiro";

char *message[2] = {"NO", "YES"};
char *message_face[2] = {"☹️", "🙂"};

typedef struct {
  double x;
  double y;
} Point;

Point point(double x, double y)
{
  Point result = {x, y};
  return result;
}

int point_eq(Point p, Point q)
{
  return p.x == q.x && p.y == q.y;
}

void point_print(Point p)
{
  printf("<%g %g>", p.x, p.y);
}

void point_println(Point p)
{
  point_print(p);
  printf("\n");
}

// Are the two arrays equal?
int points_eq(const Point *a, int n, const Point *b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (point_eq(a[i], b[i]))
      i++;
    else
      result = 0;
  return result;
}

int points_read(FILE *f, Point *a)
{
  int result = 0;
  double x, y;
  while (fscanf(f, "%lf%lf", &x, &y) != EOF)
    a[result++] = point(x, y);
  return result;
}

void points_fprintf(FILE *f, const Point *a, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    fprintf(f, fmt, a[i].x, a[i].y);
}

void points_fprintfln(FILE *f, const Point *a, int n, const char *fmt)
{
  points_fprintf(f, a, n, fmt);
  fprintf(f, "\n");
}


//Euclidean distance
double distance(Point p, Point q)
{
//  return sqrt((p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y));
  return sqrt(dbl_square(p.x-q.x) + dbl_square(p.y-q.y));
}

void unit_test_distance(void)
{
  Point p1 = point(2.0, 4.0);
  Point p2 = point(5.0, 8.0);
  assert(distance(p1, p2) == 5.0);
  Point p3 = point(0,0);
  Point p4 = point(1,1);
  assert(distance(p3, p4) == sqrt(2.0));
  assert(distance(p1, p3) == sqrt(20.0));
  assert(distance(p1, p1) == 0.0);
  assert(distance(p2, p4) == sqrt(65.0));
  Point p5 = point(1.5, 2.0);
  Point p6 = point(2.25, 3.0);
  assert(distance(p5, p6) == 1.25);
}

//Manhattan distance
double distance_manhattan(Point p, Point q)
{
  return fabs(p.x-q.x) + fabs(p.y-q.y);
}

void unit_test_distance_manhattan(void)
{
  Point p1 = point(2.0, 4.0);
  Point p2 = point(5.0, 8.0);
  assert(distance_manhattan(p1, p2) == 7.0);
  Point p3 = point(0,0);
  Point p4 = point(1,1);
  assert(distance_manhattan(p3, p4) == 2.0);
  assert(distance_manhattan(p1, p3) == 6.0);
  assert(distance_manhattan(p1, p1) == 0.0);
  assert(distance_manhattan(p2, p4) == 11.0);
  Point p5 = point(1.5, 2.0);
  Point p6 = point(2.25, 3.0);
  assert(distance_manhattan(p5, p6) == 1.75);
}

//q.y - p.y    r.y - q.y
//--------- == ---------
//q.x - p.x    r.x - q.x

int collinear(Point p, Point q, Point r)
{
//  return (q.x-p.x)*(r.y-p.y) == (r.x-p.x)*(q.y-p.y);
  return (q.y-p.y) * (r.x-q.x) == (q.x-p.x) * (r.y-q.y);
}

void unit_test_collinear(void)
{
  Point p1 = point(2.0, 4.0);
  Point p2 = point(5.0, 8.0);
  Point p3 = point(8.0, 12.0);
  assert(collinear(p1, p2, p3));
  Point p4 = point(0.0, 0.0);
  Point p5 = point(1.0, 1.0);
  Point p6 = point(4.0, 4.0);
  assert(collinear(p4, p5, p6));
  Point p7 = point(1000.0, 4.0);
  assert(collinear(p1, p6, p7));
  assert(!collinear(p4, p1, p2));
}

void test_points(void)
{
  double x1, y1, x2, y2, x3, y3;
  while (scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3) != EOF)
  {
    Point p1 = point(x1, y1);
    Point p2 = point(x2, y2);
    Point p3 = point(x3, y3);
    point_println(p1);
    point_println(p2);
    point_println(p3);
    double d12 = distance(p1, p2);
    double d23 = distance(p2, p3);
    double d31 = distance(p3, p1);
    double dm12 = distance_manhattan(p1, p2);
    double dm23 = distance_manhattan(p2, p3);
    double dm31 = distance_manhattan(p3, p1);
    int c = collinear(p1, p2, p3);
    printf("%f %f %f\n", d12, d23, d31);
    printf("%f %f %f\n", dm12, dm23, dm31);
    printf("%d\n", c);
  }
}

void points_exchange(Point *a, int x, int y)
{
  Point m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void points_isort_by_x(Point *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1].x > a[j].x)
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_isort_by_x(void)
{
  Point a1[10] = {{5,1},{3,5},{2,2},{7,7},{9,5},{3,1},{8,5},{5,2},{1,4},{7,6}};
  points_isort_by_x(a1, 10);
  Point b1[10] = {{1,4},{2,2},{3,5},{3,1},{5,1},{5,2},{7,7},{7,6},{8,5},{9,5}};
  assert(points_eq(a1, 10, b1, 10));
  
  Point a2[6] = {{5,7},{3,9},{2,2},{9,1},{7,3},{4,4}};
  points_isort_by_x(a2, 6);
  Point b2[6] = {{2,2},{3,9},{4,4},{5,7},{7,3},{9,1}};
  assert(points_eq(a2, 6, b2, 6));
  
  Point a3[6] = {{8,3},{4,3},{5,3},{9,3},{7,3},{1,3}};
  points_isort_by_x(a3, 6);
  Point b3[6] = {{1,3},{4,3},{5,3},{7,3},{8,3},{9,3}};
  assert(points_eq(a3, 6, b3, 6));
  
  Point a4[6] = {{5,6},{5,2},{5,1},{5,8},{5,3},{5,7}};
  points_isort_by_x(a4, 6);
  Point b4[6] = {{5,6},{5,2},{5,1},{5,8},{5,3},{5,7}};
  assert(points_eq(a4, 6, b4, 6));
}

void points_isort_by_y(Point *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1].y > a[j].y)
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_isort_by_y(void)
{
  Point a1[10] = {{5,1},{3,5},{2,2},{7,7},{9,5},{3,1},{8,5},{5,2},{1,4},{7,6}};
  points_isort_by_y(a1, 10);
  Point b1[10] = {{5,1},{3,1},{2,2},{5,2},{1,4},{3,5},{9,5},{8,5},{7,6},{7,7}};
  assert(points_eq(a1, 10, b1, 10));
  
  Point a2[6] = {{5,7},{3,9},{2,2},{9,1},{7,3},{4,4}};
  points_isort_by_y(a2, 6);
  Point b2[6] = {{9,1},{2,2},{7,3},{4,4},{5,7},{3,9}};
  assert(points_eq(a2, 6, b2, 6));
  
  Point a3[6] = {{8,3},{4,3},{5,3},{9,3},{7,3},{1,3}};
  points_isort_by_y(a3, 6);
  Point b3[6] = {{8,3},{4,3},{5,3},{9,3},{7,3},{1,3}};
  assert(points_eq(a3, 6, b3, 6));
  
  Point a4[6] = {{5,6},{5,2},{5,1},{5,8},{5,3},{5,7}};
  points_isort_by_y(a4, 6);
  Point b4[6] = {{5,1},{5,2},{5,3},{5,6},{5,7},{5,8}};
  assert(points_eq(a4, 6, b4, 6));
}

void test_points_isort_by_x(void)
{
  Point a[1000];
  int n = points_read(stdin, a);
  points_fprintfln(stdout, a, n, "<%g %g>");
  points_isort_by_x(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
}

void test_points_isort_by_y(void)
{
  Point a[1000];
  int n = points_read(stdin, a);
  points_fprintfln(stdout, a, n, "<%g %g>");
  points_isort_by_y(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
}

// For demonstration only. It does not work.
void points_isort_by_x_then_by_y_demo(Point *a, int n)
{
  points_isort_by_x(a, n);
  points_isort_by_y(a, n);
}

// For demonstration only. It fixes the function above.
void points_isort_by_x_then_by_y(Point *a, int n)
{
  points_isort_by_y(a, n);
  points_isort_by_x(a, n);
}

void test_points_isort_by_x_then_by_y(void)
{
  Point a[1000];
  int n = points_read(stdin, a);
  points_fprintfln(stdout, a, n, "<%g %g>");
  points_isort_by_x_then_by_y(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
}

void test_points_isort_by_x_then_points_isort_by_y(void)
{
  Point a[1000];
  int n = points_read(stdin, a);
  points_fprintfln(stdout, a, n, "<%g %g>");
  points_isort_by_x(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
  points_isort_by_y(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
}

int point_gt(Point p, Point q)
{
  return p.x > q.x || (p.x == q.x && p.y > q.y);
}

int point_le(Point p, Point q)
{
  return p.x < q.x || (p.x == q.x && p.y <= q.y);
}

// For reference: version using `point_gt`
void points_isort1(Point *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && point_gt(a[j-1], a[j]))
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

// For reference: version using `!point_le`
void points_isort2(Point *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && !point_le(a[j-1], a[j]))
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

double point_cmp(Point p, Point q)
{
  double result = p.x - q.x;
  if (result == 0)
    result = p.y - q.y;
  return result;
}

// Standard version, using `point_cmp`
void points_isort(Point *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && point_cmp(a[j-1], a[j]) > 0)
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

void unit_test_isort(void)
{
  Point a1[10] = {{5,1},{3,5},{2,2},{7,7},{9,5},{3,1},{8,5},{5,2},{1,4},{7,6}};
  points_isort(a1, 10);
  Point b1[10] = {{1,4},{2,2},{3,1},{3,5},{5,1},{5,2},{7,6},{7,7},{8,5},{9,5}};
  assert(points_eq(a1, 10, b1, 10));
  
  Point a2[6] = {{5,7},{3,9},{2,2},{9,1},{7,3},{4,4}};
  points_isort(a2, 6);
  Point b2[6] = {{2,2},{3,9},{4,4},{5,7},{7,3},{9,1}};
  assert(points_eq(a2, 6, b2, 6));
  
  Point a3[6] = {{8,3},{4,3},{5,3},{9,3},{7,3},{1,3}};
  points_isort(a3, 6);
  Point b3[6] = {{1,3},{4,3},{5,3},{7,3},{8,3},{9,3}};
  assert(points_eq(a3, 6, b3, 6));
  
  Point a4[6] = {{5,6},{5,2},{5,1},{5,8},{5,3},{5,7}};
  points_isort(a4, 6);
  Point b4[6] = {{5,1},{5,2},{5,3},{5,6},{5,7},{5,8}};
  assert(points_eq(a4, 6, b4, 6));
}

void test_points_isort(void)
{
  Point a[1000];
  int n = points_read(stdin, a);
  points_fprintfln(stdout, a, n, "<%g %g>");
  points_isort(a, n);
  points_fprintfln(stdout, a, n, "[%g,%g]");
}


void points_isort_gen(Point *a, int n, int cmp(Point, Point))
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && cmp(a[j-1], a[j]) > 0)
    {
      points_exchange(a, j-1, j);
      j--;
    }
  }
}

double angle(Point p)
{
  double result = atan2(p.y, p.x);
  if (result < 0)
    result += 2*M_PI;
  return result;
}

void unit_test_angle(void)
{
  assert(angle(point(1, 0)) == 0);
  assert(angle(point(1, 1)) == M_PI_4);
  assert(angle(point(0, 1)) == M_PI_2);
  assert(angle(point(-1, 1)) == M_PI_2 + M_PI_4);
  assert(angle(point(-1, 0)) == M_PI);
  assert(angle(point(-1, -1)) == M_PI + M_PI_4);
  assert(angle(point(0, -1)) == M_PI + M_PI_2);
  assert(angle(point(1, -1)) == M_PI + M_PI_2 + M_PI_4);
}

double magnitude(Point p)
{
  return sqrt(p.x*p.x + p.y*p.y);
}

void unit_test_magnitude(void)
{
  assert(magnitude(point(0, 0)) == 0.0);
  assert(magnitude(point(0, 2)) == 2.0);
  assert(magnitude(point(-7, 0)) == 7.0);
  assert(magnitude(point(1, 1)) == sqrt(2.0));
  assert(magnitude(point(3, 4)) == 5);
  assert(magnitude(point(12, 5)) == 13);
  assert(magnitude(point(12, -5)) == 13);
  assert(magnitude(point(-12, 5)) == 13);
  assert(magnitude(point(-12, -5)) == 13);
}

void unit_tests(void)
{
  unit_test_distance();
  unit_test_collinear();
  unit_test_angle();
  unit_test_magnitude();

  unit_test_isort_by_x();
  unit_test_isort_by_y();
  unit_test_isort();
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
    test_points_isort_by_x();
  else if (x == 'B')
    test_points_isort_by_y();
  else if (x == 'C')
    test_points_isort_by_x_then_by_y();
  else if (x == 'D')
    test_points_isort_by_x_then_points_isort_by_y();
  else if (x == 'E')
    test_points_isort();
  
  else if (x == 'U')
    printf("All unit tests PASSED\n");
  else
    printf("%s: Invalid option.\n", argv[1]);
  return 0;
}