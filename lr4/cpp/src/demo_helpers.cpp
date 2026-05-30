#include "../include/demo_helpers.hpp"

#include <iostream>
#include <sstream>

namespace lr4 {

std::vector<Event<int>> parse_events(const std::string& line) {
    std::vector<Event<int>> out;
    std::istringstream iss(line);
    std::string token;
    size_t idx = 0;
    while (iss >> token) {
        auto pos = token.find(':');
        if (pos == std::string::npos) {
            try {
                int value = std::stoi(token);
                out.push_back(Event<int>{double(idx), value});
            } catch (...) {
            }
        } else {
            try {
                double t = std::stod(token.substr(0, pos));
                int value = std::stoi(token.substr(pos + 1));
                out.push_back(Event<int>{t, value});
            } catch (...) {
            }
        }
        ++idx;
    }
    return out;
}

void print_events(const std::string& label, const std::vector<Event<int>>& events) {
    std::cout << label << "\n";
    for (size_t i = 0; i < events.size(); ++i) {
        std::cout << "  " << i << ": t=" << events[i].t << ", value=" << events[i].value << "\n";
    }
}

void print_synced_result(const std::shared_ptr<Sequence<std::pair<double, std::vector<std::optional<int>>>>>& synced) {
    for (size_t i = 0; i < synced->GetSize(); ++i) {
        auto row = synced->Get(i);
        std::cout << i << ": t_ref=" << row.first << " -> [";
        for (size_t j = 0; j < row.second.size(); ++j) {
            if (j) std::cout << ", ";
            if (row.second[j].has_value()) std::cout << row.second[j].value();
            else std::cout << "<nil>";
        }
        std::cout << "]\n";
    }
}

}
