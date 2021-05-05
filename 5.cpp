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

#include <cmath>

std::vector<int> rabin_karp(const std::vector<short>& sequence,
                            const std::vector<short>& search) {
  const int p = 101;
  const int m = 1e9 + 9;

  std::vector<long long> p_pow(std::max(search.size(), sequence.size()));
  p_pow[0] = 1;
  for (int i = 1; i < (int)p_pow.size(); i++) {
    p_pow[i] = (p_pow[i - 1] * p) % m;
  }

  std::vector<long long> h(sequence.size() + 1, 0);
  for (int i = 0; i < sequence.size(); i++) {
    h[i + 1] = (h[i] + (sequence[i] + 1) * p_pow[i]) % m;
  }

  long long h_s = 0;
  for (int i = 0; i < search.size(); i++) {
    h_s = (h_s + (search[i] + 1) * p_pow[i]) % m;
  }

  std::vector<int> occurences;

  for (int i = sequence.size() - search.size(); i > -1 && occurences.size() < 2;
       i--) {
    long long cur_h = (h[i + search.size()] + m - h[i]) % m;

    if (cur_h == h_s * p_pow[i] % m) {
      occurences.push_back(i);
    }
  }

  return occurences;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int V;
  std::cin >> V;
  std::vector<short> sequence;
  sequence.reserve(V);

  for (auto i = 0; i < V; i++) {
    short n;
    std::cin >> n;
    sequence.push_back(n);
  }

  int P;
  std::cin >> P;
  std::vector<short> subsequence;
  subsequence.reserve(P);

  for (auto i = 0; i < P; i++) {
    short n;
    std::cin >> n;
    subsequence.push_back(n);
  }

  auto r = rabin_karp(sequence, subsequence);

  int i = r[1];
  int j = r[0];

  std::cout << i + j - V << std::endl;
}
