#pragma once

#include <cstddef>
#include <vector>
#include "types.hpp"

namespace lr4 {

template<typename T>
class WriteOnlyStream {
public:
    WriteOnlyStream();

    void Open();
    void Close();
    size_t GetPosition() const;
    size_t Write(const Event<T>& e);
    const std::vector<Event<T>>& Buffer() const;

private:
    std::vector<Event<T>> buf_;
    bool opened_;
};

extern template class WriteOnlyStream<int>;

} // namespace lr4
