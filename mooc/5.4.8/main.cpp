#include <math.h>
#include <stdio.h>
int main()
{
  printf("Input days:\n");
  int days;
  scanf("%d", &days);
  printf("x=%d\n", 3 * (1 << (days - 1)) - 2);
  return 0;
}
