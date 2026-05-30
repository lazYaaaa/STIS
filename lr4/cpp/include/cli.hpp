#pragma once

#include <string>
#include <vector>
#include "types.hpp"

namespace lr4 {

// Печать меню для CLI
void print_menu();

// Парсинг строки вида "t1:v1 t2:v2 ..." в вектор Event<int>
std::vector<Event<int>> parse_events(const std::string &line);

} // namespace lr4
