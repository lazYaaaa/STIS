#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace lr4 {

// Базовый абстрактный класс для последовательностей (Sequence)
// Может быть реализован как материализованная последовательность или ленивый источник
template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    // Получить элемент по индексу (может материализовать при необходимости)
    virtual T Get(size_t index) const = 0;
    // Число материализованных элементов (если известно)
    virtual size_t GetMaterializedCount() const { return 0; }
    // Вернуть материализованную подпоследовательность [start, end)
    virtual std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const = 0;
};

// Простая реализация полностью материализованной последовательности
template<typename T>
class MaterializedSequence : public Sequence<T> {
public:
    MaterializedSequence(std::vector<T> data) : data_(std::move(data)) {}
    T Get(size_t index) const override {
        if (index >= data_.size()) throw std::out_of_range("index out of range");
        return data_[index];
    }
    size_t GetMaterializedCount() const override { return data_.size(); }
    std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const override {
        if (start > end || end > data_.size()) throw std::out_of_range("invalid subsequence");
        return std::make_shared<MaterializedSequence<T>>(std::vector<T>(data_.begin()+start, data_.begin()+end));
    }
private:
    std::vector<T> data_;
};

} // namespace lr4
