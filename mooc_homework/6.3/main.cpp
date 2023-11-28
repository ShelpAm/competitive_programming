#include <stdio.h>
int gcd(int const x, int const y)
{
  return y == 0 ? x : gcd(y, x % y);
}
int main()
{
  printf("Input m,n:");
  int m, n;
  scanf("%d,%d", &m, &n);
  if (m <= 0 || n <= 0) {
    printf("Input error!");
    return 0;
  }
  int g = gcd(m, n);
  printf("%d/%d", m / g, n / g);
  return 0;
}
