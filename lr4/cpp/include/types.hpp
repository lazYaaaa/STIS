#pragma once

#include <optional>

namespace lr4 {

// Событие с временной меткой и значением
template<typename T>
struct Event {
    double t; // временная метка
    T value;  // полезная нагрузка
};

} // namespace lr4
