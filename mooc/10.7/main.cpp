#include <stdio.h>
#include <string.h>
int main()
{
  printf("Input n (n<=10):\n");
  int n;
  scanf("%d", &n);

  int a[n + 1];
  memset(a, 0, sizeof(a));
  a[1] = 1;
  for (size_t i = 1; i != n + 1; ++i) {
    for (size_t j = i; j != 1; --j) {
      a[j] = a[j] + a[j - 1];
    }
    for (size_t j = 1; j != i + 1; ++j) {
      printf("%4d", a[j]);
    }
    printf("\n");
  }
}
