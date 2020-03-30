#include <utility>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

typedef struct item *pitem;

struct item {
  int prior, value, cnt;
  bool rev;
  pitem l, r;

  item(int value, int prior) : prior(prior), value(value), cnt(-1), rev(false), l(nullptr), r(nullptr) {}
};

class Treap {
public:

  Treap(int n, int q) : n_(n), q_(q) {
    srand(time(0));
    tree_ = build(0, n);
    std::cerr << "\n\n";
    requests.reserve(q);
  }

  void ProcessRequests() {

    std::vector<std::vector<int>> queries = {
        {2, 4},
        {3, 5},
        {1, 3}
    };

    output(tree_);
    std::cerr << '\n';
    for (auto &query : queries) {

      pitem left, right;
      split(tree_, left, right, query[1]);

      pitem left_left, left_right;
      split(left, left_left, left_right, query[0] - 1);

      pitem tmp;
//      output(left_left);
//      std::cerr << "\n";
//      output(left_right);
//      std::cerr << "\n";
//      output(right);
//      std::cerr << "\n";

      merge(tmp, left_right, left_left);

      merge(tree_, tmp, right);

    output(tree_);
    std::cerr << "\n";
    }
  }
  
  void output(pitem t) {
    if (!t) return;

    output(t->l);
    std::cerr << t->value;
    output(t->r);
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

  friend std::ostream &operator<<(std::ostream &out, const pitem &it);

private:

  void PrintTree(std::ostream &out, pitem tree) const {
    if (!tree) return;
    PrintTree(out, tree->l);
    out << tree->value;
    PrintTree(out, tree->r);
  }

  void merge(pitem &tree, pitem left, pitem right) {
    if (!left || !right) {
      if (left != nullptr) {
        tree = left;
      } else {
        tree = right;
      }
    } else {
      if (left->prior > right->prior) {
        merge(left->r, left->r, right);
        tree = left;
      } else {
        merge(right->l, left, right->l);
        tree = right;
      }
    }

    upd_cnt(tree);
  }

  void split(pitem src_tree, pitem &left, pitem &right, int key, int add = 0) {
    if (src_tree == nullptr) {
      left = nullptr;
      right = nullptr;
      return;
    }

    int cur_key = add + cnt(src_tree->l);

    if (key <= cur_key) {
      split(src_tree->l, left, src_tree->l, key, add);
      right = src_tree;
    } else {
      split(src_tree->r, src_tree->r, right, key, add + 1 + cnt(src_tree->l));
      left = src_tree;
    }

    upd_cnt(src_tree);
  }

  void heapify(pitem t) {
    if (!t) {
      return;
    }

    pitem max = t;

    if (t->l != nullptr && t->l->prior > max->prior) {
      max = t->l;
    }

    if (t->r != nullptr && t->r->prior > max->prior) {
      max = t->r;
    }

    if (max != t) {
      std::swap(t->prior, max->prior);
      heapify(max);
    }
  }

  pitem build(int value, int n) {
    if (n == 0) {
      return nullptr;
    }

    int mid = n / 2;
    auto tree = new item(value + mid + 1, rand());

    tree->l = build(value, mid);

    tree->r = build(value + mid + 1, n - mid - 1);

    heapify(tree);

    upd_cnt(tree->l);
    upd_cnt(tree->r);
    upd_cnt(tree);

    return tree;
  }

  int cnt(pitem it) {
    if (it != nullptr) {
      return it->cnt;
    } else {
      return 0;
    }
  }

  void upd_cnt(pitem tree) {
    if (tree != nullptr) {
      tree->cnt = cnt(tree->l) + cnt(tree->r) + 1;
    }
  }

  std::vector<std::pair<int, int>> requests;
  int n_, q_;
  pitem tree_;
};

std::ostream &operator<<(std::ostream &out, const Treap &treap) {
  treap.PrintTree(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, const pitem &item) {
  out << item->value;
  return out;
}

int main() {
  std::ifstream reader("input.txt");
  std::ofstream writer("output.txt");
  int n, q;
  reader >> n >> q;

  Treap treap(n, q);

//  std::cerr << treap;

  treap.ReadRequests(reader);

  treap.ProcessRequests();

  writer << treap;
  return 0;
}
