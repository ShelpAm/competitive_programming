#include <stdio.h>
int main()
{
  printf("Please enter the number:\n");
  int even = 0;
  int odd = 0;
  int first = 1;
  while (1) {
    int i;
    scanf("%d", &i);
    if (i == -1) {
      if (first) {
        printf("over!\n");
      }
      break;
    }
    first = 0;
    if (i % 2 == 0) {
      printf("%d:even\n", i);
      ++even;
    }
    else {
      printf("%d:odd\n", i);
      ++odd;
    }
  }
  printf("The total number of odd is %d\n", odd);
  printf("The total number of even is %d\n", even);
  return 0;
}
