#include "undirected_graph.h"

#include "../global/global.h"

#include <algorithm>
#include <numeric>

UndirectedGraph::UndirectedGraph(int size) : size_(size) {}

UndirectedGraph::UndirectedGraph(int size, const std::vector<std::pair<int, int>> &edges)
    : size_(size)
    , edges_(edges)
{
    for (auto &[v, u] : edges_) {
        if (v > u) {
            std::swap(v, u);
        }
    }
    std::sort(edges_.begin(), edges_.end());
}

std::pair<int, int> UndirectedGraph::size() const {
    return {size_, edges_.size()};
}

std::vector<std::pair<int, int>> UndirectedGraph::edges() const {
    return edges_;
}

std::vector<std::vector<int>> UndirectedGraph::graph() const {
    std::vector<std::vector<int>> graph(size_);
    for (const auto &[v, u] : edges_) {
        graph[v].push_back(u);
        if (v != u) {
            graph[u].push_back(v);
        }
    }
    return graph;
}

bool UndirectedGraph::hasEdge(std::pair<int, int> edge) const {
    if (edge.first > edge.second) {
        std::swap(edge.first, edge.second);
    }
    return std::binary_search(edges_.begin(), edges_.end(), edge);
}

void UndirectedGraph::resize(int newSize) {
    if (newSize < size_) {
        auto newEnd = std::remove_if(edges_.begin(), edges_.end(), [this](const std::pair<int, int> &edge) {
            return edge.second >= size_;
        });
        edges_.erase(newEnd, edges_.end());
    }
    size_ = newSize;
}

bool UndirectedGraph::isTree() const {
    return int(edges_.size()) == size_ - 1 && components() == 1;
}

int UndirectedGraph::components() const {
    std::vector<int> parent(size_);
    std::iota(parent.begin(), parent.end(), 0);

    auto root = [&](auto self, int v) -> int {
        return parent[v] == v ? v : (parent[v] = self(self, parent[v]));
    };

    int components = size_;
    for (auto [v, u] : edges_) {
        v = root(root, v);
        u = root(root, u);
        if (v != u) {
            components--;
            parent[v] = u;
        }
    }
    return components;
}

std::vector<int> UndirectedGraph::getDegreeSequence() const {
    std::vector<int> degree(size_);
    for (const auto &[v, u] : edges_) {
        degree[v]++;
        degree[u]++;
    }
    return degree;
}

UndirectedGraph UndirectedGraph::mergeEdges(const UndirectedGraph &graph1, const UndirectedGraph &graph2, bool keepMultipleEdges) {
    global::assertf(graph1.size().first == graph2.size().first, "Can not merge two graphs on a different number of vertices");
    auto edges1 = graph1.edges();
    auto edges2 = graph1.edges();
    std::vector<std::pair<int, int>> mergedEdges(edges1.size() + edges2.size());
    std::merge(edges1.begin(), edges1.end(), edges2.begin(), edges2.end(), mergedEdges.begin());

    if (!keepMultipleEdges) {
        mergedEdges.erase(std::unique(mergedEdges.begin(), mergedEdges.end()), mergedEdges.end());
    }
    return UndirectedGraph(graph1.size().first, mergedEdges);
}
