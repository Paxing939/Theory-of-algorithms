#include <utility>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

class Treap {
public:

  struct item {
    int priority, value, cnt;
    bool rev;
    item *left, *right;

    item(int value, int prior) : priority(prior), value(value), cnt(-1), rev(false), left(nullptr), right(nullptr) {}
  };

  Treap(int n, int q) : n_(n), q_(q) {
    srand(time(0));
    tree_ = BuildRecursion(n, n);
    std::cerr << "\n\n";
    requests.reserve(q);
  }

  void ProcessRequests() {
    for (auto &query : requests) {
      item *left = nullptr, *right = nullptr;
      split(tree_, left, right, query.second);

      item *left_left = nullptr, *left_right = nullptr;
      split(left, left_left, left_right, query.first - 1);

      item *tmp = nullptr;
      merge(tmp, left_right, left_left);

      merge(tree_, tmp, right);
    }
  }

  void ReadRequests(std::istream &reader) {
    int value1, value2;
    for (int i = 0; i < q_; ++i) {
      reader >> value1 >> value2;
      requests.emplace_back(value1, value2);
    }
  }

  void PrintTree(std::ostream &out) const {
    PrintTree(out, tree_);
  }

  friend std::ostream &operator<<(std::ostream &out, const Treap::item &it);

private:

  void PrintTree(std::ostream &out, item *tree) const {
    if (!tree) return;
    PrintTree(out, tree->left);
    out << tree->value;
    PrintTree(out, tree->right);
  }

  item *BuildRecursion(int value, int n) {
    if (n == 0) {
      return nullptr;
    }

    int mid = n / 2;

    item *current_tree = new item(mid + 1, rand());

    current_tree->left = BuildRecursion(value, mid);

    current_tree->right = BuildRecursion(value + mid + 1,  n - mid - 1);

    heapify(current_tree);

    UpdateCount(current_tree->left);
    UpdateCount(current_tree->right);
    UpdateCount(current_tree);

    return current_tree;
  }

  void merge(item *tree, item *left, item *right) {
    if (!left || !right) {
      if (left != nullptr) {
        tree = left;
      } else {
        tree = right;
      }
    } else {
      if (left->priority > right->priority) {
        merge(left->right, left->right, right), tree = left;
      } else {
        merge(right->left, left, right->left), tree = right;
      }
    }

    UpdateCount(tree);
  }

  void split(item *src_tree, item *left, item *right, int key, int add = 0) {
    if (src_tree == nullptr) {
      return;
    }

    int cur_key = add + Count(src_tree->left);

    if (key <= cur_key) {
      split(src_tree->left, left, src_tree->left, key, add);
      right = src_tree;
    } else {
      split(src_tree->right, src_tree->right, right, key, add + 1 + Count(src_tree->left));
      left = src_tree;
    }

    UpdateCount(src_tree);
  }


  void heapify(item *t) {
    if (!t) {
      return;
    }

    item *max = t;

    if (t->left != nullptr && t->left->priority > max->priority) {
      max = t->left;
    }

    if (t->right != nullptr && t->right->priority > max->priority) {
      max = t->right;
    }

    if (max != t) {
      std::swap(t->priority, max->priority);
      heapify(max);
    }
  }

  int Count(item *current_tree) {
    if (current_tree != nullptr) {
      return current_tree->cnt;
    } else {
      return 0;
    }
  }

  void UpdateCount(item *current_tree) {
    if (current_tree != nullptr) {
      current_tree->cnt = Count(current_tree->left) + Count(current_tree->right) + 1;
    }
  }

  std::vector<std::pair<int, int>> requests;
  int n_, q_;
  item *tree_;
};

std::ostream &operator<<(std::ostream &out, const Treap &treap) {
  treap.PrintTree(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, const Treap::item &it) {
  out << it.value;
  return out;
}

int main() {
  std::ifstream reader("input.txt");
  std::ofstream writer("output.txt");
  int n, q;
  reader >> n >> q;

  Treap treap(n, q);

  std::cerr << treap;

  treap.ReadRequests(reader);

  treap.ProcessRequests();

  writer << treap;
  return 0;
}
