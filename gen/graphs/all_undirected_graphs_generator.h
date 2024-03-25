#pragma once

#include "undirected_graph.h"

/*
 * Generator of all size^(size * (size - 1) / 2) numbered undirected graphs.
 * How to use:

AllUndirectedGraphsGenerator generator(size);
do {
    auto graph = generator.buildGraph();
    ...
} while (graph.next());
*/

namespace random::graph::undirected {
    class AllUndirectedGraphsGenerator {
    public:
        AllUndirectedGraphsGenerator(int size);
        UndirectedGraph buildGraph() const;
        bool next();

        // Returns the number of already builded graphs
        int buildedGraphs() const;

    private:
        int size_;
        int edgesMask_{0};
        int buildedGraphs_{0};
    };
} // namespace random::graph::undirected
