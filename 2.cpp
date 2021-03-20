#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <vector>
#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

bool fn(std::vector<std::vector<short>>& edges, std::vector<bool>& taken,
        short index) {
  for (auto& edge : edges[index]) {
    if (taken[edge] && !fn(edges, taken, edge)) {
      continue;
    }
    taken[edge] = true;
    return true;
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  short n;
  std::cin >> n;

  std::vector<std::vector<short>> board(n, std::vector<short>(n));
  std::vector<std::vector<std::vector<std::tuple<short, short>>>> edges(
      n, std::vector<std::vector<std::tuple<short, short>>>(n));

  for (auto i = 0; i < n; i++) {
    for (auto j = 0; j < n; j++) {
      std::cin >> board[i][j];
    }
  }

  for (auto i = 0; i < n; i++) {
    for (auto j = 0; j < n; j++) {
      if (board[i][j] == 0) {
        continue;
      }
      if (board[i][j] == 1) {
        edges[i][j].push_back(std::make_tuple(i - 1, j + 2));
        edges[i][j].push_back(std::make_tuple(i, j + 3));
        edges[i][j].push_back(std::make_tuple(i + 1, j + 2));
        continue;
      }
      if (board[i][j] == 2) {
        edges[i][j].push_back(std::make_tuple(i - 1, j));
        edges[i][j].push_back(std::make_tuple(i, j + 1));
        edges[i][j].push_back(std::make_tuple(i + 1, j));
      }
      edges[i][j].push_back(std::make_tuple(i - 1, j + 2));
      edges[i][j].push_back(std::make_tuple(i, j + 1));
      edges[i][j].push_back(std::make_tuple(i + 1, j + 2));
    }
  }

  //   std::cout <<n*n - r;
  //   std::cout << 19;
}