#include "all_trees_generator.h"

#include "trees_generators.h"

#include <algorithm>
#include <vector>

namespace random::tree {
    AllTreesGenerator::AllTreesGenerator(int size) : size_(size), prufer_(std::max(0, size_ - 2)) {}

    UndirectedGraph AllTreesGenerator::buildGraph() const {
        if (size_ <= 1) {
            return UndirectedGraph(size_);
        }
        if (size_ == 2) {
            return UndirectedGraph(size_, {{0, 1}});
        }
        return random::tree::decodePruferCode(prufer_);
    }

    bool AllTreesGenerator::next() {
        if (size_ <= 2) {
            return false;
        }
        int index = size_ - 3;
        while (index >= 0 && prufer_[index] == size_ - 1) {
            index--;
        }
        if (index < 0) {
            return false;
        }

        prufer_[index]++;
        std::fill(prufer_.begin() + index + 1, prufer_.end(), 0);
        buildedGraphs_++;
        return true;
    }

    int AllTreesGenerator::buildedGraphs() const {
        return buildedGraphs_;
    }
} // namespace random::tree
