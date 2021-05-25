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

struct Point {
  double x;
  double y;

  bool operator<(Point &b) { return x < b.x || (x == b.x && y < b.y); }
};

double angle(Point &a, Point &b, Point &c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

void convexHull(std::vector<Point> &points) {
  std::sort(points.begin(), points.end());
  auto &first = points.front();
  auto &last = points.back();
  std::vector<Point> up;
  std::vector<Point> down;
  up.push_back(first);
  down.push_back(first);

  for (auto i = 1; i < points.size(); i++) {
    if (i == points.size() - 1 || angle(first, points[i], last) < 0) {
      while (up.size() >= 2 &&
             angle(up[up.size() - 2], up[up.size() - 1], points[i]) >= 0) {
        up.pop_back();
      }
      up.push_back(points[i]);
    }

    if (i == points.size() - 1 || angle(first, points[i], last) > 0) {
      while (down.size() >= 2 && angle(down[down.size() - 2],
                                       down[down.size() - 1], points[i]) <= 0) {
        down.pop_back();
      }
      down.push_back(points[i]);
    }
  }
  points.clear();

  points.insert(points.end(), up.begin(), up.end());

  for (auto i = down.size() - 2; i > 0; i--) {
    points.push_back(down[i]);
  }
}

double area(const std::vector<Point> &points) {
  double area = 0;
  for (unsigned i = 0; i < points.size(); i++) {
    Point p = i ? points[i - 1] : points.back();
    Point q = points[i];
    area += (p.x - q.x) * (p.y + q.y);
  }
  return std::abs(area) / 2;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N;
  std::cin >> N;
  std::vector<Point> points(N);

  for (auto i = 0; i < N; i++) {
    std::cin >> points[i].x >> points[i].y;
  }

  convexHull(points);

  std::cout.precision(3);
  std::cout << std::fixed << area(points) << std::endl;
}