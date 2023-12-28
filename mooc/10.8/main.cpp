#include <ctype.h>
#include <stdio.h>
#include <string.h>
char back(char const* const s)
{
  return s[strlen(s) - 1];
}
char* pback(char* const s)
{
  return s + strlen(s) - 1;
}
int main()
{
  printf("Input a sentence:");
  size_t k = 0;
  char strings[100][50];
  int is_last_word = 0;
  char sign;
  while (!is_last_word) {
    scanf("%s", strings[k++]);
    if (!isalnum(back(strings[k - 1]))) {
      sign = back(strings[k - 1]);
      *pback(strings[k - 1]) = '\0';
      is_last_word = 1;
    }
  }
  for (size_t i = k - 1; i != -1; --i) {
    printf("%s ", strings[i]);
  }
  printf("\b%c\n", sign);
}
