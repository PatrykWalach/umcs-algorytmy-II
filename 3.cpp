
#include <iostream>
#include <list>
#include <map>
#include <string>

#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

template <typename K, typename T>
class Tree {
  enum Color { Color_RED, Color_BLACK };

 public:
  void insert(T& v) {}
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  std::list<std::string> songsByFavourites;
  std::map<std::string, std::list<std::string>::iterator> songsByNames;

  for (auto i = 0; i < n; i++) {
    std::string str;
    std::cin >> str;

    songsByNames[str] = songsByFavourites.insert(songsByFavourites.end(), str);
  }

  int K;
  std::cin >> K;

  for (auto i = 0; i < K; i++) {
    char action;
    std::cin >> action;
    if (action == 'a') {
      std::string str;
      std::cin >> str;
      songsByNames[str] =
          songsByFavourites.insert(songsByFavourites.end(), str);
      continue;
    }
    if (action == 'm') {
      std::string str;
      int value;
      std::cin >> str >> value;

      auto song = songsByNames.at(str);

      if (value < 0) {
        auto to = std::next(song);
        while (to != songsByFavourites.end() && value++ < 0) {
          std::advance(to, 1);
        }
        songsByFavourites.splice(to, songsByFavourites, song);
        continue;
      }

      auto to = song;
      while (to != songsByFavourites.end() && value-- > 0) {
        std::advance(to, -1);
      }
      songsByFavourites.splice(to, songsByFavourites, song);

      continue;
    }
    if (action == 'r') {
      std::string str1, str2;
      std::cin >> str1 >> str2;

      std::swap(*songsByNames.at(str1), *songsByNames.at(str2));

      continue;
    }
  }
  for (auto& song : songsByFavourites) {
    std::cout << song << std::endl;
  }
}