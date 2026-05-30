#include "../include/cli.hpp"
#include <iostream>
#include <sstream>

namespace lr4 {

void print_menu() {
    std::cout << "1) Demo: synchronize example streams\n";
    std::cout << "2) Enter two streams manually and synchronize\n";
    std::cout << "3) Exit\n";
    std::cout << "Select an option: ";
}

std::vector<Event<int>> parse_events(const std::string &line) {
    std::vector<Event<int>> out;
    std::istringstream iss(line);
    std::string token;
    size_t idx = 0;
    while (iss >> token) {
        auto pos = token.find(':');
        if (pos == std::string::npos) {
            try { int v = std::stoi(token); out.push_back(Event<int>{double(idx), v}); }
            catch (...) { }
        } else {
            try {
                double t = std::stod(token.substr(0,pos)); int v = std::stoi(token.substr(pos+1)); out.push_back(Event<int>{t, v});
            } catch (...) {
            }
        }
        ++idx;
    }
    return out;
}

}
