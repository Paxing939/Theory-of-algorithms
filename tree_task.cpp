#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

template<typename T>
class Tree {
public:
    Tree() : size_(0), root_(nullptr) {}

    void SetK(int k) { k_ = k; }

    bool Empty() {
        return !root_;
    }

    void Add(T element) {
        Node *node = root_;
        if (root_ == nullptr) {
            root_ = new Node;
            root_->key_ = element;
            root_->parent_ = nullptr;
            root_->left_ = nullptr;
            root_->right_ = nullptr;
            size_++;
            return;
        }

        while (true) {
            if (node->key_ > element) {
                if (node->left_ == nullptr) {
                    Node *tmp = new Node(element);
                    tmp->parent_ = node;
                    size_++;
                    node->left_ = tmp;
                    node = node->left_;
                    return;
                }
                node = node->left_;
                continue;
            }
            if (node->key_ < element) {
                if (node->right_ == nullptr) {
                    Node *tmp = new Node(element);
                    tmp->parent_ = node;
                    size_++;
                    node->right_ = tmp;
                    node = node->right_;
                    return;
                }
                node = node->right_;
                continue;
            }
            if (node->key_ == element) {
                return;
            }
        }

    }

    void Delete(T element) {
        Node *node = root_;

        if (root_->key_ == element) {
            root_ = DeleteNode(root_);
            return;
        }

        while (true) {
            if (node == nullptr) { return; }

            if (node->key_ > element) {
                if (node->left_->key_ == element) {
                    node->left_ = DeleteNode(node->left_);
                    return;
                }
                node = node->left_;
                continue;
            }
            if (node->key_ < element) {
                if (node->right_->key_ == element) {
                    node->right_ = DeleteNode(node->right_);
                    return;
                }
                node = node->right_;
                continue;
            }
        }
    }

    void DeleteMaxVertexes(int key_to_delete) {
        if (root_ == nullptr) {
            return;
        }

        LNRMark(root_, 0); // mark all vertexes

        root_->depth_ = Depth(root_);
        CountOtherDepths(root_, root_->depth_ + 1);

        NLRDeleteSemipath(root_);

        auto element_to_delete = std::max_element(vertex_hypotheses_.begin(), vertex_hypotheses_.end());
        if (element_to_delete != vertex_hypotheses_.end()) {
            Delete(*element_to_delete);
        }
    }

    void PrintTree(std::string file_name) {
        writer.open(file_name);
        if (root_ == nullptr) {
            writer << "No tree";
            return;
        }
        NLRForFile(root_);
    }

    void PrintTreeTest() {
        if (root_ == nullptr) {
            test_stream << "No tree";
            return;
        }
        NLRForTest(root_);
    }

    void PrintTree(std::ostream &out) {
        NLRWithVector(root_);

        for (const auto &key : elements_) {
            out << key << '\n';
        }
    }

    const std::stringstream &getWriter() const {
        return test_stream;
    }

private:
    struct Node {
        Node()  : height_(0) {}

        explicit Node(T element) : key_(element), left_(nullptr), right_(nullptr), height_(0), parent_(nullptr) {}

        long long height_, depth_;
        T key_;
        Node *left_, *right_, *parent_;
    };

    int Depth(Node* node) {
        int depth = 0;
        if (node != nullptr) {
            depth = std::max(Depth(node->left_) + 1, Depth(node->right_) + 1);
        }
        return depth;
    }

    void CountOtherDepths(Node *node, long long depth) {
        if (node == nullptr) {
            return;
        }
        node->depth_ = --depth;
        CountOtherDepths(node->left_, depth);
        CountOtherDepths(node->right_, depth);

    }

    void NLRDeleteSemipath(Node *node) {
        if (node == nullptr) {
            return;
        }

        if (CheckVertex(node)) {
            vertex_hypotheses_.push_back(node->key_);
        }

        NLRDeleteSemipath(node->left_);
        NLRDeleteSemipath(node->right_);
    }

