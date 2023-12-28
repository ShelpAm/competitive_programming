#include <stdio.h>
int is_prime(int n)
{
  if (n <= 1) {
    return 0;
  }
  for (size_t i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}
int main()
{
  printf("Input n(n<=500):");
  int n;
  scanf("%d", &n);
  int sum = 0;
  int num = 0;
  for (size_t i = n; i > 1; --i) {
    if (is_prime(i)) {
      sum += i;
      ++num;
      printf("%6d", i);
      if (num == 10) {
        break;
      }
    }
  }
  printf("\nsum=%d\n", sum);
}
