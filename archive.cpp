#include <cstdlib>
#include <utility>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

typedef struct item* pitem;

struct item {
  int prior, value, cnt;
  bool rev;
  pitem l, r;

  item(int value, int prior) : prior(prior), value(value), cnt(-1), rev(false), l(nullptr), r(nullptr) {}
};

int cnt(pitem it) {
  if (it != nullptr) {
    return it->cnt;
  } else {
    return 0;
  }
//  return it ? it->cnt : 0;
}

void upd_cnt(pitem tree) {
  if (tree != nullptr) {
    tree->cnt = cnt(tree->l) + cnt(tree->r) + 1;
  }
}

void push(pitem it) {
  if (it != nullptr && it->rev) {
    it->rev = false;
    swap(it->l, it->r);
    if (it->l) it->l->rev ^= true;
    if (it->r) it->r->rev ^= true;
  }
}

void merge(pitem& tree, pitem left, pitem right) {
  push(left);
  push(right);

  if (!left || !right) {
    if (left != nullptr) {
      tree = left;
    } else {
      tree = right;
    }
  } else {
    if (left->prior > right->prior) {
      merge(left->r, left->r, right), tree = left;
    } else {
      merge(right->l, left, right->l), tree = right;
    }
  }

  upd_cnt(tree);
}

void split(pitem src_tree, pitem& left, pitem& right, int key, int add = 0) {
  if (src_tree == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }

  push(src_tree);

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

//void reverse(pitem t, int l, int r) {
//  pitem t1, t2, t3;
//  split(t, t1, t2, l);
//  split(t2, t2, t3, r - l + 1);
//  t2->rev ^= true;
//  merge(t, t1, t2);
//  merge(t, t, t3);
//}

void output(pitem t) {
  if (!t) return;
//  push(t);
  output(t->l);
  std::cerr << t->value;
  output(t->r);
}

void rebuild_to_array(pitem t, std::vector<int>* res) {
  if (t == nullptr) {
    return;
  }
  push(t);
  rebuild_to_array(t->l, res);
  res->push_back(t->value);
  rebuild_to_array(t->r, res);
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
    swap(t->prior, max->prior);
    heapify(max);
  }
}

pitem build(int* a, int n) {
  // Construct a treap on values {a[0], a[1], ..., a[n - 1]}
  if (n == 0) {
    return nullptr;
  }

  int mid = n / 2;
  auto tree = new item(a[mid], rand()); // NO LINT

  tree->l = build(a, mid);

  tree->r = build(a + mid + 1, n - mid - 1);

  heapify(tree);

  upd_cnt(tree->l);
  upd_cnt(tree->r);
  upd_cnt(tree);

  return tree;
}

int main() {
  std::vector<int> v(6);
  std::iota(v.begin(), v.end(), 1);

  pitem treap = build(v.data(), v.size());

  std::vector<std::vector<int>> queries = {
      {2, 4},
      {3, 5},
      {1, 3}
  };

  for (auto& query : queries) {
    std::vector<int> values;
    std::cerr << query[0] << "\t" << query[1] << "\t" << v[query[0] - 1] << "\t" << v[query[1] - 1] << "\n";
    values.reserve(6);

    pitem left, right;
    split(treap, left, right, v[query[1] - 1]);
    upd_cnt(left);
    upd_cnt(right);
    pitem left_left, left_right;
    split(left, left_left, left_right, v[query[0] - 1] - 1);
    upd_cnt(left_left);
    upd_cnt(left_right);
    pitem tmp;
    output(left_left);
    std::cerr << "\n";
    output(left_right);
    std::cerr << "\n";
    output(right);
    std::cerr << "\n";

    merge(tmp, left_right, left_left);
    upd_cnt(tmp);

    merge(treap, tmp, right);
    upd_cnt(treap);

//    output(treap);
//    std::cerr << "\n";
    rebuild_to_array(treap, &values);
    v = values;
  }

//  output(treap);
  return 0;
}
