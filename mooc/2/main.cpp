#include <stdio.h>
#define R  5.3
#define PI 3.14159
int main()
{
  printf("Area=%.5f\n"
         "circumference=%.5f\n",
         1.0 / 2.0 * PI * R * R, R * PI);
  return 0;
}
