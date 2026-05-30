#include "../include/read_only_stream.hpp"

#include <sstream>
#include <stdexcept>

namespace lr4 {

template<typename T>
ReadOnlyStream<T>::ReadOnlyStream(std::shared_ptr<Sequence<Event<T>>> seq)
    : seq_(std::move(seq)), pos_(0), opened_(true), file_mode_(false) {}

template<typename T>
ReadOnlyStream<T>::ReadOnlyStream(std::string filePath, std::function<Event<T>(const std::string&)> parser)
    : file_path_(std::move(filePath)), parser_(std::move(parser)), pos_(0), opened_(true), file_mode_(true) {}

template<typename T>
ReadOnlyStream<T>::ReadOnlyStream(const char* filePath, std::function<Event<T>(const std::string&)> parser)
    : ReadOnlyStream(std::string(filePath), std::move(parser)) {}

template<typename T>
void ReadOnlyStream<T>::Open() {
    pos_ = 0;
    if (file_mode_) {
        file_.clear();
        file_.open(file_path_);
        if (!file_) {
            opened_ = false;
            throw std::runtime_error("cannot open input file");
        }
    }
    opened_ = true;
}

template<typename T>
void ReadOnlyStream<T>::Close() {
    opened_ = false;
    if (file_.is_open()) file_.close();
}

template<typename T>
bool ReadOnlyStream<T>::IsEndOfStream() const {
    if (!opened_) return true;
    if (file_mode_) return !file_.is_open() || file_.peek() == std::char_traits<char>::eof();
    if (!seq_) return true;
    return pos_ >= seq_->GetSize();
}

template<typename T>
Event<T> ReadOnlyStream<T>::Read() {
    if (!opened_) throw std::runtime_error("read-only stream is closed");
    if (file_mode_) {
        std::string line;
        if (!std::getline(file_, line)) throw std::runtime_error("end of file");
        ++pos_;
        if (parser_) return parser_(line);
        std::istringstream iss(line);
        double t{};
        T value{};
        iss >> t >> value;
        return Event<T>{t, value};
    }
    auto e = seq_->Get(pos_);
    ++pos_;
    return e;
}

template<typename T>
size_t ReadOnlyStream<T>::GetPosition() const {
    return pos_;
}

template<typename T>
size_t ReadOnlyStream<T>::Seek(size_t idx) {
    if (!opened_) throw std::runtime_error("read-only stream is closed");
    if (file_mode_) throw std::runtime_error("seek is not supported for file stream");
    pos_ = idx;
    return pos_;
}

template class ReadOnlyStream<int>;

} // namespace lr4
