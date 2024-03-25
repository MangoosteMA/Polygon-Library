#pragma once

#include "undirected_graph.h"

namespace random::tree {
    // Generates completely random numbered tree
    template<typename random_t>
    UndirectedGraph randomPruferCode(int vertices, random_t &rng);

    // Decodes Prufer code.
    UndirectedGraph decodePruferCode(const std::vector<int> &prufer);

    // Generates random forest with 'edges' edges by using randomPruferCode and removing random extra edges.
    template<typename random_t>
    UndirectedGraph randomPruferForest(int vertices, int edges, random_t &rng);
} // namespace random::tree
