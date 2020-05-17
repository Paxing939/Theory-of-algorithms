#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>

int main() {
    int n = 0;

    std::ifstream reader("input.txt");
    std::ofstream writer("output.txt");
    reader >> n;

    std::stack<int> stack;
    double unused_coord;
    int pipe = 0;
    for (int i = 0; i < n; ++i) {
        bool push = true;
        reader >> unused_coord >> unused_coord >> pipe;
        if (!stack.empty()) {
            if (stack.top() == pipe) {
                stack.pop();
                push = false;
            }
        }
        if (push) {
            stack.push(pipe);
        }
    }

    if (stack.empty()) {
        writer << "Yes";
    } else {
        writer << "No";
    }

    return 0;
}