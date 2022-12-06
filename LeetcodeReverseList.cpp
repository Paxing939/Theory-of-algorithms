//
// Created by isach on 30.11.2022.
//

#include <iostream>


struct ListNode {
  int val;
  ListNode *next;

  ListNode() : val(0), next(nullptr) {}

  ListNode(int x) : val(x), next(nullptr) {}

  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void PrintList(ListNode *head) {
  ListNode *node = head;
  while (node) {
    std::cout << node->val;
    node = node->next;
  }
}

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode *prev = head;
    ListNode *node = head->next;
    prev->next = nullptr;
    while (node) {
      ListNode *where_to_next = node->next;
      node->next = prev;
      prev = node;
      node = where_to_next;
    }

    return prev;
  }
};

int main() {
  auto head = new ListNode();
  ListNode *node = head, *another;
  for (int i = 0; i < 5; ++i) {
    node->next = new ListNode();
    node = node->next;
    node->val = i + 1;
    another = node;
  }

  PrintList(head);

  Solution solution;
  solution.reverseList(head);

  PrintList(another);
}
