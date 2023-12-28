#include <math.h>
#include <stdio.h>

double Y(double x, int n)
{
  if (n == 0) {
    return 0.0;
  }
  return sqrt(x + Y(x, n - 1));
}

int main()
{
  double x;
  int n;

  printf("Please input x and n:");
  scanf("%lf,%d", &x, &n);

  if (n < 0) {
    printf("Result=0.00\n");
  }
  else {
    double result = Y(x, n);
    printf("Result=%.2f\n", result);
  }

  return 0;
}
// ShelpAm