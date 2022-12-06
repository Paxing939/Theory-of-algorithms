#include <iostream>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

  bool IsAllZero(TreeNode *root) {
    if (root == nullptr) {
      return true;
    }

    bool left = IsAllZero(root->left);
    bool right = IsAllZero(root->right);

    if (root->val == 1 || !(left && right)) {
      if (left) {
        root->left = nullptr;
      }
      if (right) {
        root->right = nullptr;
      }
      return false;
    }

    return left && right;
  }

  TreeNode *pruneTree(TreeNode *root) {
    if (IsAllZero(root)) {
      root = nullptr;
    }
    return root;
  }

};

TreeNode *BuildTreeFromVector(std::vector<int> arr, int i) {
  TreeNode *root = nullptr;
  if (i < arr.size()) {
    root = new TreeNode(arr[i]);
    root->left = BuildTreeFromVector(arr, 2 * i + 1);
    root->right = BuildTreeFromVector(arr, 2 * i + 2);
  }
  return root;
}

std::vector<int> BuildVectorFromTree(TreeNode *TreeNode) {

}

void TestSolution(std::vector<int> input, const std::vector<int> &answer) {

  Solution solution;
  TreeNode *tree_node = new TreeNode(1);
  solution.pruneTree(tree_node);
}

int main() {
  { 1, 1, 1, 1, 1, 0, 0, 0, 1, -1, 0, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
}