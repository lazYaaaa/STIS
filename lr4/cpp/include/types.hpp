#pragma once

#include <optional>

namespace lr4 {

template<typename T>
struct Event {
    double t; // временная метка
    T value;  
};

} 
