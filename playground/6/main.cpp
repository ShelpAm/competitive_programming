#include <cstdio>
#include <iostream>

#define row 5
#define col 5

char board[row][col];

void init_board(char board[][col])
{
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (i <= 2)
        board[i][j] = '*';
      else if (i == 4 && j > 0 && j < 4)
        board[i][j] = '#';
      else
        board[i][j] = ' ';
    }
  }
}
void print(char board[][col])
{
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < col; j++) {
      if (j < col - 1) {
        printf(" %c |", board[i][j]);
      }
      else {
        printf(" %c ", board[i][j]);
      }
    }
    printf("\n");
    for (int m = 0; m < col; m++) {
      if (m < col - 1)
        printf("---|");
      else
        printf("---");
    }
    printf("\n");
  }
}
long long distance(long long i, long long j, long long x, long long y)
{
  return abs(i - x) + abs(j - y);
}
void process_input()
{
  std::cout << "Please enter your pos(x, y) and target(x, y):\n";
  std::size_t i, j, x, y;
  std::cin >> i >> j >> x >> y;
  auto d{distance(i, j, x, y)};
  if (d > 2 || d == 0) {
    std::cout << "Error input\n";
    return;
  }
  if (d == 1) {
    if (board[x][y] != '*' && board[x][y] != ' ') {
      std::cout << "Cannot move to " << x << ", " << y << ". Target invalid.";
      return;
    }
  }
  if (d == 2) {
    if (x == i) {
      if (board[x][(y + j) / 2] != ' ') {
        std::cout << "Cannot move to " << x << ", " << y << ", blocked.\n";
        return;
      }
    }
    else if (y == i) {
      if (board[(x + i) / 2][y / 2] != ' ') {
        std::cout << "Cannot move to " << x << ", " << y << ", blocked.\n";
        return;
      }
    }
    else {
      std::cout << "Cannot move diagonally.\n";
    }
  }
  board[x][y] = '#';
  board[i][j] = ' ';
}
void game()
{
  init_board(board);
  bool should_close{false};
  while (!should_close) {
    print(board);
    process_input();
  }
}
