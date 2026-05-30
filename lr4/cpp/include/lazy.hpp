#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "sequence.hpp"
#include "vector_sequence.hpp"

namespace lr4 {

template<typename T>
class LazySequence : public Sequence<T> {
 public:
    using Generator = std::function<T(size_t)>;

    LazySequence() = delete;
    LazySequence(Generator gen, std::vector<T> prefix = {}) : gen_(std::move(gen)), materialized_(std::move(prefix)) {}

    T Get(size_t index) const override {
        if (index < materialized_.size()) return materialized_[index];
        for (size_t i = materialized_.size(); i <= index; ++i) {
            materialized_.push_back(gen_(i));
        }
        return materialized_[index];
    }

    size_t GetMaterializedCount() const override { return materialized_.size(); }

    std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const override {
        if (end < start) throw std::out_of_range("invalid subsequence");
        std::vector<T> v;
        for (size_t i = start; i < end; ++i) v.push_back(Get(i));
        return std::make_shared<VectorSequence<T>>(std::move(v));
    }

    // Map: получить ленивую последовательность, полученную применением функции f к каждому элементу
    template<typename U>
    LazySequence<U> Map(std::function<U(T)> f) const {
        auto gen = [s = std::make_shared<LazySequence<T>>(*this), f](size_t i) mutable {
            return f(s->Get(i));
        };
        return LazySequence<U>(gen);
    }

    // Zip: объединить по индексам с другой последовательностью в пары
    template<typename U>
    LazySequence<std::pair<T,U>> Zip(std::shared_ptr<Sequence<U>> other) const {
        auto s = std::make_shared<LazySequence<T>>(*this);
        auto gen = [s, other](size_t i) {
            return std::make_pair(s->Get(i), other->Get(i));
        };
        return LazySequence<std::pair<T,U>>(gen);
    }

    // Append: конкатенация — возвращает последовательность, объединяющую текущую и другую
    std::shared_ptr<Sequence<T>> Append(std::shared_ptr<Sequence<T>> other) const {
        struct ConcatSeq : public Sequence<T> {
            ConcatSeq(std::shared_ptr<Sequence<T>> a, std::shared_ptr<Sequence<T>> b) : a(a), b(b), left_len(SIZE_MAX) {}
            T Get(size_t index) const override {
                if (left_len == SIZE_MAX) {
                    try {
                        return a->Get(index);
                    } catch (const std::out_of_range&) {
                        left_len = index;
                        return b->Get(index - left_len);
                    }
                } else {
                    if (index < left_len) return a->Get(index);
                    return b->Get(index - left_len);
                }
            }
            size_t GetMaterializedCount() const override { return 0; }
            std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const override {
                 std::vector<T> v;
                 for (size_t i = start; i < end; ++i) v.push_back(Get(i));
                 return std::make_shared<VectorSequence<T>>(std::move(v));
            }
            std::shared_ptr<Sequence<T>> a, b;
            mutable size_t left_len;
        };
        return std::make_shared<ConcatSeq>(std::make_shared<LazySequence<T>>(*this), other);
    }

private:
    Generator gen_;
    mutable std::vector<T> materialized_;
};

}
