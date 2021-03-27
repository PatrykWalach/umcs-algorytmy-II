#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  short n;
  std::cin >> n;

  std::vector<short> vertecies(n * n);
  std::vector<std::vector<int>> edges(n * n);

  for (auto i = 0; i < n * n; i++) {
    std::cin >> vertecies[i];
  }

  for (auto k = 0; k < n * n; k++) {
    if (vertecies[k] == 0) {
      continue;
    }

    auto y1 = (((vertecies[k] / 2 + 1) % 2) * 2 + 1) * ((k % 2) * -2 + 1);

    if (std::floor((float)(k + y1) / (float)n) == k / n &&
        vertecies[k + y1] != 0) {
      edges[k].push_back(k + y1);
      edges[k + y1].push_back(k);
    }

    auto y2 = (vertecies[k] % 2) * 2 * ((k % 2) * -2 + 1);

    if (std::floor((float)(k + y2) / (float)n) != k / n) {
      continue;
    }

    if (k + n < n * n && vertecies[k + n + y2] != 0) {
      edges[k].push_back(k + n + y2);
      edges[k + n + y2].push_back(k);
    }

    if (k - n >= 0 && vertecies[k - n + y2] != 0) {
      edges[k].push_back(k - n + y2);
      edges[k - n + y2].push_back(k);
    }
  }

  std::vector<int> pairs(n * n, -1);
  std::vector<int> parents(n * n);

  for (auto i = 0; i < n * n; i += 2) {
    if (pairs[i] != -1) {
      continue;
    }

    std::vector<int> visited(n * n, false);
    std::queue<int> queue;

    visited[i] = true;
    parents[i] = -1;
    queue.push(i);

    while (!queue.empty()) {
      auto j = queue.front();
      queue.pop();

      if (j % 2 != 0) {
        if (pairs[j] == -1) {
          while (parents[j] != -1) {
            if (j % 2 != 0) {
              pairs[j] = parents[j];
              pairs[parents[j]] = j;
            }
            j = parents[j];
          }
          break;
        }
        parents[pairs[j]] = j;
        visited[pairs[j]] = true;
        queue.push(pairs[j]);
        continue;
      }

      for (auto& edge : edges[j]) {
        if (visited[edge]) {
          continue;
        }
        visited[edge] = true;
        parents[edge] = j;
        queue.push(edge);
      }
    }
  }

  int r = 0;
  for (int i = 1; i < n * n; i += 2) {
    if (pairs[i] != -1) {
      r++;
    }
  }

  std::cout << n * n - r;
}