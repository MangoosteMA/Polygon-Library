#include "undirected_graphs_generators.h"

#include "../global/global.h"
#include "../random/random.h"

#include <set>
#include <vector>

namespace random::graph::undirected {
    template<typename random_t>
    UndirectedGraph randomNoLoopsAndMultipleEdges(int vertices, int edges, random_t &rng) {
        global::assertf(vertices >= 0, "Negative number of vertices: " + std::to_string(vertices));
        global::assertf(edges >= 0, "Negative number of edges: " + std::to_string(edges));
        long long maxNumberOfEdges = 1ll * vertices * (vertices - 1) / 2;
        global::assertf(edges <= maxNumberOfEdges, "There is no graph with " + std::to_string(vertices)
                                                 + " vertices and " + std::to_string(edges) + " edges.");

        if (edges * 2 > maxNumberOfEdges) {
            std::vector<std::pair<int, int>> options;
            options.reserve(maxNumberOfEdges);
            for (int v = 0; v < vertices; v++) {
                for (int u = v + 1; u < vertices; u++) {
                    options.emplace_back(v, u);
                }
            }
            random::shuffle(options.begin(), options.end(), rng);
            return UndirectedGraph(vertices, std::vector<std::pair<int, int>>(options.begin(), options.begin() + edges));
        }

        std::set<std::pair<int, int>> edgesSet;
        for (int i = 0; i < edges; i++) {
            int v, u;
            do {
                v = random::random(0, vertices, rng);
                u = random::random(0, vertices, rng);
            } while (v == u || !edgesSet.insert(std::minmax(v, u)).second);
        }
        return UndirectedGraph(vertices, std::vector<std::pair<int, int>>(edgesSet.begin(), edgesSet.end()));
    }
} // namespace random::graph::undirected
