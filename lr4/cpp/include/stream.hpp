// Простейшие реализации потоков: ReadOnlyStream и WriteOnlyStream
#pragma once

#include <memory>
#include <vector>
#include <optional>
#include "sequence.hpp"
#include "types.hpp"

namespace lr4 {

// Поток только для чтения, обёртка вокруг Sequence<Event<T>>
template<typename T>
class ReadOnlyStream {
public:
    explicit ReadOnlyStream(std::shared_ptr<Sequence<Event<T>>> seq) : seq_(seq), pos_(0) {}
    void Open() {}
    void Close() {}
    bool IsEndOfStream() const {
        try { seq_->Get(pos_); return false; } catch (...) { return true; }
    }
    Event<T> Read() {
        auto e = seq_->Get(pos_);
        ++pos_;
        return e;
    }
    size_t GetPosition() const { return pos_; }
    bool IsCanSeek() const { return true; }
    void Seek(size_t idx) { pos_ = idx; }
private:
    std::shared_ptr<Sequence<Event<T>>> seq_;
    size_t pos_;
};

// Поток только для записи: буферизует поступающие Event<T>
template<typename T>
class WriteOnlyStream {
public:
    WriteOnlyStream() = default;
    size_t Write(const Event<T>& e) { buf_.push_back(e); return buf_.size()-1; }
    void Open() {}
    void Close() {}
    const std::vector<Event<T>>& Buffer() const { return buf_; }
private:
    std::vector<Event<T>> buf_;
};

} // namespace lr4
