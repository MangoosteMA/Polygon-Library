#include "trees_generators.h"

#include "../global/global.h"
#include "../random/random.h"

namespace random::tree {
    template<typename random_t>
    UndirectedGraph randomPruferCode(int vertices, random_t &rng) {
        global::assertf(vertices >= 0, "Negative number of vertices: " + std::to_string(vertices));
        if (vertices <= 1) {
            return UndirectedGraph(vertices);
        }
        if (vertices == 2) {
            return UndirectedGraph(vertices, {{0, 1}});
        }
        std::vector<int> prufer(vertices - 2);
        for (auto &vertex : prufer) {
            vertex = random::random(0, vertices, rng);
        }
        return decodePruferCode(prufer);
    }

    UndirectedGraph decodePruferCode(const std::vector<int> &prufer) {
        int vertices = prufer.size() + 2;
        std::vector<int> count(vertices);
        for (auto vertex : prufer) {
            count[vertex]++;
        }

        std::vector<std::pair<int, int>> edges;
        edges.reserve(vertices - 1);
        int pointer = 0;
        int option = -1;

        for (auto vertex : prufer) {
            if (option == -1) {
                while (count[pointer] > 0) {
                    pointer++;
                }
                option = pointer++;
            }
            edges.emplace_back(vertex, option);
            option = -1;
            if (--count[vertex] == 0 && vertex < pointer) {
                option = vertex;
            }
        }

        if (prufer.back() == vertices - 1) {
            while (count[pointer] > 0) {
                pointer++;
            }
            edges.emplace_back(pointer, vertices - 1);
        } else {
            edges.emplace_back(prufer.back(), vertices - 1);
        }
        return UndirectedGraph(vertices, edges);
    }

    template<typename random_t>
    UndirectedGraph randomPruferForest(int vertices, int edges, random_t &rng) {
        global::assertf(0 <= edges && edges < vertices, "[randomPruferForest] 0 <= edges < vertices must holds.");
        auto tree = randomPruferCode(vertices, rng).getEdges();
        random::shuffle(tree.begin(), tree.end(), rng);
        tree.resize(edges);
        return UndirectedGraph(vertices, tree);
    }
} // namespace random::tree
