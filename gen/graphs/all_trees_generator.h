#pragma once

#include "undirected_graph.h"

#include <vector>

/*
 * Generator of all size^(size - 2) numbered trees.
 * How to use:

AllTreesGenerator generator(size);
do {
    auto graph = generator.buildGraph();
    ...
} while (graph.next());
*/

namespace random::tree {
    class AllTreesGenerator {
    public:
        AllTreesGenerator(int size);
        UndirectedGraph buildGraph() const;
        bool next();

        // Returns the number of already builded graphs
        int buildedGraphs() const;

    private:
        int size_;
        std::vector<int> prufer_;
        int buildedGraphs_{0};
    };
} // namespace random::tree
