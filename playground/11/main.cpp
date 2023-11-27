#include <stdio.h>
#define bool int
int main()
{
  int x1, x2;
  do {
    x1 = 0, x2 = 0;
    bool flag = 1;
    bool flag1 = 1, flag2 = 1;
    bool f1 = 0, f2 = 0;
    char x;
    printf("Input x1, x2:");

    scanf("%c", &x);

    if (x == '-' || (x >= 48 && x <= 57)) {
      if (x == '-')
        f1 = 1;
      else
        x1 = x1 * 10 + x - 48;

      while (1) {
        scanf("%c", &x);
        if (x == ',')
          break;
        else if (x >= 48 and x <= 57)
          x1 = x1 * 10 + x - 48;
        else
          flag = 0;
      }

      scanf("%c", &x);

      if (x == '-' || (x >= 48 && x <= 57)) {
        if (x == '-')
          f2 = 1;
        else
          x2 = x2 * 10 + x - 48;
        while (1) {
          scanf("%c", &x);
          if (x == '\n') {
            break;
          }
          else if (x >= 48 and x <= 57)
            x2 = x2 * 10 + x - 48;
          else
            flag = 0;
        }
      }
      else {
        flag = 0;
        while (x != '\n')
          scanf("%c", &x);
      }
    }
    else {
      flag = 0;
      while (x != '\n')
        scanf("%c", &x);
    }

    if (flag) {
      if (f1)
        x1 = -x1;
      if (f2)
        x2 = -x2;
    }

    //		printf("%d %d\n",x1,x2);
  }
  while (x1 * x2 >= 0);

  printf("x1=%d,x2=%d\n", x1, x2);
  return 0;
}
