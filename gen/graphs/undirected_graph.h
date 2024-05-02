#pragma once

#include <utility>
#include <vector>

class UndirectedGraph {
public:
    UndirectedGraph(int size = 0);
    UndirectedGraph(int size, const std::vector<std::pair<int, int>> &edges);

    // (number of vertices, number of edges)
    std::pair<int, int> size() const;
    std::vector<std::pair<int, int>> edges() const;
    std::vector<std::vector<int>> graph() const;
    bool hasEdge(std::pair<int, int> edge) const;

    // Removes all edges, that became invalid
    void resize(int newSize);
    bool isTree() const;
    int components() const;
    std::vector<int> getDegreeSequence() const;

    // Merge edges of two graphs on the same vertices
    static UndirectedGraph mergeEdges(const UndirectedGraph &graph1, const UndirectedGraph &graph2, bool keepMultipleEdges);

private:
    int size_;
    std::vector<std::pair<int, int>> edges_;
};
