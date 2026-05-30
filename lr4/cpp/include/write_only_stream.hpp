#pragma once

#include <cstddef>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "stream.hpp"
#include "types.hpp"

namespace lr4 {

template<typename T>
class WriteOnlyStream : public Stream<T> {
public:
    WriteOnlyStream();
    explicit WriteOnlyStream(std::string filePath, std::function<std::string(const Event<T>&)> serializer);
    explicit WriteOnlyStream(const char* filePath, std::function<std::string(const Event<T>&)> serializer);

    void Open() override;
    void Close() override;
    size_t GetPosition() const override;
    size_t Write(const Event<T>& e);
    const std::vector<Event<T>>& Buffer() const;

private:
    std::vector<Event<T>> buf_;
    std::ofstream file_;
    std::string file_path_;
    std::function<std::string(const Event<T>&)> serializer_;
    bool opened_;
    bool file_mode_;
};

extern template class WriteOnlyStream<int>;

} // namespace lr4
