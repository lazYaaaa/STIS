#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>
#include "sequence.hpp"

namespace lr4 {

template<typename T>
class VectorSequence : public Sequence<T> {
public:
    VectorSequence(std::vector<T> data) : data_(std::move(data)) {}

    T Get(size_t index) const override {
        if (index >= data_.size()) throw std::out_of_range("index out of range");
        return data_[index];
    }

    size_t GetSize() const override { return data_.size(); }

    std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end > data_.size()) throw std::out_of_range("invalid subsequence");
        return std::make_shared<VectorSequence<T>>(std::vector<T>(data_.begin() + start, data_.begin() + end));
    }

private:
    std::vector<T> data_;
};

}
