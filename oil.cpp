#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

struct rib {
	int b, u, c, f;
	size_t back;
};

void add_rib(std::vector<std::vector<rib>> &g, int a, int b, int u, int c) {
	rib r1 = {b, u, c, 0, g[b].size()};
	rib r2 = {a, 0, -c, 0, g[a].size()};
	g[a].push_back(r1);
	g[b].push_back(r2);
}

int main() {
	std::ifstream reader("input.txt");
	int n, k = std::numeric_limits<int>::max(), towers, factories;
	reader >> towers >> factories;
	n = towers + factories + 2;

	std::vector<std::vector<rib>> g;
	int s = 0, t = n - 1;

	for (int i = 0; i < towers; ++i) {

	}



	int flow = 0, cost = 0;
	while (flow < k) {
		std::vector<int> id(n, 0);
		std::vector<int> d(n, std::numeric_limits<int>::max());
		std::vector<int> q(n);
		std::vector<int> p(n);
		std::vector<size_t> p_rib(n);
		int qh = 0, qt = 0;
		q[qt++] = s;
		d[s] = 0;
		while (qh != qt) {
			int v = q[qh++];
			id[v] = 2;
			if (qh == n) qh = 0;
			for (size_t i = 0; i < g[v].size(); ++i) {
				rib &r = g[v][i];
				if (r.f < r.u && d[v] + r.c < d[r.b]) {
					d[r.b] = d[v] + r.c;
					if (id[r.b] == 0) {
						q[qt++] = r.b;
						if (qt == n) qt = 0;
					} else if (id[r.b] == 2) {
						if (--qh == -1) qh = n - 1;
						q[qh] = r.b;
					}
					id[r.b] = 1;
					p[r.b] = v;
					p_rib[r.b] = i;
				}
			}
		}
		if (d[t] == std::numeric_limits<int>::max()) {
			break;
		}
		int add_flow = k - flow;
		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];
			size_t pr = p_rib[v];
			add_flow = std::min(add_flow, g[pv][pr].u - g[pv][pr].f);
		}
		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];
			size_t pr = p_rib[v], r = g[pv][pr].back;
			g[pv][pr].f += add_flow;
			g[v][r].f -= add_flow;
			cost += g[pv][pr].c * add_flow;
		}
		flow += add_flow;
	}

	// ... вывод результата ...

}