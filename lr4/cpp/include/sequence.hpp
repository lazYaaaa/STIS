#pragma once

#include <cstddef>
#include <memory>

namespace lr4 {

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T Get(size_t index) const = 0;
    virtual size_t GetSize() const { return 0; }
    virtual std::shared_ptr<Sequence<T>> GetSubsequence(size_t start, size_t end) const = 0;
};

} 
