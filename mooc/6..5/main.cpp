#include <stdio.h>

// 输入指定范围内的整数函数
int getint(int min, int max)
{
  int num;

  // 提示输入区间
  printf("Please enter min,max:\n");
  scanf("%d,%d", &min, &max);

  // 循环获取合法输入
  do {
    // 提示输入整数
    printf("Please enter an integer [%d..%d]:\n", min, max);
    scanf("%d", &num);

    // 判断是否在指定范围内
    if (num < min || num > max) {
      printf("Invalid input. ");
    }
  }
  while (num < min || num > max);

  // 返回合法输入的整数
  return num;
}

int main()
{
  int min, max;

  // 调用getint函数获取指定范围内的整数
  int result = getint(min, max);

  // 输出结果
  printf("The integer you have entered is:%d\n", result);

  return 0;
}
// ShelpAm
