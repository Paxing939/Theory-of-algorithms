#include <iostream>
#include <vector>

int SearchRight(const std::vector<int>& array, int key) {
    int l = 0, r = array.size(), m = 0;
    while (l < r - 1) {
        m = (l + r) / 2;
        if (array[m] < key) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

int SearchLeft(const std::vector<int>& array, int key) {
    int l = 0, r = array.size(), m = 0;
    while (l < r - 1) {
        m = (l + r) / 2;
        if (array[m] <= key) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int LowerBound(const std::vector<int>& numbers, int key) {
    int l = 0, r = numbers.size(), k = 0;
    while (l < r) {
        k = (l + r) / 2;
        if (key <= numbers[k]) {
            r = k;
        } else {
            l = k + 1;
        }
    }
    return l;
}

int UpperBound(const std::vector<int>& numbers, int key) {
    int l = 0, r = numbers.size(), k = 0;
    while (l < r) {
        k = (l + r) / 2;
        if (key < numbers[k]) {
            r = k;
        } else {
            l = k + 1;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    int tmp = 0;
    std::vector<int> numbers(n);
    for (auto& el : numbers) {
        std::cin >> el;
    }

    int k = 0, r = 0, l = 0;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        std::cin >> tmp;
        r = UpperBound(numbers, tmp);
        l = LowerBound(numbers, tmp);
        if (r == l) {
            std::cout << 0 << ' ' << l << ' ' << r << '\n';
        } else {
            std::cout << 1 << ' ' << l << ' ' << r << '\n';
        }
    }

    return 0;
}