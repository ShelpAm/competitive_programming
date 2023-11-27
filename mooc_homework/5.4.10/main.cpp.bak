#include <ctype.h>
#include <math.h>
#include <stdio.h>
int main()
{
  size_t cnt = 0;
  char c;
  printf("Input your password:\n");
  int first = 1;
  while (1) {
    if (first) {
      scanf("%c", &c);
      first = 0;
    }
    else {
      scanf("\n%c", &c);
    }
    if (isdigit(c)) {
      ++cnt;
      printf("%c, you have enter %d-bits number\n", c, cnt);
    }
    else {
      printf("error\n");
    }
    if (cnt == 6) {
      return 0;
    }
  }
}
