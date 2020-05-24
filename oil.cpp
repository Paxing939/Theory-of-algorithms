#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Edge {
    int destination_vertex;
    int capacity;
    int cost;
    int amount_of_flow;
    size_t back_vertex;

    Edge() : Edge(0, 0, 0, 0, 0) {}

    Edge(int destination_vertex, int capacity, int cost, int amount_of_flow, size_t back_vertex)
            : destination_vertex(destination_vertex), capacity(capacity), cost(cost), amount_of_flow(amount_of_flow),
              back_vertex(back_vertex) {}
};

class Graph {
public:
    Graph(int n) : graph_(std::vector<std::vector<Edge>>(n)) {}

    void AddEdge(int start_vertex, int end_vertex, int capacity, int cost) {
        graph_[start_vertex].emplace_back(end_vertex, capacity, cost, 0, graph_[end_vertex].size());
        graph_[end_vertex].emplace_back(start_vertex, 0, -cost, 0, graph_[start_vertex].size());
    }

    int GetMinCostKFlow(int k, int source, int target) {
        int flow = 0, cost = 0;
        while (flow < k) {
            vector<int> id(graph_.size());
            vector<int> distances(graph_.size(), std::numeric_limits<int>::max());
            vector<int> queue(graph_.size());
            vector<int> parents(graph_.size());
            vector<size_t> parent_edge_indexes(graph_.size());
            int queue_head = 0, queue_tail = 0;
            queue[queue_tail++] = source;
            distances[source] = 0;

            while (queue_head != queue_tail) {
                int v = queue[queue_head++];
                id[v] = 2;
                if (queue_head == graph_.size()) {
                    queue_head = 0;
                }
                for (size_t i = 0; i < graph_[v].size(); ++i) {
                    Edge &edge = graph_[v][i];
                    if (edge.amount_of_flow < edge.capacity &&
                        distances[v] + edge.cost < distances[edge.destination_vertex]) {
                        distances[edge.destination_vertex] = distances[v] + edge.cost;
                        if (id[edge.destination_vertex] == 0) {
                            queue[queue_tail++] = edge.destination_vertex;
                            if (queue_tail == graph_.size()) queue_tail = 0;
                        } else if (id[edge.destination_vertex] == 2) {
                            if (--queue_head == -1) queue_head = static_cast<int>(graph_.size()) - 1;
                            queue[queue_head] = edge.destination_vertex;
                        }
                        id[edge.destination_vertex] = 1;
                        parents[edge.destination_vertex] = v;
                        parent_edge_indexes[edge.destination_vertex] = i;
                    }
                }
            }

            if (distances[target] == std::numeric_limits<int>::max()) break;
            int add_flow = k - flow;

            for (int v = target; v != source; v = parents[v]) {
                int parent = parents[v];
                size_t parent_edge = parent_edge_indexes[v];
                add_flow = min(add_flow,
                              graph_[parent][parent_edge].capacity - graph_[parent][parent_edge].amount_of_flow);
            }

            for (int v = target; v != source; v = parents[v]) {
                int parent = parents[v];
                size_t parent_edge = parent_edge_indexes[v];
                size_t edge = graph_[parent][parent_edge].back_vertex;
                graph_[parent][parent_edge].amount_of_flow += add_flow;
                graph_[v][edge].amount_of_flow -= add_flow;
                cost += graph_[parent][parent_edge].cost * add_flow;
            }
            flow += add_flow;
        }

        return cost;
    }

private:
    std::vector<std::vector<Edge>> graph_;
};

int main() {
    std::ifstream reader("input.txt");
    std::ofstream writer("output.txt");

    int n, k = std::numeric_limits<int>::max();
    int s, t, towers, factories;
    reader >> towers >> factories;
    n = towers + factories + 2;
    s = 0;
    t = n - 1;

    Graph full_graph(n);
    for (int i = 0; i < towers; ++i) {
        int u;
        reader >> u;
        full_graph.AddEdge(0, i + 1, u, 0);
    }

    std::vector<int> factory_to_target(factories);
    for (int i = 0; i < factories; ++i) {
        int u;
        reader >> u;
        factory_to_target[i] = u;
    }

    for (int i = 0; i < towers; ++i) {
        for (int j = 0; j < factories; ++j) {
            int c;
            reader >> c;
            full_graph.AddEdge(i + 1, towers + j + 1, std::numeric_limits<int>::max(), c);
        }
    }

    for (int i = 0; i < factories; ++i) {
        full_graph.AddEdge(towers + i + 1, n - 1, factory_to_target[i], 0);
    }

    writer << full_graph.GetMinCostKFlow(k, s, t);
}
