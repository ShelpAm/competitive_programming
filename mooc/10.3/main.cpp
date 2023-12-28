//
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
//   char first[200], second[200], *result;
//   printf("Input the first string:\n");
//   fgets(first, 100, stdin);
//   printf("Input the second string:\n");
//   fgets(second, 100, stdin);
//   first[strlen(first) - 1] = '\0';
//   second[strlen(second) - 1] = '\0';
//   result = strcat(first, second);
//   printf("The result is : %s\n", result);
//   return 0;
// }
#include <stdio.h>
#include <string.h>

#define STR_LEN 80

char* MyStrcat(char* dest, char* source);

int main(void)
{
  char first[STR_LEN + 1], second[STR_LEN + 1], *result;
  printf("Input the first string:\n");
  gets(first);
  printf("Input the second string:\n");
  gets(second);
  result = MyStrcat(second, first);
  printf("The result is : %s\n", result);
  return 0;
}

char* MyStrcat(char* dest, char* source)
{
  int i = 0;
  while (*(dest + i) != '\0')
    i++;
  for (; *dest != '\0'; i++) {
    *(source + i) = *dest++;
  }
  *(source + i) = '\0';
  return source;
}
