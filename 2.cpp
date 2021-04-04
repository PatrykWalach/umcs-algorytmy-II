#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

std::vector<int> pairs;
std::vector<bool> visited;
std::vector<std::list<int>> edges;

bool kuhn(int v) {
  if (visited[v]) {
    return false;
  }

  visited[v] = true;
  for (auto& to : edges[v]) {
    if (pairs[to] != -1 && !kuhn(pairs[to])) {
      continue;
    }
    pairs[to] = v;
    return true;
  }

  return false;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<short> verticies;
  verticies.reserve(n * n);
  edges.resize(n * n);

  for (auto i = 0; i < n * n; i++) {
    short v;
    std::cin >> v;
    verticies.push_back(v);
  }

  std::vector<short> VERTEX_TO_D1 = {SHRT_MAX, 3, 1, 1};
  std::vector<short> VERTEX_TO_D2 = {SHRT_MAX, 2, 0, 2};

  for (auto i = 0; i < n; i++) {
    for (auto j = i % 2; j < n; j += 2) {
      auto k = i * n + j;
      if (verticies[k] == 0) {
        continue;
      }

      auto d1 = VERTEX_TO_D1[verticies[k]];

      if (std::floor((float)(k + d1) / (float)n) == i &&
          verticies[k + d1] != 0) {
        edges[k].push_back(k + d1);
      }

      auto d2 = VERTEX_TO_D2[verticies[k]];

      if (std::floor((float)(k + d2) / (float)n) != i) {
        continue;
      }

      if (k + n < n * n && verticies[k + n + d2] != 0) {
        edges[k].push_back(k + n + d2);
      }

      if (k - n >= 0 && verticies[k - n + d2] != 0) {
        edges[k].push_back(k - n + d2);
      }
    }
  }

  pairs.assign(n * n, -1);

  int r = 0;
  for (auto i = 0; i < n; i++) {
    for (auto j = i % 2; j < n; j += 2) {
      auto k = i * n + j;
      visited.assign(n * n, false);
      if (kuhn(k)) {
        r++;
      }
    }
  }

  std::cout << n * n - r;
}