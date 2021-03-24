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

bool isBlack(short i) { return i % 2 == 0; }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  short n;
  std::cin >> n;

  std::vector<short> vertecies(n * n);

  std::vector<std::vector<short>> edges(n * n);

  for (auto i = 0; i < n * n; i++) {
    std::cin >> vertecies[i];
  }

  for (auto k = 0; k < n * n; k++) {
    // for (auto j = 0; j < n; j++) {
    if (vertecies[k] == 0) {
      continue;
    }

    auto y1 = (((vertecies[k] / 2 + 1) % 2) * 2 + 1) * ((k % 2) * -2 + 1);

    if ((k + y1) / n == k / n && vertecies[k + y1] != 0) {
      edges[k].push_back(k + y1);
    }

    auto y2 = (vertecies[k] % 2) * 2 * ((k % 2) * -2 + 1);

    if ((k + y2) / n != k / n) {
      continue;
    }

    if (k + n < n * n && vertecies[k + n + y2] != 0) {
      edges[k].push_back(k + n + y2);
    }

    if (k - n >= 0 && vertecies[k - n + y2] != 0) {
      edges[k].push_back(k - n + y2);
    }
  }

  std::vector<short> pairs(n * n, -1);
  std::vector<short> branches(n * n);

  for (auto i = 0; i < n * n; i += 2) {
    if (pairs[i] > -1) {
      continue;
    }

    std::vector<short> visited(n * n, false);
    std::queue<short> queue;

    visited[i] = true;
    branches[i] = -1;
    queue.push(i);

    while (!queue.empty()) {
      auto j = queue.front();
      queue.pop();

      if (!isBlack(j)) {
        if (pairs[j] <= -1) {
          while (branches[j] > -1) {
            if (!isBlack(j)) {
              pairs[j] = branches[j];
              pairs[branches[j]] = j;
            }
            j = branches[j];
          }
          break;
        }
        pairs[branches[j]] = j;
        visited[branches[j]] = true;
        queue.push(pairs[j]);
        continue;
      }

      for (auto& edge : edges[j]) {
        if (visited[edge]) {
          continue;
        }
        visited[edge] = true;
        branches[edge] = j;
        queue.push(edge);
      }
    }
  }

  int r = 0;
  for (int i = 0; i < n * n; i++) {
    // std::cout << i << "->" << pairs[i] << std::endl;

    if (pairs[i] > -1) {
      r++;
    }
  }

  // std::cout << r;
  // r - zbitych
  // znaleźć max par bijących
  // jedna z dwóch w parze, może się zbić

  std::cout << n * n - r / 2;
}