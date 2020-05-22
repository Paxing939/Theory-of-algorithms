#include <iostream>
#include <vector>
#include <fstream>
#include <set>

class Shooting {
public:
	Shooting(int r, int c, std::istream &in) : r(r), c(c) {
		g.resize(c);
		for (int i = 0; i < c; ++i) {
			int row_1, row_2;
			in >> row_1 >> row_2;
			g[i] = {row_1, row_2};
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

	int r, c;
	std::vector<std::vector<int>> g;
	std::vector<int> mt;
	std::vector<char> used{};
};

int main() {
	std::ofstream writer("output.txt");
	std::ifstream reader("input.txt");

	int r, c;
	reader >> r >> c;
	Shooting shooting(r, c, reader);

	shooting.mt.assign(r, -1);
	for (int v = 0; v < c; ++v) {
		shooting.used.assign(c, false);
		shooting.try_kuhn(v);
	}

	std::set<int> s;
	std::vector<int> v(c);
	for (int i = 0, p = 0; i < r; ++i) {
		if (shooting.mt[i] != -1) {
			int size = s.size();
			s.insert(i + 1);
			if (s.size() != size) {
				v[p++] = i + 1;
				size++;
			}

			s.insert(shooting.mt[i] + 1);
			if (s.size() != size) {
				v[p++] = shooting.mt[i] + 1;
			}
		}
	}

	if (s.size() < c) {
		writer << "No";
	} else {
		for (const auto &el : v) {
			writer << el << " ";
		}
	}
}
