#include <iostream>
#include <vector>

struct Node {
  int64_t value;
  int64_t left;
  int64_t right;
};

int main() {
  freopen("bst.in", "r", stdin);
  freopen("bst.out", "w", stdout);

  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int64_t n;
  std::cin >> n;

  std::vector<Node> tree(n);
  std::cin >> tree[0].value;
  tree[0].right = std::numeric_limits<int>::max();
  tree[0].left = std::numeric_limits<int>::min();
  tree[0].right += 10;
  tree[0].left -= 10;


  for (int64_t i = 1; i < n; ++i) {
    int64_t m, p;
    char c;
    std::cin >> m >> p >> c;

    p--;
    if (p == 6)
    {
      int df = 0;
    }
    if (c == 'L') {
      if (!(m >= tree[p].left && m < tree[p].value)) {
        std::cout << "NO";
        return 0;
      }
      tree[i].left = tree[p].left;
      tree[i].right = tree[p].value;
    } else {
      if (!(m < tree[p].right && m >= tree[p].value)) {
        std::cout << "NO";
        return 0;
      }
      tree[i].left = tree[p].value;
      tree[i].right = tree[p].right;
    }

    tree[i].value = m;
  }

  std::cout << "YES";
}
