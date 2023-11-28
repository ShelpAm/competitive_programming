#include <stdio.h>
int is_prime(long long n)
{
  if (n < 2) {
    return 0;
  }
  for (long long i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}
int main()
{
  printf("Input n:");
  int n;
  scanf("%d", &n);
  long sum = 0;
  for (long long i = 0; i <= n; ++i) {
    if (is_prime(i)) {
      sum += i;
    }
  }
  printf("sum=%d\n", sum);
  return 0;
}
