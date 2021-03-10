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

struct Point {
  int x;
  int y;

  int distance(const Point& point) {
    return std::min(std::abs(x - point.x), std::abs(y - point.y));
  }
  Point() { std::cin >> x >> y; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Point> points(n);
  std::vector<std::vector<std::tuple<int, short>>> edges(n);

  for (auto i = 0; i < n; i++) {
    std::vector<std::tuple<int, short>> vertexEdges;
    vertexEdges.reserve(i);

    for (auto j = 0; j < i; j++) {
      if (edges[j].size() < 4) {
        vertexEdges.push_back(
            std::make_tuple<int, short>(points[i].distance(points[j]), j));
      }
    }

    std::nth_element(vertexEdges.begin(), vertexEdges.begin() + 3,
                     vertexEdges.end());
    vertexEdges.resize(std::min<int>(4, vertexEdges.size()));

    for (auto& edge : vertexEdges) {
      short j;
      int distance;
      std::tie(distance, j) = edge;
      edges[j].push_back(std::make_tuple(distance, i));
    }

    edges[i].swap(vertexEdges);
  }

  int s, d;
  std::cin >> s >> d;

  std::vector<int> distances(n, INT_MAX);
  distances[s] = 0;

  std::priority_queue<std::tuple<int, short>,
                      std::vector<std::tuple<int, short>>,
                      std::greater<std::tuple<int, short>>>
      queue;

  std::vector<bool> visited(n, false);

  queue.push(std::make_tuple(0, s));

  while (!queue.empty()) {
    int fromDistance;
    short from;

    std::tie(fromDistance, from) = queue.top();
    queue.pop();

    if (visited[from]) {
      continue;
    }
    visited[from] = true;

    for (auto& edge : edges[from]) {
      int distance;
      short to;
      std::tie(distance, to) = edge;

      auto toDistance = distance + fromDistance;

      if (toDistance >= distances[to]) {
        continue;
      }

      distances[to] = toDistance;
      queue.push(std::make_tuple(toDistance, to));
    }
  }
  std::cout << distances[d];
}