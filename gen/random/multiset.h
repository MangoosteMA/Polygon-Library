#pragma once

#include "../global/global.h"
#include "random.h"

#include <vector>

namespace random {
    /*
     * Insert an element.
     * Get a random element.
     * Extract a random element.
     */
    template<typename T>
    class Multiset {
    public:
        Multiset();
        void insert(const T &value);

        template<typename random_t>
        T get(random_t &rnd);

        template<typename random_t>
        T extract(random_t &rnd);

    private:
        template<typename random_t>
        size_t randomIndex(random_t &rnd);

        std::vector<T> data_;
    };
} // namespace random

namespace random {
    template<typename T>
    Multiset<T>::Multiset() {}

    template<typename T>
    void Multiset<T>::insert(const T &value) {
        data_.push_back(value);
    }

    template<typename T>
    template<typename random_t>
    T Multiset<T>::get(random_t &rnd) {
        return data_[randomIndex(rnd)];
    }

    template<typename T>
    template<typename random_t>
    T Multiset<T>::extract(random_t &rnd) {
        std::swap(data_[randomIndex(rnd)], data_.back());
        auto value = data_.back();
        data_.pop_back();
        return value;
    }

    template<typename T>
    template<typename random_t>
    size_t Multiset<T>::randomIndex(random_t &rnd) {
        global::assertf(!data_.empty(), "[Multiset] trying to get a random element from an empty set");
        return random<size_t>(0, data_.size(), rnd);
    }
} // namespace random
