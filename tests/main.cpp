#include <bits/stdc++.h>
using namespace std;
int rand(int a, int b)
{
  srand(time(nullptr));
  return rand() % b + a;
}
int main()
{
  cout << rand(100, 200) << ' ' << rand(200, 300) << ' ' << rand(10, 500)
       << '\n';
}
