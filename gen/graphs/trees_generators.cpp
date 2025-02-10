#include "trees_generators.h"

#include "../global/global.h"
#include "../random/random.h"

#include <algorithm>
#include <functional>
#include <numeric>

namespace random::tree {
    template<typename random_t>
    UndirectedGraph randomPruferCode(int vertices, random_t &rng) {
        global::assertf(vertices >= 0, "[randomPruferCode] Negative number of vertices: " + std::to_string(vertices));
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

        if (vertices == 2 || prufer.back() == vertices - 1) {
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

    template<typename random_t>
    UndirectedGraph bamboo(int vertices, int root, bool shuffle, random_t &rng) {
        global::assertf(-1 <= root && root < vertices, "[bamboo] root must be from interval [-1, n).");
        if (vertices == 0) {
            return UndirectedGraph();
        }

        if (root == -1) {
            root = random::random(0, vertices, rng);
        }

        std::vector<int> order(vertices);
        std::iota(order.begin(), order.end(), 0);
        std::swap(order[root], order[0]);

        if (shuffle) {
            random::shuffle(order.begin() + 1, order.end(), rng);
        }

        std::vector<std::pair<int, int>> edges(vertices - 1);
        for (int i = 0; i + 1 < vertices; i++) {
            edges[i] = std::make_pair(order[i], order[i + 1]);
        }
        return UndirectedGraph(vertices, edges);
    }

    template<typename random_t>
    UndirectedGraph star(int vertices, int root, random_t &rng) {
        global::assertf(-1 <= root && root < vertices, "[star] root must be from interval [-1, n).");
        if (vertices == 0) {
            return UndirectedGraph();
        }

        if (root == -1) {
            root = random::random(0, vertices, rng);
        }
        std::vector<std::pair<int, int>> edges;
        edges.reserve(vertices - 1);
        for (int i = 0; i < vertices; i++) {
            if (i != root) {
                edges.emplace_back(i, root);
            }
        }
        return UndirectedGraph(vertices, edges);
    }

    std::vector<int> decodeParentArray(const UndirectedGraph &graph, int root) {
        global::assertf(graph.isTree(), "[decodeParentArray] Can't decode parents for non-tree graph.");

        const auto g = graph.graph();
        std::vector<int> parents(graph.size().first, -1);
        int free_index = 0;

        std::function<void(int, int)> dfs = [&](int v, int p) -> void {
            int index = free_index;
            free_index++;
            for (auto u : g[v]) {
                if (u != p) {
                    parents[free_index] = index;
                    dfs(u, v);
                }
            }
        };

        dfs(root, root);
        return parents;
    }
} // namespace random::tree
