#include <stdio.h>
int is_pallindrome(char const* const s)
{
  size_t i = 0, j = strlen(s) - 1;
  while (i < j) {
    if (s[i] != s[j]) {
      return 0;
    }
    ++i;
    --j;
  }
  return 1;
}
int main()
{
  printf("Input string:");
  char buf[1000];
  gets(buf);
  if (is_pallindrome(buf)) {
    printf("Yes!\n");
  }
  else {
    printf("No!\n");
  }
  return 0;
}
