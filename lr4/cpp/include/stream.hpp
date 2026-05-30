#pragma once

#include <cstddef>

namespace lr4 {

template<typename T>
class Stream {
public:
    virtual ~Stream() = default;
    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual size_t GetPosition() const = 0;
};

} // namespace lr4
