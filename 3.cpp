
#include <iostream>
#include <list>
#include <string>

#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

template <typename Key, typename T>
class Map {
  struct Node {
    enum Color { Color_BLACK, Color_RED };
    Key key;
    T value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Color color = Color_BLACK;
  };

  Node* _begin = new Node();
  Node* _end = _begin;

  Node* _uncle(Node* node) {
    return node->parent == node->parent->parent->right
               ? node->parent->parent->left
               : node->parent->parent->right;
  }

  void _rotate_right(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != _end) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      _begin = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void _rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != _end) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      _begin = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void _fix_tree(Node* node) {
    while (node != _begin && node->parent->color == Node::Color_RED) {
      Node* uncle = _uncle(node);

      if (uncle->color == Node::Color_RED) {
        uncle->color = Node::Color_BLACK;
        node->parent->color = Node::Color_BLACK;
        node->parent->parent->color = Node::Color_RED;
        node = node->parent->parent;
        continue;
      }

      if (node->parent == node->parent->parent->right) {
        if (node == node->parent->left) {
          node = node->parent;
          _rotate_right(node);
        }

        node->parent->color = Node::Color_BLACK;
        node->parent->parent->color = Node::Color_RED;
        _rotate_left(node->parent->parent);
        continue;
      }

      if (node == node->parent->right) {
        node = node->parent;
        _rotate_left(node);
      }

      node->parent->color = Node::Color_BLACK;
      node->parent->parent->color = Node::Color_RED;
      _rotate_right(node->parent->parent);
    }

    _begin->color = Node::Color_BLACK;
  }

  Node* _at(Node* node, const Key& key) {
    if (node == _end || key == node->key) {
      return node;
    }

    if (key < node->key) {
      return _at(node->left, key);
    }
    return _at(node->right, key);
  }

 public:
  void insert(const Key& key, const T& value) {
    auto node = new Node();
    node->value = value;
    node->key = key;
    node->left = _end;
    node->right = _end;
    node->color = Node::Color_RED;
    Node* parent = nullptr;
    auto child = _begin;
    while (child != _end) {
      parent = child;
      if (node->key < child->key) {
        child = child->left;
      } else {
        child = child->right;
      }
    }

    node->parent = parent;
    if (parent == nullptr) {
      _begin = node;
      node->color = Node::Color_BLACK;

      return;
    }
    if (node->key < parent->key) {
      parent->left = node;
    } else {
      parent->right = node;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    _fix_tree(node);
  }

  T& at(const Key& key) { return _at(_begin, key)->value; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;

  std::list<std::string> songs_by_favourites;
  Map<std::string, std::list<std::string>::iterator> songs_by_names;

  for (auto i = 0; i < n; i++) {
    std::string str;
    std::cin >> str;

    songs_by_names.insert(str,
                        songs_by_favourites.insert(songs_by_favourites.end(), str));
  }

  int K;
  std::cin >> K;

  for (auto i = 0; i < K; i++) {
    char action;
    std::cin >> action;
    if (action == 'a') {
      std::string str;
      std::cin >> str;
      songs_by_names.insert(
          str, songs_by_favourites.insert(songs_by_favourites.end(), str));
      continue;
    }
    if (action == 'm') {
      std::string str;
      int value;
      std::cin >> str >> value;

      auto song = songs_by_names.at(str);

      if (value < 0) {
        auto to = std::next(song);
        while (to != songs_by_favourites.end() && value++ < 0) {
          std::advance(to, 1);
        }
        songs_by_favourites.splice(to, songs_by_favourites, song);
        continue;
      }

      auto to = song;
      while (to != songs_by_favourites.end() && value-- > 0) {
        std::advance(to, -1);
      }
      songs_by_favourites.splice(to, songs_by_favourites, song);
      continue;
    }
    if (action == 'r') {
      std::string str1, str2;
      std::cin >> str1 >> str2;

      std::swap(*songs_by_names.at(str1), *songs_by_names.at(str2));
      std::swap(songs_by_names.at(str1), songs_by_names.at(str2));

      continue;
    }
  }
  for (auto& song : songs_by_favourites) {
    std::cout << song << std::endl;
  }
}