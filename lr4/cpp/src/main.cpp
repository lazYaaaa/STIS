#include <iostream>
#include <filesystem>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/types.hpp"
#include "../include/sequence.hpp"
#include "../include/vector_sequence.hpp"
#include "../include/read_only_stream.hpp"
#include "../include/write_only_stream.hpp"
#include "../include/sync.hpp"
#include "../include/cli.hpp"
#include "../include/demo_helpers.hpp"

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
            print_events("Stream A before synchronization:", std::vector<Event<int>>{{0.0,10},{1.0,20},{2.0,30}});
            print_events("Stream B before synchronization:", std::vector<Event<int>>{{0.1,100},{1.5,200}});
            auto synced = SynchronizeStreams<int>(streams, tau);
            std::cout << "Synchronization result (tau=" << tau << "):\n";
            print_synced_result(synced);

        } else if (choice == 2) {
            std::cout << "Enter the first stream as 't:v' pairs separated by spaces (value must be int, example: 0.0:10 1.0:20):\n";
            std::string line1; std::getline(std::cin, line1);
            auto events1 = parse_events(line1);
            std::cout << "Enter the second stream similarly (integers only):\n";
            std::string line2; std::getline(std::cin, line2);
            auto events2 = parse_events(line2);
            if (events1.empty() || events2.empty()) {
                std::cout << "No valid integer events were parsed. Use input like 0.0:10 1.0:20.\n";
                continue;
            }
            auto a = std::make_shared<VectorSequence<Event<int>>>(events1);
            auto b = std::make_shared<VectorSequence<Event<int>>>(events2);
            std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{a,b};
            std::cout << "Enter tau (window) as a number (e.g. 0.5): ";
            double tau = 0.5; std::cin >> tau; std::getline(std::cin, rest);
            print_events("Stream A before synchronization:", events1);
            print_events("Stream B before synchronization:", events2);
            auto synced = SynchronizeStreams<int>(streams, tau);
            std::cout << "Synchronization result:\n";
            print_synced_result(synced);

        } else if (choice == 3) {
            auto temp_path = std::filesystem::current_path() / "lr4_stream_demo.csv";
            WriteOnlyStream<int> writer(temp_path.string().c_str(), [](const Event<int>& e) {
                return std::to_string(e.t) + "," + std::to_string(e.value);
            });
            writer.Open();
            writer.Write({0.0, 10});
            writer.Write({1.0, 20});
            writer.Close();

            ReadOnlyStream<int> reader(temp_path.string().c_str(), [](const std::string& line) {
                std::istringstream iss(line);
                std::string t_text;
                std::string value_text;
                if (!std::getline(iss, t_text, ',')) throw std::runtime_error("invalid csv row");
                if (!std::getline(iss, value_text, ',')) throw std::runtime_error("invalid csv row");
                double t{};
                int v{};
                t = std::stod(t_text);
                v = std::stoi(value_text);
                return Event<int>{t, v};
            });
            reader.Open();
            std::cout << "File demo saved to " << temp_path.string() << ":\n";
            while (!reader.IsEndOfStream()) {
                auto e = reader.Read();
                std::cout << e.t << " -> " << e.value << "\n";
            }
            reader.Close();

        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Unknown option\n";
        }
    }

    std::cout << "Exit.\n";
    return 0;
}
