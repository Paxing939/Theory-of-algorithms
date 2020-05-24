#include <vector>
#include <algorithm>
#include <fstream>

int64_t infinity = std::numeric_limits<int32_t>::max();

struct Edge {
    int64_t destination_vertex;
    int64_t capacity;
    int64_t cost;
    int64_t amount_of_flow;
    int64_t back_vertex;

    Edge() : Edge(0, 0, 0, 0, 0) {}

    Edge(int64_t destination_vertex, int64_t capacity, int64_t cost, int64_t amount_of_flow, int64_t back_vertex)
            : destination_vertex(destination_vertex), capacity(capacity), cost(cost), amount_of_flow(amount_of_flow),
              back_vertex(back_vertex) {}
};

class Graph {
public:
    Graph(int64_t n) : graph_(std::vector<std::vector<Edge>>(n)) {}

    void AddEdge(int64_t start_vertex, int64_t end_vertex, int64_t capacity, int64_t cost) {
        graph_[start_vertex].emplace_back(end_vertex, capacity, cost, 0, graph_[end_vertex].size());
        graph_[end_vertex].emplace_back(start_vertex, 0, -cost, 0, graph_[start_vertex].size());
    }

    int64_t GetMinCostKFlow(int64_t k, int64_t source, int64_t target) {
        int64_t flow = 0, cost = 0;
        while (flow < k) {
            std::vector<int64_t> id(graph_.size());
            std::vector<int64_t> distances(graph_.size(), infinity);
            std::vector<int64_t> queue(graph_.size());
            std::vector<int64_t> parents(graph_.size());
            std::vector<int64_t> parent_edge_indexes(graph_.size());
            int64_t queue_head = 0, queue_tail = 0;
            queue[queue_tail++] = source;
            distances[source] = 0;

            while (queue_head != queue_tail) {
                int64_t v = queue[queue_head++];
                id[v] = 2;
                if (queue_head == graph_.size()) {
                    queue_head = 0;
                }
                for (int64_t i = 0; i < graph_[v].size(); ++i) {
                    Edge &edge = graph_[v][i];
                    if (edge.amount_of_flow < edge.capacity &&
                        distances[v] + edge.cost < distances[edge.destination_vertex]) {
                        distances[edge.destination_vertex] = distances[v] + edge.cost;
                        if (id[edge.destination_vertex] == 0) {
                            queue[queue_tail++] = edge.destination_vertex;
                            if (queue_tail == graph_.size()) {
                                queue_tail = 0;
                            }
                        } else if (id[edge.destination_vertex] == 2) {
                            if (--queue_head == -1) {
                                queue_head = static_cast<int64_t>(graph_.size()) - 1;
                            }
                            queue[queue_head] = edge.destination_vertex;
                        }
                        id[edge.destination_vertex] = 1;
                        parents[edge.destination_vertex] = v;
                        parent_edge_indexes[edge.destination_vertex] = i;
                    }
                }
            }

            if (distances[target] == infinity) {
                break;
            }
            int64_t add_flow = k - flow;

            for (int64_t v = target; v != source; v = parents[v]) {
                int64_t parent = parents[v];
                int64_t parent_edge = parent_edge_indexes[v];
                add_flow = std::min(add_flow,
                              graph_[parent][parent_edge].capacity - graph_[parent][parent_edge].amount_of_flow);
            }

            for (int64_t v = target; v != source; v = parents[v]) {
                int64_t parent = parents[v];
                int64_t parent_edge = parent_edge_indexes[v];
                int64_t edge = graph_[parent][parent_edge].back_vertex;
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

    int64_t n, k = infinity;
    int64_t s, t, towers, factories;
    reader >> towers >> factories;
    n = towers + factories + 2;
    s = 0;
    t = n - 1;

    Graph full_graph(n);
    for (int64_t i = 0; i < towers; ++i) {
        int64_t u;
        reader >> u;
        full_graph.AddEdge(0, i + 1, u, 0);
    }

    std::vector<int64_t> factory_to_target(factories);
    for (int64_t i = 0; i < factories; ++i) {
        int64_t u;
        reader >> u;
        factory_to_target[i] = u;
    }

    for (int64_t i = 0; i < towers; ++i) {
        for (int64_t j = 0; j < factories; ++j) {
            int64_t c;
            reader >> c;
            full_graph.AddEdge(i + 1, towers + j + 1, infinity, c);
        }
    }

    for (int64_t i = 0; i < factories; ++i) {
        full_graph.AddEdge(towers + i + 1, n - 1, factory_to_target[i], 0);
    }

    writer << full_graph.GetMinCostKFlow(k, s, t);
}
