#include <stdio.h>

// 计算n的阶乘
long Fact(int n)
{
  if (n == 0 || n == 1) {
    return 1;
  }
  else {
    return n * Fact(n - 1);
  }
}

int main()
{
  printf("三位阶乘和数:\n");

  // 遍历所有三位数
  for (int m = 100; m <= 999; ++m) {
    // 提取百位、十位和个位数字
    int a = m / 100;
    int b = (m % 100) / 10;
    int c = m % 10;

    // 计算阶乘和
    long sum = Fact(a) + Fact(b) + Fact(c);

    // 判断是否为三位阶乘和数
    if (m == sum) {
      // 输出结果
      printf("%d\n", m);
    }
  }

  return 0;
}
// ShelpAm
