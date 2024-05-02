#pragma once

#include "undirected_graph.h"

#include <vector>

namespace random::tree {
    // Generates completely random numbered tree
    template<typename random_t>
    UndirectedGraph randomPruferCode(int vertices, random_t &rng);

    // Decodes Prufer code.
    UndirectedGraph decodePruferCode(const std::vector<int> &prufer);

    // Generates random forest with 'edges' edges by using randomPruferCode and removing random extra edges.
    template<typename random_t>
    UndirectedGraph randomPruferForest(int vertices, int edges, random_t &rng);

    // Returns parent array of size 'graph.size().first' where parent[0] = -1 and parent[i] < i (parent of vertex i)
    std::vector<int> decodeParentArray(const UndirectedGraph &graph, int root = 0);
} // namespace random::tree
