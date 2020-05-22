#include <iostream>
#include <vector>
#include <fstream>
#include <set>

class Shooting {
public:

    Shooting() {
        reader.open("input.txt");
        reader >> r >> c;
        g.resize(c);
        answer.resize(c);
        for (int i = 0; i < c; ++i) {
            int row_1, row_2;
            reader >> row_1 >> row_2;
            g[i] = {row_1 - 1, row_2 - 1};
        }
    }


    bool try_kuhn(int v) {
        if (used[v]) {
            return false;
        }

        used[v] = true;
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (mt[to] == -1 || try_kuhn(mt[to])) {
                mt[to] = v;
                return true;
            }
        }

        return false;
    }

    void Solve() {
        mt.assign(r, -1);
        std::vector<char> used1(c);
        for (int i = 0; i < c; ++i) {
            for (int j = 0; j < g[i].size(); ++j) {
                if (mt[g[i][j]] == -1) {
                    mt[g[i][j]] = i;
                    answer[i] = 1;
                    used1[i] = true;
                    break;
                }
            }
        }

        for (int i = 0; i < c; ++i) {
            if (used1[i]) {
                continue;
            }
            used.assign(c, false);
            try_kuhn(i);
        }
    }

    void Out() {
        writer.open("output.txt");

        for (int i = 0; i < r; ++i) {
            if (mt[i] != -1) {
                answer[mt[i]] = i + 1;
            }
        }

        for (const auto &el : answer) {
            writer << el << " ";
        }
    }

private:
    int c, r;
    std::vector<std::vector<int>> g;
    std::vector<char> used;
    std::vector<int> mt, answer;
    std::ifstream reader;
    std::ofstream writer;
};

int main() {
    Shooting shooting;
    shooting.Solve();
    shooting.Out();
}
