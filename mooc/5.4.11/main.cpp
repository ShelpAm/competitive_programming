#include <stdio.h>
int main()
{
  printf("Please enter the number:\n");
  int i;
  scanf("%d", &i);
  int j = i;
  int cnt = 0;
  while (i) {
    i /= 10;
    ++cnt;
  }
  printf("%d: %d bits\n", j, cnt);
  return 0;
}
