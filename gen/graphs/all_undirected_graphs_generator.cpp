#include "all_undirected_graphs_generator.h"

#include <utility>
#include <vector>

namespace random::graph::undirected {
    AllUndirectedGraphsGenerator::AllUndirectedGraphsGenerator(int size) : size_(size) {}

    UndirectedGraph AllUndirectedGraphsGenerator::buildGraph() const {
        std::vector<std::pair<int, int>> edges;
        edges.reserve(__builtin_popcount(edgesMask_));

        std::pair<int, int> currentPair{0, 1};
        for (int mask = edgesMask_; mask != 0; mask >>= 1) {
            if (mask % 2 == 1) {
                edges.push_back(currentPair);
            }
            if (++currentPair.second == size_) {
                currentPair.first++;
                currentPair.second = currentPair.first + 1;
            }
        }
        return UndirectedGraph(size_, edges);
    }

    bool AllUndirectedGraphsGenerator::next() {
        int pairs = size_ * (size_ - 1) / 2;
        if (pairs <= 60 && edgesMask_ + 1 == (1ll << pairs)) {
            return false;
        }

        edgesMask_++;
        buildedGraphs_++;
        return true;
    }

    int AllUndirectedGraphsGenerator::buildedGraphs() const {
        return buildedGraphs_;
    }
} // namespace random::graph::undirected
