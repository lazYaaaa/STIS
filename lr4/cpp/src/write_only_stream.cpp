#include "../include/write_only_stream.hpp"

#include <stdexcept>

namespace lr4 {

template<typename T>
WriteOnlyStream<T>::WriteOnlyStream() : opened_(true) {}

template<typename T>
void WriteOnlyStream<T>::Open() {
    opened_ = true;
}

template<typename T>
void WriteOnlyStream<T>::Close() {
    opened_ = false;
}

template<typename T>
size_t WriteOnlyStream<T>::GetPosition() const {
    return buf_.size();
}

template<typename T>
size_t WriteOnlyStream<T>::Write(const Event<T>& e) {
    if (!opened_) throw std::runtime_error("write-only stream is closed");
    buf_.push_back(e);
    return buf_.size();
}

template<typename T>
const std::vector<Event<T>>& WriteOnlyStream<T>::Buffer() const {
    return buf_;
}

template class WriteOnlyStream<int>;

} // namespace lr4