    bool CheckVertex(Node *node) {
        long long node_height = node->height_;
        int depth = 0, k_tmp = 0;
        Node* parent = node;

        int path = 0;

        if (node->key_ == 2) {
            //std::cerr << "abracadabra!\n";
        }

        path += node->height_;
        if (path >= k_) {
            return false;
        }

        int tmp = 0;
        if (node->left_ != nullptr) {
            tmp += node->left_->height_ + 1;
        }
        if (node->right_ != nullptr) {
            tmp += node->right_->height_ + 1;
        }
        if (tmp >= k_) {
            return false;
        }

        while (true) {
            depth++;
            parent = parent->parent_;
            if (parent == nullptr) {
                break;
            }

            int max_path = node->height_ + depth;
            if (max_path >= k_) {
                return false;
            }

            if (node->key_ > parent->key_) {
                if (parent->left_ != nullptr) {

                    max_path += parent->left_->height_ + 1;
                    k_tmp = parent->left_->height_ + 1 + depth;

                    if (k_tmp >= k_ || max_path >= k_) {
                        return false;
                    }
                }
            } else {
                if (parent->right_ != nullptr) {

                    max_path += parent->right_->height_ + 1;
                    k_tmp = parent->right_->height_ + 1 + depth;

                    if (k_tmp >= k_ || max_path >= k_) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void LNRMark(Node *node, long long h) {
        if (node == nullptr) {
            return;
        }

        LNRMark(node->left_, h);
        LNRMark(node->right_, h);

        if (node->left_ == nullptr && node->right_ == nullptr) {
            node->height_ = 0;
        }
        if (node->left_ != nullptr && node->right_ == nullptr) {
            node->height_ = node->left_->height_ + 1;
        }
        if (node->left_ == nullptr && node->right_ != nullptr) {
            node->height_ = node->right_->height_ + 1;
        }
        if (node->left_ != nullptr && node->right_ != nullptr) {
            node->height_ = std::max(node->right_->height_ + 1, node->left_->height_ + 1);
        }
    }

    void NLRWithVector(Node *node) {
        if (node == nullptr) {
            return;
        }
        elements_.push_back(node->key_);
        NLRWithVector(node->left_);
        NLRWithVector(node->right_);
    }

    void NLRForFile(Node *node) {
        if (node == nullptr) {
            return;
        }
        writer << node->key_ << '\n';
//        writer << node->key_ << ", height: " << node->height_ << ", depth: " << node->depth_ << '\n';
        NLRForFile(node->left_);
        NLRForFile(node->right_);
    }

    void NLRForTest(Node *node) {
        if (node == nullptr) {
            return;
        }
        test_stream << node->key_ << ' ';
        NLRForTest(node->left_);
        NLRForTest(node->right_);
    }

    Node *DeleteNode(Node *node) {
        if (node->left_ == nullptr) {
            if (node->right_ == nullptr) {
                return nullptr;
            } else {
                return node->right_;
            }
        } else {
            if (node->right_ == nullptr) {
                return node->left_;
            }
        }

        if (node->right_->left_ == nullptr) {
            node->right_->left_ = node->left_;
            return node->right_;
        }

        Node *tmp = node->right_;
        while (true) {
            if (tmp->left_->left_ == nullptr) {
                break;
            }
            tmp = tmp->left_;
        }
        node->key_ = tmp->left_->key_;
        tmp->left_ = tmp->left_->right_;
        return node;
    }

    std::vector<T> elements_, vertex_hypotheses_;
    std::ofstream writer;
    std::stringstream test_stream;
    Node *root_;
    long long size_, k_;
};

int main() {
    std::ifstream reader("tst.in");
    Tree<int> tree;

    int number = 0, number_to_delete = 0;
    reader >> number_to_delete;
    tree.SetK(number_to_delete);

    while (!reader.eof()) {
        reader >> number;
        tree.Add(number);
    }

    if (tree.Empty()) {
        std::ofstream writer("tst.out");
        return 0;
    }

    tree.DeleteMaxVertexes(number_to_delete);
    tree.PrintTree("tst.out");

    return 0;
}

//int main() {
//    std::vector<std::string> tests = {
//                                       "6 5 3 1 0 6 4 8 2 7 9",
//                                       "5 5 3 1 0 6 4 8 2 7 9",
//                                       "2 5 3 1 0 6 4 8 2 7 9",
//                                       "1 5 3 1 0 6 4 8 2 7 9",
//                                       "7 5 3 1 0 6 4 8 2 7 9",
//                                       "7 5 3 1 0 6 4 8 2",
//                                       "7 5 3 1 0 4 2",
//                                       "0 5 3 1 0 4 2",
//                                       "6 5",
//                                       "4 5 3 1 6",
//                                       "6 10 3 2 1 5 6 7 8 11", // 11
//                                       "6 1 2 3 4 5 6 7 8 9 10",
//                                       "6 5 4 3 2 1",
//                                       "11 5 4 3 2 1 6 7 8 9",
//                                       "4 1 5 3 7 2 4 6 8",
//                                       "4 50 25 30 31 32 27 26 28",
//                                       "9 0 4 5 6 7 8 9 3 1",
//                                       "5 1 10 2 8 5",
//                                       "5 3 2 1 4 5 6",
//                                       "5 10 5 20 4 8 14 22 6",
//                                       "6 0 -1 1 2 100 101 102 103 3",
//                                       "8 2 10 1 9 3 6 5 7 4 8",
//                                       "9 16 8 11 19 17 1 12 18 3 5 4 2 15 13 14 7 6",
//                                       "7 18 23 20 21 7 10 9 3 29 26 30 12 1 6",
//                                       "7 18 23 20 21 7 10 9 3 29 26 30 12 1 6 19",
//                                       "7 2 1 7 5 6 3 4 12 13 9 8 11 10",
//                                       "6 2 1 6 7 8 9 5 4",
//                                       "5 20 15 16 10 9 12 11 13",
//                                       "6 3 1 4 2 6 5 10 9 11 7 12 13 8",
//                                       "8 3 1 4 2 12 8 7 10 5 9 11 6",
//                                       "5 5 2 1 6 7",
//                                       "6 3 2 1 8 7 10 33 12 42 81",
//                                       "8 10 7 12 3 9 11 2 4 8 1 6 5"
//                                       };
//    std::vector<std::string> answers = {
//                                         "5 3 1 0 2 6 8 7 9 ",
//                                         "5 3 1 0 2 4 6 8 7 9 ",
//                                         "5 3 1 0 2 4 6 8 7 9 ",
//                                         "5 3 1 0 2 4 6 8 7 9 ",
//                                         "5 3 1 0 2 4 6 8 7 ",
//                                         "5 3 1 0 2 4 6 ",
//                                         "3 1 0 2 4 ",           // 6
//                                         "5 3 1 0 2 4 ",
//                                         "No tree",
//                                         "5 3 1 ",
//                                         "10 3 2 1 5 6 7 8 11 ",
//                                         "1 2 3 4 5 6 7 8 9 10 ", // 11
//                                         "4 3 2 1 ",
//                                         "5 4 3 2 1 6 7 8 ",
//                                         "5 3 2 4 7 6 8 ",
//                                         "50 25 30 27 26 28 31 32 ",
//                                         "0 4 3 1 5 6 7 8 ", // 15
//                                         "1 2 8 5 ",
//                                         "3 2 1 4 5 6 ",
//                                         "10 5 8 6 20 14 22 ",
//                                         "0 -1 1 2 100 101 102 103 ",
//                                         "2 1 9 3 6 5 4 7 8 ",
//                                         "16 8 1 3 5 4 7 6 11 12 15 13 14 19 17 18 ",
//                                         "18 7 3 1 6 10 9 12 23 20 21 29 26 ",
//                                         "18 7 3 1 6 10 9 12 23 20 19 21 29 26 ",
//                                         "2 1 7 5 3 4 6 12 9 8 11 10 ",
//                                         "2 1 6 5 4 7 8 ",
//                                         "15 10 9 12 11 13 16 ",
//                                         "3 1 2 4 6 10 9 7 8 11 12 13 ",
//                                         "3 1 2 4 12 8 7 5 6 10 9 ",
//                                         "5 2 1 6 ",
//                                         "3 2 1 8 10 33 12 42 81 ",
//                                         "10 7 3 1 9 4 8 6 5 12 11 "
//    };
//
//    if (tests.size() != answers.size()) {
//        std::cerr << "tests.size() != answers.size()\n";
//        return 1;
//    }
//
//    for (int i = 0; i < tests.size(); i++) {
//        Tree<int> tree;
//        std::stringstream reader(tests[i]);
//        int number = 0, number_to_delete = 0;
//        reader >> number_to_delete;
//        tree.SetK(number_to_delete);
//
//        while (!reader.eof()) {
//            reader >> number;
//            tree.Add(number);
//        }
//
//        tree.DeleteMaxVertexes(number_to_delete);
//        tree.PrintTreeTest();
//        if (tree.getWriter().str() == answers[i]) {
//            std::cerr << "Test " << i << " completed\n";
//        } else {
//            std::cerr << "Test " << i << " failed\n" << tree.getWriter().str() << "watch probel\n";
//            return 2;
//        }
//    }
//    return 0;
//}