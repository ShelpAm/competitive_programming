#include <stdio.h>
int main()
{
  printf("Input 10 numbers:\n");
  int a[10];
  for (size_t i = 0; i != 10; ++i) {
    scanf("%d", &a[i]);
  }

  int maxn = 0, minn = 0;
  for (int i = 0; i != 10; ++i) {
    if (a[maxn] < a[i]) {
      maxn = i;
    }
    else if (a[minn] > a[i]) {
      minn = i;
    }
  }
  printf("Max=%d,Position=%d,Min=%d,Position=%d\n", a[maxn], maxn, a[minn], minn);
}
