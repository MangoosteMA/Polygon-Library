#pragma once

#include "../global/global.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

/*
 * Simple utils for randomizing things.
 * random_t must have .next(n) method defined for every integral type
   which returns random number on the interval [0, n).
   Example: random_t from https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h
 * In case any error std::runtime_error will be throwed.
 */

namespace random {
    // Random number on the interval [minValue, maxValue)
    template<typename T, typename random_t>
    T random(const T &minValue, const T&maxValue, random_t &rng);

    // Shuffles the range
    template<typename iterator_t, typename random_t>
    void shuffle(iterator_t beg, iterator_t end, random_t &rng);

    // Generates n distinct random integers from [minValue, maxValue)
    // Returned integers are not sorted
    template<typename T, typename random_t>
    std::vector<T> distinctRandomIntegers(const T &minValue, const T &maxValue, int n, random_t &rng);

    // Generates random vector of size 'tests' with values >= 'minSize' and the sum equal to 'totalSize'
    template<typename T, typename random_t>
    std::vector<T> distributeSize(T totalSize, const T &minSize, int tests, random_t &rng);

    // Generates random vector of size 'size' of elements from [minValue, maxValue)
    template<typename T, typename random_t>
    std::vector<T> array(int size, const T &minValue, const T &maxValue, random_t &rng);

    // Generates random vector of size 'size' of elements from [minValue, maxValue)
    // Contains all elements from [minValue, maxValue)
    template<typename T, typename random_t>
    std::vector<T> distributeToGroups(int size, const T &minValue, const T &maxValue, random_t &rng);
} // namespace random
