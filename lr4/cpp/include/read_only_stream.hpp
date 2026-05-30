#pragma once

#include <cstddef>
#include <functional>
#include <fstream>
#include <memory>
#include <string>
#include "sequence.hpp"
#include "stream.hpp"
#include "types.hpp"

namespace lr4 {

template<typename T>
class ReadOnlyStream : public Stream<T> {
public:
    explicit ReadOnlyStream(std::shared_ptr<Sequence<Event<T>>> seq);
    explicit ReadOnlyStream(std::string filePath, std::function<Event<T>(const std::string&)> parser);
    explicit ReadOnlyStream(const char* filePath, std::function<Event<T>(const std::string&)> parser);

    void Open() override;
    void Close() override;
    size_t GetPosition() const override;
    bool IsEndOfStream() const;
    Event<T> Read();
    size_t Seek(size_t idx);

private:
    std::shared_ptr<Sequence<Event<T>>> seq_;
    mutable std::ifstream file_;
    std::string file_path_;
    std::function<Event<T>(const std::string&)> parser_;
    size_t pos_;
    bool opened_;
    bool file_mode_;
};

extern template class ReadOnlyStream<int>;

}
