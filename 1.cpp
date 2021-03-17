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

struct Point {
  int x;
  int y;
  short i;

  int distance(const Point& point) {
    return std::min(std::abs(x - point.x), std::abs(y - point.y));
  }

  Point(short i) {
    this->i = i;
    std::cin >> x >> y;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  short n;
  std::cin >> n;

  std::vector<Point*> points;
  points.reserve(n);
  std::vector<std::vector<std::tuple<int, short>>> edges(n);

  for (auto i = 0; i < n; i++) {
    points.push_back(new Point(i));
  }

  std::sort(points.begin(), points.end(),
            [](auto& a, auto& b) { return a->x < b->x; });

  for (auto i = 1; i < n; i++) {
    auto weight = points[i]->distance(*points[i - 1]);

    edges[points[i - 1]->i].push_back(std::make_tuple(weight, points[i]->i));
    edges[points[i]->i].push_back(std::make_tuple(weight, points[i - 1]->i));
  }

  std::sort(points.begin(), points.end(),
            [](auto& a, auto& b) { return a->y < b->y; });

  for (auto i = 1; i < n; i++) {
    auto weight = points[i]->distance(*points[i - 1]);

    edges[points[i - 1]->i].push_back(std::make_tuple(weight, points[i]->i));
    edges[points[i]->i].push_back(std::make_tuple(weight, points[i - 1]->i));
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