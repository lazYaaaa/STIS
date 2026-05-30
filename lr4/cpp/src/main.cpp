#include <iostream>
#include <string>
#include <vector>
#include "../include/types.hpp"
#include "../include/sequence.hpp"
#include "../include/stream.hpp"
#include "../include/sync.hpp"
#include "../include/cli.hpp"

using namespace lr4;

extern int RunCatchTests(int argc, char* argv[]);

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string arg1(argv[1]);
        if (arg1 == "--run-tests" || arg1 == "test") {
            char* new_argv[1];
            new_argv[0] = argv[0];
            return RunCatchTests(1, new_argv);
        }
    }

    while (true) {
        print_menu();
        int choice = 0;
        if (!(std::cin >> choice)) break;
        std::string rest;
        std::getline(std::cin, rest);

        if (choice == 1) {
            auto a = std::make_shared<VectorSequence<Event<int>>>(std::vector<Event<int>>{{0.0,10},{1.0,20},{2.0,30}});
            auto b = std::make_shared<VectorSequence<Event<int>>>(std::vector<Event<int>>{{0.1,100},{1.5,200}});
            std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{a,b};
            double tau = 0.5;
            auto synced = SynchronizeStreams<int>(streams, tau);
            std::cout << "Synchronization result (tau=" << tau << "):\n";
            for (size_t i=0;i<synced->GetMaterializedCount();++i) {
                auto row = synced->Get(i);
                std::cout << i << ": t_ref=" << row.first << " -> [";
                for (size_t j=0;j<row.second.size();++j) {
                    if (j) std::cout << ", ";
                    if (row.second[j].has_value()) std::cout << row.second[j].value(); else std::cout << "<nil>";
                }
                std::cout << "]\n";
            }

        } else if (choice == 2) {
            std::cout << "Enter the first stream as 't:v' pairs separated by spaces (example: 0.0:10 1.0:20):\n";
            std::string line1; std::getline(std::cin, line1);
            auto events1 = parse_events(line1);
            std::cout << "Enter the second stream similarly:\n";
            std::string line2; std::getline(std::cin, line2);
            auto events2 = parse_events(line2);
            auto a = std::make_shared<VectorSequence<Event<int>>>(events1);
            auto b = std::make_shared<VectorSequence<Event<int>>>(events2);
            std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{a,b};
            std::cout << "Enter tau (window) as a number (e.g. 0.5): ";
            double tau = 0.5; std::cin >> tau; std::getline(std::cin, rest);
            auto synced = SynchronizeStreams<int>(streams, tau);
            std::cout << "Synchronization result:\n";
            for (size_t i=0;i<synced->GetMaterializedCount();++i) {
                auto row = synced->Get(i);
                std::cout << i << ": t_ref=" << row.first << " -> [";
                for (size_t j=0;j<row.second.size();++j) {
                    if (j) std::cout << ", ";
                    if (row.second[j].has_value()) std::cout << row.second[j].value(); else std::cout << "<nil>";
                }
                std::cout << "]\n";
            }

        } else {
            break;
        }
    }

    std::cout << "Exit.\n";
    return 0;
}
