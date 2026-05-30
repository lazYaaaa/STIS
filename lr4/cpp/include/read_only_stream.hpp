#pragma once

#include <cstddef>
#include <memory>
#include "sequence.hpp"
#include "types.hpp"

namespace lr4 {

template<typename T>
class ReadOnlyStream {
public:
    explicit ReadOnlyStream(std::shared_ptr<Sequence<Event<T>>> seq);

    void Open();
    void Close();
    bool IsEndOfStream() const;
    Event<T> Read();
    size_t GetPosition() const;
    bool IsCanSeek() const;
    bool IsCanGoBack() const;
    size_t Seek(size_t idx);

private:
    std::shared_ptr<Sequence<Event<T>>> seq_;
    size_t pos_;
    bool opened_;
};

extern template class ReadOnlyStream<int>;

} // namespace lr4
