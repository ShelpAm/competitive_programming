#include <stdio.h>
int shown_up[10001];
int main()
{
  int n;
  scanf("%d", &n);
  int a[n];
  for (size_t i = 0; i != n; ++i) {
    scanf("%d", &a[i]);
    shown_up[a[i]] = true;
  }
  int num = 0;
  for (size_t i = 0; i != n; ++i) {
    for (size_t j = i + 1; j != n; ++j) {
      if (shown_up[a[i] + a[j]]) {
        ++num;
      }
    }
  }
  printf("%d", num);
  return 0;
}
