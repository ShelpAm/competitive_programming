#include <stdio.h>
#include <stdlib.h>
int main()
{
  printf("Input x:\n");
  int x = 0;
  scanf("%d", &x);
  x = abs(x);
  printf("y=");
  while (x != 0) {
    int i = x % 10;
    if (i != 0) {
      printf("%d", x % 10);
    }
    x /= 10;
  }
  printf("\n");
  return 0;
}
