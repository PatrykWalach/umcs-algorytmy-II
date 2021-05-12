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

std::vector<int> rabinKarp(const std::vector<short>& sequence,
                            const std::vector<short>& search) {
  const int p = 101;
  const int m = 1e9 + 9;

  std::vector<long long> p_pow(std::max(search.size(), sequence.size()));
  p_pow[0] = 1;
  for (int i = 1; i < (int)p_pow.size(); i++) {
    p_pow[i] = (p_pow[i - 1] * p) % m;
  }

  std::vector<long long> hashed_sequence(sequence.size() + 1, 0);
  for (int i = 0; i < sequence.size(); i++) {
    hashed_sequence[i + 1] =
        (hashed_sequence[i] + (sequence[i] + 1) * p_pow[i]) % m;
  }

  long long hashed_search = 0;
  for (int i = 0; i < search.size(); i++) {
    hashed_search = (hashed_search + (search[i] + 1) * p_pow[i]) % m;
  }

  std::vector<int> occurrences;

  for (int i = sequence.size() - search.size(); i > -1 && occurrences.size() < 2;
       i--) {
    long long cur_h =
        (hashed_sequence[i + search.size()] + m - hashed_sequence[i]) % m;

    if (cur_h == hashed_search * p_pow[i] % m &&
        std::equal(sequence.begin() + i, sequence.begin() + i + search.size(),
                   search.begin())) {
      occurrences.push_back(i);
    }
  }

  return occurrences;
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

  auto r = rabinKarp(sequence, subsequence);

  int i = r[1];
  int j = r[0];

  std::cout << i + j - V << std::endl;
}