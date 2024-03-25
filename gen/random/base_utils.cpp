#include "base_utils.h"

namespace random {
    template<typename T, typename random_t>
    T random(const T &minValue, const T&maxValue, random_t &rng) {
        global::assertf(minValue < maxValue, "Can not create random number on the interval ["
                                        + std::to_string(minValue) + ", " + std::to_string(maxValue) + ")");
        return minValue + rng.next(maxValue - minValue);
    }

    template<typename iterator_t, typename random_t>
    void shuffle(iterator_t beg, iterator_t end, random_t &rng) {
        for (int i = 0; beg + i != end; i++) {
            int j = random(0, i + 1, rng);
            if (j != i) {
                std::swap(*(beg + i), *(beg + j));
            }
        }
    }

    template<typename T, typename random_t>
    std::vector<T> distinctRandomIntegers(const T &minValue, const T &maxValue, int n, random_t &rng) {
        global::assertf(maxValue - minValue >= n, "[generateNDistinctRandomIntegers] maxValue - minValue >= n must holds.");
        std::vector<T> result(n);
        if (maxValue - minValue <= 2 * n) {
            std::vector<T> elements(maxValue - minValue);
            std::iota(elements.begin(), elements.end(), minValue);
            random::shuffle(elements.begin(), elements.end(), rng);
            for (int i = 0; i < n; i++) {
                result[i] = elements[i];
            }
        } else {
            std::set<T> got;
            for (auto &value : result) {
                do {
                    value = random(minValue, maxValue, rng);
                } while (!got.insert(value).second);
            }
        }
        return result;
    }

    template<typename T, typename random_t>
    std::vector<T> distributeSize(T totalSize, const T &minSize, int tests, random_t &rng) {
        global::assertf(tests >= 1, "[distributeSize] 'tests' must be at least one.");
        global::assertf(1ll * minSize * tests <= totalSize, "[distributeSize] totalSize is less than minSize * tests.");

        totalSize -= minSize * tests;
        auto borders = generateNDistinctRandomIntegers(0, totalSize + tests - 1, tests - 1, rng);
        std::sort(borders.begin(), borders.end());

        std::vector<T> result(tests);
        int lastBorder = -1;
        for (int i = 0; i + 1 < tests; i++) {
            result[i] = borders[i] - lastBorder - 1 + minSize;
            lastBorder = borders[i];
        }
        result.back() = totalSize + minSize * tests - std::accumulate(result.begin(), result.end(), T(0));
        return result;
    }

    template<typename T, typename random_t>
    std::vector<T> array(int size, const T &minValue, const T &maxValue, random_t &rng) {
        std::vector<T> result(size);
        for (auto &value : result) {
            value = random::random(minValue, maxValue, rng);
        }
        return result;
    }

    template<typename T, typename random_t>
    std::vector<T> distributeToGroups(int size, const T &minValue, const T &maxValue, random_t &rng) {
        global::assertf(maxValue - minValue <= size, "[generateRandomGroups] maxValue - minValue <= size must holds");
        auto result = generateRandomVector(size, minValue, maxValue, rng);
        auto leaders = generateNDistinctRandomIntegers(0, size, maxValue - minValue, rng);
        for (int i = 0; i < int(leaders.size()); i++) {
            result[leaders[i]] = minValue + i;
        }
        return result;
    }
} // namespace random
