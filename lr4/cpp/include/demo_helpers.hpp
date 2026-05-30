#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "sequence.hpp"
#include "types.hpp"

namespace lr4 {

std::vector<Event<int>> parse_events(const std::string& line);
void print_events(const std::string& label, const std::vector<Event<int>>& events);
void print_synced_result(const std::shared_ptr<Sequence<std::pair<double, std::vector<std::optional<int>>>>>& synced);

}
