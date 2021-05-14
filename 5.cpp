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

  std::vector<long long> pPow(std::max(search.size(), sequence.size()));
  pPow[0] = 1;
  for (int i = 1; i < (int)pPow.size(); i++) {
    pPow[i] = (pPow[i - 1] * p) % m;
  }

  std::vector<long long> hashedSequence(sequence.size() + 1, 0);
  for (int i = 0; i < sequence.size(); i++) {
    hashedSequence[i + 1] =
        (hashedSequence[i] + (sequence[i] + 1) * pPow[i]) % m;
  }

  long long hashedSearch = 0;
  for (int i = 0; i < search.size(); i++) {
    hashedSearch = (hashedSearch + (search[i] + 1) * pPow[i]) % m;
  }

  std::vector<int> occurrences;

  for (int i = sequence.size() - search.size();
       i > -1 && occurrences.size() < 2; i--) {
    long long hash =
        (hashedSequence[i + search.size()] + m - hashedSequence[i]) % m;

    if (hash == hashedSearch * pPow[i] % m &&
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

  int j = r[0];
  int c = r[1] + j;

  while (c < V) {
    c += j;
  }

  std::cout << c - V << std::endl;
}