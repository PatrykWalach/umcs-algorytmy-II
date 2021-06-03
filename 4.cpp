#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <string>

#undef INT_MAX
#define INT_MAX 0x7fffffff
#undef SHRT_MAX
#define SHRT_MAX 0x7fff

template <typename Key, typename T>
class BTree {
  int _T;

  struct Leaf;

  struct Node {
    Key key;
    T value;
    Leaf* next;

    Node(Key& key, T& value, Leaf* next) {
      this->key = key;
      this->value = value;
      this->next = next;
    }
  };

  struct Leaf {
    std::list<Node*> children;
    Leaf* next;

    Leaf(Leaf* next) { this->next = next; }
  };

  Leaf* _begin = new Leaf(nullptr);
  Leaf* _end = nullptr;

  Node* _find(Leaf* leaf, Key& key) {
    if (leaf == _end) {
      return nullptr;
    }

    auto it = _shallow_find(leaf, key);

    if (it == leaf->children.end()) {
      return _find(leaf->next, key);
    }
    auto& child = *it;

    if (child->key == key) {
      return child;
    }

    return _find(child->next, key);
  }

  typename std::list<Node*>::iterator _shallow_find(Leaf* leaf, Key& key) {
    return std::lower_bound(
        leaf->children.begin(), leaf->children.end(), key,
        [](auto& node, auto& key) { return node->key < key; });
  }

  bool _insert(Leaf* leaf, Node* node) {
    auto it = _shallow_find(leaf, node->key);

    if (it != leaf->children.end() && (*it)->key == node->key) {
      (*it)->value = node->value;
      return true;
    }

    auto& next = it != leaf->children.end() ? (*it)->next : leaf->next;

    if (next == _end) {
      leaf->children.insert(it, node);
      return leaf->children.size() < _T;
    }

    if (_insert(next, node)) {
      return true;
    }

    _split(leaf, next, it);

    return leaf->children.size() < _T;
  }

 public:
  BTree(int _T) { this->_T = _T; }

  Leaf* end() { return _end; }

  Node* find(Key& key) { return _find(_begin, key); }

  void _split(Leaf* parent_leaf, Leaf* leaf,
              typename std::list<Node*>::iterator it) {
    auto& children = leaf->children;
    auto middle_it = children.begin();
    std::advance(middle_it, children.size() / 2);
    auto middle = *middle_it;

    middle->next = new Leaf(middle->next);
    middle->next->children.splice(middle->next->children.begin(), children,
                                  children.begin(), middle_it);

    parent_leaf->children.splice(it, children, middle_it);

    if (it == parent_leaf->children.end()) {
      parent_leaf->next = leaf;
    } else {
      (*it)->next = leaf;
    }
  }

  void insert(Key& key, T& value) {
    if (!_insert(_begin, new Node(key, value, _end))) {
      _begin = new Leaf(_begin);

      _split(_begin, _begin->next, _begin->children.end());
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  BTree<std::string, std::string> m(41);
  int n;
  std::cin >> n;
  std::cin.ignore();

  for (auto i = 0; i < n; i++) {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss(line);
    std::string key;
    std::getline(ss, key, ':');
    std::string value;

    if (std::getline(ss, value, ':')) {
      value.erase(value.begin());
      m.insert(key, value);
      continue;
    }

    auto definition = m.find(key);

    std::cout << (definition == nullptr ? "BRAK" : definition->value) << '\n';
  }
}