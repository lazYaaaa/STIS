#pragma once

#include <string>
#include <vector>
#include "types.hpp"

namespace lr4 {

void print_menu();

std::vector<Event<int>> parse_events(const std::string &line);

}
