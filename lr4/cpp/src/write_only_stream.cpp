#include "../include/write_only_stream.hpp"

#include <sstream>
#include <stdexcept>

namespace lr4 {

template<typename T>
WriteOnlyStream<T>::WriteOnlyStream() : opened_(true), file_mode_(false) {}

template<typename T>
WriteOnlyStream<T>::WriteOnlyStream(std::string filePath, std::function<std::string(const Event<T>&)> serializer)
    : file_path_(std::move(filePath)), serializer_(std::move(serializer)), opened_(true), file_mode_(true) {}

template<typename T>
WriteOnlyStream<T>::WriteOnlyStream(const char* filePath, std::function<std::string(const Event<T>&)> serializer)
    : WriteOnlyStream(std::string(filePath), std::move(serializer)) {}

template<typename T>
void WriteOnlyStream<T>::Open() {
    if (file_mode_) {
        file_.clear();
        file_.open(file_path_);
        if (!file_) {
            opened_ = false;
            throw std::runtime_error("cannot open output file");
        }
    }
    opened_ = true;
}

template<typename T>
void WriteOnlyStream<T>::Close() {
    opened_ = false;
    if (file_.is_open()) file_.close();
}

template<typename T>
size_t WriteOnlyStream<T>::GetPosition() const {
    return buf_.size();
}

template<typename T>
size_t WriteOnlyStream<T>::Write(const Event<T>& e) {
    if (!opened_) throw std::runtime_error("write-only stream is closed");
    buf_.push_back(e);
    if (file_mode_) {
        if (!file_.is_open()) throw std::runtime_error("output file is not open");
        if (serializer_) {
            file_ << serializer_(e) << '\n';
        } else {
            file_ << e.t << ' ' << e.value << '\n';
        }
    }
    return buf_.size();
}

template<typename T>
const std::vector<Event<T>>& WriteOnlyStream<T>::Buffer() const {
    return buf_;
}

template class WriteOnlyStream<int>;
template class WriteOnlyStream<std::string>;

} // namespace lr4
