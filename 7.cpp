

#include <ctime>
#include <iostream>
#include <random>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::mt19937 gen;

  int N = 5e7;
  double X, Y;
  std::cin >> X >> Y;

  std::uniform_real_distribution<double> distrib_x(0.0, X);
  std::uniform_real_distribution<double> distrib_y(0.0, Y);

  gen.seed(std::time(nullptr));

  long double depth = 0;

  for (auto i = 0; i < N; i++) {
    double x = distrib_x(gen);
    double y = distrib_y(gen);

    double distance = d(x, y);
    if (distance < 0) {
      continue;
    }
    depth += distance;
  }

  std::cout << (int)(X * Y * depth / N) << '\n';
}