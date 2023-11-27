#include <math.h>
#include <stdio.h>
int main()
{
  printf("Please enter rate, year, capital:\n");
  double rate, year, capital;
  scanf("%lf, %lf,%lf", &rate, &year, &capital);
  printf("deposit=%.3lf\n", capital * pow(1 + rate, year));
}
