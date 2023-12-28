#include <stdio.h>
#define ARR_SIZE 5
void YH(int a[][ARR_SIZE], int n);
void PrintYH(int a[][ARR_SIZE], int n);
int main(void)
{
  int a[ARR_SIZE][ARR_SIZE];
  YH(a, ARR_SIZE);
  PrintYH(a, ARR_SIZE);
  return 0;
}
void YH(int a[][ARR_SIZE], int n)
{
  int i, j;
  for (i = 1; i < n; i++) {
    a[i][1] = 1;
    a[i][i] = 1;
  }
  for (i = 3; i <= n; i++) {
    for (j = 2; j <= i - 1; j++) {
      a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
    }
  }
}
void PrintYH(int a[][ARR_SIZE], int n)
{
  int i, j;
  for (i = 1; i < n; i++) {
    for (j = 1; j <= i; j++) {
      printf("%4d", a[i][j]);
    }
    printf("\n");
  }
}
