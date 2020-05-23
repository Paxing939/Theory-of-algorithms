#include <cmath>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

int data1[20010][10010];
int infinity = 100000000;

int p[10010];
int l[10010];

int main() {

    ifstream in("input.txt");
    ofstream out("output.txt");

    int size;
    in >> size;

    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < size; i++) {
        int lifetime, position;
        in >> position;
        in >> lifetime;

        l[i] = lifetime;
        p[i] = position;

        data1[i][i] = 0;
    }

    for (int k = 2; k < size * 2 + 2; k += 2) {
        for (int i = 0; i < size - k / 2; i++) {
            int first = data1[k - 2][i];
            int second = data1[k - 1][i];

            int wayFromFirst = first + (p[i + k / 2] - p[i + k / 2 - 1]);
            int wayFromSecond = second + (p[k / 2 + i] - p[i]);

            data1[k][i] = min(wayFromFirst, wayFromSecond);
            if (data1[k][i] > l[i + k / 2]) {
                data1[k][i] = infinity;
            }

            first = data1[k - 2][i + 1];
            second = data1[k - 1][i + 1];

            wayFromFirst = first + p[i + k / 2] - p[i];
            wayFromSecond = second + p[i + 1] - p[i];

            data1[k + 1][i] = min(wayFromFirst, wayFromSecond);
            if (data1[k + 1][i] > l[i]) {
                data1[k + 1][i] = infinity;
            }
        }
    }

    long result = min(data1[size * 2 - 2][0], data1[size * 2 - 1][0]);

    if (result != infinity) {
        out << result;
    } else {
        out << "No solution";
    }

    return 0;
}
