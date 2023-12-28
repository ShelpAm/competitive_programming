#include <math.h>
#include <stdio.h>
int main()
{
  int days;
  printf("Input days:\n");
  while (1) {
    if (scanf("%d", &days) == 1) {
      if (days > 0) {
        break;
      }
    }
    printf("Input days:\n");
    while (getchar() != '\n') {
    }
  }
  printf("x=%d\n", 3 * (1 << (days - 1)) - 2);
  return 0;
}
