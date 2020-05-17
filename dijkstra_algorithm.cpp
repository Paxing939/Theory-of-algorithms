#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

int main() {
	std::ofstream writer("output.txt");
	std::ifstream reader("input.txt");
	int64_t n, m;
	reader >> n >> m;

	int64_t vertex1, vertex2, weight;
	std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(n);
	for (int64_t i = 0; i < m; ++i) {
		reader >> vertex1 >> vertex2 >> weight;
		graph[vertex1 - 1].push_back({vertex2 - 1, weight});
		graph[vertex2 - 1].push_back({vertex1 - 1, weight});
	}

	int64_t s = 0;
	std::vector<int64_t> d(n, std::numeric_limits<int64_t>::max());
	d[s] = 0;
	std::set<std::pair<int64_t, int64_t>> q;
	q.insert({d[s], s});
	while (!q.empty()) {
		int64_t v = q.begin()->second;
		q.erase(q.begin());

		for (size_t j = 0; j < graph[v].size(); ++j) {
			int64_t to = graph[v][j].first, len = graph[v][j].second;

			if (d[v] + len < d[to]) {
				q.erase({d[to], to});
				d[to] = d[v] + len;
				q.insert({d[to], to});
			}
		}
	}

	writer << d.back();
	return 0;
}
