#pragma once

#include "undirected_graph.h"

/*
 * Simple utils for generating random undirected graphs.
 * In case any error std::runtime_error will be throwed.
 */

namespace random::graph::undirected {
    // Generates random graph with no loops and multiple-edges.
    template<typename random_t>
    UndirectedGraph randomNoLoopsAndMultipleEdges(int vertices, int edges, random_t &rng);
} // namespace random::graph::undirected
