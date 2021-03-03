#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <vector>
// #define MAX_INT 0x7fffffff
struct Point {
  int x;
  int y;

  int dist(const Point& point) const {
    return std::abs(point.x - x) + std::abs(point.y - y);
  }
};

template <typename T>
class WeightedGraph {
   std::vector<std::list<std::tuple<int, int>>> edges;

 public:
  WeightedGraph(int length) {
    weights.resize(length);
    std::fill(weights.begin(), weights.end(), MAX_INT);
  }

  int insert(const T& node) { nodes.push_back(node); }
  int connect(int nodeIndex, int nodeIndex) {}
  find() { std::priority_queue queue(); }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  for (auto i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
  }
  int s, d;
  std::cin >> s, d;
}