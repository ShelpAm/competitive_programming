#include <stdio.h>

int main()
{
  int n;

  printf("Input n(1<n<=5):\n");
  scanf("%d", &n);

  if (n <= 1 || n > 5) {
    printf("Error!\n");
  }
  else {
    int t = n - 1;

    for (int i = 0; i != n; ++i) {
      printf("Current num: %d\n", t);
      if (t % (n - 1) != 0) {
        t *= n - 1;
      }
      t = t * n / (n - 1) + 1;
    }

    printf("y=%d\n", t);
  }

  return 0;
}
