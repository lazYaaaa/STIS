#include "../include/cli.hpp"
#include "../include/demo_helpers.hpp"
#include <iostream>

namespace lr4 {

void print_menu() {
    std::cout << "1) Demo: synchronize example streams\n";
    std::cout << "2) Enter two streams manually and synchronize\n";
    std::cout << "3) File I/O demo\n";
    std::cout << "4) Exit\n";
    std::cout << "Select an option: ";
}

}
