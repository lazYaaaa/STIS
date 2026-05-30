#include "../include/read_only_stream.hpp"

#include <stdexcept>

namespace lr4 {

template<typename T>
ReadOnlyStream<T>::ReadOnlyStream(std::shared_ptr<Sequence<Event<T>>> seq)
    : seq_(std::move(seq)), pos_(0), opened_(true) {}

template<typename T>
void ReadOnlyStream<T>::Open() {
    opened_ = true;
}

template<typename T>
void ReadOnlyStream<T>::Close() {
    opened_ = false;
}

template<typename T>
bool ReadOnlyStream<T>::IsEndOfStream() const {
    if (!opened_ || !seq_) return true;
    try {
        seq_->Get(pos_);
        return false;
    } catch (...) {
        return true;
    }
}

template<typename T>
Event<T> ReadOnlyStream<T>::Read() {
    if (!opened_) throw std::runtime_error("read-only stream is closed");
    auto e = seq_->Get(pos_);
    ++pos_;
    return e;
}

template<typename T>
size_t ReadOnlyStream<T>::GetPosition() const {
    return pos_;
}

template<typename T>
bool ReadOnlyStream<T>::IsCanSeek() const {
    return true;
}

template<typename T>
bool ReadOnlyStream<T>::IsCanGoBack() const {
    return true;
}

template<typename T>
size_t ReadOnlyStream<T>::Seek(size_t idx) {
    if (!opened_) throw std::runtime_error("read-only stream is closed");
    pos_ = idx;
    return pos_;
}

template class ReadOnlyStream<int>;

} // namespace lr4
