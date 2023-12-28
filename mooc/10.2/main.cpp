#include <stdio.h>
struct student_t {};
void show_menu()
{
  printf("Management for Students' scores\n"
         "1.Input record\n"
         "2.Caculate total and average score of course\n"
         "3.Sort in descending order by score\n"
         "4.Sort in ascending order by number\n"
         "5.Search by number\n"
         "6.Statistic analysis\n"
         "7.List record\n"
         "0.Exit\n"
         "Please Input your choice:\n");
}
int main()
{
  printf("Input students number(n<30):");
  int n;
  scanf("%d", &n);
  int should_leave = 0;
  while (!should_leave) {
    show_menu();
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
    }
    printf("Your selection: %d\n", opt);
  }
}
