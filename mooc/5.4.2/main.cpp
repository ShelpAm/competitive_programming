#include <math.h>
#include <stdio.h>
int main()
{
  long long m;
  scanf("%ld", &m);
  long long b = 0;
  if (m <= 100000) {
    b = m * 0.1;
  }
  else if (m <= 200000) {
    b = m * 0.075 + 2500;
  }
  else if (m <= 400000) {
    b = m * 0.05 + 7500;
  }
  else if (m <= 600000) {
    b = m * 0.03 + 15500;
  }
  else if (m <= 1000000) {
    b = m * 0.015 + 33500;
    b -= 9000;
  }
  else {
    b = m * 0.01 + 29500;
  }
  printf("bonus=%ld\n", b);
  return 0;
}
