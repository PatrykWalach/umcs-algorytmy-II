#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <sstream>
#include <string>

#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N;
  std::cin >> N;
  std::vector<std::tuple<int, int>> points;

  for (auto i = 0; i < N; i++) {
    int x, y;
    std::cin >> x >> y;
    points.push_back(std::make_tuple(x, y));
  }
}