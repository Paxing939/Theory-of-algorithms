#include <utility>
#include <iostream>
#include <fstream>
#include <ctime>

typedef struct element *pelement;

struct element {
  int priority, value, key;
  pelement l, r;

  element(int value, int priority) : priority(priority), value(value), key(-1), l(nullptr),
                                                 r(nullptr) {}
};

class Treap {
public:

  Treap(int n, int q) : n_(n), q_(q) {
    srand(time(0));
    tree_ = BuildTreap(0, n);
  }

  void ProcessRequests(std::istream &reader) {
    int value1, value2;
    pelement l, r, ll, lr, tmp;
    for (int i = 0; i < q_; ++i) {
      reader >> value1 >> value2;
      Split(tree_, l, r, value2, 0);
      Split(l, ll, lr, value1 - 1, 0);
      Merge(lr, ll, tmp);
      Merge(tmp, r, tree_);
    }
  }

  void PrintTree(std::ostream &out) {
    PrintTree(out, tree_);
  }

  friend std::ostream &operator<<(std::ostream &out, pelement &it);

private:

  void PrintTree(std::ostream &out, pelement& tree) {
    if (!tree) {
      return;
    }
    PrintTree(out, tree->l);
    out << tree->value << " ";
    PrintTree(out, tree->r);
  }

  static void Split(pelement src_tree, pelement &l, pelement &r, int key, int add) {
    if (src_tree == nullptr) {
      l = nullptr, r = nullptr;
      return;
    }

    if (key <= add + CountKey(src_tree->l)) {
      Split(src_tree->l, l, src_tree->l, key, add);
      r = src_tree;
    } else {
      Split(src_tree->r, src_tree->r, r, key, add + 1 + CountKey(src_tree->l));
      l = src_tree;
    }

    UpdateKey(src_tree);
  }

  static void Merge(pelement &l, pelement &r, pelement &tree) {
    if (l == nullptr || r == nullptr) {
      if (l != nullptr) {
        tree = l;
      } else {
        tree = r;
      }
    } else {
      if (l->priority > r->priority) {
        Merge(l->r, r, l->r);
        tree = l;
      } else {
        Merge(l, r->l, r->l);
        tree = r;
      }
    }

    UpdateKey(tree);
  }

  static void Heap(pelement &t) {
    if (!t) {
      return;
    }

    pelement max = t;

    if (t->l != nullptr && t->l->priority > max->priority) {
      max = t->l;
    }

    if (t->r != nullptr && t->r->priority > max->priority) {
      max = t->r;
    }

    if (max != t) {
      std::swap(t->priority, max->priority);
      Heap(max);
    }
  }

  static pelement BuildTreap(int value, int n) {
    if (n == 0) {
      return nullptr;
    }

    int mid = n / 2;
    auto tree = new element(value + mid + 1, rand());

    tree->l = BuildTreap(value, mid);

    tree->r = BuildTreap(value + mid + 1, n - mid - 1);

    Heap(tree);

    UpdateKey(tree->l);
    UpdateKey(tree->r);
    UpdateKey(tree);

    return tree;
  }

  static void UpdateKey(pelement &tree) {
    if (tree != nullptr) {
      tree->key = CountKey(tree->l) + CountKey(tree->r) + 1;
    }
  }

  static int CountKey(pelement &pel) {
    if (pel != nullptr) {
      return pel->key;
    } else {
      return 0;
    }
  }

  int n_, q_;
  pelement tree_;
};

std::ostream &operator<<(std::ostream &out, Treap &treap) {
  treap.PrintTree(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, pelement &item) {
  out << item->value;
  return out;
}

int main() {
  std::ifstream reader("input.txt");
  std::ofstream writer("output.txt");
  int n, q;
  reader >> n >> q;

  Treap treap(n, q);

  treap.ProcessRequests(reader);

  writer << treap;
  return 0;
}
