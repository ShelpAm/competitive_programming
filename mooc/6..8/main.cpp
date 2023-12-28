#include <stdio.h>

int main()
{
  int n;

  printf("Input n(27<n<=77):\n");
  scanf("%d", &n);

  for (int men = 0; men <= n / 4; ++men) {
    for (int women = 0; women <= n / 3; ++women) {
      int children = (n - men * 4 - women * 3) * 2;

      // 判断是否满足条件
      if (children >= 0 && men + women + children == 36) {
        printf("men=%d,women=%d,children=%d\n", men, women, children);
      }
    }
  }

  return 0;
}
// ShelpAm
