#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <ctime>
#include <queue>
#include <algorithm>

const int CONNECTED = -1;
const int NOEDGES = -2;

class Pair {
public:
    int first_;
    int second_;

    Pair() {
        first_ = 0;
        second_ = 0;
    }

    Pair(int first, int second) {
        first_ = first;
        second_ = second;
    }
};


void connectivityComponentToSequence(int currentVertex, int previousVertex, std::vector<bool> &connected,
                                     std::vector<std::vector<Pair>> &adjacencyList, std::vector<int> &sequence) {

    connected[currentVertex] = true;
    for (Pair &adjacentVertex : adjacencyList.at(currentVertex)) {
        if (adjacentVertex.second_ != previousVertex && !connected[adjacentVertex.first_]) {
            sequence[adjacentVertex.second_] = adjacentVertex.first_;
            connectivityComponentToSequence(adjacentVertex.first_, adjacentVertex.second_, connected, adjacencyList,
                                            sequence);
        }

        if (connected[adjacentVertex.first_] && sequence[adjacentVertex.second_] == NOEDGES) {
            sequence[adjacentVertex.second_] = adjacentVertex.first_;
        }
    }
}

int dfs(int currentVertex, int previousVertex, std::vector<bool> &visited, std::vector<bool> &connected,
        std::vector<std::vector<Pair>> &adjacencyList, std::vector<int> &sequence,
        std::deque<int64_t> &CCcomponentVertexes) {

    visited[currentVertex] = true;

    for (Pair &adjacentVertex : adjacencyList.at(currentVertex)) {
        if (adjacentVertex.second_ != previousVertex) {
            if (visited[adjacentVertex.first_]) {

                sequence[adjacentVertex.second_] = adjacentVertex.first_;
                CCcomponentVertexes.push_back(currentVertex);

                return adjacentVertex.first_;
            }

            int tempVertex = dfs(adjacentVertex.first_, adjacentVertex.second_, visited, connected, adjacencyList,
                                 sequence, CCcomponentVertexes);

            if ((tempVertex != NOEDGES && tempVertex != CONNECTED)) {

                sequence[adjacentVertex.second_] = adjacentVertex.first_;
                connected[currentVertex] = true;
                CCcomponentVertexes.push_back(currentVertex);

                if (tempVertex != currentVertex) {
                    return tempVertex;
                } else {
                    while (!CCcomponentVertexes.empty()) {
                        int64_t top = CCcomponentVertexes.front();
                        CCcomponentVertexes.pop_front();
                        connectivityComponentToSequence(top, NOEDGES, connected, adjacencyList, sequence);
                    }
                    return CONNECTED;
                }
            }

            if (tempVertex == CONNECTED) {
                return CONNECTED;
            }
        }
    }

    if (previousVertex == NOEDGES) {
        std::ofstream writer("output.txt");
        writer << "No";
        return -10;
    }
    return NOEDGES;
}

int run() {
    int r, c;
    std::ifstream reader("input.txt");
    reader >> r >> c;

    std::vector<std::vector<Pair>> adjacencyList(r);

    std::vector<int> sequence(c);
    std::vector<bool> visited(r, false);
    std::vector<bool> connected(r, false);

    int i, from, to;
    for (i = 0; i < c; ++i) {
        sequence[i] = NOEDGES;
        reader >> from >> to;
        from--, to--;
        adjacencyList.at(from).push_back({to, i});
        adjacencyList.at(to).push_back({from, i});
    }

    int q = 0;
    std::deque<int64_t> CCcomponentVertexes;
    for (i = 0; i < r; ++i) {
        if (!(visited[i] | connected[i])) {
            q = dfs(i, NOEDGES, visited, connected, adjacencyList, sequence, CCcomponentVertexes);
        }
    }

    std::ofstream writer("output.txt");
    if (q == -10) {
        writer << "No";
        return 0;
    }
    for (i = 0; i < c; ++i) {
        writer << sequence[i] + 1 << ' ';
    }

    return 0;
}

std::string ReadWholeFile(std::string filename) {
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

class Shooting {
public:

    Shooting() {
        reader.open("input.txt");
        reader >> r >> c;
        g.resize(c);
        answer.resize(c, -1);
        for (int i = 0; i < c; ++i) {
            int row_1, row_2;
            reader >> row_1 >> row_2;
            g[i] = {row_1 - 1, row_2 - 1};
            std::sort(g[i].begin(), g[i].end());
        }
        reader.close();
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
        if (r > c) {
            return;
        }
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
        for (int i=0; i<r; ++i)
            if (mt[i] != -1)
                printf ("%d %d\n", mt[i]+1, i+1);
    }

    void Out() {
        writer.open("output.txt");

        for (int i = 0; i < r; ++i) {
            if (mt[i] != -1) {
                answer[mt[i]] = i + 1;
            }
        }

//        if (r == 2) {
//            answer.resize(c, 1);
//        }

        if (r < c) {
            int counter = 0;
            for (int i = 0; i < c; ++i) {
                if (answer[i] != -1) {
                    counter++;
                }
            }
            if (counter == r) {
                for (int i = 0; i < c; ++i) {
                    if (answer[i] == -1) {
                        answer[i] = g[i][0] + 1;
                    }
                }
            }
        }

        for (const auto &el : answer) {
            if (el == -1) {
                writer << "No";
                writer.close();
                return;
            }
        }

        for (const auto &el : answer) {
            writer << el << " ";
        }

        writer.close();
    }

private:
    int c, r;
    std::vector<std::vector<int>> g;
    std::vector<char> used;
    std::vector<int> mt, answer;
    std::ifstream reader;
    std::ofstream writer;
};

void Generator() {
    int n = 10;

    srand(time(nullptr));
    for (int i = 0; i < n; ++i) {
//        int p = rand() % 10 + 2, p2 = rand() % 10 + 2;
        int p = rand() % 10 + 2; int p2 = p;
        std::ofstream writer_input("input.txt");
        writer_input << p << " " << p2 << '\n';
        for (int j = 0; j < p2; ++j) {
            int tmp1 = rand() % p + 1;
            writer_input << tmp1 << " ";
            int tmp2 = rand() % p + 1;
            while(tmp1 == tmp2) {
                tmp2 = rand() % p + 1;
            }
            writer_input << tmp2 << "\n";
        }
        writer_input.close();

        Shooting shooting;
        shooting.Solve();
        shooting.Out();
        std::string my_algorithm = ReadWholeFile("output.txt");

        run();
        std::string correct_answer = ReadWholeFile("output.txt");
        if (my_algorithm == correct_answer) {
            std::cout << "Test #" << i + 1 << " completed\n";
        } else {
            std::cout << "Test #" << i + 1 << " failed\n";
            std::ofstream writer("log.txt");
            writer << my_algorithm;
            writer << "-------------\n";
            writer << correct_answer;
            writer << "-------------\n";
            return;
        }
    }

}

int main() {
//    Generator();
    Shooting shooting;
    shooting.Solve();
    shooting.Out();
 }
