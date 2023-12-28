#include <stdio.h>
int main()
{
  int x1, x2;
  int r;
  do {
    printf("Input x1, x2:\n");
    r = scanf("%d,%d", &x1, &x2);
    if (r == 2) {
      if (x1 * x2 < 0) {
        break;
      }
    }
    while (getchar() != '\n') {
    }
  }
  while (1);
  printf("x1=%d,x2=%d\n", x1, x2);
  return 0;
}
